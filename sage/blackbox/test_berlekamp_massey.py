from sage.all import *
from berlekamp_massey import min_poly_BM

def generate_sequence_from_minpoly(min_poly, init=None, length=50):
    F = min_poly.base_ring()
    min_poly = min_poly.monic()
    assert min_poly.leading_coefficient() == 1
    coeffs = min_poly.list()[::-1]
    rec = coeffs[1:]
    d = len(rec)
    if init is None:
        init = [F(0)]*(d-1) + [F(1)]
    else:
        assert len(init) == d
    seq = list(init)
    for _ in range(length - d):
        next_term = -sum(rec[i] * seq[-(i+1)] for i in range(d))
        seq.append(next_term)
    return seq

def run_tests(num_tests=30):
    F = GF(7)
    R = PolynomialRing(F, 'x')
    d = 4
    passed = 0
    for i in range(1, num_tests + 1):
        while True:
            min_poly = R.random_element(degree=d)
            if not min_poly.is_zero():
                min_poly = min_poly.monic()
                break
        seq = generate_sequence_from_minpoly(min_poly, length=40)
        recovered_poly = min_poly_BM(F, seq)
        if recovered_poly.monic() == min_poly:
            print(f"Test {i}: Passed")
            passed += 1
        else:
            print(f"Test {i}: Failed")
            print("Generated minimal polynomial:", min_poly)
            print("Recovered polynomial:", recovered_poly)
    print(f"\n{passed}/{num_tests} tests passed.")

if __name__=="__main__":
    run_tests()
