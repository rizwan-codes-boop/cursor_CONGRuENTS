/**
 * Wrapper functions for data objects and utilities
 */

#ifndef WRAPPERS_DATA_H
#define WRAPPERS_DATA_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// Utility functions
void logspace_array_wrapper(int n, double min, double max, py::array_t<double> output);

// Bind to Python module
void bind_data_functions(py::module &m);

#endif
