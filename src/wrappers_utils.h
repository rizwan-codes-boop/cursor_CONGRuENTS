/**
 * Wrapper functions for utility functions
 */

#ifndef WRAPPERS_UTILS_H
#define WRAPPERS_UTILS_H

#include <pybind11/pybind11.h>
#include "halo_mass_funcs.h"
#include "gal_rad.h"

namespace py = pybind11;

// Galaxy properties
double sigma_gas_Yu_wrapper(double SFR__Msolyrm1);
double sigma_star_Bezanson_wrapper(double M_star__Msol, double Re__kpc);
double Sigma_gas_Shi_iKS_wrapper(double Sigma_SFR__Msolyrm1pcm2, double Sigma_star__Msolpcm2);
double Tdust_wrapper(double z, double SFR__Msolyrm1, double M_star__Msol);

// Halo mass functions
double R_vir__kpc_wrapper(double R_half_mass__kpc);
double R_half_mass__kpc_wrapper(double Re__kpc, double z);

// Bind to Python module
void bind_utility_functions(py::module &m);

#endif
