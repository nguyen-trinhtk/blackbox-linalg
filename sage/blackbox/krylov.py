from sage.all import *

def krylov(black_box, b, order, u):
    krylov_seq = []
    v = b
    for _ in range(order):
        krylov_seq.append(u.dot_product(v))
        v = black_box.prod(v)
    return krylov_seq