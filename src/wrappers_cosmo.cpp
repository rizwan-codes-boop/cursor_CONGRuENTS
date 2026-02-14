/**
 * Implementation of cosmology function wrappers
 */

#include "wrappers_cosmo.h"

// Direct wrappers - these functions are already simple enough
double d_l_MPc_wrapper(double z) {
    return d_l_MPc(z);
}

double d_c_MPc_wrapper(double z_low, double z_high) {
    return d_c_MPc(z_low, z_high);
}

double d_m_MPc_wrapper(double z) {
    return d_m_MPc(z);
}

double d_a_MPc_wrapper(double z) {
    return d_a_MPc(z);
}

double dV_c_wrapper(double z) {
    return dV_c(z);
}

double Vc_dOm_MPc3srm1_wrapper(double z_low, double z_high) {
    return Vc_dOm_MPc3srm1(z_low, z_high);
}

double E_z_wrapper(double z) {
    return E_z(z);
}

void bind_cosmo_functions(py::module &m) {
    m.def("d_l_MPc", &d_l_MPc_wrapper, 
          "Luminosity distance in Mpc",
          py::arg("z"));
    
    m.def("d_c_MPc", &d_c_MPc_wrapper,
          "Comoving distance in Mpc",
          py::arg("z_low"), py::arg("z_high"));
    
    m.def("d_m_MPc", &d_m_MPc_wrapper,
          "Transverse comoving distance in Mpc",
          py::arg("z"));
    
    m.def("d_a_MPc", &d_a_MPc_wrapper,
          "Angular diameter distance in Mpc",
          py::arg("z"));
    
    m.def("dV_c", &dV_c_wrapper,
          "Comoving volume element",
          py::arg("z"));
    
    m.def("Vc_dOm_MPc3srm1", &Vc_dOm_MPc3srm1_wrapper,
          "Comoving volume between z_low and z_high",
          py::arg("z_low"), py::arg("z_high"));
    
    m.def("E_z", &E_z_wrapper,
          "Hubble expansion factor",
          py::arg("z"));
}
