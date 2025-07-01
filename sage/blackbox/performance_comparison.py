#!/usr/bin/env sage

"""
Wiedemann Algorithm Performance Comparison

This script compares the performance of Wiedemann's algorithm on different matrix types.

Usage:
    sage performance_comparison.py                    # Quick comparison (50x50, 3 trials)
    sage performance_comparison.py benchmark          # Full benchmark (multiple sizes)
    sage performance_comparison.py detailed [dim] [field_size]  # Detailed analysis

Matrix Types Tested:
- sparse: Random sparse matrices with controlled density
- dft: Discrete Fourier Transform matrices
- toeplitz: Toeplitz matrices (constant along diagonals)
- vandermonde: Vandermonde matrices
- sylvester: Sylvester matrices from polynomials

The comparison includes:
- Success rate of Wiedemann algorithm
- Average, minimum, and maximum execution times
- Number of attempts needed for convergence
- Method used (first polynomial vs LCM)
"""

from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from functools import reduce
import time
import sys

# Import all the classes and functions from main-in-one.py
exec(open('main-in-one.py').read())

def quick_demo():
    """Run a quick demonstration of the performance differences"""
    print("QUICK PERFORMANCE DEMO")
    print("=" * 50)
    
    field = GF(101)
    dim = 60
    
    print(f"Testing {dim}x{dim} matrices over GF({field.cardinality()})")
    print("Matrix types: sparse, dft, toeplitz, sylvester")
    print()
    
    for matrix_type in ['sparse', 'dft', 'toeplitz', 'sylvester']:
        print(f"Testing {matrix_type} matrix...", end=" ")
        
        try:
            result = solve_system(matrix_type, field, dim)
            if result['success'] and result['correct']:
                print(f"SUCCESS - {result['time']:.3f}s ({result['attempts']} attempts, {result['method']})")
            else:
                print(f"FAILED - {result.get('error', 'Unknown error')}")
        except Exception as e:
            print(f"ERROR - {e}")
    
    print("\nNote: DFT, Toeplitz, and Sylvester matrices often solve much faster")
    print("than sparse matrices due to their special structure.")

if __name__ == '__main__':
    if len(sys.argv) == 1:
        quick_demo()
    elif sys.argv[1] == "help":
        print(__doc__)
    else:
        # Use the main function from main-in-one.py
        main()
