from sage.all import *
from wiedemann import wiedemann
from sage.misc.prandom import randrange

def lin_sys_gen(order, dim):
    field = GF(order)
    invertible = False
    while not invertible: 
        A = random_matrix(field, dim, dim, density=0.2, sparse=True)
        invertible = A.is_invertible()
    b = vector(field, [field.random_element() for _ in range(dim)])
    return A, b, field


def test_success_rate(num_tests = 100, dim = None, field_order = None):
    passed = 0
    failed = 0
    failed_cases = []
    for _ in range(num_tests):
        if not dim: 
            dim = randrange(100)
        if not field_order: 
            field_order = random_prime(57, proof=True)
        A, b, field = lin_sys_gen(field_order, dim)
        x = wiedemann(A, b, field)
        LHS = vector(list(A*x))
        RHS = b
        if (LHS == RHS):
            passed += 1
        else: 
            failed += 1
            failed_cases.append([A*x, b])
    print(f"Passed: {passed} case(s) \n Failed: {failed} case(s) \n ")
    return failed_cases

if __name__=='__main__':
    failed_cases = test_success_rate(num_tests=30)
    for case in failed_cases: 
        print(f"A*x = {case[0]}\n b = {case[1]}")