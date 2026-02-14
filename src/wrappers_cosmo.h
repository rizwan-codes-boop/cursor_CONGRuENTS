/**
 * Wrapper functions for cosmology calculations
 */

#ifndef WRAPPERS_COSMO_H
#define WRAPPERS_COSMO_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "cosmo_funcs.h"

namespace py = pybind11;

// Wrapper functions
double d_l_MPc_wrapper(double z);
double d_c_MPc_wrapper(double z_low, double z_high);
double d_m_MPc_wrapper(double z);
double d_a_MPc_wrapper(double z);
double dV_c_wrapper(double z);
double Vc_dOm_MPc3srm1_wrapper(double z_low, double z_high);
double E_z_wrapper(double z);

// Bind to Python module
void bind_cosmo_functions(py::module &m);

#endif
