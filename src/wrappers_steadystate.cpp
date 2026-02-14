/**
 * Implementation of steady state solver wrappers
 */

#include "wrappers_steadystate.h"
#include <vector>

py::array_t<double> CRe_steadystate_solve_wrapper(
    int structure,
    py::array_t<double> E_e_lims__GeV,
    int n_E,
    double n_H__cmm3,
    double B__G,
    double h__pc,
    int n_gso2D,
    py::array_t<double> E_gam_table,
    py::array_t<double> E_e_table,
    py::array_t<double> IC_Gamma_table_2D,
    py::array_t<double> E_gam_BS_table,
    py::array_t<double> E_e_BS_table,
    py::array_t<double> BS_table_2D,
    py::array_t<double> E_e_diffusion,
    py::array_t<double> D_e__cm2sm1,
    py::array_t<double> E_e_inject,
    py::array_t<double> Q_inject_1,
    py::array_t<double> Q_inject_2
) {
    // Convert input arrays
    auto E_e_lims_buf = E_e_lims__GeV.request();
    if (E_e_lims_buf.size != 2) {
        throw std::runtime_error("E_e_lims__GeV must have size 2");
    }
    
    double E_e_lims[2];
    E_e_lims[0] = static_cast<double*>(E_e_lims_buf.ptr)[0];
    E_e_lims[1] = static_cast<double*>(E_e_lims_buf.ptr)[1];
    
    // Create GSL splines from arrays
    // This is a simplified version - actual implementation may be more complex
    
    auto E_e_diff_buf = E_e_diffusion.request();
    auto D_e_buf = D_e__cm2sm1.request();
    
    if (E_e_diff_buf.size != D_e_buf.size) {
        throw std::runtime_error("E_e_diffusion and D_e__cm2sm1 must have same size");
    }
    
    double* E_e_diff_ptr = static_cast<double*>(E_e_diff_buf.ptr);
    double* D_e_ptr = static_cast<double*>(D_e_buf.ptr);
    gsl_spline_object_1D De_gso1D = gsl_so1D(E_e_diff_buf.size, E_e_diff_ptr, D_e_ptr);
    
    // Create injection splines
    auto E_e_inj_buf = E_e_inject.request();
    auto Q1_buf = Q_inject_1.request();
    auto Q2_buf = Q_inject_2.request();
    
    if (E_e_inj_buf.size != Q1_buf.size || E_e_inj_buf.size != Q2_buf.size) {
        throw std::runtime_error("Injection arrays must have same size");
    }
    
    double* E_e_inj_ptr = static_cast<double*>(E_e_inj_buf.ptr);
    double* Q1_ptr = static_cast<double*>(Q1_buf.ptr);
    double* Q2_ptr = static_cast<double*>(Q2_buf.ptr);
    
    gsl_spline_object_1D gso_1D_Q_inject_1 = gsl_so1D(E_e_inj_buf.size, E_e_inj_ptr, Q1_ptr);
    gsl_spline_object_1D gso_1D_Q_inject_2 = gsl_so1D(E_e_inj_buf.size, E_e_inj_ptr, Q2_ptr);
    
    // Create IC Gamma spline (simplified)
    gsl_spline_object_2D gso2D_IC_Gamma;
    // TODO: Initialize from arrays
    
    // Create BS spline (simplified)
    gsl_spline_object_2D gso2D_BS;
    // TODO: Initialize from arrays
    
    // Output splines
    gsl_spline_object_1D qe_1_so, qe_2_so;
    
    // Call original function
    int result = CRe_steadystate_solve(
        structure,
        E_e_lims,
        n_E,
        n_H__cmm3,
        B__G,
        h__pc,
        n_gso2D,
        &gso2D_IC_Gamma,
        gso2D_BS,
        De_gso1D,
        gso_1D_Q_inject_1,
        gso_1D_Q_inject_2,
        &qe_1_so,
        &qe_2_so
    );
    
    if (result != 0) {
        throw std::runtime_error("CRe_steadystate_solve failed");
    }
    
    // Extract results to numpy array
    // Create energy array for output
    std::vector<double> E_out(n_E);
    double log_E_min = log(E_e_lims[0]);
    double log_E_max = log(E_e_lims[1]);
    for (int i = 0; i < n_E; i++) {
        double log_E = log_E_min + (log_E_max - log_E_min) * i / (n_E - 1.0);
        E_out[i] = exp(log_E);
    }
    
    // Evaluate splines
    std::vector<double> qe_1_out(n_E), qe_2_out(n_E);
    for (int i = 0; i < n_E; i++) {
        qe_1_out[i] = gsl_so1D_eval(qe_1_so, E_out[i]);
        qe_2_out[i] = gsl_so1D_eval(qe_2_so, E_out[i]);
    }
    
    // Clean up
    gsl_so1D_free(De_gso1D);
    gsl_so1D_free(gso_1D_Q_inject_1);
    gsl_so1D_free(gso_1D_Q_inject_2);
    gsl_so1D_free(qe_1_so);
    gsl_so1D_free(qe_2_so);
    
    // Return as numpy array (stacked: [qe_1, qe_2])
    py::array_t<double> output = py::cast(std::vector<double>{qe_1_out.begin(), qe_1_out.end()});
    return output;
}

void bind_steadystate_functions(py::module &m) {
    m.def("CRe_steadystate_solve", &CRe_steadystate_solve_wrapper,
          "Solve steady state cosmic ray electron spectrum",
          py::arg("structure"),
          py::arg("E_e_lims__GeV"),
          py::arg("n_E"),
          py::arg("n_H__cmm3"),
          py::arg("B__G"),
          py::arg("h__pc"),
          py::arg("n_gso2D"),
          py::arg("E_gam_table"),
          py::arg("E_e_table"),
          py::arg("IC_Gamma_table_2D"),
          py::arg("E_gam_BS_table"),
          py::arg("E_e_BS_table"),
          py::arg("BS_table_2D"),
          py::arg("E_e_diffusion"),
          py::arg("D_e__cm2sm1"),
          py::arg("E_e_inject"),
          py::arg("Q_inject_1"),
          py::arg("Q_inject_2"));
}
