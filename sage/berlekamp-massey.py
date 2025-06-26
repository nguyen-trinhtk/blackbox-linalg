from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey

def min_poly_bm(sequence):
    R = PolynomialRing(AA,"x")
    n = len(sequence)
    C = [AA(1)]
    B = [AA(1)]
    L = ZZ(0)
    m = ZZ(1)
    b = AA(1)
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

print(berlekamp_massey([1, 7, 9, 2, 5, 1]))
print(min_poly_bm([1, 7, 9, 2, 5, 1]))
