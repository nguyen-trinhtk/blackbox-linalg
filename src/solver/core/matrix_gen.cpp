#include "matrix_gen.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

/* ------------ internal helper prototypes ------------ */
static int gen_dense(int n, int q, FILE* f, va_list args);
static int gen_sparse(int n, int q, FILE* f, va_list args);
static int gen_diagonal(int n, int q, FILE* f, va_list args);
static int gen_block_diagonal(int n, int q, FILE* f, va_list args);
static int gen_jordan(int n, int q, FILE* f, va_list args);
static int gen_companion(int n, int q, FILE* f, va_list args);
static int gen_toeplitz(int n, int q, FILE* f, va_list args);
static int is_prime(int q);

/* ------------ main entry ------------ */
int mat_gen(int n, int q, const char* type, ...) {
    if (n <= 0 || q <= 1 || !is_prime(q) || !type) return -2;

    va_list args;
    va_start(args, type);

    const char* directory = NULL;
    const char* next = va_arg(args, const char*);
    if (next && strchr(next, '/'))
        directory = next;
    else
        va_end(args), va_start(args, type);

    char filename[256];
    snprintf(filename, sizeof(filename), "%d_%dx%d_%s.sms", q, n, n, type);

    char filepath[512];
    if (directory)
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    else
        snprintf(filepath, sizeof(filepath), "%s", filename);

    FILE* f = fopen(filepath, "w");
    if (!f) {
        va_end(args);
        return -1;
    }

    srand((unsigned)time(NULL));

    int result = 0;
    if (strcmp(type, "dense") == 0) result = gen_dense(n, q, f, args);
    else if (strcmp(type, "sparse") == 0) result = gen_sparse(n, q, f, args);
    else if (strcmp(type, "diagonal") == 0) result = gen_diagonal(n, q, f, args);
    else if (strcmp(type, "block_diagonal") == 0) result = gen_block_diagonal(n, q, f, args);
    else if (strcmp(type, "jordan") == 0) result = gen_jordan(n, q, f, args);
    else if (strcmp(type, "companion") == 0) result = gen_companion(n, q, f, args);
    else if (strcmp(type, "toeplitz") == 0) result = gen_toeplitz(n, q, f, args);
    else result = -2;

    fclose(f);
    va_end(args);
    return result;
}

/* ------------ helper implementations ------------ */

static int gen_dense(int n, int q, FILE* f, va_list args) {
    int** custom_matrix = va_arg(args, int**); // optional
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = (custom_matrix) ? custom_matrix[i][j] % q : rand() % q;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    return 0;
}

static int gen_sparse(int n, int q, FILE* f, va_list args) {
    double density = 0.01;
    double* density_ptr = va_arg(args, double*);
    if (density_ptr) density = *density_ptr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = ((double)rand() / RAND_MAX) < density ? rand() % q : 0;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    return 0;
}

static int gen_diagonal(int n, int q, FILE* f, va_list args) {
    int* diag_values = va_arg(args, int*);
    int count = va_arg(args, int);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = 0;
            if (i == j) {
                if (diag_values) {
                    val = diag_values[(i < count) ? i : count - 1] % q;
                    if (val == 0) val = 1; // avoid zero
                } else {
                    val = (rand() % (q - 1)) + 1; // random from 1..q-1
                }
            }
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    return 0;
}

static int gen_block_diagonal(int n, int q, FILE* f, va_list args) {
    int num_blocks = va_arg(args, int);
    int* blocks = va_arg(args, int*);
    if (num_blocks <= 0 || !blocks) return -2;

    int block_size = n / num_blocks;
    for (int bi = 0; bi < num_blocks; bi++) {
        for (int i = 0; i < block_size; i++) {
            for (int bj = 0; bj < num_blocks; bj++) {
                for (int j = 0; j < block_size; j++) {
                    int val = (bi == bj)
                        ? blocks[bi * block_size * block_size + i * block_size + j] % q
                        : 0;
                    fprintf(f, "%d ", val);
                }
            }
            fprintf(f, "\n");
        }
    }
    return 0;
}

static int gen_jordan(int n, int q, FILE* f, va_list args) {
    int eigen_value = va_arg(args, int);
    if (eigen_value < 0) eigen_value = rand() % q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = 0;
            if (i == j) val = eigen_value % q;
            else if (i == j - 1) val = 1;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    return 0;
}

static int gen_companion(int n, int q, FILE* f, va_list args) {
    int* poly_coeffs = va_arg(args, int*);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = 0;
            if (i < n - 1 && j == i + 1) val = 1;
            else if (i == n - 1) val = (poly_coeffs) ? ((-poly_coeffs[j]) % q + q) % q : rand() % q;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }
    return 0;
}

static int gen_toeplitz(int n, int q, FILE* f, va_list args) {
    int* first_row = va_arg(args, int*);
    int* first_col = va_arg(args, int*);

    if (!first_row || !first_col) {
        first_row = (int*)malloc(n * sizeof(int));
        first_col = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            first_row[i] = rand() % q;
            first_col[i] = (i == 0) ? first_row[0] : rand() % q;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = (j >= i) ? first_row[j - i] % q : first_col[i - j] % q;
            fprintf(f, "%d ", val);
        }
        fprintf(f, "\n");
    }

    free(first_row);
    free(first_col);
    return 0;
}

/* ------------ helpers ------------ */
static int is_prime(int q) {
    if (q <= 1) return 0;
    if (q <= 3) return 1;
    if (q % 2 == 0 || q % 3 == 0) return 0;
    for (int i = 5; i * i <= q; i += 6)
        if (q % i == 0 || q % (i + 2) == 0) return 0;
    return 1;
}