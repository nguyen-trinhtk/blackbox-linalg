#ifndef PRECOND_MULT_H
#define PRECOND_MULT_H

#include <stdio.h>

/**
 * Multiply a preconditioner matrix by a matrix: P * A over GF(q)
 *
 * Parameters:
 *  - precond_file: path to the preconditioner .sms file
 *  - matrix_file: path to the original matrix .sms file
 *  - q: field size (prime)
 *  - out_dir: optional output directory (NULL = current dir)
 *
 * Returns:
 *  - 0 : success
 *  - -1: file read/write error
 *  - -2: size mismatch
 */
int multiply_precond(const char* precond_file, const char* matrix_file, int q, const char* out_dir);

#endif // PRECOND_MULT_H
