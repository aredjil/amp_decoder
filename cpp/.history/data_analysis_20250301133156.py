import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import sys 


def main():
    L = 8192
    rates = [1.3, 1.4, 1.45, 1.6]
    errpr_type ="SER"
    argc = len(sys.argv)
    for r in rates:
        df = pd.read_csv(f"./data/ser_{r}.csv")   
        plt.plot(df["SER"], label=f"{r}", ls="--")
        # plt.scatter(idx_min, min_pt, marker=".", s=200)
        # plt.xticks(range(0, mean_size, 5))
        plt.xlabel("Iteration")
        plt.ylabel("SER")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
        plt.legend(title="Communication Rate",
                            loc="best", fontsize='small', fancybox=True)
    plt.xlim(0, )
    plt.title(f"""Section Error Rate (SER) Vs number of iterations 
              """)
    plt.tight_layout()
    plt.savefig(f"./figures/ser.png")
    # plt.show()
    print(f"figure saved at: ./figures/ser.png")

if __name__=="__main__":
    main()