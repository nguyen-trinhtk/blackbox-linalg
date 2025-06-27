from sage.all import *
# from sage.matrix.berlekamp_massey import berlekamp_massey
from krylov import krylov
from berlekamp_massey import min_poly_BM

def wiedemann(A, b, field):
    n = A.nrows()
    sol = None
    R = PolynomialRing(field, 'x')
    x = R.gen()
    while not sol:
        u = vector(field, [field.random_element() for _ in range(n)])
        krylov_sequence = krylov(A, b, 2 * n, u)
        m = min_poly_BM(field, krylov_sequence)
        m_poly = R(list(m))
        try: 
            h = - (m_poly - m[0]) / (m[0] * x)
            sol = h(A) * b
            return vector(list(sol))
        except Exception: 
            continue