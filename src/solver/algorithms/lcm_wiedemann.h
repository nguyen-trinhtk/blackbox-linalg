#ifndef LCM_WIEDEMANN_H
#define LCM_WIEDEMANN_H

#include <string>

// Runs the LCM Wiedemann experiment on a given matrix over GF(q).
// Returns the average number of iterations (excluding failed trials).
double run_lcm_wiedemann(const std::string &matrix_file, int q, int trials = 1000);

#endif
