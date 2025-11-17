// solve.cpp
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

// user requested include
#include "algorithms/all.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: solve run_dir alg_type\n";
        return 1;
    }
    fs::path run_dir = argv[1];
    std::string alg_type = argv[2];

    fs::path precond_matrix_dir = run_dir / "precond_matrix";
    fs::path results_csv = run_dir / "results.csv";

    if (!fs::exists(precond_matrix_dir) || !fs::is_directory(precond_matrix_dir)) {
        std::cerr << "precond_matrix directory not found: " << precond_matrix_dir << "\n";
        return 1;
    }

    std::ofstream out(results_csv);
    if (!out) {
        std::cerr << "Failed to open results file: " << results_csv << "\n";
        return 1;
    }

    // CSV header
    out << "q,n,res\n";

    // iterate files in precond_matrix_dir
    std::regex fname_re(R"((\d+)_([0-9]+)x\2_.*\.sms)"); // captures q and n (n like 100x100)
    for (const auto &entry : fs::directory_iterator(precond_matrix_dir)) {
        if (!entry.is_regular_file()) continue;
        std::string fname = entry.path().filename().string();

        std::smatch m;
        if (!std::regex_match(fname, m, fname_re)) {
            // try more permissive parse: look for q_nxn_...
            std::regex alt_re(R"((\d+)_([0-9]+)x([0-9]+)_.*\.sms)");
            if (std::regex_match(fname, m, alt_re)) {
                // alt_re: m[1]=q m[2]=n m[3]=n
            } else {
                std::cerr << "[solve] Skipping file (unrecognized name format): " << fname << "\n";
                continue;
            }
        }
        // attempt to extract q and n more robustly:
        // try to parse leading "<q>_<n>x<n>_"
        std::smatch m2;
        std::regex r2(R"(^(\d+)_([0-9]+)x[0-9]+_.*\.sms$)");
        if (!std::regex_search(fname, m2, r2)) {
            std::cerr << "[solve] Could not parse q/n from filename: " << fname << "\n";
            continue;
        }
        int q = std::stoi(m2[1].str());
        int n = std::stoi(m2[2].str());
        std::string fullpath = entry.path().string();

        std::cout << "[solve] Running " << alg_type << " on " << fname << " (q="<<q<<" n="<<n<<")\n";

        long long res = -1;
        bool ok = true;
        if (alg_type == "wiedemann") {
            // assumes function: long long wiedemann(const char* matrix_file, int q)
            res = run_wiedemann(fullpath.c_str(), q);
        } else if (alg_type == "lcm_wiedemann") {
            std::cout << "LCM not currently usable..." << "\n";
        } else {
            std::cerr << "Unknown algorithm type: " << alg_type << "\n";
            ok = false;
        }

        if (ok) {
            out << q << "," << n << "," << res << "\n";
            out.flush();
            std::cout << "[solve] Result for " << fname << " -> " << res << "\n";
        }
    }

    out.close();
    std::cout << "[solve] Results written to " << results_csv << "\n";
    return 0;
}
