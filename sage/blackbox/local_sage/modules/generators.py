from sage.all import *
def generate_nonsingular_square_matrix(field, dim, sparsity):
    invertible = False
    attempts = 0
    max_matrix_attempts = 1000
    while not invertible and attempts < max_matrix_attempts: 
        attempts += 1
        A = random_matrix(field, dim, dim, density=(1 - sparsity), sparse=True)
        invertible = A.is_invertible()
    if not invertible:
        raise RuntimeError(f"Failed to generate invertible matrix after {max_matrix_attempts} attempts")
    return A

def generate_vector(field, dim):
    return vector(field, [field.random_element() for _ in range(dim)])

def generate_linear_system(field=None, dim=None, sparsity=0.8):
    if not dim: 
        dim = ZZ.random_element(100, 300)
    if not field:
        field = GF(random_prime(2, 57))
    if dim <= 5:
        sparsity = min(sparsity, 0.3)
    elif dim <= 10:
        sparsity = min(sparsity, 0.5)
        
    A = generate_nonsingular_square_matrix(field, dim, sparsity)
    b = generate_vector(field, dim)
    return A, b, dim, field