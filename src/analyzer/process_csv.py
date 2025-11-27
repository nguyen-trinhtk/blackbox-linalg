import os
import sys
import pandas as pd

if __name__=="__main__":
    csv_path = sys.argv[1]
    df = pd.read_csv(csv_path)
    cols = ["precond?", "n", "q", "trial", "success"]
    df[cols] = df[cols].astype(int)
    df_sorted = df.sort_values(by=cols)
    df_sorted = df_sorted[cols]
    df_sorted.to_csv(csv_path, index=False)
