#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include "algorithm/early-berlekamp-massey.h"
#include "matvec/all.h"

namespace wiedemann {
    inline std::pair<NTL::ZZ_pX, long> early_wiedemann(const NTL::mat_ZZ_p& A, const NTL::vec_ZZ_p* v_in = nullptr) {
        long n = A.NumRows();
        NTL::vec_ZZ_p u = matvec::random_vector(n, NTL::to_long(NTL::ZZ_p::modulus()));
        NTL::vec_ZZ_p v = v_in ? *v_in : matvec::random_vector(n, NTL::to_long(NTL::ZZ_p::modulus()));

        std::vector<NTL::ZZ_p> sequence(2 * n);
        NTL::vec_ZZ_p w = v;
        for (long i = 0; i < 2 * n; ++i) {
            sequence[i] = u * w;
            w = A * w;
        }
        return early_berlekamp_massey(sequence);
    }

}
