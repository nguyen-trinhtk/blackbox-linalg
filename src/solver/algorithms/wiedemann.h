#ifndef WIEDEMANN_H
#define WIEDEMANN_H

#include <string>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/algorithms/wiedemann.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/ring/modular.h>
#include <fstream>
#include <iostream>

namespace Wiedemann {

template <typename Field>
bool polynomial_is_zero(const LinBox::DensePolynomial<Field>& p) {
    size_t n = p.size();
    for (size_t i = 0; i < n; ++i) {
        if (p[i] != 0) return false;
    }
    return true;
}

// Performs one Wiedemann minimal polynomial trial
template <typename Field>
bool wiedemann_trial(const std::string &matrix_file, int q) {
    Field F(q);

    LinBox::SparseMatrix<Field> A(F);
    std::ifstream input(matrix_file);
    if (!input) { std::cerr << "Error opening matrix file\n"; return false; }
    A.read(input); input.close();

    if (A.rowdim() != A.coldim()) {
        std::cerr << "Matrix must be square\n";
        return false;
    }

    LinBox::DensePolynomial<Field> minP(F);
    LinBox::Method::Wiedemann method;
    LinBox::minpoly(minP, A, method);

    return !polynomial_is_zero(minP);
}

} // namespace Wiedemann

// Non-template wrapper for convenience
inline double run_wiedemann(const std::string &matrix_file, int q, int trials = 1000) {
    using Field = Givaro::Modular<int>;
    int success_count = 0;

    for (int i = 0; i < trials; ++i) {
        if (Wiedemann::wiedemann_trial<Field>(matrix_file, q))
            ++success_count;
    }

    double probability = double(success_count) / trials;
    std::cout << "Success probability: " << probability
              << " (" << success_count << "/" << trials << ")\n";

    return probability;
}

#endif // WIEDEMANN_H
