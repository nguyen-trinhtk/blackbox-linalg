#include "wiedemann.h"

#include <linbox/linbox-config.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/algorithms/wiedemann.h>
#include <linbox/ring/modular.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <iostream>
#include <fstream>

using namespace LinBox;
using namespace std;

template <typename Field>
bool wiedemann_trial(const std::string &matrix_file, int q) {
    Field F(q);  // Modular field GF(q)

    // Read sparse matrix from SMS file
    SparseMatrix<Field> A(F);
    ifstream input(matrix_file);
    if (!input) {
        cerr << "Error opening matrix file: " << matrix_file << endl;
        return false;
    }
    A.read(input);
    input.close();

    if (A.rowdim() != A.coldim()) {
        cerr << "Matrix must be square for scalar Wiedemann." << endl;
        return false;
    }

    DensePolynomial<Field> minP(F);
    Method::Wiedemann method;
    method.shapeFlags = Shape::Scalar;

    // Compute minimal polynomial
    minpoly(minP, A, RingCategories::Modular, method);

    return !minP.isZero();
}

double run_wiedemann(const std::string &matrix_file, int q, int trials) {
    int success_count = 0;

    for (int i = 0; i < trials; ++i) {
        bool result = wiedemann_trial<Givaro::Modular<int>>(matrix_file, q);
        if (result) ++success_count;
    }

    double probability = static_cast<double>(success_count) / trials;
    cout << "Success probability: " << probability << " ("
         << success_count << "/" << trials << ")" << endl;

    return probability;
}

// Main wrapper
#ifdef WIEDEMANN_MAIN
int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <matrix-file.sms> <prime-q> [trials]" << endl;
        return -1;
    }

    std::string matrix_file = argv[1];
    int q = atoi(argv[2]);
    int trials = (argc >= 4) ? atoi(argv[3]) : 1000;

    run_wiedemann_experiment(matrix_file, q, trials);
    return 0;
}
#endif
