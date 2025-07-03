from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from krylov import krylov
from generators import *
from horner import horner

# Implementation of Wiedemann's Algorithm on nonsingular matrices
def wiedemann(black_box, b, dim, field): 
    R = PolynomialRing(field, 'x') # Define Poly Ring

    max_attempts = 10 # Avoid forever loop
    attempt = 0
    base_poly = R(1) # Polynomial to store factors of failed min poly

    # If RHS is zero, return the zero vector 
    if b.is_zero():
        print("zero RHS")
        return vector(field, [0] * dim)

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

        # Append the new factors of m_poly to base_poly
        # Factorizing both polys
        factors_base = dict(m_poly.factor())
        factors_m = dict(m_poly.factor())
        # For each factor - multiplicity in m_poly, check and update in base_poly
        for factor, mult_m in factors_m.item():
            mult_base = factors_base.get(factor, 0) # 
            if mult_m > mult_base: 
                base_poly *= factor**(mult_m - mult_base)
        base_poly_coeffs = list(base_poly)
        try:
            h_coeffs = [-c / base_poly_coeffs[0] for c in base_poly_coeffs[1:]] # h(x)
            result = horner(h_coeffs[::-1], black_box, b) # x = h(A)b
            # Verifying solution by checking Ax - b = 0
            if (black_box.prod(result)- b).is_zero(): 
                print(f"Valid solution: attempt #{attempt}")
                return result, attempt
            else:
                print("Attempt failed, continuing...")

        # Error handling
        except Exception as e:
            print(f"Exception: {e}")
    # Failed after max attempts
    print("Max attempts failed")
    # Print systems' details
    print(f"Failure: A = {black_box.get_matrix()}")
    print(f"Failure: b = {b}")
    raise RuntimeError("Wiedemann failed after max attempts")
