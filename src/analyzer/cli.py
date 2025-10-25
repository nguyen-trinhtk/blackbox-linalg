import sys
from plot import *

if __name__ == "__main__":
    # CLI usage:
    if len(sys.argv) < 4:
        print("Usage: python3 plot.py path1.csv[,path2.csv,...] x y [label1,label2,...]")
        sys.exit(1)

    paths = sys.argv[1].split(",")
    x = sys.argv[2]
    y = sys.argv[3]
    labels = sys.argv[4].split(",") if len(sys.argv) > 4 else None

    plot_csv_xy(paths, x, y, labels)