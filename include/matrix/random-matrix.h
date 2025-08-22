#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
// Return a nxn matrix with random entries in GF(p)
namespace matrix {
    inline NTL::mat_ZZ_p random_matrix(std::size_t n, long p) {
        NTL::ZZ_p::init(NTL::ZZ(p));
        NTL::mat_ZZ_p M;
        M.SetDims(n, n);
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                M[i][j] = NTL::random_ZZ_p();
            }
        }
        return M;
    }
}