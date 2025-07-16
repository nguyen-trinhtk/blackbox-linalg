#include <iostream>
#include <givaro/modular.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/solutions/det.h>
using namespace LinBox;

int main()
{
    typedef Givaro::Modular<double> Field;
    Field F(101);
    
    // Use SparseMatrix for sparse matrix operations
    SparseMatrix<Field> A(F, 3, 3); // 3x3 sparse matrix
    
    // Initialize with some test values - sparse matrices store only non-zero entries
    A.setEntry(0, 0, 1);
    A.setEntry(0, 1, 2);
    A.setEntry(0, 2, 3);
    A.setEntry(1, 0, 4);
    A.setEntry(1, 1, 5);
    A.setEntry(1, 2, 6);
    A.setEntry(2, 0, 7);
    A.setEntry(2, 1, 8);
    A.setEntry(2, 2, 9);
    
    Field::Element d;
    det(d, A);
    F.write(std::cout << "the determinant is ", d) << std::endl;
    return 0;
}