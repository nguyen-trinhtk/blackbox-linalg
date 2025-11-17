import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_csv_xy(path_to_csv, x, y, label="Plot"):
    """
    Plot y vs x from a single CSV file and save the figure to the CSV's parent directory.

    Args:
        path_to_csv (str): Path to the CSV file.
        x (str): Column name for x-axis.
        y (str): Column name for y-axis.
    """
    if not os.path.exists(path_to_csv):
        raise FileNotFoundError(f"CSV file not found: {path_to_csv}")

    # Read CSV
    try:
        df = pd.read_csv(path_to_csv)
    except Exception as e:
        raise ValueError(f"Error reading CSV '{path_to_csv}': {e}")

    # Validate columns
    if x not in df.columns:
        raise KeyError(f"Column '{x}' not found in {path_to_csv}. Available: {list(df.columns)}")
    if y not in df.columns:
        raise KeyError(f"Column '{y}' not found in {path_to_csv}. Available: {list(df.columns)}")

    # Plot
    plt.figure(figsize=(8, 6))
    plt.plot(df[x], df[y], marker='o', label=label)
    plt.xlabel(x)
    plt.ylabel(y)
    plt.title(f"{y} vs {x}")
    plt.ylim(0, 1.1)  # <-- fixed y-axis range
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    # Save figure
    parent_dir = os.path.dirname(os.path.abspath(path_to_csv))
    save_path = os.path.join(parent_dir, f"{os.path.splitext(os.path.basename(path_to_csv))[0]}_{y}_vs_{x}.png")
    plt.savefig(save_path)
    print(f"Figure saved to: {save_path}")

    # Show plot
    plt.show()


if __name__ == "__main__":
    import sys, traceback

    def usage():
        print("Usage: plot.py <path_to_csv> <x_column> <y_column> [label]")

    try:
        if len(sys.argv) < 4:
            usage()
            sys.exit(1)

        path = sys.argv[1]
        xcol = sys.argv[2]
        ycol = sys.argv[3]
        lab = sys.argv[4] if len(sys.argv) > 4 else "Plot"

        # Try to use a non-interactive backend when running headless
        try:
            import matplotlib
            if os.environ.get('DISPLAY','') == '':
                matplotlib.use('Agg')
        except Exception:
            pass

        plot_csv_xy(path, xcol, ycol, lab)
    except Exception:
        traceback.print_exc()
        sys.exit(2)
