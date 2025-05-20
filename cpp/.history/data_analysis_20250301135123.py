import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import sys 


def main():
    L = 8192 # Message Length
    rates = [1.3, 1.4, 1.45, 1.6]
    errpr_type = ["SER", "MSE"]
    for err in error
    for r in rates:
        df = pd.read_csv(f"./data/mse_{r}.csv")   
        plt.plot(df[f"{errpr_type}"], label=f"{r}", ls="--")
        # plt.scatter(idx_min, min_pt, marker=".", s=200)
        # plt.xticks(range(0, mean_size, 5))
        plt.xlabel("Iteration")
        plt.ylabel("MSE")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Communication Rate",
                            loc="best", fontsize='small', fancybox=True)
    plt.xlim(0, )
    plt.title(f"""Mean Square Error (MSE) Vs number of iterations 
              """)
    plt.tight_layout()
    plt.savefig(f"./figures/mse.png")
    # plt.show()
    print(f"figure saved at: ./figures/mse.png")

if __name__=="__main__":
    main()