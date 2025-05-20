import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 
def main():
    # Read the data excluding the last line which contains the time the decodre took 
    fig, ax = plt.subplots(ncols=2, nrows=1, figsize=(16, 8))
    for i in [1.3, 1.4, 1.45, 1.5, 1.6]: 
        df_ser = pd.read_csv(f"./data/data_ser_{i}_.csv")[:-1]
        df_mse = pd.read_csv(f"./data/data_mse_{i}_.csv")[:-1]
        # Plot the section error rate on the left column
        ax[0].plot(df_ser["Iter"], df_ser["SER"], label=f"R={i}")
        ax[0].set_ylabel("SER")
        ax[0].set_xlabel("Iteration")
        ax[0].set_yscale("log")
        ax[0].set_xlim(0, int(df_ser["Iter"].size))
        # ax[0].set_xticks(range(0, int(df_ser["Iter"].size), 3))
        ax[0].legend()  # Add legend
        ax[0].grid(True, ls="--") #add a grid.
        ax[0].set_title("Section Error Rate (SER) vs Iteration")
        # Plot the Mean Square Error on the right column
        ax[1].plot(df_mse["Iter"], df_mse["MSE"], label=f"R={i}")
        ax[1].set_ylabel("MSE")
        ax[1].set_xlabel("Iteration")
        ax[1].set_yscale("log")
        # ax[1].set_xlim(0, int(df_mse["Iter"].size))
        # ax[1].set_xticks(range(0, int(df_mse["Iter"].size), 3))
        ax[1].legend()  # Add legend
        ax[1].grid(True, ls="--") #add a grid.
        ax[1].set_title("Mean Square Error (MSE) vs Iteration")
    plt.tight_layout()
    plt.show()
if __name__ =="__main__":
    main()