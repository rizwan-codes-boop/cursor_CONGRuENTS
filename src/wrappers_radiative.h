/**
 * Wrapper functions for radiative processes
 * (Inverse Compton, Synchrotron, Bremsstrahlung)
 */

#ifndef WRAPPERS_RADIATIVE_H
#define WRAPPERS_RADIATIVE_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "CR_spectra/inverse_Compton.h"
#include "CR_spectra/synchrotron.h"
#include "CR_spectra/bremsstrahlung.h"
#include "gsl_decs.h"

namespace py = pybind11;

// Inverse Compton spectrum
double eps_IC_3_wrapper(
    double E_gam__GeV,
    py::array_t<double> E_gam_table,
    py::array_t<double> E_e_table,
    py::array_t<double> IC_table_2D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
);

// Synchrotron spectrum
double eps_SY_4_wrapper(
    double E_gam__GeV,
    double B__G,
    py::array_t<double> sync_freq_table,
    py::array_t<double> sync_table_1D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
);

// Bremsstrahlung spectrum
double eps_BS_3_wrapper(
    double E_gam__GeV,
    double n_H__cmm3,
    py::array_t<double> E_gam_table,
    py::array_t<double> E_e_table,
    py::array_t<double> BS_table_2D,
    py::array_t<double> E_e_spectrum,
    py::array_t<double> qe_spectrum
);

// Free-free spectrum
double eps_FF_wrapper(
    double E_gam__GeV,
    double Re__kpc,
    double T_e__K,
    double tau_ff
);

// Bind to Python module
void bind_radiative_functions(py::module &m);

#endif
