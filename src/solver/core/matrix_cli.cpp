#include <iostream>
#include <string>
#include <cstdlib>

extern "C" {
#include "matrix_gen.h"
#include "preconditioner.h"
}

// Helper: print usage
void print_usage() {
    std::cerr << "Usage:\n";
    std::cerr << "  ./mat_precond gen-matrix   n q mattype output_dir\n";
    std::cerr << "  ./mat_precond gen-precond  n q pctype output_dir\n";
    std::cerr << "  ./mat_precond precond-matrix precond_file matrix_file q [output_dir]\n";
}

// Convert string to int safely
int to_int(const char* str) {
    return std::atoi(str);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "gen-matrix") {
        if (argc != 6) {
            print_usage();
            return 1;
        }
        int n = to_int(argv[2]);
        int q = to_int(argv[3]);
        const char* mattype = argv[4];
        const char* output_dir = argv[5];

        if (mat_gen(n, q, mattype, output_dir) != 0) {
            std::cerr << "Error generating matrix.\n";
            return 1;
        }

    } else if (cmd == "gen-precond") {
        if (argc != 6) {
            print_usage();
            return 1;
        }
        int n = to_int(argv[2]);
        int q = to_int(argv[3]);
        const char* pctype = argv[4];
        const char* output_dir = argv[5];

        if (mat_gen(n, q, pctype, output_dir) != 0) {
            std::cerr << "Error generating preconditioner.\n";
            return 1;
        }

    } else if (cmd == "precond-matrix") {
        if (argc < 5 || argc > 6) {
            print_usage();
            return 1;
        }
        const char* precond_file = argv[2];
        const char* matrix_file = argv[3];
        int q = to_int(argv[4]);
        const char* output_dir = (argc == 6) ? argv[5] : nullptr;

        if (multiply_precond(precond_file, matrix_file, q, output_dir) != 0) {
            std::cerr << "Error applying preconditioner.\n";
            return 1;
        }

    } else {
        std::cerr << "Unknown command: " << cmd << "\n";
        print_usage();
        return 1;
    }

    return 0;
}
