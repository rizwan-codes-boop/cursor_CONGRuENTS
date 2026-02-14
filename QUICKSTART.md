# Quick Start Guide

## Overview

This wrapper exposes all your C/C++ physics functions to Python via pybind11. You get:
- **Full C performance** - computations run at native C speed
- **Python flexibility** - use NumPy, matplotlib, Jupyter, etc.
- **Easy integration** - call C functions like Python functions

## Installation

1. **Install dependencies**:
```bash
pip install pybind11 numpy
sudo apt-get install libgsl-dev  # Ubuntu/Debian
# or
brew install gsl  # macOS
```

2. **Build the module**:
```bash
cd python_wrapper
python setup.py build_ext --inplace
```

3. **Test it works**:
```python
python -c "import spectra_core; print('Success!')"
```

## Basic Usage

### Example 1: Cosmology Functions

```python
import spectra_core
import numpy as np

# Calculate distances
z = 0.5
d_l = spectra_core.d_l_MPc(z)  # Luminosity distance
d_c = spectra_core.d_c_MPc(0.0, z)  # Comoving distance

print(f"At z={z}:")
print(f"  Luminosity distance: {d_l:.2f} Mpc")
print(f"  Comoving distance: {d_c:.2f} Mpc")
```

### Example 2: Galaxy Properties

```python
import spectra_core

# Galaxy parameters
M_star = 1e10  # Solar masses
Re = 5.0  # kpc
SFR = 10.0  # Solar masses per year
z = 0.5

# Calculate properties
sigma_star = spectra_core.sigma_star_Bezanson(M_star, Re)
sigma_gas = spectra_core.sigma_gas_Yu(SFR)
T_dust = spectra_core.Tdust(z, SFR, M_star)

print(f"Stellar velocity dispersion: {sigma_star:.2f} km/s")
print(f"Gas velocity dispersion: {sigma_gas:.2f} km/s")
print(f"Dust temperature: {T_dust:.2f} K")
```

### Example 3: Spectra Calculations

```python
import numpy as np
import spectra_core

# Create energy arrays
n_E = 1000
E_min, E_max = 1e-3, 1e8
E_array = np.logspace(np.log10(E_min), np.log10(E_max), n_E)
f_cal = np.ones(n_E) * 0.5  # Calorimetry fraction

# Calculate pion decay spectrum
E_gam = 1.0  # GeV
n_H = 1.0  # cm^-3
C_p = 1e-10
T_p_cutoff = 1e8

spec_pi = spectra_core.eps_pi(
    E_gam, n_H, C_p, T_p_cutoff,
    E_array, f_cal
)

print(f"Pion decay spectrum at {E_gam} GeV: {spec_pi:.6e}")
```

### Example 4: Using NumPy Arrays

```python
import numpy as np
import spectra_core

# Create logarithmically spaced array
n = 100
output = np.zeros(n)
spectra_core.logspace_array(n, 1e-3, 1e8, output)

print(f"Energy array: {output[:5]} ... {output[-5:]}")
```

## Running the Full Pipeline

```bash
python python/spectra_main.py input/galaxies.txt data/ output/
```

## Available Functions

### Cosmology
- `d_l_MPc(z)` - Luminosity distance
- `d_c_MPc(z_low, z_high)` - Comoving distance  
- `d_m_MPc(z)` - Transverse comoving distance
- `d_a_MPc(z)` - Angular diameter distance
- `E_z(z)` - Hubble expansion factor

### Galaxy Properties
- `sigma_gas_Yu(SFR)` - Gas velocity dispersion
- `sigma_star_Bezanson(M_star, Re)` - Stellar velocity dispersion
- `Sigma_gas_Shi_iKS(Sigma_SFR, Sigma_star)` - Gas surface density
- `Tdust(z, SFR, M_star)` - Dust temperature

### Spectra
- `eps_pi(...)` - Pion decay spectrum
- `eps_IC_3(...)` - Inverse Compton spectrum
- `eps_SY_4(...)` - Synchrotron spectrum
- `eps_BS_3(...)` - Bremsstrahlung spectrum
- `eps_FF(...)` - Free-free spectrum

### Utilities
- `logspace_array(n, min, max, output)` - Create log-spaced array
- `J(...)` - Injection spectrum
- `C_norm_E(...)` - Normalization constant

## Tips

1. **NumPy arrays**: All arrays are passed directly - no copying overhead
2. **Memory**: pybind11 handles memory automatically
3. **Performance**: C code runs at full speed
4. **Debugging**: Use Python's debugging tools (pdb, print statements)

## Troubleshooting

**Module not found**: Run `python setup.py build_ext --inplace` again

**GSL errors**: Install GSL development libraries

**Compilation errors**: Check that all header files are in `include/` directory

## Next Steps

- See `README.md` for detailed documentation
- Check `python/spectra_main.py` for full example
- Modify wrappers in `src/wrappers_*.cpp` to add more functions
