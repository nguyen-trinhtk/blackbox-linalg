# All-in-one Python/Sage script to test new functions
from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from functools import reduce
import time

class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix
        self.__min_poly = None
    def prod(self, vector):
        return self.__matrix * vector
    def getDimensions(self):
        return self.__matrix.nrows()
    def setMinPoly(self, minpoly):
        self.__min_poly = minpoly
    def getMinPoly(self):
        return self.__min_poly
    
class MatrixGenerator: 
    def __init__(self, dim, field): 
        self.__dim = dim
        self.__field = field
    
    def nonsingular_sqr_mat(self, sparsity):
        attempts = 0
        max_attempts = 100
        while attempts < max_attempts: 
            attempts += 1
            A = random_matrix(self.__field, self.__dim, self.__dim, 
                            density=(1 - sparsity), sparse=True)
            if A.is_invertible():
                return A
        raise RuntimeError(f"Failed to generate invertible matrix after {max_attempts} attempts")
    
    def DFT_mat(self, omega=None):
        if omega is None and self.__field.is_finite():
            omega = self.__field.multiplicative_generator()
        elif omega is None:
            omega = self.__field.random_element()
            
        W = matrix(self.__field, self.__dim, self.__dim)
        for j in range(self.__dim):
            for k in range(self.__dim):
                W[j, k] = omega**(j * k)
        
        if not W.is_invertible():
            return W
        return W
    
    def toeplitz(self):
        attempts = 0
        max_attempts = 50
        while attempts < max_attempts:
            attempts += 1
            first_row = [self.__field.random_element() for _ in range(self.__dim)]
            first_col = [first_row[0]] + [self.__field.random_element() for _ in range(self.__dim - 1)]
            
            T = matrix(self.__field, self.__dim, self.__dim)
            for i in range(self.__dim):
                for j in range(self.__dim):
                    if j >= i:
                        T[i, j] = first_row[j - i]
                    else:
                        T[i, j] = first_col[i - j]
            
            if T.is_invertible():
                return T
        
        # Fallback to identity + random
        return matrix.identity(self.__field, self.__dim) + random_matrix(self.__field, self.__dim, self.__dim, density=0.1)
    
    def vandermonde(self):
        if self.__field.is_finite() and self.__field.cardinality() < self.__dim:
            raise ValueError(f"Field size {self.__field.cardinality()} too small for dimension {self.__dim}")
        
        attempts = 0
        max_attempts = 50
        while attempts < max_attempts:
            attempts += 1
            # Generate distinct points
            points = []
            used_points = set()
            
            for _ in range(self.__dim):
                point = self.__field.random_element()
                retries = 0
                while point in used_points and retries < 50:
                    point = self.__field.random_element()
                    retries += 1
                points.append(point)
                used_points.add(point)
            
            V = matrix(self.__field, self.__dim, self.__dim)
            for i in range(self.__dim):
                for j in range(self.__dim):
                    V[i, j] = points[i] ** j
            
            if V.is_invertible():
                return V
        
        # Fallback: use consecutive field elements
        if self.__field.is_finite():
            points = list(self.__field)[:self.__dim]
        else:
            points = list(range(self.__dim))
        
        V = matrix(self.__field, self.__dim, self.__dim)
        for i in range(self.__dim):
            for j in range(self.__dim):
                V[i, j] = self.__field(points[i]) ** j
        return V

def generate_linear_system(field=None, dim=None, sparsity=0.9, matrix_type="sparse"):
    if dim is None: 
        dim = 50
    if field is None:
        field = GF(101)
    
    gen = MatrixGenerator(dim, field)
    
    if matrix_type == "sparse":
        A = gen.nonsingular_sqr_mat(sparsity)
    elif matrix_type == "dft":
        A = gen.DFT_mat()
    elif matrix_type == "toeplitz":
        A = gen.toeplitz()
    elif matrix_type == "vandermonde":
        A = gen.vandermonde()
    else:
        A = gen.nonsingular_sqr_mat(0.5)
    
    b = vector(field, [field.random_element() for _ in range(dim)])
    return A, b

def krylov(black_box, b, order, u):
    krylov_seq = []
    v = b
    for _ in range(order):
        krylov_seq.append(u.dot_product(v))
        v = black_box.prod(v)
    return krylov_seq

def horner(coeffs, black_box, vector):
    if not coeffs:
        return vector * 0
    result = vector * 0
    for coeff in reversed(coeffs):
        result = black_box.prod(result) + coeff * vector
    return result

