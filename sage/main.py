from sage.all import *
from wiedemann import wiedemann

def lin_sys_gen(p, n):
    field = GF(p)
    invertible = False
    while not invertible: 
        A = random_matrix(field, n, n, density=0.2, sparse=True)
        invertible = A.is_invertible()
    b = vector(field, [field.random_element() for _ in range(n)])
    return A, b, field

if __name__=='__main__':
    A, b, field = lin_sys_gen(5, 10)
    x = wiedemann(A, b, field)
    LHS = vector(list(A*x))
    RHS = b
    print(RHS == LHS)