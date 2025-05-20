import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt  
import os 

def main():
    L = 16384  # Message Length
    rates = [1.3, 1.4, 1.45, 1.6]
    
    data_dir = "./data"
    figures_dir = "./figures/exp1"
    if not os.path.exists(figures_dir):
        try:
            os.mkdir(figures_dir)
        except OSError as e:
            print(f"Error creating the directory '{figures_dir}': {e}")
        if not os.path.exists(figures_dir):
            print(f"Data directory {data_dir} does not exist!")

    # Process MSE data
    plt.figure()  # Create a new figure for MSE
    for r in rates:
        data_file = os.path.join(data_dir, f"mse_{r}.csv")
        df = pd.read_csv(data_file)
        plt.plot(df["MSE"], label=f"{r}", ls="--")
        plt.xlabel("Iteration")
        plt.ylabel("MSE")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Communication Rate", loc="best", fontsize='small', fancybox=True)
    plt.xlim(0,)
    plt.title(f"Mean Square Error (MSE) Vs number of iterations")
    plt.tight_layout()
    mse_figure_path = os.path.join(figures_dir, "mse.png")
    plt.savefig(mse_figure_path)
    print(f"figure saved at: {mse_figure_path}")
    plt.close() # close figure after saving

    # Process SER data
    plt.figure()  # Create a new figure for SER
    for r in rates:
        data_file = os.path.join(data_dir, f"ser_{r}.csv")
        df = pd.read_csv(data_file)
        plt.plot(df["SER"], label=f"{r}", ls="--")
        plt.xlabel("Iteration")
        plt.ylabel("SER")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Communication Rate", loc="best", fontsize='small', fancybox=True)
    plt.xlim(0,)
    plt.title(f"Section Error Rate (SER) Vs number of iterations\n Uisng {L} sections")
    plt.tight_layout()
    ser_figure_path = os.path.join(figures_dir, "ser.png")
    plt.savefig(ser_figure_path)
    print(f"figure saved at: {ser_figure_path}")
    plt.close() # close figure after saving


if __name__=="__main__":
    main()