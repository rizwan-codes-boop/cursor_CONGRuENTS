/**
 * Implementation of spectra function wrappers
 */

#include "wrappers_spectra.h"

double eps_pi_wrapper(
    double E_gam__GeV,
    double n_H__cmm3,
    double C_p,
    double T_p_cutoff__GeV,
    py::array_t<double> T_CR__GeV,
    py::array_t<double> f_cal
) {
    // Convert numpy arrays to C arrays
    auto T_CR_buf = T_CR__GeV.request();
    auto f_cal_buf = f_cal.request();
    
    if (T_CR_buf.size != f_cal_buf.size) {
        throw std::runtime_error("T_CR and f_cal arrays must have same size");
    }
    
    // Create GSL spline from arrays
    double* T_CR_ptr = static_cast<double*>(T_CR_buf.ptr);
    double* f_cal_ptr = static_cast<double*>(f_cal_buf.ptr);
    
    gsl_spline_object_1D gso1D_fcal = gsl_so1D(
        T_CR_buf.size,
        T_CR_ptr,
        f_cal_ptr
    );
    
    // Call original function
    double result = eps_pi(E_gam__GeV, n_H__cmm3, C_p, T_p_cutoff__GeV, gso1D_fcal);
    
    // Clean up
    gsl_so1D_free(gso1D_fcal);
    
    return result;
}

double J_wrapper(double T, double C, double q, double m, double T_cutoff) {
    return J(T, C, q, m, T_cutoff);
}

double C_norm_E_wrapper(double q, double m, double T_cutoff) {
    return C_norm_E(q, m, T_cutoff);
}

double q_e_wrapper(
    double T_CR__GeV,
    double n_H__cmm3,
    double C,
    double T_p_cutoff__GeV,
    py::array_t<double> T_CR_array,
    py::array_t<double> f_cal_array
) {
    // Convert numpy arrays to C arrays
    auto T_CR_buf = T_CR_array.request();
    auto f_cal_buf = f_cal_array.request();
    
    if (T_CR_buf.size != f_cal_buf.size) {
        throw std::runtime_error("T_CR and f_cal arrays must have same size");
    }
    
    // Create GSL spline from arrays
    double* T_CR_ptr = static_cast<double*>(T_CR_buf.ptr);
    double* f_cal_ptr = static_cast<double*>(f_cal_buf.ptr);
    
    gsl_spline_object_1D gso1D_fcal = gsl_so1D(
        T_CR_buf.size,
        T_CR_ptr,
        f_cal_ptr
    );
    
    // Call original function
    double result = q_e(T_CR__GeV, n_H__cmm3, C, T_p_cutoff__GeV, gso1D_fcal);
    
    // Clean up
    gsl_so1D_free(gso1D_fcal);
    
    return result;
}

void bind_spectra_functions(py::module &m) {
    m.def("eps_pi", &eps_pi_wrapper,
          "Pion decay gamma-ray spectrum",
          py::arg("E_gam__GeV"),
          py::arg("n_H__cmm3"),
          py::arg("C_p"),
          py::arg("T_p_cutoff__GeV"),
          py::arg("T_CR__GeV"),
          py::arg("f_cal"));
    
    m.def("J", &J_wrapper,
          "Cosmic ray injection spectrum",
          py::arg("T"), py::arg("C"), py::arg("q"), py::arg("m"), py::arg("T_cutoff"));
    
    m.def("C_norm_E", &C_norm_E_wrapper,
          "Normalization constant for cosmic ray energy",
          py::arg("q"), py::arg("m"), py::arg("T_cutoff"));
    
    m.def("q_e", &q_e_wrapper,
          "Secondary electron injection spectrum",
          py::arg("T_CR__GeV"),
          py::arg("n_H__cmm3"),
          py::arg("C"),
          py::arg("T_p_cutoff__GeV"),
          py::arg("T_CR_array"),
          py::arg("f_cal_array"));
}
