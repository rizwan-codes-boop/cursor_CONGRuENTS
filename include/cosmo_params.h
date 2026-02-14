/**
 * Cosmological Parameters
 * Default values for flat Lambda-CDM cosmology
 */

#ifndef COSMO_PARAMS_H
#define COSMO_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

// Matter density parameter
extern double om_M;

// Curvature density parameter (0 for flat universe)
extern double om_k;

// Dark energy density parameter
extern double om_lam;

// Hubble constant in Mpc
extern double D_H_MPc;

#ifdef __cplusplus
}
#endif

#endif /* COSMO_PARAMS_H */
