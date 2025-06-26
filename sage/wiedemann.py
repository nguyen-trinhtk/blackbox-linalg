from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from krylov import krylov

# input matrix over GF(19)
field = GF(19)
A = matrix(field, [
        [1, 0, 2, 43 % 19, 5],
        [9, 0, 1, 0, 8],
        [7, 0, 1, 0, 23 % 19], 
        [1, 0, 0, 1, 0], 
        [0, 9, 1, 3, 70 % 19]
    ])
print(f'A is invertible: {A.is_invertible()}')
b = vector(field, [1, 2, 3, 4, 5])

def wiedemann(A, b, field):
    sol = None
    n = A.nrows()

    R = PolynomialRing(field, 'x')
    x = R.gen()

    while not sol: 
        u = vector(field, [field.random_element() for _ in range(n)])
        krylov_sequence = krylov(A, b, 2 * n, u)
        m = berlekamp_massey(krylov_sequence)
        m_poly = R(list(m))
        try: 
            h = - (m_poly - m[0]) / (m[0] * x)
            sol = h(A) * b
            return sol
        except Exception: 
            continue

print(wiedemann(A, b, field))