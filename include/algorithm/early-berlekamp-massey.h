#pragma once
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <vector>
#include <cmath>



namespace wiedemann {
    inline std::pair<NTL::ZZ_pX, long> early_berlekamp_massey(const std::vector<NTL::ZZ_p>& sequence, long c = 3) {
        long n = sequence.size() / 2;
        long q = NTL::to_long(NTL::ZZ_p::modulus());
        long omega = static_cast<long>(c * std::log(n) / std::log(q));
        std::vector<NTL::ZZ_p> C = {NTL::ZZ_p(1)};
        std::vector<NTL::ZZ_p> B = {NTL::ZZ_p(1)};
        long L = 0, m = 1, streak = 1, stop = 0;
        NTL::ZZ_p b = NTL::ZZ_p(1);

        for (long k = 0; k < sequence.size(); ++k) {
            NTL::ZZ_p d = sequence[k];
            for (long i = 1; i <= L; ++i)
                d += C[i] * sequence[k - i];

            if (d == 0) {
                m += 1;
                streak += 1;
                if (streak >= omega) {
                    stop = k;
                    break;
                }
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
                streak = 1;
            } else {
                if (C.size() < m + B.size())
                    C.resize(m + B.size(), NTL::ZZ_p(0));
                for (long i = 0; i < B.size(); ++i)
                    C[i + m] -= d / b * B[i];
                m += 1;
                streak = 1;
            }
        }
        if (!stop) stop = sequence.size();

        // Reverse and trim leading zeros
        std::reverse(C.begin(), C.end());
        while (C.size() > 1 && C[0] == 0)
            C.erase(C.begin());

        NTL::ZZ_pX minpoly;
        for (long i = 0; i < C.size(); ++i)
            NTL::SetCoeff(minpoly, i, C[i]);
        return {minpoly, stop};
    }
}