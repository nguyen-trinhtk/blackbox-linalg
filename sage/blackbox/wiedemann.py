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
        print("Zero vector b - returning zero solution")
        return vector(field, [0] * dim)

    while attempt < max_attempts:
        attempt += 1
        u = generate_vector(field, dim)
        if u.is_zero():
            continue

        krylov_sequence = krylov(black_box, b, 2 * dim, u)

        try:
            m_poly = list(berlekamp_massey(krylov_sequence))
        except Exception as e:
            print(f"Berlekamp-Massey failed: {e}")
            continue

        if not m_poly or m_poly[0] == 0:
            print("Invalid minimal polynomial, retrying...")
            continue

        polys.append(R(m_poly))
        try:
            m_0 = m_poly[0]
            h_coeffs = [-c / m_0 for c in m_poly[1:]]
            result = horner(h_coeffs, black_box, b)
            Ax = black_box.prod(result)
            residual = Ax - b

            if residual.is_zero():
                print(f"Solution verified in {attempt} attempts.")
                return result

            elif len(polys) > 1:
                print("First poly failed, trying LCM of all collected minimal polynomials...")
                try:
                    lcm_poly = reduce(lambda a, b: a.lcm(b), polys)
                    lcm_coeffs = lcm_poly.list()
                    if lcm_coeffs and lcm_coeffs[0] != 0:
                        m_0 = lcm_coeffs[0]
                        h_coeffs = [-c / m_0 for c in lcm_coeffs[1:]]
                        result = horner(h_coeffs, black_box, b)
                        residual = black_box.prod(result) - b
                        if residual.is_zero():
                            print(f"LCM poly succeeded in attempt {attempt}.")
                            return result
                        else:
                            print("LCM residual nonzero, continuing...")
                except Exception as e:
                    print(f"LCM computation failed in attempt {attempt}: {e}")
                    continue
            else:
                print("First attempt failed, moving on...")
        except Exception as e:
            print(f"Exception during Horner or residual check: {e}")

    print("All individual and LCM attempts failed.")
    raise RuntimeError("Wiedemann failed after multiple attempts.")
