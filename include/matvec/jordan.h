#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <random>

namespace matvec {
    inline NTL::mat_ZZ_p jordan_matrix(std::size_t n, long p, const NTL::ZZ_p* eigenval = nullptr) {
        NTL::ZZ_p::init(NTL::ZZ(p));
        NTL::mat_ZZ_p M;
        M.SetDims(n, n);
        NTL::ZZ_p lambda = eigenval ? *eigenval : NTL::random_ZZ_p();
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                if (i == j)
                    M[i][j] = lambda;
                else if (j == i + 1)
                    M[i][j] = NTL::ZZ_p(1);
                else
                    M[i][j] = NTL::ZZ_p(0);
            }
        }
        return M;
    }
}