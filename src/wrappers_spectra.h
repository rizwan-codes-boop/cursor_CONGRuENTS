/**
 * Wrapper functions for spectra calculations
 */

#ifndef WRAPPERS_SPECTRA_H
#define WRAPPERS_SPECTRA_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "spectra_funcs.h"
#include "gsl_decs.h"

namespace py = pybind11;

// Wrapper for spectra calculation functions
// These handle numpy arrays and GSL spline conversion

// Pion decay spectrum
double eps_pi_wrapper(
    double E_gam__GeV,
    double n_H__cmm3,
    double C_p,
    double T_p_cutoff__GeV,
    py::array_t<double> T_CR__GeV,
    py::array_t<double> f_cal
);

// Injection spectrum
double J_wrapper(
    double T,
    double C,
    double q,
    double m,
    double T_cutoff
);

// Normalization constant
double C_norm_E_wrapper(
    double q,
    double m,
    double T_cutoff
);

// Secondary electron injection
double q_e_wrapper(
    double T_CR__GeV,
    double n_H__cmm3,
    double C,
    double T_p_cutoff__GeV,
    py::array_t<double> T_CR_array,
    py::array_t<double> f_cal_array
);

// Bind to Python module
void bind_spectra_functions(py::module &m);

#endif
