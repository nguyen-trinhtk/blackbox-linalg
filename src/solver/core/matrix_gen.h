#ifndef MATGEN_H
#define MATGEN_H

#include <stdio.h>

/**
 * Generate an n x n matrix over GF(q) of a specified type and save as a .sms file.
 *
 * File name format: q_nxn_matrixtype.sms
 *
 * Parameters:
 *  - n:  matrix size (n x n)
 *  - q:  field cardinality (prime)
 *  - type: matrix type ("dense", "sparse", "diagonal", "block_diagonal",
 *           "jordan", "companion", "toeplitz")
 *  - ... : optional parameters depending on matrix type, and optional directory path
 *          If no directory provided, file is created in the current directory.
 *
 * Return:
 *  - 0 : success
 *  - -1: file creation error
 *  - -2: invalid parameters (n <= 0, nonprime q, unsupported type, etc.)
 */
int mat_gen(int n, int q, const char* type, ...);

#endif // MATGEN_H