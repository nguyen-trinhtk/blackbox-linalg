from sage.matrix.berlekamp_massey import berlekamp_massey
import random
from matplotlib import pyplot as plt

def companion_matrix(poly, F):
    n = poly.degree()
    coeffs = poly.list()
    coeffs = [F(c) for c in coeffs]
    leading = coeffs[-1]
    if leading == 0:
        raise ValueError("Leading coefficient a_n must be non-zero.")
    coeffs = [c / leading for c in coeffs]
    a = coeffs[:-1]

    C = matrix(F, n, n, sparse=True)
    for i in range(n - 1):
        C[i + 1, i] = 1
    for i in range(n):
        C[i, n - 1] = -a[i]
    return C

def block_companion_matrix(poly_list, F):
    blocks = [companion_matrix(f, F) for f in poly_list]
    return block_diagonal_matrix(blocks)

def theoretical_success(inv_factors, p):
    degrees = [f.degree() for f in inv_factors]
    max_deg = degrees[-1]
    prob = 1.0
    for deg in degrees[:-1]:
        diff = max_deg - deg
        if diff > 0:
            prob *= (1 - 1 / (p**diff))
        else:
            prob *= 1.0
    return f"{float(prob)*100:.2f}%"

def emperical_success(inv_factors, p, trials=1000):
    f = GF(p)
    A = block_companion_matrix(inv_factors, f)
    n = A.nrows()
    succeeded = 0
    min_poly = A.minpoly()
    
    for _ in range(trials):
        u = vector(f, [f.random_element() for _ in range(n)])
        v = vector(f, [f.random_element() for _ in range(n)])
        kappa = [u.dot_product((A^i)*v) for i in range(2*n)]
        mu = berlekamp_massey(kappa)
        if mu == min_poly:
            succeeded += 1
    prob = succeeded * 100 / trials
    return f"{float(prob):.2f}%"

if __name__=='__main__':
    # Example usage
    p = 7
    R.<x> = PolynomialRing(F)
    # Define some monic invariant factors over F
    f1 = x^2 + 1
    f2 = x^3 + x + 1

    inv_factors = [f1, f2]

    # Run the recovery success experiment with 500 trials
    em = emperical_success(inv_factors, p, trials=1000)
    th = theoretical_success(inv_factors, p)
    print(f"Theoretical: {th}")
    print(f"Emperical: {em}")


