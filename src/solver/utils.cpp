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