def horner(coeffs, black_box, vector, scale=1):
    if not coeffs:
        return vector * 0
    result = vector * 0
    for coeff in reversed(coeffs):
        result = black_box.prod(result) + scale * coeff * vector
    return result