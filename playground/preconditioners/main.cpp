#include <linbox/linbox-config.h>
#include <regex>
#include <iostream>
#include <fstream>
#include <linbox/ring/modular.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/solutions/minpoly.h>
#include <linbox/algorithms/wiedemann.h>
using namespace LinBox;
using namespace std;

int main(int argc, char **argv)
{
    // read args
    if (argc != 3) {
        cerr << "Usage: main <matrix-file-in-SMS-format>" <q><< endl;
        return -1;
    }
    std::string file_name = argv[1];

    ifstream input(file_name);
    if (!input) {
        cerr << "Error opening matrix file " << argv[1] << endl;
        return -1;
    }

    long q = std::stol(argv[2]);
    Givaro::Modular<int> F(q);
    SparseMatrix<Givaro::Modular<int>> A(F);
    A.read(input);
    // turn A into blackbox?
    Vector x; // reference to solutions
    Vector b = 0; // nullspace
    bool useRandIter = true; // test both

    // WiedemannSolver<Field>::solveNonsingular (const Blackbox &A,
    // Vector &x,
    // const Vector &b,
    // bool useRandIter)

    // it will return RETURN STATUS, print it for debugging/exp
    return 0;
}