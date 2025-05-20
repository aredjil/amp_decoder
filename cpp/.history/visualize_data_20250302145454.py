import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt  
import os 
import sys 
def main():
    L = 16384  # Message Length or double 
    argc = len(sys.argv)
    for i in range(1, argc, 1):
        if sys.argv[i] == "-l" and i + 1 < argc: 
            i+=1
            L = int(sys.argv[i])
    rates = [1.3, 1.4, 1.45, 1.6]
    bs = [5, 15, 35, 45] 
    data_dir = "./data/exp3/"
    figures_dir = "./figures/exp3"
    if not os.path.exists(figures_dir):
        try:
            os.mkdir(figures_dir)
        except OSError as e:
            print(f"Error creating the directory '{figures_dir}': {e}")
        if not os.path.exists(figures_dir):
            print(f"Data directory {data_dir} does not exist!")

    # Process MSE data
    plt.figure()  # Create a new figure for MSE
    for b in bs:
        data_file = os.path.join(data_dir, f"mse_{b}.csv")
        df = pd.read_csv(data_file)
        plt.plot(df["MSE"], label=f"{b}", ls="--", lw=1.0)
        plt.xlabel("Iteration")
        plt.ylabel("MSE")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Section Size", loc="best", fontsize='small', fancybox=True)
    plt.xlim(0,)
    plt.title(f"Mean Square Error (MSE) Vs number of iterations")
    plt.tight_layout()
    mse_figure_path = os.path.join(figures_dir, "mse.png")
    plt.savefig(mse_figure_path)
    print(f"figure saved at: {mse_figure_path}")
    plt.close() # close figure after saving

    # Process SER data
    plt.figure()  # Create a new figure for SER
    for b in bs:
        data_file = os.path.join(data_dir, f"ser_{b}.csv")
        df = pd.read_csv(data_file)
        plt.plot(df["SER"], label=f"{b}", ls="--", lw=1.0)
        plt.xlabel("Iteration")
        plt.ylabel("SER")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Section Size", loc="best", fontsize='small', fancybox=True)
    plt.xlim(0,)
    plt.title(f"Section Error Rate (SER) Vs number of iterations")
    plt.tight_layout()
    ser_figure_path = os.path.join(figures_dir, "ser.png")
    plt.savefig(ser_figure_path)
    print(f"figure saved at: {ser_figure_path}")
    plt.close() # close figure after saving


if __name__=="__main__":
    main()