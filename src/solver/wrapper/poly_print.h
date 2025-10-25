#include <iostream>
#include <linbox/linbox-config.h>

template <class Field, class Polynomial>
std::ostream& polyPrint(std::ostream& out, const Field &F, const Polynomial &v)
{
    bool first = true;
    for (int i = (int)v.size() - 1; i >= 0; --i) {
        if (v[(size_t)i] != F.zero()) {
            if (!first)
                out << " + ";


            F.write(out, v[(size_t)i]);

            // Print variable
            if (i > 0) {
                out << "x";
                if (i > 1)
                    out << "^" << i;
            }

            first = false;
        }
    }

    if (first)
        out << "0";

    return out;
}
