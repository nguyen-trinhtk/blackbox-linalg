from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey

def min_poly_BM(field, sequence):
    R = PolynomialRing(field,"x")
    n = len(sequence)
    C = [field(1)]
    B = [field(1)]
    L = 0
    m = 1
    b = field(1)
    sequence = [field(s) for s in sequence]
    for k in range(n):
        d = sequence[k]
        for i in range(1, L+1):
            d += C[i] * sequence[k - i]
        if d == 0:
            m += 1
        elif 2*L <= k:
            T = C[:]
            C += [0]*(m + len(B) - len(C))
            for i in range(len(B)):
                C[i + m] -= d/b * B[i]
            L = k + 1 - L
            B = T
            b = d
            m = 1
        else:
            C += [0]*(m + len(B) - len(C))
            for i in range(len(B)):
                C[i + m] -= d/b * B[i]
            m += 1
    return R(C[::-1])
