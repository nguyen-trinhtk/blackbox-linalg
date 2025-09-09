#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <vector>
#include <cmath>
#include <algorithm>

namespace wiedemann {
    inline NTL::ZZ_pX berlekamp_massey(const std::vector<NTL::ZZ_p>& sequence) {
        std::vector<NTL::ZZ_p> C = {NTL::ZZ_p(1)};
        std::vector<NTL::ZZ_p> B = {NTL::ZZ_p(1)};
        long L = 0, m = 1;
        NTL::ZZ_p b = NTL::ZZ_p(1);

        for (size_t k = 0; k < sequence.size(); ++k) {
            NTL::ZZ_p d = sequence[k];
            for (long i = 1; i <= L; ++i)
                d += C[i] * sequence[k - i];

            if (d == 0) {
                m += 1;
            } else if (2 * L <= k) {
                std::vector<NTL::ZZ_p> T = C;
                if (C.size() < m + B.size())
                    C.resize(m + B.size(), NTL::ZZ_p(0));
                for (long i = 0; i < B.size(); ++i)
                    C[i + m] -= d / b * B[i];
                L = k + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                if (C.size() < m + B.size())
                    C.resize(m + B.size(), NTL::ZZ_p(0));
                for (long i = 0; i < B.size(); ++i)
                    C[i + m] -= d / b * B[i];
                m += 1;
            }
        }
        std::reverse(C.begin(), C.end());
        while (C.size() > 1 && C[0] == 0)
            C.erase(C.begin());

        NTL::ZZ_pX minpoly;
        for (long i = 0; i < C.size(); ++i)
            NTL::SetCoeff(minpoly, i, C[i]);
        return minpoly;
    }
}