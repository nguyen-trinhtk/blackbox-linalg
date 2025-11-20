import sys, os

def dense_to_sms(infile, outfile=None):
    if outfile is None:
        outfile = infile.rsplit('.', 1)[0] + '.sms'

    with open(infile, 'r') as f:
        lines = f.readlines()

    # First line: n n nnz
    n_rows, n_cols = map(int, lines[0].split())
    entries = []

    # Read matrix and collect nonzero entries
    for i, line in enumerate(lines[1:]):
        for j, val in enumerate(map(int, line.split())):
            if val != 0:
                # SMS uses 1-based indexing
                entries.append((i+1, j+1, val))

    # Write SMS format
    with open(outfile, 'w') as f:
        f.write("%%MatrixMarket matrix coordinate integer general\n")
        f.write(f"{n_rows} {n_cols} {len(entries)}\n")
        for i, j, val in entries:
            f.write(f"{i} {j} {val}\n")

    # print(f"Converted {infile} -> {outfile}, nnz={len(entries)}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python convert.py run_dir")
        sys.exit(1)

    run_dir = sys.argv[1]

    for root, dirs, files in os.walk(run_dir):
        if 'fin' in dirs:
            fin_dir = os.path.join(root, 'fin')
            for file in os.listdir(fin_dir):
                if file.endswith('.txt'):
                    mat_file = os.path.join(fin_dir, file)
                    dense_to_sms(mat_file)
                    
        if 'matrix' in dirs:
            matrix_dir = os.path.join(root, 'matrix')
            for file in os.listdir(matrix_dir):
                if file.endswith('.txt'):
                    mat_file = os.path.join(matrix_dir, file)
                    dense_to_sms(mat_file)
