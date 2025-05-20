import pandas as pd 
import matplotlib.pyplot as plt 

def main():
    max_iter = 0
    # Read the data excluding the last line which contains the time the decodre took 
    fig, ax = plt.subplots(figsize=(16, 8))
    for i in [1.3, 1.4, 1.45, 1.5, 1.6]: #NOTE: Declar the rate in an input file  
        df_ser = pd.read_csv(f"./data/data_ser_{i}_.csv")[:-1]
        ax.plot(df_ser["Iter"], df_ser["SER"], label=f"R={i}")
        ax.set_yscale("log")
        ax.set_xlim(0, 25)
        ax.legend()  # Add legend
        plt.grid(True, which="both", ls="--") #add a grid.
    plt.show()
if __name__ =="__main__":
    main()