def wiedemann(black_box, b, verbose=False): 
    field = b.base_ring()
    dim = len(b)
    R = PolynomialRing(field, 'x')
    max_attempts = 5
    if b.is_zero():
        return vector(field, [0] * dim)
    for attempt in range(1, max_attempts + 1):
        u = vector(field, [field.random_element() for _ in range(dim)])
        if u.is_zero():
            continue
        krylov_sequence = krylov(black_box, b, 2 * dim, u)
        try:
            m_poly = list(berlekamp_massey(krylov_sequence))
        except:
            if verbose:
                print(f"Attempt {attempt}: Berlekamp-Massey failed")
            continue
        if not m_poly or m_poly[0] == 0:
            if verbose:
                print(f"Attempt {attempt}: Invalid minimal polynomial")
            continue
        try:
            m_0 = m_poly[0]
            h_coeffs = [-c / m_0 for c in m_poly[1:]]
            result = horner(h_coeffs, black_box, b)
            residual = black_box.prod(result) - b
            if residual.is_zero():
                if verbose:
                    print(f"Solution found in {attempt} attempts")
                black_box.setMinPoly(m_poly)
                return result
        except:
            if verbose:
                print(f"Attempt {attempt}: Solution verification failed")
            continue
    raise RuntimeError("Wiedemann algorithm failed")

def solve_and_time(matrix_type, field, dim, sparsity=0.8, verbose=False):
    try:
        A, b = generate_linear_system(field, dim, sparsity, matrix_type)
        bbox = BlackBox(A)
        start_time = time.time()
        x = wiedemann(bbox, b, verbose)
        end_time = time.time()
        residual = bbox.prod(x) - b
        success = residual.is_zero()
        return {
            'success': success,
            'time': end_time - start_time,
            'matrix_type': matrix_type,
            'dim': dim
        }
    except Exception as e:
        return {
            'success': False,
            'time': None,
            'matrix_type': matrix_type,
            'dim': dim,
            'error': str(e)
        }

def compare_matrix_types(dim=50, field=GF(101), num_trials=3):
    matrix_types = ['sparse', 'dft', 'toeplitz', 'vandermonde']
    
    print(f"Comparing Wiedemann performance on {dim}x{dim} matrices over {field}")
    print("=" * 60)
    
    for matrix_type in matrix_types:
        print(f"\n{matrix_type.upper()} matrices:")
        times = []
        successes = 0
        
        for trial in range(num_trials):
            result = solve_and_time(matrix_type, field, dim)
            if result['success']:
                times.append(result['time'])
                successes += 1
                print(f"  Trial {trial+1}: {result['time']:.4f}s")
            else:
                print(f"  Trial {trial+1}: FAILED - {result.get('error', 'Unknown error')}")
        
        if times:
            avg_time = sum(times) / len(times)
            print(f"  Success rate: {successes}/{num_trials}")
            print(f"  Average time: {avg_time:.4f}s")
        else:
            print(f"  All trials failed")

def determinant(black_box):
    minpoly = black_box.getMinPoly()
    if not minpoly: 
        raise ValueError('This blackbox havent ran Wiedemann')
    dim = black_box.getDimensions()
    
    # Generic case: minimal polynomial degree equals matrix dimension
    if len(minpoly) - 1 == dim:
        return (-1)**(dim)*minpoly[0]
    
    # Degenerate case: minimal polynomial degree < matrix dimension
    # Use random diagonal similarity transformation to make matrix non-derogatory
    else:
        field = black_box._BlackBox__matrix.base_ring()
        max_attempts = 20
        
        for attempt in range(max_attempts):
            # Generate random diagonal matrix D with non-zero entries
            diagonal_entries = [field.random_element() for _ in range(dim)]
            while any(d == 0 for d in diagonal_entries):
                diagonal_entries = [field.random_element() for _ in range(dim)]
            
            D = diagonal_matrix(field, diagonal_entries)
            det_D = reduce(lambda x, y: x * y, diagonal_entries)
            
            # Create new black box B = A * D
            B_matrix = black_box._BlackBox__matrix * D
            B_bbox = BlackBox(B_matrix)
            
            # Generate random vector and run Wiedemann on B
            b = vector(field, [field.random_element() for _ in range(dim)])
            if b.is_zero():
                continue
                
            try:
                wiedemann(B_bbox, b, verbose=False)
                B_minpoly = B_bbox.getMinPoly()
                
                # Check if B is non-derogatory (minimal polynomial degree = dimension)
                if B_minpoly and len(B_minpoly) - 1 == dim:
                    det_B = (-1)**(dim) * B_minpoly[0]
                    # det(A) = det(B) / det(D) since B = A * D
                    return det_B / det_D
                    
            except Exception:
                continue
        
        # If all attempts failed, raise an error
        raise RuntimeError(f"Failed to compute determinant after {max_attempts} attempts with diagonal similarity")


def main():    
    print("\nComparing matrix types...")
    compare_matrix_types(dim=200, field=GF(1009), num_trials=20)

if __name__ == '__main__':
    main()