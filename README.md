# Python Wrapper for Spectra Calculations

This directory contains a comprehensive pybind11 wrapper that exposes all computationally heavy C/C++ functions to Python, allowing you to use high-performance physics code from Python without rewriting it.

## Structure

```
python_wrapper/
├── src/                    # C++ wrapper source files
│   ├── spectra_core.cpp    # Main module
│   ├── wrappers_cosmo.*    # Cosmology function wrappers
│   ├── wrappers_spectra.*  # Spectra calculation wrappers
│   ├── wrappers_radiative.* # Radiative process wrappers
│   ├── wrappers_steadystate.* # Steady state solver wrappers
│   ├── wrappers_data.*     # Data utility wrappers
│   └── wrappers_utils.*    # Utility function wrappers
├── include/                # Header files (copied from parent)
├── python/                 # Python scripts
│   └── spectra_main.py     # Main Python script
├── setup.py                # Build script (setuptools)
├── CMakeLists.txt          # Build script (CMake)
└── README.md               # This file
```

## Features

- **All C functions exposed**: Every computationally heavy function is wrapped and accessible from Python
- **NumPy integration**: Arrays are passed directly between Python and C with minimal overhead
- **Memory safety**: pybind11 handles memory management automatically
- **High performance**: C code runs at full speed, Python handles I/O and orchestration

## Prerequisites

- Python 3.6+
- pybind11 (`pip install pybind11`)
- GSL (GNU Scientific Library)
- OpenMP (optional, for parallelization)
- C++ compiler with C++11 support

## Building

### Option 1: Using setuptools (Recommended)

```bash
cd python_wrapper
python setup.py build_ext --inplace
```

This will create `spectra_core.so` (Linux) or `spectra_core.pyd` (Windows) in the current directory.

### Option 2: Using CMake

```bash
cd python_wrapper
mkdir build
cd build
cmake ..
make
```

## Usage

### Basic Example

```python
import numpy as np
import spectra_core

# Calculate luminosity distance
z = 0.5
d_l = spectra_core.d_l_MPc(z)
print(f"Luminosity distance at z={z}: {d_l:.2f} Mpc")

# Calculate gas velocity dispersion
SFR = 10.0  # Solar masses per year
sigma_gas = spectra_core.sigma_gas_Yu(SFR)
print(f"Gas velocity dispersion: {sigma_gas:.2f} km/s")
```

### Advanced Example

```python
import numpy as np
import spectra_core

# Create energy arrays
n_E = 1000
E_min = 1e-3
E_max = 1e8
E_array = np.logspace(np.log10(E_min), np.log10(E_max), n_E)

# Create calorimetry fraction array
f_cal = np.ones(n_E) * 0.5

# Calculate pion decay spectrum
E_gam = 1.0  # GeV
n_H = 1.0    # cm^-3
C_p = 1e-10
T_p_cutoff = 1e8

spec_pi = spectra_core.eps_pi(
    E_gam, n_H, C_p, T_p_cutoff,
    E_array, f_cal
)

print(f"Pion decay spectrum at {E_gam} GeV: {spec_pi:.6e}")
```

### Running the Main Script

```bash
python python/spectra_main.py <galaxy_file> <data_dir> <output_dir>
```

## Available Functions

### Cosmology Functions
- `d_l_MPc(z)` - Luminosity distance
- `d_c_MPc(z_low, z_high)` - Comoving distance
- `d_m_MPc(z)` - Transverse comoving distance
- `d_a_MPc(z)` - Angular diameter distance
- `dV_c(z)` - Comoving volume element
- `Vc_dOm_MPc3srm1(z_low, z_high)` - Comoving volume
- `E_z(z)` - Hubble expansion factor

### Spectra Functions
- `eps_pi(...)` - Pion decay gamma-ray spectrum
- `J(...)` - Cosmic ray injection spectrum
- `C_norm_E(...)` - Normalization constant
- `q_e(...)` - Secondary electron injection spectrum

### Radiative Processes
- `eps_IC_3(...)` - Inverse Compton spectrum
- `eps_SY_4(...)` - Synchrotron spectrum
- `eps_BS_3(...)` - Bremsstrahlung spectrum
- `eps_FF(...)` - Free-free spectrum

### Steady State Solver
- `CRe_steadystate_solve(...)` - Solve steady state cosmic ray electron spectrum

### Utility Functions
- `sigma_gas_Yu(SFR)` - Gas velocity dispersion
- `sigma_star_Bezanson(M_star, Re)` - Stellar velocity dispersion
- `Sigma_gas_Shi_iKS(Sigma_SFR, Sigma_star)` - Gas surface density
- `Tdust(z, SFR, M_star)` - Dust temperature
- `R_vir__kpc(R_half_mass)` - Virial radius
- `R_half_mass__kpc(Re, z)` - Half-mass radius
- `logspace_array(n, min, max, output)` - Create logarithmically spaced array

## Performance

- **Overhead**: pybind11 adds minimal overhead (~nanoseconds per call)
- **Array conversion**: NumPy arrays are passed efficiently with minimal copying
- **Parallelization**: OpenMP parallelization in C code is preserved

## Troubleshooting

### Module not found
- Ensure you've built the module: `python setup.py build_ext --inplace`
- Check that `spectra_core.so` (or `.pyd`) exists in the current directory
- Verify Python can find the module: `python -c "import spectra_core"`

### GSL not found
- Install GSL: `sudo apt-get install libgsl-dev` (Ubuntu/Debian)
- Or: `brew install gsl` (macOS)
- Update library paths in `setup.py` if needed

### OpenMP issues
- OpenMP is optional - the code will work without it
- If you want OpenMP, ensure your compiler supports it

## Development

### Adding New Functions

1. Add wrapper function in appropriate `wrappers_*.cpp` file
2. Add binding in corresponding `bind_*_functions()` function
3. Rebuild: `python setup.py build_ext --inplace`

### Testing

```python
import spectra_core
import numpy as np

# Test cosmology functions
assert spectra_core.d_l_MPc(0.0) == 0.0

# Test with arrays
E = np.logspace(-3, 8, 100)
f_cal = np.ones(100) * 0.5
result = spectra_core.eps_pi(1.0, 1.0, 1e-10, 1e8, E, f_cal)
assert np.isfinite(result)
```

## Notes

- All functions preserve the original C behavior
- NumPy arrays are automatically converted to/from C arrays
- GSL splines are created/destroyed automatically in wrapper functions
- Memory is managed safely by pybind11

## License

Same as the original codebase.
