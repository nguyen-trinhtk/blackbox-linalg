#include <iostream>
#include <list>
#include <string>
// #include "utils.h"

#include <iostream>
#include <list>
#include <string>
#include <fstream>

std::list<int> file_to_list(const std::string& file_name) {
    std::list<int> intList;
    std::ifstream inputFile(file_name);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return std::list<int>();
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            intList.push_back(std::stoi(line));
        }
    }

    return intList;
}

void print_list(const std::list<int>& lst) {
    for (const int& v : lst) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}


void generate_matrix(int n, int q, std::string dest_dir) {
    std::string file_name = std::to_string(n) + "x" + std::to_string(n) + "-" + "GF" + std::to_string(q) + ".sms";
    std::string save_path = dest_dir + "/" + file_name;
    std::ofstream outputFile(save_path);
    if (outputFile.is_open()) {
        outputFile << file_name << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to open or create matrix file." << std::endl;
    }
}


// main.cpp
int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Incorrect number of arguments.\n";
        return 1;
    }

    std::string matrix_type = argv[1];
    std::list<int> n_list = file_to_list(argv[2]);
    std::list<int> q_list = file_to_list(argv[3]);
    std::string dest_dir = argv[4];
    for (int n : n_list) {
        for (int q : q_list) {
            generate_matrix(n, q, dest_dir);
        }
    }
    // print_list(n_list);
    // print_list(q_list);
    std::cout << dest_dir << "\n";
    return 0;
}
