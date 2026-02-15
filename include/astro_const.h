/**
 * Astronomical Constants
 */

#ifndef ASTRO_CONST_H
#define ASTRO_CONST_H

#include "physical_constants.h"

// These are typically the same as physical constants
// but kept separate for clarity

// Solar mass (already in physical_constants.h)
#define Msol__kg 1.989e30
 #define Msol__g 1.989e33

// Parsec (already in physical_constants.h)
#define pc__cm 3.085677581e18
#define Mpc__cm 3.085677581e24

// Year (already in physical_constants.h)
#define yr__s 3.15576e7

// Solar luminosity (already in physical_constants.h)
#define Lsol__GeVsm1 

// Additional astronomical constants if needed
#define AU__cm 1.495978707e13      // Astronomical unit in cm
#define ly__cm 9.460730472e17      // Light year in cm

#endif /* ASTRO_CONST_H */
