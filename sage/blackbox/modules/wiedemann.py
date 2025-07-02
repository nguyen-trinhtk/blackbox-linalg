from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from krylov import krylov
from generators import *
from functools import reduce
from horner import horner

def wiedemann(black_box, b, dim, field): 
    R = PolynomialRing(field, 'x')
    max_attempts = 10
    attempt = 0
    polys = []
    if b.is_zero():
        print("zero RHS")
        return vector(field, [0] * dim)

    while attempt < max_attempts:
        attempt += 1
        u = generate_vector(field, dim)
        if u.is_zero():
            continue
        krylov_sequence = krylov(black_box, b, 2 * dim, u)
        m_poly = list(berlekamp_massey(krylov_sequence))
        polys.append(R(m_poly)) # check before append, store factors only
        try:
            h_coeffs = [-c / m_poly[0] for c in m_poly[1:]]
            result = horner(h_coeffs, black_box, b)
            Ax = black_box.prod(result)
            residual = Ax - b
            if (Ax - b).is_zero():
                print(f"Valid solution: attempt #{attempt}")
                return result, attempt
            elif len(polys) > 1:
                    print("Individual min poly failed, trying LCM of min polys")
                    lcm_poly = reduce(lambda a, b: a.lcm(b), polys) # check field
                    lcm_coeffs = lcm_poly.list()
                    if lcm_coeffs and lcm_coeffs[0] != 0:
                        m_0 = lcm_coeffs[0]
                        h_coeffs = [-c / m_0 for c in lcm_coeffs[1:]]
                        result = horner(h_coeffs, black_box, b)
                        residual = black_box.prod(result) - b
                        if residual.is_zero():
                            print(f"LCM poly succeeded: attempt #{attempt}.")
                            return result, attempt
                        else:
                            print("LCM failed, continuing")
            else:
                print("First attempt failed, continuing...")
        except Exception as e:
            print(f"Exception: {e}")

    print("Max attempts failed")
    print(f"Failure: A = {black_box.get_matrix()}")
    print(f"Failure: b = {b}")
    raise RuntimeError("Wiedemann failed after max attempts")
