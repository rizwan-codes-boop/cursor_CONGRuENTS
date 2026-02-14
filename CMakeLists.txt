cmake_minimum_required(VERSION 3.12)
project(spectra_core)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(pybind11 REQUIRED)
find_package(GSL REQUIRED)
find_package(OpenMP)

# Include directories
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/CR_spectra
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${GSL_INCLUDE_DIRS}
)

include_directories(${INCLUDE_DIRS})

# Source files
set(SOURCES
    src/spectra_core.cpp
    src/wrappers_cosmo.cpp
    src/wrappers_spectra.cpp
    src/wrappers_radiative.cpp
    src/wrappers_steadystate.cpp
    src/wrappers_data.cpp
    src/wrappers_utils.cpp
)

# Add C source files
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../cosmo_funcs.c")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../cosmo_funcs.c")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/cosmo_params.c")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/cosmo_params.c")
endif()

# Create Python module
pybind11_add_module(spectra_core ${SOURCES})

# Link libraries
target_link_libraries(spectra_core PRIVATE
    ${GSL_LIBRARIES}
)

# OpenMP
if(OpenMP_CXX_FOUND)
    target_link_libraries(spectra_core PRIVATE OpenMP::OpenMP_CXX)
    target_compile_options(spectra_core PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fopenmp>)
endif()

# Compiler flags
target_compile_options(spectra_core PRIVATE
    -O3
    -Wall
)

# Set output directory
set_target_properties(spectra_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    CXX_VISIBILITY_PRESET "hidden"
)
