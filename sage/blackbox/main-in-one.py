from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from functools import reduce
import time

class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix
    def prod(self, vector):
        return self.__matrix * vector
    def get_matrix(self):
        return self.__matrix
    
def generate_nonsingular_square_matrix(field, dim, sparsity):
    invertible = False
    attempts = 0
    max_matrix_attempts = 1000
    while not invertible and attempts < max_matrix_attempts: 
        attempts += 1
        A = random_matrix(field, dim, dim, density=(1 - sparsity), sparse=True)
        invertible = A.is_invertible()
    if not invertible:
        raise RuntimeError(f"Failed to generate invertible matrix after {max_matrix_attempts} attempts")
    return A

def generate_vector(field, dim):
    return vector(field, [field.random_element() for _ in range(dim)])

def generate_linear_system(field=None, dim=None, sparsity=0.8):
    if not dim: 
        dim = ZZ.random_element(100, 300)
    if not field:
        field = GF(random_prime(2, 57))
    if dim <= 5:
        sparsity = min(sparsity, 0.3)
    elif dim <= 10:
        sparsity = min(sparsity, 0.5)
        
    A = generate_nonsingular_square_matrix(field, dim, sparsity)
    b = generate_vector(field, dim)
    return A, b, dim, field

def krylov(black_box, b, order, u):
    krylov_seq = []
    v = b
    for _ in range(order):
        krylov_seq.append(u.dot_product(v))
        v = black_box.prod(v)
    return krylov_seq

def horner(coeffs, black_box, vector, scale=1):
    if not coeffs:
        return vector * 0
    result = vector * 0
    for coeff in reversed(coeffs):
        result = black_box.prod(result) + scale * coeff * vector
    return result

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

def main():
    A, b, dim, field = generate_linear_system()
    bbox_A = BlackBox(A)
    start = time.time()
    x = wiedemann(bbox_A, b, dim, field)
    end = time.time()
    print(f"Finished Wiedemann in {end - start:.3f}s")
    return True

if __name__ == '__main__':
    i = 0
    failed = 0
    while failed == 0:
        i += 1
        try:
            print(f'Case {i}...', end=' ')
            main()
            print('Passed')
        except Exception as e:
            print(f'Failed: {e}')
            failed += 1
    print(f'Failed {failed} cases')