"""
Setup script for building the spectra_core pybind11 module
"""

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup, Extension
import pybind11
import os
import sys

# Get the directory containing this file
this_dir = os.path.dirname(os.path.abspath(__file__))
src_dir = os.path.join(this_dir, "src")
include_dir = os.path.join(this_dir, "include")
parent_dir = os.path.dirname(this_dir)

# Include directories
include_dirs = [
    pybind11.get_include(),
    src_dir,
    include_dir,
    os.path.join(include_dir, "CR_spectra"),
    parent_dir,  # For any headers in parent directory
]

# Library directories and libraries
# Adjust these based on your system's GSL installation
library_dirs = []
libraries = ['gsl', 'gslcblas', 'm']

# Check for OpenMP
extra_compile_args = ['-std=c++11', '-O3']
extra_link_args = []

try:
    import subprocess
    result = subprocess.run(['gcc', '-fopenmp', '-E', '-'], 
                          input='', capture_output=True, timeout=1)
    if result.returncode == 0:
        extra_compile_args.append('-fopenmp')
        extra_link_args.append('-fopenmp')
        libraries.append('gomp')
except:
    pass

# Source files
sources = [
    os.path.join(src_dir, "spectra_core.cpp"),
    os.path.join(src_dir, "wrappers_cosmo.cpp"),
    os.path.join(src_dir, "wrappers_spectra.cpp"),
    os.path.join(src_dir, "wrappers_radiative.cpp"),
    os.path.join(src_dir, "wrappers_steadystate.cpp"),
    os.path.join(src_dir, "wrappers_data.cpp"),
    os.path.join(src_dir, "wrappers_utils.cpp"),
]

# Add C source files if they exist
c_sources = [
    os.path.join(parent_dir, "cosmo_funcs.c"),
    os.path.join(include_dir, "cosmo_params.c"),
]

for c_file in c_sources:
    if os.path.exists(c_file):
        sources.append(c_file)

ext_modules = [
    Pybind11Extension(
        "spectra_core",
        sources,
        include_dirs=include_dirs,
        library_dirs=library_dirs,
        libraries=libraries,
        language='c++',
        extra_compile_args=extra_compile_args,
        extra_link_args=extra_link_args,
    ),
]

setup(
    name="spectra_core",
    version="0.1.0",
    author="Your Name",
    description="High-performance C/C++ physics code exposed to Python via pybind11",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.6",
    install_requires=["pybind11>=2.6", "numpy"],
)
