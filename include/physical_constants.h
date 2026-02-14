/**
 * Physical Constants
 * All constants in CGS units unless otherwise specified
 */

#ifndef PHYSICAL_CONSTANTS_H
#define PHYSICAL_CONSTANTS_H

#include <math.h>

// Masses in GeV
#define m_e__GeV 0.5109989461e-3  // Electron mass in GeV
#define m_p__GeV 0.9382720813     // Proton mass in GeV
#define m_pi0__GeV 0.1349766      // Neutral pion mass in GeV
#define m_piC__GeV 0.13957018     // Charged pion mass in GeV
#define m_mu__GeV 0.1056583745e-3 // Muon mass in GeV

// Masses in grams
#define m_e__g 9.10938356e-28     // Electron mass in grams
#define m_H__kg 1.6735575e-27      // Hydrogen atom mass in kg
#define m_H__g 1.6735575e-24       // Hydrogen atom mass in grams

// Speed of light
#define c__cmsm1 2.99792458e10     // Speed of light in cm/s

// Length conversions
#define pc__cm 3.085677581e18      // Parsec in cm
#define Mpc__cm 3.085677581e24     // Megaparsec in cm

// Mass conversions
#define Msol__kg 1.989e30          // Solar mass in kg
#define Msol__g 1.989e33           // Solar mass in grams

// Energy conversions
#define erg__GeV 6.242e8            // Erg to GeV conversion
#define GeV__erg 1.602176634e-10    // GeV to erg conversion
#define yr__s 3.15576e7             // Year in seconds

// Planck constant
#define h__ergs 6.62607015e-27     // Planck constant in erg*s
#define h__GeVs 6.582119569e-25    // Planck constant in GeV*s
#define hbar_GeVs 1.054571817e-34 * 6.242e8 / 1e9  // Reduced Planck constant in GeV*s
#define h_GeVs h__GeVs             // Alias

// Elementary charge
#define e__esu 4.80320425e-10      // Elementary charge in esu

// Boltzmann constant
#define k_B__GeVKm1 8.617333262e-14 // Boltzmann constant in GeV/K

// Fine structure constant
#define alpha 7.2973525693e-3      // Fine structure constant

// Thomson cross-section
#define sigma_T__mb 0.665245873    // Thomson cross-section in mb
#define mb__cm2 1e-27              // Millibarn to cm^2 conversion

// Radiation constant
#define arad__GeVcmm3Km4 4.723e-10 // Radiation constant in GeV/(cm^3 K^4)

// Solar luminosity
#define Lsol__GeVsm1 3.828e26 * erg__GeV / yr__s  // Solar luminosity in GeV/s

// CMB temperature
#define T_0_CMB__K 2.725            // CMB temperature at z=0 in K

#endif /* PHYSICAL_CONSTANTS_H */
