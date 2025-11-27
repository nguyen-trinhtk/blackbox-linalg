#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <linbox/ring/modular.h>
#include <linbox/matrix/sparse-matrix.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/solutions/minpoly.h>

using namespace LinBox;

// Solve one trial using a fresh stream
int solve(long q, std::istream &input_stream) {
    Givaro::Modular<int> F(q);
    SparseMatrix<Givaro::Modular<int>> B(F);
    B.read(input_stream);

    DensePolynomial<Givaro::Modular<int>> m_exact(F);
    DensePolynomial<Givaro::Modular<int>> m_wied(F);

    minpoly(m_exact, B, Method::Elimination());
    minpoly(m_wied, B, Method::Wiedemann());

    return (m_exact == m_wied) ? 1 : 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: run_wiedemann <matrix-file-in-SMS-format>" << std::endl;
        return -1;
    }

    std::string file_name = argv[1];
    std::ifstream file_input(file_name);
    if (!file_input) {
        std::cerr << "Error opening matrix file " << file_name << std::endl;
        return -1;
    }

    std::stringstream buffer;
    buffer << file_input.rdbuf();
    std::string matrix_data = buffer.str();  // store data for reuse

    std::regex re("GF(\\d+)");
    std::smatch match;
    long q = 0;
    if (std::regex_search(file_name, match, re)) {
        q = std::stol(match[1].str());
    } else {
        std::cerr << "Could not find GF(q) in filename!" << std::endl;
        return -1;
    }

    int success = 0;
    int trials = 100;  // adjustable
    for (int i = 0; i < trials; i++) {
        std::stringstream trial_input(matrix_data);  // fresh stream per trial
        success += solve(q, trial_input);
    }

    // std::cout << "Successes: " << success << "/" << trials << std::endl;
    // std::cout << std::endl;
    return success;
}
