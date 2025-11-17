#include "wiedemann.h"
#include <string>
#include <iostream>

#ifdef WIEDEMANN_MAIN
int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <matrix-file.sms> <prime-q> [trials]\n";
        return -1;
    }

    std::string matrix_file = argv[1];
    int q = std::atoi(argv[2]);
    int trials = (argc >= 4) ? std::atoi(argv[3]) : 1000;

    // Call the wrapper function
    run_wiedemann(matrix_file, q, trials);

    return 0;
}
#endif
