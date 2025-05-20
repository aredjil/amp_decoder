import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import sys 

# NOTE: Clean the code and generlize it to produce all the plots 
# NOTE: Plot different code lengths per fixed block size at the same figure for a given rate  
""""
Plot each one independently 
10 for 1.4 1024 
4  for 1.4 2048 

25 for 1.3 1024 
5 for  1.3 2048 
7 for  1.3  4096

30 for 1.45 2048
25 for 1.45 1024

50 for 1.6 1024
30 for 1.6 2048
"""
def main():
    # L = 512
    number_of_files = 10
    rates = [1.3, 1.4]
    L = 8192
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
    plt.title(f"""Section Error Rate (SER) Vs number of iterations """)
    plt.tight_layout()
    plt.savefig(f"./figures/ser.png")
    # plt.show()
    print(f"figure saved at: ./figures/ser.png")

if __name__=="__main__":
    main()