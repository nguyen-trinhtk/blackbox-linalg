#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include "../utils/utils.h"

// generate_matrix.cpp
int random_field_element(int q) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, q - 1);
    return distrib(gen);
}

void random_dense(int n, int q, std::string dest_file) {
    std::ofstream outputFile(dest_file);
    if (outputFile.is_open()) {
        outputFile << std::to_string(n) + " " + std::to_string(n) << "\n";
        for (int r=0; r < n; r++) {
            for (int c=0; c < n; c++) {
                outputFile << std::to_string(random_field_element(q));
                if (c + 1 < n) outputFile << " ";
            }
            outputFile << "\n";
        }
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open or create matrix file." << "\n";
    }
}

void random_diagonal(int n, int q, std::string dest_file) {
    std::ofstream outputFile(dest_file);
    if (outputFile.is_open()) {
        std::string matrix_string = std::to_string(n) + " " + std::to_string(n) + "\n";
        for (int r=0; r < n; r++) {
            for (int c=0; c < r; c++) {
                matrix_string +=  "0 ";
            }
            matrix_string += std::to_string(random_field_element(q)) + " ";
            for (int c=r+1; c < n; c++) {
                matrix_string +=  "0 ";
            }
            matrix_string += "\n";
        }
        outputFile << matrix_string;
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open or create matrix file." << "\n";
    }
}

void identity(int n, int q, std::string dest_file) {
    std::ofstream outputFile(dest_file);
    if (outputFile.is_open()) {
        std::string matrix_string = std::to_string(n) + " " + std::to_string(n) + "\n";
        for (int r=0; r < n; r++) {
            for (int c=0; c < r; c++) {
                matrix_string +=  "0 ";
            }
            matrix_string += "1 ";
            for (int c=r+1; c < n; c++) {
                matrix_string +=  "0 ";
            }
            matrix_string += "\n";
        }
        outputFile << matrix_string;
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open or create matrix file." << "\n";
    }
}

void generate_matrix(std::string matrix_type, int n, int q, std::string dest_dir) {
    std::string file_name = std::to_string(n) + "x" + std::to_string(n) + "-" + "GF" + std::to_string(q) + ".txt";
    std::string dest_file = dest_dir + "/" + file_name;
    if (matrix_type=="dense") {
        random_dense(n, q, dest_file);
    }
    else if (matrix_type=="diagonal") {
        random_diagonal(n, q, dest_file);
    }
    else if (matrix_type=="identity") {
        identity(n, q, dest_file);
    }
    else {
        std::cerr << "Error: Unsupported matrix type." << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Incorrect number of arguments.\n";
        return 1;
    }

    std::string matrix_type = argv[1];
    std::list<int> n_list = file_to_list(argv[2]);
    std::list<int> q_list = file_to_list(argv[3]);
    std::string dest_dir = argv[4];
    for (std::list<int>::const_iterator n_it = n_list.begin(); n_it != n_list.end(); ++n_it) {
        for (std::list<int>::const_iterator q_it = q_list.begin(); q_it != q_list.end(); ++q_it) {
            generate_matrix(matrix_type, *n_it, *q_it, dest_dir);
        }
    }
    return 0;
}
