from plot import Plot
import sys
import pandas as pd
import os
if __name__=="__main__":
    # TODO: error handling
    # python3 main.py path n [optional: title]
    csv_path = sys.argv[1]
    varying = sys.argv[2]
    dest = sys.argv[3]
    varying = "n"
    if len(sys.argv) > 4:
        title = sys.argv[4]
    else:
        title = "Plot Title"
    plotter = Plot(xlabel=varying,ylabel="Probability",title=title)
    df = pd.read_csv(csv_path)
    length = len(df)
    # add nonprecond plot
    og_x = []
    og_y = []
    for i in range(length//2):
        og_x.append(df.iloc[i][varying])
        og_y.append(df.iloc[i]["success"])
    plotter.addLine(label="Original", abscissas=og_x,ordinates=og_y)
    # add precond plot
    precond_x = []
    precond_y = []
    for i in range(length//2, length):
        precond_x.append(df.iloc[i][varying])
        precond_y.append(df.iloc[i]["success"])
    plotter.addLine(label="Preconditioned", abscissas=precond_x,ordinates=precond_y)
    
    # plot & save
    plotter.plotAll(dest)