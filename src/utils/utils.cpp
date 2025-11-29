#include "utils.h"
#include <iostream>
#include <fstream>

std::list<int> file_to_list(const std::string& file_name) {
    std::list<int> intList;
    std::ifstream inputFile(file_name);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << file_name << "\n";
        return intList;
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
    for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
