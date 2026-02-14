/**
 * Main pybind11 module for spectra calculations
 * Wraps all computationally heavy C functions for Python access
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include <cmath>
#include <memory>

// Include all existing headers
#include "gen_funcs.h"
#include "spectra_funcs.h"
#include "CRe_steadystate.h"
#include "EBL_funcs.h"
#include "gal_rad.h"
#include "CR_spectra/inverse_Compton.h"
#include "CR_spectra/synchrotron.h"
#include "CR_spectra/bremsstrahlung.h"
#include "CR_spectra/ionisation.h"
#include "CR_spectra/diffusion.h"
#include "CR_spectra/CR_funcs.h"
#include "spec_integrate.h"
#include "cosmo_funcs.h"
#include "halo_mass_funcs.h"
#include "data_objects.h"
#include "data_calc.h"
#include "freefreeabsorption.h"
#include "gsl_decs.h"
#include "physical_constants.h"

namespace py = pybind11;

// Forward declarations for wrapper functions
#include "wrappers_cosmo.h"
#include "wrappers_spectra.h"
#include "wrappers_radiative.h"
#include "wrappers_steadystate.h"
#include "wrappers_data.h"
#include "wrappers_utils.h"

PYBIND11_MODULE(spectra_core, m) {
    m.doc() = "High-performance C/C++ physics code exposed to Python via pybind11";
    
    // Bind modules
    bind_cosmo_functions(m);
    bind_spectra_functions(m);
    bind_radiative_functions(m);
    bind_steadystate_functions(m);
    bind_data_functions(m);
    bind_utility_functions(m);
}
