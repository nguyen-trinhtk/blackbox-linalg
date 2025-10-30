// gen_precond.cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>

// user requested includes
#include "core/all.h"

namespace fs = std::filesystem;

static std::vector<std::string> split_csv(const std::string &s) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ',')) {
        if (!item.empty()) out.push_back(item);
    }
    return out;
}

int main(int argc, char** argv) {
    if (argc < 6) {
        std::cerr << "Usage: gen_precond q_list n_list dir mattype pctype\n";
        return 1;
    }

    std::string q_list_s = argv[1];
    std::string n_list_s = argv[2];
    fs::path run_dir = argv[3];
    std::string mattype = argv[4];
    std::string pctype = argv[5];

    fs::path matrix_dir = run_dir / "matrix";
    fs::path precond_dir = run_dir / "precond";
    fs::path precond_matrix_dir = run_dir / "precond_matrix";

    fs::create_directories(matrix_dir);
    fs::create_directories(precond_dir);
    fs::create_directories(precond_matrix_dir);

    auto q_list = split_csv(q_list_s);
    auto n_list = split_csv(n_list_s);

    // iterate q and n lists
    for (const auto &qstr : q_list) {
        for (const auto &nstr : n_list) {
            int q = std::stoi(qstr);
            int n = std::stoi(nstr);

            // filenames
            std::ostringstream base;
            base << q << "_" << n << "x" << n << "_" << mattype << ".sms";
            std::string matrix_fname = base.str();
            fs::path matrix_path = matrix_dir / matrix_fname;

            // 1) Generate the matrix A and save in matrix_dir
            std::cout << "[gen_precond] Generating matrix q=" << q << " n=" << n << " type=" << mattype << " -> " << matrix_path << "\n";
            // assumes mat_gen(n, q, mattype, out_dir) exists in solver/core/all.h
            // we'll call as: mat_gen(n, q, mattype, matrix_dir.string())
            if (!mat_gen(n, q, mattype.c_str(), matrix_dir.string().c_str())) {
                std::cerr << "mat_gen failed for q="<<q<<" n="<<n<<"\n";
                // continue to next but keep going
            }

            // 2) Generate the preconditioner D and store in precond_dir
            std::ostringstream pbase;
            pbase << q << "_" << n << "x" << n << "_" << pctype << ".sms";
            std::string precond_fname = pbase.str();
            fs::path precond_path = precond_dir / precond_fname;

            std::cout << "[gen_precond] Generating preconditioner q=" << q << " n=" << n << " type=" << pctype << " -> " << precond_path << "\n";
            if (!mat_gen(n, q, pctype.c_str(), precond_dir.string().c_str())) {
                std::cerr << "mat_gen failed for precond q="<<q<<" n="<<n<<"\n";
            }

            // 3) Compute P * A and write into precond_matrix_dir
            std::cout << "[gen_precond] Multiplying preconditioner * matrix -> precond_matrix\n";
            // expects multiply_precond(precond_file, matrix_file, q, out_dir)
            if (!multiply_precond(precond_path.string().c_str(), matrix_path.string().c_str(), q, precond_matrix_dir.string().c_str())) {
                std::cerr << "multiply_precond failed for q="<<q<<" n="<<n<<"\n";
            }

            // For consistent naming, you may want to copy/rename the produced file to include both types
            // but we assume multiply_precond writes a sensible filename into precond_matrix_dir.
        }
    }

    std::cout << "[gen_precond] Done.\n";
    return 0;
}
