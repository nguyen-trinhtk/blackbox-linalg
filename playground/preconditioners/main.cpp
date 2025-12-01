#include <linbox/linbox-config.h>
#include <iostream>
#include <fstream>
#include <linbox/ring/modular.h>
#include <linbox/polynomial/dense-polynomial.h>
#include <linbox/solutions/minpoly.h>
#include <linbox/algorithms/wiedemann.h>
#include <linbox/util/matrix-stream.h>
#include <linbox/solutions/methods.h>

using namespace LinBox;
using namespace std;

std::string explainStatus(int status) {
    switch (status) {
        case 0: return "OK (solution found)";
        case 1: return "FAILED (algorithm failure)";
        case 2: return "SINGULAR (matrix has no inverse)";
        case 3: return "INCONSISTENT (no solution exists)";
        case 4: return "BAD_PRECONDITIONER";
        default: return "UNKNOWN STATUS";
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: main <matrix-file-in-SMS-format> <q>" << endl;
        return -1;
    }

    std::string file_name = argv[1];
    ifstream input(file_name);
    if (!input) {
        cerr << "Error opening matrix file " << argv[1] << endl;
        return -1;
    }

    long q = std::stol(argv[2]);
    typedef Givaro::Modular<double> Field;
    Field F(q);

    MatrixStream<Field> ms(F, input);
    SparseMatrix<Field> A(ms);

    DenseVector<Field> X(F, A.coldim());
    DenseVector<Field> B(F, A.rowdim());

    // B = 0
    for (auto &v : B)
        F.assign(v, 0);

    bool useRandIter = false;

    WiedemannSolver<Field> solver(F);
    int status = solver.solveNonsingular(A, X, B, useRandIter);
    cout << "Return status: " << explainStatus(status) << endl;

    return 0;
}


/*
	WiedemannSolver<Field>::solve (const Blackbox   &A,
				       Vector           &x,
				       const Vector     &b,
				       Vector           &u)
	{
		linbox_check ((x.size () == A.coldim ()) &&
			      (b.size () == A.rowdim ()));
		linbox_check (_traits.singularity != Singularity::NonSingular || A.coldim () == A.rowdim ());

		commentator().start ("Solving linear system (Wiedemann)", "WiedemannSolver::solve");

		Singularity singular = _traits.singularity;
		if (A.rowdim() != A.coldim() ) _traits.singularity = (singular = Singularity::Singular);
		ReturnStatus status = FAILED;

		unsigned int tries = (unsigned int)_traits.trialsBeforeFailure;

		size_t r = (size_t) -1;

		// Dan Roche 6-21-04 Changed this from UNKNOWN which I think was incorrect
		if (_traits.rank != Rank::Unknown)
			r = _traits.rank;

		while (status == FAILED && tries-- > 0) {
			switch (singular) {
			case Singularity::Unknown:
				{
					switch (solveNonsingular (A, x, b, true)) {
					case OK:
						status = OK;
						break;

					case FAILED:
						break;

					case SINGULAR:
						commentator().report (Commentator::LEVEL_IMPORTANT, INTERNAL_DESCRIPTION)
						<< "System found to be singular. Reverting to nonsingular solver." << std::endl;
						tries = (unsigned int)_traits.trialsBeforeFailure;
						singular = Singularity::Singular;
						break;
					default:
						throw LinboxError ("Bad return value from solveNonsingular");
					}
					break;
				}

			case Singularity::NonSingular:
				{
					switch (solveNonsingular (A, x, b, false)) {
					case OK:
						status = OK;
						break;

					case FAILED:
						break;

					case SINGULAR:
						status = SINGULAR;
						break;

					default:
						throw LinboxError ("Bad return value from solveNonsingular");
					}

					break;
				}

			case Singularity::Singular:
				{
					if (r == (size_t) -1) {
						rank (r, A);
						commentator().report (Commentator::LEVEL_IMPORTANT, INTERNAL_DESCRIPTION)
						<< "Rank of A = " << r << std::endl;
					}

					switch (solveSingular (A, x, b, u, r)) {
					case OK:
						status = OK;
						break;

					case FAILED:
						r = (size_t) -1;
						break;

					case SINGULAR:
						throw LinboxError ("solveSingular returned SINGULAR");

					default:
						break;

					case INCONSISTENT:
						status = INCONSISTENT;
					}

					break;
				}
			}
		}

		if (status == FAILED)
			commentator().report (Commentator::LEVEL_IMPORTANT, INTERNAL_DESCRIPTION)
			<< "Maximum tries exceeded with no resolution. Giving up." << std::endl;

		commentator().stop ("done", NULL, "WiedemannSolver::solve");

		return status;
	}
*/