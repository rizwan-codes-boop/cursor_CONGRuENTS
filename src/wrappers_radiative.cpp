/**
 * Implementation of radiative process function wrappers
 */

#include "wrappers_radiative.h"

double eps_IC_3_wrapper(
    double E_gam__GeV,
    py::array_t<double> E_gam_table,
    py::array_t<double> E_e_table,
    py::array_t<double> IC_table_2D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
) {
    // Convert numpy arrays
    auto E_gam_buf = E_gam_table.request();
    auto E_e_buf = E_e_table.request();
    auto IC_buf = IC_table_2D.request();
    auto E_e_spec_buf = E_e_spectrum.request();
    auto qe_spec_buf = qe_spectrum.request();
    
    if (E_e_spec_buf.size != qe_spec_buf.size) {
        throw std::runtime_error("E_e_spectrum and qe_spectrum must have same size");
    }
    
    // Create 1D spline for electron spectrum
    double* E_e_ptr = static_cast<double*>(E_e_spec_buf.ptr);
    double* qe_ptr = static_cast<double*>(qe_spec_buf.ptr);
    gsl_spline_object_1D qe_so = gsl_so1D(E_e_spec_buf.size, E_e_ptr, qe_ptr);
    
    // Create 2D spline for IC table
    // Note: This is simplified - actual implementation may need more complex handling
    double* E_gam_tbl = static_cast<double*>(E_gam_buf.ptr);
    double* E_e_tbl = static_cast<double*>(E_e_buf.ptr);
    double* IC_tbl = static_cast<double*>(IC_buf.ptr);
    
    // For now, we'll need to create the 2D spline properly
    // This is a placeholder - actual implementation depends on your data structure
    gsl_spline_object_2D gso2D_IC;
    // TODO: Initialize gso2D_IC from arrays
    
    // Call original function
    double result = eps_IC_3(E_gam__GeV, gso2D_IC, qe_so);
    
    // Clean up
    gsl_so1D_free(qe_so);
    // gsl_so2D_free(gso2D_IC);
    
    return result;
}

double eps_SY_4_wrapper(
    double E_gam__GeV,
    double B__G,
    py::array_t<double> sync_freq_table,
    py::array_t<double> sync_table_1D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
) {
    // Convert numpy arrays
    auto sync_freq_buf = sync_freq_table.request();
    auto sync_tbl_buf = sync_table_1D.request();
    auto E_e_spec_buf = E_e_spectrum.request();
    auto qe_spec_buf = qe_spectrum.request();
    
    if (E_e_spec_buf.size != qe_spec_buf.size) {
        throw std::runtime_error("E_e_spectrum and qe_spectrum must have same size");
    }
    
    // Create splines
    double* sync_freq_ptr = static_cast<double*>(sync_freq_buf.ptr);
    double* sync_tbl_ptr = static_cast<double*>(sync_tbl_buf.ptr);
    gsl_spline_object_1D sync_so = gsl_so1D(sync_freq_buf.size, sync_freq_ptr, sync_tbl_ptr);
    
    double* E_e_ptr = static_cast<double*>(E_e_spec_buf.ptr);
    double* qe_ptr = static_cast<double*>(qe_spec_buf.ptr);
    gsl_spline_object_1D qe_so = gsl_so1D(E_e_spec_buf.size, E_e_ptr, qe_ptr);
    
    // Call original function
    double result = eps_SY_4(E_gam__GeV, B__G, sync_so, qe_so);
    
    // Clean up
    gsl_so1D_free(sync_so);
    gsl_so1D_free(qe_so);
    
    return result;
}

double eps_BS_3_wrapper(
    double E_gam__GeV,
    double n_H__cmm3,
    py::array_t<double> E_gam_table,
    py::array_t<double> E_e_table,
    py::array_t<double> BS_table_2D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
) {
    // Similar pattern to IC wrapper
    auto E_e_spec_buf = E_e_spectrum.request();
    auto qe_spec_buf = qe_spectrum.request();
    
    if (E_e_spec_buf.size != qe_spec_buf.size) {
        throw std::runtime_error("E_e_spectrum and qe_spectrum must have same size");
    }
    
    // Create splines
    double* E_e_ptr = static_cast<double*>(E_e_spec_buf.ptr);
    double* qe_ptr = static_cast<double*>(qe_spec_buf.ptr);
    gsl_spline_object_1D qe_so = gsl_so1D(E_e_spec_buf.size, E_e_ptr, qe_ptr);
    
    // Create 2D spline for BS table
    // TODO: Proper initialization
    gsl_spline_object_2D gso2D_BS;
    
    // Call original function
    double result = eps_BS_3(E_gam__GeV, n_H__cmm3, gso2D_BS, qe_so);
    
    // Clean up
    gsl_so1D_free(qe_so);
    
    return result;
}

double eps_FF_wrapper(double E_gam__GeV, double Re__kpc, double T_e__K, double tau_ff) {
    return eps_FF(E_gam__GeV, Re__kpc, T_e__K, tau_ff);
}

void bind_radiative_functions(py::module &m) {
    m.def("eps_IC_3", &eps_IC_3_wrapper,
          "Inverse Compton gamma-ray spectrum",
          py::arg("E_gam__GeV"),
          py::arg("E_gam_table"),
          py::arg("E_e_table"),
          py::arg("IC_table_2D"),
          py::arg("E_e_spectrum"),
          py::arg("qe_spectrum"));
    
    m.def("eps_SY_4", &eps_SY_4_wrapper,
          "Synchrotron gamma-ray spectrum",
          py::arg("E_gam__GeV"),
          py::arg("B__G"),
          py::arg("sync_freq_table"),
          py::arg("sync_table_1D"),
          py::arg("E_e_spectrum"),
          py::arg("qe_spectrum"));
    
    m.def("eps_BS_3", &eps_BS_3_wrapper,
          "Bremsstrahlung gamma-ray spectrum",
          py::arg("E_gam__GeV"),
          py::arg("n_H__cmm3"),
          py::arg("E_gam_table"),
          py::arg("E_e_table"),
          py::arg("BS_table_2D"),
          py::arg("E_e_spectrum"),
          py::arg("qe_spectrum"));
    
    m.def("eps_FF", &eps_FF_wrapper,
          "Free-free spectrum",
          py::arg("E_gam__GeV"),
          py::arg("Re__kpc"),
          py::arg("T_e__K"),
          py::arg("tau_ff"));
}
