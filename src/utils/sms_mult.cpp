#include "sms_mult.h"
#include <fstream>
#include <iostream>
#include <vector>

// M = D * A   (D is diagonal, stored as full n×n matrix)
// All values are integers
void diagonal_scaling(int n, int q,
                      const std::string &Dfile,
                      const std::string &Afile,
                      const std::string &Mfile)
{
    std::ifstream dInputFile(Dfile);
    std::ifstream aInputFile(Afile);
    std::ofstream mOutputFile(Mfile);

    if (!dInputFile || !aInputFile || !mOutputFile) {
        std::cerr << "Error opening one of the files.\n";
        return;
    }

    int Drows, Dcols;
    dInputFile >> Drows >> Dcols;

    int Arows, Acols;
    aInputFile >> Arows >> Acols;
    std::vector<int> diag(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int value;
            dInputFile >> value;
            if (i == j) diag[i] = value;
        }
    }

    mOutputFile << std::to_string(n) + " " + std::to_string(n) + "\n";
    for (int i = 0; i < n; i++) {
        int scale = diag[i];
        for (int j = 0; j < n; j++) {
            int a;
            aInputFile >> a;
            mOutputFile << (scale * a) % q;
            if (j + 1 < n) mOutputFile << " ";
        }
        mOutputFile << "\n";
    }
}
