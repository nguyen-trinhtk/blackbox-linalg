import math
import random
SPARY_LOG = []
def nz(M):

    return len(M.nonzero_positions())

def companion_sparse(n, coeffs, p):
    if len(coeffs) != n + 1:
        raise ValueError(f"Need exactly n+1 = {n+1} coefficients.")
    if not is_prime(p):
        raise ValueError(f"{p} is not prime.")
    F = GF(p)

    coeffs = [F(c) for c in coeffs]
    leading = coeffs[-1]
    if leading == 0:
        raise ValueError("Leading coefficient a_n must be non-zero.")
    coeffs = [c / leading for c in coeffs]
    a = coeffs[:-1]

    C = matrix(F, n, n, sparse=True)
    for i in range(n - 1):
        C[i + 1, i] = 1
    for i in range(n):
        C[i, n - 1] = -a[i]
    return C


def _linbox_lines(M):
    n = M.nrows()
    lines = [f"{n} {n} M"]
    for i, j in M.nonzero_positions():
        lines.append(f"{i+1} {j+1} {int(M[i, j])}")
    lines.append("0 0 0")
    return lines

def companion_block_sparse(inv_factors, p):
    blocks = []
    for coeffs in inv_factors:
        d = len(coeffs) - 1
        blocks.append(companion_sparse(d, coeffs, p))
    C = block_diagonal_matrix(blocks, subdivide=False, sparse=True)
    return C, _linbox_lines(C)


def random_similarity_spray(A):

    n = A.nrows()
    if n < 2:
        return
    i, j = random.sample(range(n), 2)
    F = A.base_ring()
    α = F.random_element()
    while α == 0:
        α = F.random_element()
    A.add_multiple_of_row(i, j,  α)   
    A.add_multiple_of_column(j, i, -α)   
    SPARY_LOG.append((i, j, α))    
    


def densify_to_omega(A, omega, c=3):

    n      = A.nrows()
    N0     = nz(A)              
    if omega < N0:
        raise ValueError("target ω is below current nnz")

    gap    = omega - N0
    max_it = int(10 * n * math.log(gap / n + 2))  

    target = omega
    it     = 0
    band   = c * math.isqrt(target)           
    while abs(nz(A) - target) > band:
        if it >= max_it:
            raise RuntimeError(
                f"Stopped after {max_it} sprays — couldn’t hit nnz band.")
        random_similarity_spray(A)
        print("similar?", matrix(A).rational_form() == A0_rf)
        it += 1
    return it    

# def verify_similarity_sparse(C_orig, C_final, log):

#     B = C_final.__copy__()                   
#     for i, j, α in reversed(log):
#        
#         B.add_multiple_of_row(i, j, -α)
#         # 2) right multiply by I + α e_i e_j^T   
#         B.add_multiple_of_column(j, i,  α)
#     return B == C_orig

if __name__ == "__main__":
    p = int(input("Prime p: ").strip())
    r = int(input("How many invariant factors? ").strip())

    inv = []
    for k in range(1, r + 1):
        coeffs = list(map(int,
            input(f"Factor {k}: coefficients a0 … ad (space-separated): ").split()))
        inv.append(coeffs)

    C, _ = companion_block_sparse(inv, p)
    A0_rf = matrix(C).rational_form() 
    n     = C.nrows()
    floor = nz(C)        

    print(f"\nInitial nnz (sparsity floor) = {floor}")

    omega = int(input(f"Target nnz ω (≥ {floor} and ≤ {n*n}): ").strip())
    if not (floor <= omega <= n * n):
        raise ValueError("ω outside allowed range.")


    sprays = densify_to_omega(C, omega, 3)
    print(f"Done.  Performed {sprays} random sprays.")
    print(f"Final nnz  = {nz(C)}  (target {omega})")


    lines = _linbox_lines(C)


    if input("Save matrix to file? (y/n): ").strip().lower() == "y":
        fname = input("Filename [dense_blocks.txt]: ").strip() or "dense_blocks.txt"
        with open(fname, "w") as f:
            f.write("\n".join(lines) + "\n")
        print(f"Written to {fname}")

