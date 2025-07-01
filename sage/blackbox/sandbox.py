from sage.all import *
from sage.matrix.berlekamp_massey import berlekamp_massey
from functools import reduce
import time

class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix
    def prod(self, vector):
        return self.__matrix * vector
    def get_matrix(self):
        return self.__matrix
    
class MatrixGenerator: 
    def __init__(self, dim, field): 
        self.__dim = dim
        self.__field = field
    def nonsingular_sqr_mat(self, sparsity):
        invertible = False
        attempts = 0
        max_matrix_attempts = 1000
        while not invertible and attempts < max_matrix_attempts: 
            attempts += 1
            A = random_matrix(self.__field, self.__dim, self.__dim, density=(1 - sparsity), sparse=True)
            invertible = A.is_invertible()
        if not invertible:
            raise RuntimeError(f"Failed to generate invertible matrix after {max_matrix_attempts} attempts")
        return A
    def DFT_mat(self, omega):
        max_attempts = 50  # Reduced from 100 for better performance
        attempts = 0
        
        # For large dimensions, DFT matrices are often singular in finite fields
        # Try to use primitive roots of unity when possible
        if self.__field.is_finite():
            # For finite fields, we need omega to be a primitive nth root of unity
            # where n divides the order of the multiplicative group
            order = self.__field.cardinality() - 1
            
            # Try to find a suitable root of unity
            for divisor in [d for d in range(1, min(self.__dim + 1, 50)) if order % d == 0]:
                if order % self.__dim == 0:
                    # Perfect case - dimension divides the group order
                    omega = self.__field.multiplicative_generator() ** (order // self.__dim)
                    break
                elif order % divisor == 0:
                    omega = self.__field.multiplicative_generator() ** (order // divisor)
                    break
        
        while attempts < max_attempts:
            attempts += 1
            W = matrix(self.__field, self.__dim, self.__dim)
            try:
                norm_factor = self.__field(1) / self.__field(self.__dim)
            except:
                norm_factor = self.__field(1)
            
            for j in range(self.__dim):
                for k in range(self.__dim):
                    W[j, k] = (omega)**(j * k) * norm_factor
            
            if W.is_invertible():
                return W
            
            # Try a different omega if current one doesn't work
            if self.__field.is_finite():
                # Use systematic approach for finding good omega values
                if attempts < 10:
                    omega = self.__field.multiplicative_generator() ** attempts
                else:
                    omega = self.__field.random_element()
                    while omega == 0:
                        omega = self.__field.random_element()
            else:
                omega = self.__field.random_element()
        
        raise RuntimeError(f"Failed to generate invertible DFT matrix after {max_attempts} attempts")
    def toeplitz(self, first_row=None, first_col=None): 
        max_attempts = 50  # Reduced for better performance
        attempts = 0
        
        while attempts < max_attempts:
            attempts += 1
            
            if first_row is None:
                first_row = [self.__field.random_element() for _ in range(self.__dim)]
            if first_col is None:
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
            
            # Reset for next attempt
            first_row = None
            first_col = None
        
        raise RuntimeError(f"Failed to generate invertible Toeplitz matrix after {max_attempts} attempts")
        
    def sylvester(self, poly1=None, poly2=None):
        max_attempts = 50  # Reduced for better performance
        attempts = 0
        
        while attempts < max_attempts:
            attempts += 1
            R = PolynomialRing(self.__field, 'x')
            
            if poly1 is None:
                # Generate random polynomial of degree roughly dim/2
                deg1 = max(1, self.__dim // 2)
                coeffs1 = [self.__field.random_element() for _ in range(deg1 + 1)]
                coeffs1[-1] = self.__field.one()  # Make it monic (leading coefficient = 1)
                poly1 = R(coeffs1)
                
            if poly2 is None:
                # Generate random polynomial of degree roughly dim/2
                deg2 = max(1, self.__dim - poly1.degree())
                coeffs2 = [self.__field.random_element() for _ in range(deg2 + 1)]
                coeffs2[-1] = self.__field.one()  # Make it monic
                poly2 = R(coeffs2)
            
            try:
                S = poly1.sylvester_matrix(poly2)
                # Check if dimensions match and matrix is invertible
                if S.nrows() == self.__dim and S.ncols() == self.__dim and S.is_invertible():
                    return S
                elif S.nrows() >= self.__dim and S.ncols() >= self.__dim:
                    # Try to extract a square submatrix
                    sub_S = S.submatrix(0, 0, self.__dim, self.__dim)
                    if sub_S.is_invertible():
                        return sub_S
            except:
                pass
            
            # Reset for next attempt
            poly1 = None
            poly2 = None
        
        raise RuntimeError(f"Failed to generate invertible Sylvester matrix after {max_attempts} attempts")
        
    def vandermonde(self, points=None):
        """Generate an invertible Vandermonde matrix"""
        max_attempts = 50  # Reduced for better performance
        attempts = 0
        
        while attempts < max_attempts:
            attempts += 1
            
            if points is None:
                # Generate distinct random points for Vandermonde matrix
                if self.__field.is_finite() and self.__field.cardinality() < self.__dim:
                    # If field is too small, we can't get enough distinct points
                    raise RuntimeError(f"Field size {self.__field.cardinality()} too small for dimension {self.__dim}")
                
                points = []
                used_points = set()
                max_point_attempts = min(100, self.__field.cardinality() if self.__field.is_finite() else 1000)
                
                for i in range(self.__dim):
                    point_attempts = 0
                    point = self.__field.random_element()
                    while point in used_points and point_attempts < max_point_attempts:
                        point = self.__field.random_element()
                        point_attempts += 1
                    
                    if point in used_points:
                        # Failed to find distinct point, break and retry with new set
                        break
                    
                    points.append(point)
                    used_points.add(point)
                
                # Check if we got enough distinct points
                if len(points) < self.__dim:
                    points = None
                    continue
            
            V = matrix(self.__field, self.__dim, self.__dim)
            for i in range(self.__dim):
                for j in range(self.__dim):
                    V[i, j] = points[i] ** j
            
            if V.is_invertible():
                return V
            
            # Reset for next attempt
            points = None
        
        raise RuntimeError(f"Failed to generate invertible Vandermonde matrix after {max_attempts} attempts")
        
    def berlekamp_over_field(self, polynomial=None):
        """Generate a matrix for Berlekamp's algorithm over finite fields"""
        if not self.__field.is_finite():
            raise ValueError("Berlekamp matrix only applies to finite fields")
            
        if polynomial is None:
            # Generate a random polynomial of appropriate degree
            R = PolynomialRing(self.__field, 'x')
            coeffs = [self.__field.random_element() for _ in range(self.__dim + 1)]
            coeffs[-1] = self.__field.one()  # Make it monic
            polynomial = R(coeffs)
        
        # Create the matrix x^q - x mod polynomial
        q = self.__field.cardinality()
        R = PolynomialRing(self.__field, 'x')
        x = R.gen()
        
        # Compute x^q mod polynomial
        xq_mod = pow(x, q, polynomial)
        diff_poly = xq_mod - x
        
        # Convert to matrix representation
        B = matrix(self.__field, self.__dim, self.__dim)
        coeffs = diff_poly.list()
        for i in range(min(len(coeffs), self.__dim)):
            for j in range(self.__dim):
                if i + j < self.__dim:
                    B[i, j] = coeffs[i] if i < len(coeffs) else 0
        return B
    
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

def generate_linear_system(field=None, dim=None, sparsity=0.8, matrix_type="sparse"):
    if not dim: 
        dim = ZZ.random_element(100, 300)
    if not field:
        field = GF(random_prime(2, 57))
    if dim <= 5:
        sparsity = min(sparsity, 0.3)
    elif dim <= 10:
        sparsity = min(sparsity, 0.5)
    gen = MatrixGenerator(dim, field)
    match matrix_type:
        case "sparse":
            A = gen.nonsingular_sqr_mat(sparsity)
        case "dft":
            # For DFT, we need a primitive root of unity if possible
            if field.is_finite():
                # Try to find a primitive element
                try:
                    omega = field.multiplicative_generator()
                except:
                    omega = field.random_element()
            else:
                omega = field.random_element()
            A = gen.DFT_mat(omega)
        case "toeplitz":
            A = gen.toeplitz()
        case "vandermonde":
            A = gen.vandermonde()
        case "sylvester":
            A = gen.sylvester()
        case "berlekamp":
            if field.is_finite():
                A = gen.berlekamp_over_field()
            else:
                print("Berlekamp matrix only for finite fields, falling back to sparse matrix")
                A = gen.nonsingular_sqr_mat(sparsity)
        case _: 
            A = gen.nonsingular_sqr_mat(0.5)
    b = generate_vector(field, dim)
    return A, b, dim, field

def krylov(black_box, b, order, u):
    krylov_seq = []
    v = b
    for _ in range(order):
        krylov_seq.append(u.dot_product(v))
        v = black_box.prod(v)
    return krylov_seq

def horner(coeffs, black_box, vector, scale=1):
    if not coeffs:
        return vector * 0
    result = vector * 0
    for coeff in reversed(coeffs):
        result = black_box.prod(result) + scale * coeff * vector
    return result

def wiedemann(black_box, b, dim, field, verbose=False): 
    R = PolynomialRing(field, 'x')
    max_attempts = 10
    attempt = 0
    polys = []
    
    if b.is_zero():
        if verbose:
            print("Zero vector b - returning zero solution")
        return vector(field, [0] * dim), {'attempts': 0, 'method': 'trivial'}

    while attempt < max_attempts:
        attempt += 1
        u = generate_vector(field, dim)
        if u.is_zero():
            continue

        krylov_sequence = krylov(black_box, b, 2 * dim, u)

        try:
            m_poly = list(berlekamp_massey(krylov_sequence))
        except Exception as e:
            if verbose:
                print(f"Berlekamp-Massey failed: {e}")
            continue

        if not m_poly or m_poly[0] == 0:
            if verbose:
                print("Invalid minimal polynomial, retrying...")
            continue

        polys.append(R(m_poly))
        try:
            m_0 = m_poly[0]
            h_coeffs = [-c / m_0 for c in m_poly[1:]]
            result = horner(h_coeffs, black_box, b)
            Ax = black_box.prod(result)
            residual = Ax - b

            if residual.is_zero():
                if verbose:
                    print(f"Solution verified in {attempt} attempts.")
                return result, {'attempts': attempt, 'method': 'first_poly'}

            elif len(polys) > 1:
                if verbose:
                    print("First poly failed, trying LCM of all collected minimal polynomials...")
                try:
                    lcm_poly = reduce(lambda a, b: a.lcm(b), polys)
                    lcm_coeffs = lcm_poly.list()
                    if lcm_coeffs and lcm_coeffs[0] != 0:
                        m_0 = lcm_coeffs[0]
                        h_coeffs = [-c / m_0 for c in lcm_coeffs[1:]]
                        result = horner(h_coeffs, black_box, b)
                        residual = black_box.prod(result) - b
                        if residual.is_zero():
                            if verbose:
                                print(f"LCM poly succeeded in attempt {attempt}.")
                            return result, {'attempts': attempt, 'method': 'lcm_poly'}
                        else:
                            if verbose:
                                print("LCM residual nonzero, continuing...")
                except Exception as e:
                    if verbose:
                        print(f"LCM computation failed in attempt {attempt}: {e}")
                    continue
            else:
                if verbose:
                    print("First attempt failed, moving on...")
        except Exception as e:
            if verbose:
                print(f"Exception during Horner or residual check: {e}")

    if verbose:
        print("All individual and LCM attempts failed.")
    raise RuntimeError("Wiedemann failed after multiple attempts.")

def solve_system(matrix_type, field, dim, sparsity=0.8):
    """Solve a linear system for a specific matrix type and return performance metrics"""
    try:
        A, b, actual_dim, actual_field = generate_linear_system(
            field=field, dim=dim, sparsity=sparsity, matrix_type=matrix_type
        )
        bbox_A = BlackBox(A)
        
        start = time.time()
        x, metrics = wiedemann(bbox_A, b, actual_dim, actual_field, verbose=False)
        end = time.time()
        
        # Verify solution
        residual = bbox_A.prod(x) - b
        is_correct = residual.is_zero()
        
        return {
            'matrix_type': matrix_type,
            'success': True,
            'time': end - start,
            'attempts': metrics['attempts'],
            'method': metrics['method'],
            'correct': is_correct,
            'dim': actual_dim,
            'field_size': actual_field.cardinality() if actual_field.is_finite() else 'infinite'
        }
    except Exception as e:
        return {
            'matrix_type': matrix_type,
            'success': False,
            'time': None,
            'attempts': None,
            'method': None,
            'correct': False,
            'error': str(e),
            'dim': dim,
            'field_size': field.cardinality() if field.is_finite() else 'infinite'
        }

def benchmark_matrix_types(dimensions=[50, 100, 150], field_sizes=[101, 1009], num_trials=3):
    """Compare Wiedemann performance across different matrix types"""
    matrix_types = ['sparse', 'dft', 'toeplitz', 'vandermonde', 'sylvester']
    results = []
    
    print("=" * 80)
    print("WIEDEMANN ALGORITHM PERFORMANCE COMPARISON")
    print("=" * 80)
    
    for field_size in field_sizes:
        field = GF(field_size)
        print(f"\nField: GF({field_size})")
        print("-" * 60)
        
        for dim in dimensions:
            print(f"\nDimension: {dim}x{dim}")
            print("-" * 40)
            
            # Store results for this dimension
            dim_results = {}
            
            for matrix_type in matrix_types:
                print(f"Testing {matrix_type} matrices...", end=" ")
                
                # Run multiple trials
                trial_results = []
                success_count = 0
                
                for trial in range(num_trials):
                    result = solve_system(matrix_type, field, dim)
                    trial_results.append(result)
                    if result['success'] and result['correct']:
                        success_count += 1
                
                # Calculate statistics
                successful_times = [r['time'] for r in trial_results if r['success'] and r['correct']]
                
                if successful_times:
                    avg_time = sum(successful_times) / len(successful_times)
                    min_time = min(successful_times)
                    max_time = max(successful_times)
                else:
                    avg_time = min_time = max_time = None
                
                dim_results[matrix_type] = {
                    'success_rate': success_count / num_trials,
                    'avg_time': avg_time,
                    'min_time': min_time,
                    'max_time': max_time,
                    'trials': trial_results
                }
                
                # Print immediate results
                if successful_times:
                    print(f"Success: {success_count}/{num_trials}, Avg: {avg_time:.3f}s, Range: [{min_time:.3f}, {max_time:.3f}]")
                else:
                    print(f"Failed all {num_trials} trials")
                    for result in trial_results:
                        if not result['success']:
                            print(f"    Error: {result.get('error', 'Unknown')}")
            
            # Print comparison for this dimension
            print("\nPerformance Summary:")
            successful_types = [(k, v) for k, v in dim_results.items() if v['avg_time'] is not None]
            if successful_types:
                # Sort by average time
                successful_types.sort(key=lambda x: x[1]['avg_time'])
                
                print(f"{'Matrix Type':<12} {'Success Rate':<12} {'Avg Time':<10} {'Best Time':<10}")
                print("-" * 50)
                for matrix_type, stats in successful_types:
                    print(f"{matrix_type:<12} {stats['success_rate']:<12.1%} {stats['avg_time']:<10.3f} {stats['min_time']:<10.3f}")
                
                # Store for global comparison
                results.append({
                    'field_size': field_size,
                    'dim': dim,
                    'results': dim_results
                })
            else:
                print("No successful trials for any matrix type")
    
    return results

def detailed_comparison(dim=100, field_size=101, num_trials=5, sparsity=0.9):
    """Detailed comparison of matrix types for a specific dimension"""
    field = GF(field_size)
    matrix_types = ['sparse', 'dft', 'toeplitz', 'vandermonde', 'sylvester']
    
    print("=" * 80)
    print(f"DETAILED COMPARISON - {dim}x{dim} matrices over GF({field_size})")
    print("=" * 80)
    
    all_results = []
    
    for matrix_type in matrix_types:
        print(f"\n{matrix_type.upper()} MATRICES")
        print("-" * 30)
        
        matrix_results = []
        for trial in range(num_trials):
            print(f"Trial {trial + 1}: ", end="")
            result = solve_system(matrix_type, field, dim, sparsity)
            matrix_results.append(result)
            
            if result['success'] and result['correct']:
                print(f"SUCCESS - {result['time']:.3f}s")
            else:
                print(f"FAILED - {result.get('error', 'Unknown error')}")
        
        # Calculate statistics
        successful_results = [r for r in matrix_results if r['success'] and r['correct']]
        if successful_results:
            times = [r['time'] for r in successful_results]
            print(f"Statistics: {len(successful_results)}/{num_trials} successful")
            print(f"  Average: {sum(times)/len(times):.3f}s")
            print(f"  Min: {min(times):.3f}s")
            print(f"  Max: {max(times):.3f}s")
            print(f"  Std Dev: {(sum((t - sum(times)/len(times))**2 for t in times) / len(times))**0.5:.3f}s")
        else:
            print(f"No successful trials")
        
        all_results.append({
            'matrix_type': matrix_type,
            'results': matrix_results,
            'successful_results': successful_results
        })
    
    # Final comparison
    print("\n" + "=" * 80)
    print("FINAL COMPARISON")
    print("=" * 80)
    
    successful_types = [(r['matrix_type'], r['successful_results']) 
                       for r in all_results if r['successful_results']]
    
    if successful_types:
        print(f"{'Matrix Type':<15} {'Success Rate':<12} {'Avg Time':<12} {'Min Time':<12} {'Max Time':<12}")
        print("-" * 75)
        
        for matrix_type, results in successful_types:
            times = [r['time'] for r in results]
            success_rate = len(results) / num_trials
            avg_time = sum(times) / len(times)
            min_time = min(times)
            max_time = max(times)
            
            print(f"{matrix_type:<15} {success_rate:<12.1%} {avg_time:<12.3f} {min_time:<12.3f} {max_time:<12.3f}")
        
        # Find best performing type
        best_type = min(successful_types, key=lambda x: sum(r['time'] for r in x[1]) / len(x[1]))
        print(f"\nBest performing matrix type: {best_type[0]}")
    else:
        print("No matrix types had successful trials")
    
    return all_results

def main():
    """Main function with options for different types of comparisons"""
    import sys
    
    if len(sys.argv) > 1:
        if sys.argv[1] == "benchmark":
            # Run comprehensive benchmark
            results = benchmark_matrix_types(
                dimensions=[50, 100, 150], 
                field_sizes=[101, 1009], 
                num_trials=3
            )
        elif sys.argv[1] == "detailed":
            # Run detailed comparison for specific size
            dim = int(sys.argv[2]) if len(sys.argv) > 2 else 100
            field_size = int(sys.argv[3]) if len(sys.argv) > 3 else 101
            results = detailed_comparison(dim=dim, field_size=field_size, num_trials=5)
        else:
            print("Usage: sage main-in-one.py [benchmark|detailed] [dim] [field_size]")
            return
    else:
        # Default: quick comparison
        print("Running quick comparison (use 'benchmark' or 'detailed' for more extensive tests)")
        results = detailed_comparison(dim=50, field_size=101, num_trials=1000)

if __name__ == '__main__':
    main()