# Missing Files Created

This document lists all the missing header files that were created to make the codebase compile.

## Created Files

### 1. `gsl_decs.h`
**Purpose**: GSL spline object structures and helper functions

**Contents**:
- `gsl_spline_object_1D` structure (with x_lim array)
- `gsl_spline_object_2D` structure
- `gsl_so1D()` - Create 1D spline
- `gsl_so1D_eval()` - Evaluate 1D spline
- `gsl_so1D_free()` - Free 1D spline
- `gsl_so2D()` - Create 2D spline
- `gsl_so2D_eval()` - Evaluate 2D spline
- `gsl_so2D_free()` - Free 2D spline

### 2. `physical_constants.h`
**Purpose**: Physical constants in CGS and GeV units

**Contents**:
- Masses: `m_e__GeV`, `m_p__GeV`, `m_pi0__GeV`, `m_piC__GeV`, `m_mu__GeV`
- Masses in grams: `m_e__g`, `m_H__kg`, `m_H__g`
- Speed of light: `c__cmsm1`
- Length conversions: `pc__cm`, `Mpc__cm`
- Mass conversions: `Msol__kg`, `Msol__g`
- Energy conversions: `erg__GeV`, `GeV__erg`, `yr__s`
- Planck constants: `h__ergs`, `h__GeVs`, `hbar_GeVs`, `h_GeVs`
- Elementary charge: `e__esu`
- Boltzmann constant: `k_B__GeVKm1`
- Fine structure constant: `alpha`
- Cross-sections: `sigma_T__mb`, `mb__cm2`
- Radiation constant: `arad__GeVcmm3Km4`
- Solar luminosity: `Lsol__GeVsm1`
- CMB temperature: `T_0_CMB__K`

### 3. `math_funcs.h`
**Purpose**: Math utility functions

**Contents**:
- `logspace_array()` - Create logarithmically spaced array
- `linspace_array()` - Create linearly spaced array
- `maxval()` - Find maximum value in array
- `minval()` - Find minimum value in array

### 4. `cosmo_params.h` and `cosmo_params.c`
**Purpose**: Cosmological parameters

**Contents**:
- `om_M` - Matter density parameter (default: 0.315)
- `om_k` - Curvature density parameter (default: 0.0)
- `om_lam` - Dark energy density parameter (default: 0.685)
- `D_H_MPc` - Hubble constant in Mpc (default: 2997.92458)

### 5. `astro_const.h`
**Purpose**: Astronomical constants

**Contents**:
- Additional astronomical constants
- References physical_constants.h for most values
- `AU__cm` - Astronomical unit
- `ly__cm` - Light year

## Dependencies

These files depend on:
- GSL (GNU Scientific Library)
- Standard C math library
- cubature library (for ERROR_INDIVIDUAL)

## Notes

- All constants use standard physics values
- Default cosmological parameters are from Planck 2018
- GSL spline objects wrap GSL's native spline structures
- All functions are inline for performance

## Integration

These files are included in:
- `setup.py` - cosmo_params.c is compiled
- `CMakeLists.txt` - cosmo_params.c is compiled
- All wrapper files include these headers as needed
