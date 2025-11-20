#ifndef UTILS_H
#define UTILS_H

#include <list>
#include <string>

std::list<int> file_to_list(const std::string& file_name);
void print_list(const std::list<int>& lst);

#endif // UTILS_H
