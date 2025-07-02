from sage.all import *

def min_poly_BM(field, sequence):
    R = PolynomialRing(field, "x")
    sequence = [field(s) for s in sequence]
    n = len(sequence)

    C = [field(1)]
    B = [field(1)]
    L = 0
    m = 1
    b = field(1)

    for k in range(n):
        d = sequence[k] + sum(C[i] * sequence[k - i] for i in range(1, L + 1))
        if d == 0:
            m += 1
        elif 2 * L <= k:
            T = C[:]
            C += [field(0)] * (m + len(B) - len(C))  # Extend C to match new length
            for i in range(len(B)):
                C[i + m] -= d / b * B[i]
            L = k + 1 - L
            B = T
            b = d
            m = 1
        else:
            C += [field(0)] * (m + len(B) - len(C))
            for i in range(len(B)):
                C[i + m] -= d / b * B[i]
            m += 1

    return R(list(C)[::-1])