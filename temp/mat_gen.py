#!/usr/bin/env python3
import random
import argparse

# Some good small primes for GF(q)
GOOD_PRIMES = [31, 127, 257, 65537, 104729]

def generate_matrix(size: int, density: float, q: int, filename: str):
    """Generate a square sparse matrix in SMS (MatrixMarket) format over GF(q)."""
    m = n = size
    entries = []

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if random.random() < density:
                # Nonzero value in GF(q)
                val = random.randint(1, q - 1)
                entries.append((i, j, val))

    with open(filename, "w") as f:
        f.write("%%MatrixMarket matrix coordinate integer general\n")
        f.write(f"{m} {n} {len(entries)}\n")
        for (i, j, v) in entries:
            f.write(f"{i} {j} {v}\n")

    print(f"Generated {m}x{n} matrix with {len(entries)} nonzeros "
          f"({100 * density:.2f}% density) over GF({q}) → {filename}")


def main():
    parser = argparse.ArgumentParser(description="Generate a Wiedemann-style sparse matrix in SMS format.")
    parser.add_argument("--size", "-n", type=int, default=1000,
                        help="Matrix size (default: 1000 for a 1000×1000 matrix)")
    parser.add_argument("--density", "-d", type=float, default=0.02,
                        help="Fraction of nonzero entries (default: 0.02)")
    parser.add_argument("--prime", "-q", type=int, default=31,
                        help="Field modulus GF(q) (prime). Default: 31.")
    parser.add_argument("--output", "-o", type=str, default=None,
                        help="Output file name (default: auto-generated)")

    args = parser.parse_args()

    if args.prime not in GOOD_PRIMES:
        print(f"{args.prime} is not one of the recommended test primes.")
        print(f"   Try one of: {GOOD_PRIMES}")

    if args.output is None:
        args.output = f"matrix{args.size}_gf{args.prime}.sms"

    generate_matrix(args.size, args.density, args.prime, args.output)


if __name__ == "__main__":
    main()
