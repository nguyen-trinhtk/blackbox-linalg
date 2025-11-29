import sys
import os
import pandas as pd

if __name__ == "__main__":
    input_file = sys.argv[1]
    output_file = sys.argv[2]

    df = pd.read_csv(input_file)

    cols = ["precond?", "n", "q", "trial", "success"]
    df[cols] = df[cols].astype(int)

    df_grouped = (
        df.groupby(["precond?", "n", "q"], as_index=False)
          .agg(success=("success", "mean"))
    )

    df_grouped = df_grouped.sort_values(by=["precond?", "n", "q"])
    df_grouped.to_csv(output_file, index=False)
