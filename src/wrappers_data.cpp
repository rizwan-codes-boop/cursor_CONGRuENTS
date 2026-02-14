/**
 * Implementation of data function wrappers
 */

#include "wrappers_data.h"
#include "gen_funcs.h"
#include <cmath>

void logspace_array_wrapper(int n, double min, double max, py::array_t<double> output) {
    auto buf = output.request();
    if (buf.size != static_cast<size_t>(n)) {
        throw std::runtime_error("Output array size mismatch");
    }
    
    double* ptr = static_cast<double*>(buf.ptr);
    double log_min = log10(min);
    double log_max = log10(max);
    double delta = (log_max - log_min) / (n - 1.0);
    
    for (int i = 0; i < n; i++) {
        ptr[i] = pow(10.0, log_min + i * delta);
    }
}

void bind_data_functions(py::module &m) {
    m.def("logspace_array", &logspace_array_wrapper,
          "Create logarithmically spaced array",
          py::arg("n"), py::arg("min"), py::arg("max"), py::arg("output"));
}
