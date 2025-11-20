// take in 2 files (SMS format), write product
// usage ./multiply_matrices n_list q_list a_dir b_dir dest_dir
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "../utils/utils.h"


void apply_preconditioner(int n, int q, std::string mat_dir, std::string precond_dir, std::string dest_dir) {
    std::string file_name = std::to_string(n) + "x" + std::to_string(n) + "-" + "GF" + std::to_string(q) + ".txt";
    std::string mat_file = mat_dir + "/" + file_name;
    std::string precond_file = precond_dir + "/" + file_name;
    std::string dest_file = dest_dir + "/" + file_name;
    std::ofstream outputFile(dest_file);
    if (outputFile.is_open()) {
        outputFile << "Successfully created";
        // multiplication logic here, write to output file in .sms format
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open or create matrix file." << "\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Incorrect number of arguments.\n";
        return 1;
    }
    // args parse
    std::list<int> n_list = file_to_list(argv[1]);
    std::list<int> q_list = file_to_list(argv[2]);
    std::string mat_dir = argv[3];
    std::string precond_dir = argv[4];
    std::string dest_dir = argv[5];

    // iter through q and n
    for (std::list<int>::const_iterator n_it = n_list.begin(); n_it != n_list.end(); ++n_it) {
        for (std::list<int>::const_iterator q_it = q_list.begin(); q_it != q_list.end(); ++q_it) {
            apply_preconditioner(*n_it, *q_it, mat_dir, precond_dir, dest_dir);
        }
    }
}