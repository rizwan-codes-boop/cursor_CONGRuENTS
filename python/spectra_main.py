#!/usr/bin/env python3
"""
Main Python script for spectra calculations.
Uses pybind11-wrapped C functions for high-performance computation.
"""

import numpy as np
import sys
import os
from pathlib import Path

# Import the compiled C module
try:
    import spectra_core
except ImportError:
    print("Error: spectra_core module not found. Please compile it first.")
    print("Run: python setup.py build_ext --inplace")
    sys.exit(1)


class SpectraCalculator:
    """Main class for spectra calculations"""
    
    def __init__(self, params=None):
        """Initialize with default or custom parameters"""
        self.params = params or self.default_params()
    
    @staticmethod
    def default_params():
        """Default calculation parameters"""
        return {
            'q_p_inject': 2.2,
            'q_e_inject': 2.2,
            'T_CR_lims__GeV': [1e-3, 1e8],
            'E_CRe_lims__GeV': [1e-3 + 0.511e-3, 1e8 + 0.511e-3],
            'E_gam_lims__GeV': [1e-16, 1e8],
            'n_T_CR': 1000,
            'n_E_gam': 500,
            'T_p_cutoff__GeV': 1e8,
            'T_e_cutoff__GeV': 1e5,
            'chi': 1e-4,
            'M_A': 2.0,
            'beta': 0.25,
            'sigma_pp_cm2': 40e-27,
            'mu_H': 1.4,
            'mu_p': 1.17,
            'n_SN_Msolm1': 1.321680e-2,
            'f_EtoCR': 0.1,
            'f_CRe_CRp': 0.2,
            'E_SN_erg': 1e51,
            'f_vAi': 1.0,
        }
    
    def read_tau_ebl(self, filename):
        """Read tau EBL data from file"""
        with open(filename, 'r') as f:
            for _ in range(2):
                f.readline()
            ny_z = int(f.readline().strip())
            f.readline()
            nx_E = int(f.readline().strip())
            f.readline()
            
            ya_z = np.array([float(x) for x in f.readline().split()])
            f.readline()
            xa_E = np.array([float(x) for x in f.readline().split()])
            f.readline()
            za_tau = np.array([float(x) for x in f.readline().split()])
        
        return nx_E, ny_z, xa_E, ya_z, za_tau
    
    def read_galaxies(self, filename):
        """Read galaxy data from file"""
        with open(filename, 'r') as f:
            f.readline()
            n_gal = int(f.readline().strip())
            f.readline()
            
            data = []
            for i in range(n_gal):
                line = f.readline().strip().split()
                z = float(line[0])
                M_star = float(line[1])
                Re = float(line[2])
                SFR = float(line[3])
                data.append([z, M_star, Re, SFR])
        
        return n_gal, np.array(data)
    
    def calculate_calorimetry(self, gal_data):
        """Calculate calorimetry fraction and related quantities"""
        n_gal = len(gal_data)
        z, M_star, Re, SFR = gal_data.T
        
        n_T_CR = self.params['n_T_CR']
        
        # Create energy arrays
        T_CR__GeV = np.logspace(
            np.log10(self.params['T_CR_lims__GeV'][0]),
            np.log10(self.params['T_CR_lims__GeV'][1]),
            n_T_CR
        )
        
        E_CRe__GeV = np.logspace(
            np.log10(self.params['E_CRe_lims__GeV'][0]),
            np.log10(self.params['E_CRe_lims__GeV'][1]),
            n_T_CR
        )
        
        # Initialize output arrays
        f_cal = np.zeros((n_gal, n_T_CR))
        D__cm2sm1 = np.zeros((n_gal, n_T_CR))
        D_e__cm2sm1 = np.zeros((n_gal, n_T_CR))
        D_e_z2__cm2sm1 = np.zeros((n_gal, n_T_CR))
        
        h__pc = np.zeros(n_gal)
        n_H__cmm3 = np.zeros(n_gal)
        B__G = np.zeros(n_gal)
        B_halo__G = np.zeros(n_gal)
        
        # Calculate for each galaxy
        for i in range(n_gal):
            # Calculate basic properties using wrapped functions
            A_Re__pc2 = np.pi * (Re[i] * 1e3)**2
            Sig_star__Msolpcm2 = M_star[i] / (2. * A_Re__pc2)
            Sig_SFR__Msolyrm1pcm2 = SFR[i] / (2. * A_Re__pc2)
            
            Sig_gas__Msolpcm2 = spectra_core.Sigma_gas_Shi_iKS(
                Sig_SFR__Msolyrm1pcm2,
                Sig_star__Msolpcm2
            )
            
            sig_gas__kmsm1 = spectra_core.sigma_gas_Yu(SFR[i])
            T_dust__K = spectra_core.Tdust(z[i], SFR[i], M_star[i])
            
            # Calculate scale height and density
            sig_star = spectra_core.sigma_star_Bezanson(M_star[i], Re[i])
            h__pc[i] = (sig_gas__kmsm1**2) / (
                np.pi * 4.302e-3 * (
                    Sig_gas__Msolpcm2 +
                    (sig_gas__kmsm1 / sig_star) * Sig_star__Msolpcm2
                )
            )
            
            n_H__cmm3[i] = Sig_gas__Msolpcm2 / (
                self.params['mu_H'] * 1.673e-27 * 2. * h__pc[i]
            ) * 1.989e30 / (3.086e18)**3
            
            # Calculate magnetic field
            u_LA = sig_gas__kmsm1 / np.sqrt(2.)
            v_Ai = 1000. * (u_LA / 10.) / (
                np.sqrt(self.params['chi'] / 1e-4) * self.params['M_A']
            )
            L_A = h__pc[i] / (self.params['M_A']**3)
            
            n__cmm3 = n_H__cmm3[i] * self.params['mu_H'] / self.params['mu_p']
            B__G[i] = np.sqrt(
                4. * np.pi * self.params['chi'] * n__cmm3 *
                self.params['mu_p'] * 1.673e-27 * 1e3
            ) * v_Ai * 1e5
            
            if np.log10(SFR[i] / M_star[i]) > -10.:
                B_halo__G[i] = B__G[i] / 3.
            else:
                B_halo__G[i] = B__G[i] / 1.5
            
            # Calculate calorimetry fraction (simplified - full implementation needed)
            # TODO: Implement full calorimetry calculation using C functions
        
        return {
            'f_cal': f_cal,
            'D__cm2sm1': D__cm2sm1,
            'D_e__cm2sm1': D_e__cm2sm1,
            'D_e_z2__cm2sm1': D_e_z2__cm2sm1,
            'h__pc': h__pc,
            'n_H__cmm3': n_H__cmm3,
            'B__G': B__G,
            'B_halo__G': B_halo__G,
            'T_CR__GeV': T_CR__GeV,
            'E_CRe__GeV': E_CRe__GeV,
        }
    
    def compute_galaxy_spectra(self, i, gal_data, cal_data, interp_objects=None):
        """Compute spectra for a single galaxy"""
        z, M_star, Re, SFR = gal_data[i]
        
        n_E_gam = self.params['n_E_gam']
        E_gam__GeV = np.logspace(
            np.log10(self.params['E_gam_lims__GeV'][0]),
            np.log10(self.params['E_gam_lims__GeV'][1]),
            n_E_gam
        )
        
        # Initialize result arrays
        result = {
            'spec_pi': np.zeros(n_E_gam),
            'spec_IC_1_z1': np.zeros(n_E_gam),
            'spec_IC_2_z1': np.zeros(n_E_gam),
            'spec_BS_1_z1': np.zeros(n_E_gam),
            'spec_BS_2_z1': np.zeros(n_E_gam),
            'spec_SY_1_z1': np.zeros(n_E_gam),
            'spec_SY_2_z1': np.zeros(n_E_gam),
            'spec_IC_1_z2': np.zeros(n_E_gam),
            'spec_IC_2_z2': np.zeros(n_E_gam),
            'spec_SY_1_z2': np.zeros(n_E_gam),
            'spec_SY_2_z2': np.zeros(n_E_gam),
            'spec_pi_fcal1': np.zeros(n_E_gam),
            'spec_nu': np.zeros(n_E_gam),
            'spec_FF': np.zeros(n_E_gam),
            'tau_gg': np.zeros(n_E_gam),
            'tau_FF': np.zeros(n_E_gam),
        }
        
        # TODO: Implement full spectra calculation using wrapped C functions
        # This would call spectra_core.eps_pi, spectra_core.eps_IC_3, etc.
        
        return result
    
    def write_output(self, results, output_dir):
        """Write output files"""
        Path(output_dir).mkdir(parents=True, exist_ok=True)
        
        # Write spectra files
        for key, data in results.items():
            if isinstance(data, np.ndarray):
                filename = os.path.join(output_dir, f"{key}.txt")
                np.savetxt(filename, data)
                print(f"Written {filename}")


def main():
    """Main function"""
    if len(sys.argv) < 4:
        print("Usage: python spectra_main.py <galaxy_file> <data_dir> <output_dir>")
        sys.exit(1)
    
    infile = sys.argv[1]
    datadir = sys.argv[2]
    outdir = sys.argv[3]
    
    print("Initializing spectra calculator...")
    calc = SpectraCalculator()
    
    print(f"Reading galaxies from {infile}...")
    n_gal, gal_data = calc.read_galaxies(infile)
    print(f"Processing {n_gal} galaxies")
    
    print("Calculating calorimetry...")
    cal_data = calc.calculate_calorimetry(gal_data)
    
    print("Computing spectra...")
    results = []
    for i in range(min(n_gal, 10)):  # Limit to 10 for testing
        print(f"  Galaxy {i+1}/{min(n_gal, 10)}")
        result = calc.compute_galaxy_spectra(i, gal_data, cal_data)
        results.append(result)
    
    print("Writing output...")
    calc.write_output({'gal_data': gal_data, 'cal_data': cal_data}, outdir)
    
    print("Done!")


if __name__ == "__main__":
    main()
