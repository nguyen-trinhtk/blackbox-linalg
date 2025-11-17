#include "preconditioner.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 10240

static int read_sms(const char* filename, int* n, int** mat) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    int lines = 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) lines++;
    rewind(f);

    *n = lines;
    *mat = (int*)malloc(sizeof(int) * (*n) * (*n));
    if (!(*mat)) { fclose(f); return -1; }

    for (int i = 0; i < *n; i++) {
        if (!fgets(line, sizeof(line), f)) { free(*mat); return -1; }
        char* token = strtok(line, " \t\n");
        for (int j = 0; j < *n; j++) {
            if (!token) { free(*mat); return -1; }
            (*mat)[i*(*n) + j] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(f);
    return 0;
}

static int write_sms(const char* filename, int n, int* mat) {
    FILE* f = fopen(filename, "w");
    if (!f) return -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) fprintf(f, "%d ", mat[i*n + j]);
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}

static void mult_mod_q(int n, int* P, int* A, int* C, int q) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i*n + j] = 0;

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            int pik = P[i*n + k];
            for (int j = 0; j < n; j++) {
                C[i*n + j] += (pik * A[k*n + j]);
                if (C[i*n + j] >= q) C[i*n + j] %= q;
            }
        }
    }
}

int multiply_precond(const char* precond_file, const char* matrix_file, int q, const char* out_dir) {
    int n1, n2;
    int *P = NULL, *A = NULL;

    if (read_sms(precond_file, &n1, &P) != 0) return -1;
    if (read_sms(matrix_file, &n2, &A) != 0) { free(P); return -1; }

    if (n1 != n2) { free(P); free(A); return -2; }

    int n = n1;
    int* C = (int*)calloc(n * n, sizeof(int));
    if (!C) { free(P); free(A); return -1; }

    mult_mod_q(n, P, A, C, q);

    const char *pname = strrchr(precond_file, '/'); pname = pname ? pname + 1 : precond_file;
    const char *aname = strrchr(matrix_file, '/'); aname = aname ? aname + 1 : matrix_file;

    char out_filename[512];
    if (out_dir)
        snprintf(out_filename, sizeof(out_filename), "%s/%d_%dx%d_%sX%s.sms", out_dir, q, n, n, pname, aname);
    else
        snprintf(out_filename, sizeof(out_filename), "%d_%dx%d_%sX%s.sms", q, n, n, pname, aname);

    int ret = write_sms(out_filename, n, C);

    free(P); free(A); free(C);
    return ret;
}
