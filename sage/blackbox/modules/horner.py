# Horner's method to recursively compute poly
# c(x) = (..((c_n)x + c_{n-1})x + ... + c_1)x + c_0 
# This horner function computes c(A)b
def horner(coeffs, black_box, vector):
    # No coeffs: return 0
    if not coeffs:
        return vector * 0
    # If only 1 coeff: return c_0*b
    if len(coeffs) == 1:
        return coeffs[0] * vector
    # Recursive call
    return black_box.prod(horner(coeffs[1:], black_box, vector)) + coeffs[0] * vector