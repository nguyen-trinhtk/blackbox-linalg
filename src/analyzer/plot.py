import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_csv_xy(paths_to_csv, x, y, labels=None):
    """
    Plot y vs x from one or multiple CSV files.

    Args:
        paths_to_csv (list[str]): List of CSV file paths.
        x (str): Column name for x-axis.
        y (str): Column name for y-axis.
        labels (list[str], optional): List of labels for each CSV line.
    """
    if not isinstance(paths_to_csv, (list, tuple)):
        raise TypeError("paths_to_csv must be a list or tuple of CSV file paths")

    plt.figure(figsize=(8, 6))

    for i, path in enumerate(paths_to_csv):
        if not os.path.exists(path):
            raise FileNotFoundError(f"CSV file not found: {path}")

        try:
            df = pd.read_csv(path)
        except Exception as e:
            raise ValueError(f"Error reading CSV '{path}': {e}")

        if x not in df.columns:
            raise KeyError(f"Column '{x}' not found in {path}. Available: {list(df.columns)}")
        if y not in df.columns:
            raise KeyError(f"Column '{y}' not found in {path}. Available: {list(df.columns)}")

        label = None
        if labels and i < len(labels):
            label = labels[i]
        else:
            # Default label is filename without extension
            label = os.path.splitext(os.path.basename(path))[0]

        plt.plot(df[x], df[y], marker='o', label=label)

    plt.xlabel(x)
    plt.ylabel(y)
    plt.title(f"{y} vs {x}")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()
