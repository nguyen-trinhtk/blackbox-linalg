import pandas as pd
import numpy as np
from plot import plot_csv_xy
import os

def compare_csvs(emp_csv, theor_csv, x, y, label=None, plot=True):
    """
    Compare empirical vs theoretical CSV data on given x, y columns.
    
    Args:
        emp_csv (str): Path to empirical CSV file
        theor_csv (str): Path to theoretical CSV file
        x (str): Key for x-axis
        y (str): Key for y-values (used to get y_emp and y_theor)
        label (str, optional): Plot label/title
        plot (bool, optional): Whether to show plot. Default True.
    """
    # --- Check files exist ---
    for path in [emp_csv, theor_csv]:
        if not os.path.exists(path):
            raise FileNotFoundError(f"File not found: {path}")

    # --- Read CSVs ---
    emp_df = pd.read_csv(emp_csv)
    theor_df = pd.read_csv(theor_csv)

    # --- Validate keys ---
    for key, df_name in [(x, "empirical"), (y, "empirical"), (x, "theoretical"), (y, "theoretical")]:
        df = emp_df if df_name == "empirical" else theor_df
        if key not in df.columns:
            raise KeyError(f"Column '{key}' not found in {df_name} CSV. Available: {list(df.columns)}")

    # --- Rename to align ---
    emp_df = emp_df[[x, y]].rename(columns={y: "y_emp"})
    theor_df = theor_df[[x, y]].rename(columns={y: "y_theor"})

    # --- Merge on x ---
    merged = pd.merge(emp_df, theor_df, on=x, how="inner")

    if merged.empty:
        raise ValueError("No overlapping x values between the two CSV files.")

    # --- Compute Metrics ---
    mae = np.mean(np.abs(merged["y_emp"] - merged["y_theor"]))
    rmse = np.sqrt(np.mean((merged["y_emp"] - merged["y_theor"]) ** 2))

    print(f"MAE  = {mae:.6f}")
    print(f"RMSE = {rmse:.6f}")

    if plot:
        plot_csv_xy([emp_csv, theor_csv], x, y, labels=[f"{label} Empirical" if label else "Empirical", f"{label} Theoretical" if label else "Theoretical"])

    return mae, rmse
