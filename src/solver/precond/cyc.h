#ifndef CYCLIC_MATRIX_GEN_H
#define CYCLIC_MATRIX_GEN_H

#include <linbox/matrix/dense-matrix.h>
#include <linbox/vector/vector.h>

namespace LinBoxMatGen {

/** 
 * Generate an n×n cyclic (circulant) matrix from a vector of first column elements.
 * If the vector is shorter than n, the last element is repeated.
 */
template <class PIR>
void cyclic_matrix(LinBox::DenseMatrix<PIR>& M, PIR& R, const LinBox::DenseVector<PIR>& first_col)
{
    int n = M.rowdim();
    int m = first_col.size();

    // Fill the cyclic matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = (i - j + n) % n;  // index for cyclic shift
            M(i,j) = (idx < m) ? first_col[idx] : first_col[m-1]; // repeat last element if vector too short
        }
    }
}

} // namespace LinBoxMatGen

#endif // CYCLIC_MATRIX_GEN_H
