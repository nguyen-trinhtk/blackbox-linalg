#include <linbox/linbox-config.h>
#include <sstream>
#include <string>
#include <iostream>
#include <linbox/ring/modular.h>
#include <linbox/matrix/dense-matrix.h>
#include "mat_gen.h"

using namespace LinBox;
using namespace std;
using namespace LinBoxMatGen;

bool testMatrixPrint(const string &testName, DenseMatrix<Givaro::Modular<int>> &M, 
                     Givaro::Modular<int> &F, const string &expected)
{
    stringstream ss;
    M.write(ss, Tag::FileFormat::Maple);
    string result = ss.str();

    // remove trailing newline for comparison
    if (!result.empty() && result.back() == '\n') result.pop_back();

    if (result == expected) {
        cout << "[PASS] " << testName << endl;
        return true;
    } else {
        cout << "[FAIL] " << testName << endl;
        cout << "  Expected: " << expected << endl;
        cout << "  Got:      " << result << endl;
        return false;
    }
}

int main()
{
    typedef Givaro::Modular<int> Mod7;
    Mod7 F(7);

    // Test 1: Random 2x2 matrix
    DenseMatrix<Mod7> M1(F,2,2);
    random_matrix(M1, F);
    cout << "Random 2x2 matrix:\n";
    M1.write(cout, Tag::FileFormat::Maple) << endl;

    // Test 2: Random sparse 3x3 with sparsity 0.3
    DenseMatrix<Mod7> M2(F,3,3);
    random_sparse_matrix(M2, F, 0.3);
    cout << "Random sparse 3x3 matrix:\n";
    M2.write(cout, Tag::FileFormat::Maple) << endl;

    // Test 3: Diagonal matrix 3x3 with field elements
    DenseMatrix<Mod7> M3(F,3,3);
    random_diagonal_matrix(M3, F);
    cout << "Random diagonal 3x3 matrix:\n";
    M3.write(cout, Tag::FileFormat::Maple) << endl;

    // Test 4: Jordan block 3x3 with lambda = 2
    DenseMatrix<Mod7> M4(F,3,3);
    jordan_block(M4, F, F(2));
    string expected4 = "[ 2 1 0 ; 0 2 1 ; 0 0 2 ]";
    testMatrixPrint("Jordan 3x3 lambda=2", M4, F, expected4);

    // Test 5: Companion matrix of x^3 + 2x^2 + 1 over mod7
    DenseVector<Mod7> poly(F);
    poly.resize(3);
    poly[0] = 1; // constant
    poly[1] = 0; // x^1
    poly[2] = 2; // x^2
    DenseMatrix<Mod7> M5(F,3,3);
    companion_matrix(M5, F, poly);
    cout << "Companion matrix 3x3:\n";
    M5.write(cout, Tag::FileFormat::Maple) << endl;

    return 0;
}
