#include <linbox/linbox-config.h>

#include <iostream>
#include <linbox/ring/modular.h>
#include <linbox/solutions/echelon.h>
#include <fflas-ffpack/ffpack/ffpack.h>
#include <linbox/util/timer.h>   // <-- include LinBox timer

#define COMPARE_FFPACK
using namespace LinBox;
using namespace std;

int main (int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: echelon <matrix-file-in-SMS-format> <p>" << endl;
        return -1;
    }
    ifstream input(argv[1]);
    if (!input) { cerr << "Error opening matrix file " << argv[1] << endl; return -1; }

    typedef Givaro::Modular<double> Field;
    double q = atof(argv[2]);
    Field F(q);

    DenseMatrix<Field> A(F);
    A.read(input);
    DenseMatrix<Field> E(F, A.rowdim(), A.coldim());
    cout << "A is " << A.rowdim() << " by " << A.coldim() << endl;

    // ===== LinBox timer for reducedRowEchelon =====
    LinBox::Timer chrono;
    chrono.start();
    reducedRowEchelon(E, A);
    chrono.stop();
    cout << "⏱ LinBox reducedRowEchelon time: " << chrono << endl;

#ifdef COMPARE_FFPACK
    DenseMatrix<Field> G(A);
    size_t *P = new size_t[G.rowdim()];
    size_t *Q = new size_t[G.coldim()];

    LinBox::Timer chrono_ffpack;
    chrono_ffpack.start();
    size_t r = FFPACK::ReducedRowEchelonForm(F, G.rowdim(), G.coldim(), G.getPointer(), G.coldim(), P, Q, false);
    FFPACK::getReducedEchelonForm(F, FFLAS::FflasUpper, G.rowdim(), G.coldim(), r, Q, G.getPointer(), G.coldim());
    chrono_ffpack.stop();

    cout << "⏱ FFLAS-FFPACK reduced row echelon time: " << chrono_ffpack << endl;

    if (G.coldim() < 20)
        G.write(cerr << "FFPACK::Echelon = " << endl) << endl;

    delete[] P;
    delete[] Q;
#endif

    if (E.coldim() < 20)
        E.write(cerr << "LinBox::Echelon = " << endl) << endl;

    return 0;
}
