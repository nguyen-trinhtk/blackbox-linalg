#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <random>
// Return a random Jordan nxn matrix over GF(p)
namespace matrix {
    inline NTL::mat_ZZ_p diagonal_matrix(std::size_t n, long p, const std::vector<NTL::ZZ_p>* diag_entries = nullptr) {
        NTL::ZZ_p::init(NTL::ZZ(p));
        NTL::mat_ZZ_p M;
        M.SetDims(n, n);
        for (std::size_t i = 0; i < n; ++i) {
            if (diag_entries && i < diag_entries->size())
                M[i][i] = (*diag_entries)[i];
            else
                M[i][i] = NTL::random_ZZ_p();
        }
        return M;
    }
}