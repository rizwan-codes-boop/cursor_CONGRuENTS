/**
 * Wrapper functions for steady state solver
 */

#ifndef WRAPPERS_STEADYSTATE_H
#define WRAPPERS_STEADYSTATE_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "CRe_steadystate.h"
#include "gsl_decs.h"

namespace py = pybind11;

// Steady state solver wrapper
// Returns electron spectrum as numpy array
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
);

// Bind to Python module
void bind_steadystate_functions(py::module &m);

#endif
