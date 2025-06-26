from sage.all import *

def krylov(A, b, n, u = None):
    krylov_seq= []
    for i in range(n):
        if u:
            krylov_seq.append(u.dot_product((A ** i) * b))
        else: 
            krylov_seq.append((A ** i) * b)
    return krylov_seq