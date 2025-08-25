
#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <vector>
#include "matvec/all.h"
#include "algorithm/berlekamp-massey.h"

namespace wiedemann {
    inline NTL::ZZ_pX wiedemann(const NTL::mat_ZZ_p& A, const NTL::vec_ZZ_p* v_in = nullptr) {
        long n = A.NumRows();
        NTL::vec_ZZ_p u = matvec::random_vector(n, NTL::to_long(NTL::ZZ_p::modulus()));
        NTL::vec_ZZ_p v = v_in ? *v_in : matvec::random_vector(n, NTL::to_long(NTL::ZZ_p::modulus()));

        std::vector<NTL::ZZ_p> sequence(2 * n);
        NTL::vec_ZZ_p w = v;
        for (long i = 0; i < 2 * n; ++i) {
            sequence[i] = u * w;
            w = A * w;
        }

        return berlekamp_massey(sequence);
    }

}
