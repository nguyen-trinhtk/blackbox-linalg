#include "lcm_wiedemann.h"

#include <linbox/linbox-config.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/algorithms/wiedemann.h>
#include <linbox/ring/modular.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <iostream>
#include <fstream>

using namespace LinBox;
using namespace std;

// Compute gcd(f, g) using Euclidean algorithm
template <typename Field>
DensePolynomial<Field> gcd_poly(const DensePolynomial<Field>& f,
                                const DensePolynomial<Field>& g) {
    Field F = f.field();
    DensePolynomial<Field> a = f;
    DensePolynomial<Field> b = g;
    while (!b.isZero()) {
        DensePolynomial<Field> r(F);
        a.divideBy(r, b); // r = a % b
        a = b;
        b = r;
    }
    if (!a.isZero()) {
        Field lc = a[a.size() - 1];
        a *= F.inv(lc); // make monic
    }
    return a;
}

// Compute lcm(f, g) = (f * g) / gcd(f, g)
template <typename Field>
DensePolynomial<Field> lcm_poly(const DensePolynomial<Field>& f,
                                const DensePolynomial<Field>& g) {
    Field F = f.field();
    DensePolynomial<Field> gcdFG = gcd_poly(f, g);
    if (gcdFG.isZero())
        return DensePolynomial<Field>::Zero(F);

    DensePolynomial<Field> prod = f * g;
    DensePolynomial<Field> lcm(F);
    prod.divideBy(lcm, gcdFG); // lcm = (f*g)/gcd
    return lcm;
}

// Performs a single LCM Wiedemann trial; returns number of iterations or -1 if failed
template <typename Field>
int lcm_wiedemann_trial(const std::string &matrix_file, int q, int max_iter = 100) {
    Field F(q);

    SparseMatrix<Field> A(F);
    ifstream input(matrix_file);
    if (!input) {
        cerr << "Error opening matrix file: " << matrix_file << endl;
        return -1;
    }
    A.read(input);
    input.close();

    if (A.rowdim() != A.coldim()) {
        cerr << "Matrix must be square." << endl;
        return -1;
    }

    DensePolynomial<Field> lcmP(F);
    lcmP = DensePolynomial<Field>::One(F);
    int iter_count = 0;

    for (; iter_count < max_iter; ++iter_count) {
        DensePolynomial<Field> minP(F);

        Method::Wiedemann method;
        method.shapeFlags = Shape::Scalar;
        method.earlyTerminationThreshold = 1;

        minpoly(minP, A, RingCategories::Modular, method);
        lcmP = lcm_poly(lcmP, minP);

        SparseMatrix<Field> result(F);
        polyEval(result, lcmP, A);

        if (result.isZero()) {
            return iter_count + 1;
        }
    }

    return -1; // failed
}

double run_lcm_wiedemann_experiment(const std::string &matrix_file, int q, int trials) {
    int total_iters = 0;
    int success_count = 0;
    int fail_count = 0;

    for (int t = 0; t < trials; ++t) {
        int iters = lcm_wiedemann_trial<Givaro::Modular<int>>(matrix_file, q);
        if (iters == -1) {
            fail_count++;
        } else {
            success_count++;
            total_iters += iters;
        }
    }

    double avg_iters = (success_count > 0) ? static_cast<double>(total_iters) / success_count : 0.0;
    double success_prob = static_cast<double>(success_count) / trials;

    cout << "Trials: " << trials << endl;
    cout << "Successes: " << success_count << ", Fails: " << fail_count << endl;
    cout << "Success probability: " << success_prob << endl;
    cout << "Average iterations (excluding fails): " << avg_iters << endl;

    return avg_iters;
}

// Main wrapper
#ifdef LCM_WIEDEMANN_MAIN
int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <matrix-file.sms> <prime-q> [trials]" << endl;
        return -1;
    }

    std::string matrix_file = argv[1];
    int q = atoi(argv[2]);
    int trials = (argc >= 4) ? atoi(argv[3]) : 1000;

    run_lcm_wiedemann_experiment(matrix_file, q, trials);
    return 0;
}
#endif
