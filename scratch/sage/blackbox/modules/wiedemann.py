from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from krylov import krylov
from generators import *
from horner import horner
from blackbox import BlackBox
import time

# Implementation of Wiedemann's Algorithm on nonsingular matrices
def wiedemann(black_box, b, dim, field): 
    R = PolynomialRing(field, 'x') # Define Poly Ring

    max_attempts = 10 # Avoid forever loop
    attempt = 0
    base_poly = R(1) # Polynomial to store factors of failed min poly

    # If RHS is zero, return the zero vector 
    if b.is_zero():
        print("zero RHS")
        return vector(field, [0] * dim), 1, base_poly

    # Main loop to find solution that satisfies Ax = b
    while attempt <= max_attempts:
        attempt += 1
        u = generate_vector(field, dim) # Random vector u

        # Regenerate u if u is zero
        while u.is_zero():
            u = generate_vector(field, dim)

        # Generate Krylov sequence & dot product with u
        krylov_sequence = krylov(black_box, b, 2 * dim, u)

        # Generate min poly of {u^TA^ib}
        m_poly = berlekamp_massey(krylov_sequence)

        # Update base_poly with factors from m_poly
        factors_m = dict(m_poly.factor())
        factors_base = dict(base_poly.factor())
        
        # For each factor in m_poly, update base_poly if higher multiplicity
        for factor, mult_m in factors_m.items():
            mult_base = factors_base.get(factor, 0)
            if mult_m > mult_base: 
                base_poly *= factor**(mult_m - mult_base)
        
        # Check if base_poly has degree equal to matrix dimension
        base_poly_coeffs = list(base_poly)
        try:
                h_coeffs = [-c / base_poly_coeffs[0] for c in base_poly_coeffs[1:]] # h(x)
                result = horner(h_coeffs, black_box, b) # x = h(A)b
                # Verify solution by checking Ax - b = 0
                if (black_box.prod(result) - b).is_zero(): 
                    print(f"Valid solution: attempt #{attempt}")
                    return result, attempt, base_poly
                else:
                    print(f"Attempt {attempt} failed...")
        except Exception as e:
                print(f"Attempt {attempt} failed: {e}")
                continue
    # Failed after max attempts
    print("Max attempts failed")
    # Print systems' details
    # print(f"Failure: A = {black_box.get_matrix()}")
    # print(f"Failure: b = {b}")
    raise RuntimeError("Wiedemann failed after max attempts")

def wiedemann_timed_test(A, b, dim, field):
    bbox_A = BlackBox(A)
    start = time.time()
    x, attempts, w_minpoly = wiedemann(bbox_A, b, dim, field)
    end = time.time()
    print(f"Finished Wiedemann in {end - start:.3f}s ({attempts} attempt{"s" if attempts != 1 else ""})")
    # start_sage = time.time()
    # assert x == A.solve_right(b), f"Failed: Solution different from Sage built-in solver"
    # end_sage = time.time()
    return (end - start)
    # print(f'Solution verified against Sage built-in solver ({end_sage - start_sage:.3f}s)')
    # assert w_minpoly == A.minpoly(), 'Wiedemann generated min poly is different from actual minpoly'
    # print('Wiedemann generated min poly is correct')
    # return attempts