#ifndef MAT_GEN_H
#define MAT_GEN_H

#include <linbox/matrix/dense-matrix.h>
#include <linbox/vector/vector.h>

namespace LinBoxMatGen {

/** Random dense matrix */
template <class PIR>
void random_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R)
{
    int n = M.rowdim();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = R.rand();
}

/** Random sparse matrix (dense representation, sparsity 0<=s<=1) */
template <class PIR>
void random_sparse_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R, double sparsity)
{
    int n = M.rowdim();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = (R.randReal() < sparsity) ? R.rand() : R.zero();
}

/** Random diagonal matrix */
template <class PIR>
void random_diagonal_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R)
{
    int n = M.rowdim();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = (i==j) ? R.rand() : R.zero();
}

/** Diagonal matrix from vector of entries; repeats last value if smaller than n */
template <class PIR>
void diagonal_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R, const LinBox::DenseVector<PIR>& diag)
{
    int n = M.rowdim();
    int m = diag.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = (i==j) ? ((i < m) ? diag[i] : diag[m-1]) : R.zero();
}

/** Block diagonal matrix from vector of blocks (each block is DenseMatrix) */
template <class PIR>
void block_diagonal_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R, 
                           const std::vector< LinBox::DenseMatrix<PIR> >& blocks)
{
    int n = M.rowdim();
    int start = 0;
    for (auto& B : blocks) {
        int bsize = B.rowdim();
        for (int i = 0; i < bsize; ++i)
            for (int j = 0; j < bsize; ++j)
                if (start+i < n && start+j < n)
                    M(start+i, start+j) = B(i,j);
        start += bsize;
        if (start >= n) break;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (M(i,j) != M(i,j))
                M(i,j) = R.zero();
}

/** Jordan block: eigenvalue lambda, size n */
template <class PIR>
void jordan_block(LinBox::DenseMatrix<PIR>& M, PIR& R, const typename PIR::Element& lambda)
{
    int n = M.rowdim();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = R.zero();

    for (int i = 0; i < n; ++i)
        M(i,i) = lambda;
    for (int i = 0; i < n-1; ++i)
        M(i,i+1) = R.one();
}

/** Companion matrix of monic polynomial over field */
template <class PIR>
void companion_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R, const LinBox::DenseVector<PIR>& poly)
{
    int n = M.rowdim();
    // Fill zeros
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M(i,j) = R.zero();
    // Subdiagonal ones
    for (int i = 1; i < n; ++i)
        M(i,i-1) = R.one();
    // Last row = -poly[0..n-1]
    for (int j = 0; j < n; ++j)
        M(0,j) = -poly[j]; // assuming poly is degree n-1
}

} // namespace LinBoxMatGen

#endif // MAT_GEN_H
