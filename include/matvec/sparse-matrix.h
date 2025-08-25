#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <random>

namespace matvec {
    inline NTL::mat_ZZ_p sparse_matrix(std::size_t n, long p, double density = 0.1) {
        NTL::ZZ_p::init(NTL::ZZ(p));
        NTL::mat_ZZ_p M;
        M.SetDims(n, n);
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> prob(0.0, 1.0);
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = 0; j < n; ++j) {
                    if (prob(gen) < density)
                        M[i][j] = NTL::random_ZZ_p();
                else
                    M[i][j] = NTL::ZZ_p(0);
            }
        }
        return M;
    }
}