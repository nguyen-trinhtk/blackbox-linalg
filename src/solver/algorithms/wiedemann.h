#ifndef WIEDEMANN_H
#define WIEDEMANN_H

#include <string>

// Runs the Wiedemann minimal polynomial experiment.
// Returns the empirical success probability.
double run_wiedemann(const std::string &matrix_file, int q, int trials = 1000);

#endif // WIEDEMANN_EXPERIMENT_H
