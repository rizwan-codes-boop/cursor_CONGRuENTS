/**
 * Implementation of utility function wrappers
 */

#include "wrappers_utils.h"

double sigma_gas_Yu_wrapper(double SFR__Msolyrm1) {
    return sigma_gas_Yu__kmsm1(SFR__Msolyrm1);
}

double sigma_star_Bezanson_wrapper(double M_star__Msol, double Re__kpc) {
    return sigma_star_Bezanson__kmsm1(M_star__Msol, Re__kpc);
}

double Sigma_gas_Shi_iKS_wrapper(double Sigma_SFR__Msolyrm1pcm2, double Sigma_star__Msolpcm2) {
    return Sigma_gas_Shi_iKS__Msolpcm2(Sigma_SFR__Msolyrm1pcm2, Sigma_star__Msolpcm2);
}

double Tdust_wrapper(double z, double SFR__Msolyrm1, double M_star__Msol) {
    return Tdust__K(z, SFR__Msolyrm1, M_star__Msol);
}

double R_vir__kpc_wrapper(double R_half_mass__kpc) {
    return R_vir__kpc(R_half_mass__kpc);
}

double R_half_mass__kpc_wrapper(double Re__kpc, double z) {
    return R_half_mass__kpc(Re__kpc, z);
}

void bind_utility_functions(py::module &m) {
    m.def("sigma_gas_Yu", &sigma_gas_Yu_wrapper,
          "Gas velocity dispersion (Yu et al.)",
          py::arg("SFR__Msolyrm1"));
    
    m.def("sigma_star_Bezanson", &sigma_star_Bezanson_wrapper,
          "Stellar velocity dispersion (Bezanson et al.)",
          py::arg("M_star__Msol"), py::arg("Re__kpc"));
    
    m.def("Sigma_gas_Shi_iKS", &Sigma_gas_Shi_iKS_wrapper,
          "Gas surface density (Shi et al.)",
          py::arg("Sigma_SFR__Msolyrm1pcm2"), py::arg("Sigma_star__Msolpcm2"));
    
    m.def("Tdust", &Tdust_wrapper,
          "Dust temperature",
          py::arg("z"), py::arg("SFR__Msolyrm1"), py::arg("M_star__Msol"));
    
    m.def("R_vir__kpc", &R_vir__kpc_wrapper,
          "Virial radius",
          py::arg("R_half_mass__kpc"));
    
    m.def("R_half_mass__kpc", &R_half_mass__kpc_wrapper,
          "Half-mass radius",
          py::arg("Re__kpc"), py::arg("z"));
}
