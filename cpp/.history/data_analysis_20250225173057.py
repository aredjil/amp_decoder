import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import sys 
# Conactinate the data and average the values 
def main():
    # L = 512
    number_of_files = 50
    r = 1.3
    errpr_type ="MSE"
    argc = len(sys.argv)
    for i in range(1, argc):
        if sys.argv[i] =="-n" and i + 1 < argc: 
            i += 1 
            number_of_files = int(sys.argv[i])
    # L = 256
    section_sizes = [2048, 4096, 8192]
    ax, fig = plt.subplots(figsize=(12, 8))
    for L in section_sizes:
        path = f"./data/data_{L}"
        mean_size = 0
        combined_df = pd.DataFrame()
        for i in range(0, number_of_files + 1, 1):
            df = pd.read_csv(f"{path}/data_{L}_{i}.csv", sep=",", dtype=np.float64)
            mean_size += df[f"{errpr_type}"].size
        mean_size = int(mean_size //number_of_files)
        # print(mean_size)
        for i in range(0, number_of_files + 1, 1):
            df = pd.read_csv(f"{path}/data_{L}_{i}.csv", sep=",", dtype=np.float64)
            if df[f"{errpr_type}"].size <= mean_size:
                combined_df = pd.concat([combined_df, df[f"{errpr_type}"]], axis=1) 
        # print(combined_df)
        combined_df = combined_df.mean(axis=1)
        # idx_min = combined_df.idxmin()
        # min_pt = combined_df.min()
        # print(df)
        # combined_df.to_csv(f"./processed_data/sample.csv")
        # df = pd.read_csv(f"./processed_data/sample.csv", index_col=False)
        # print(combined_df)
        # plt.plot(combined_df, marker="+",  markersize=20)
        plt.plot(combined_df, label=f"{L}", ls="--")
        # plt.scatter(idx_min, min_pt, marker=".", s=200)
        plt.xlim(0, )
        plt.xticks(range(0, 30, 5))
        plt.xlabel("Iteration")
        plt.ylabel("SER")
        plt.grid(True, which="both", ls="-")
        plt.yscale("log")
    plt.legend(title="Number of Sections",
                    loc="best", fontsize='small', fancybox=True)
    plt.title(f"""Section Error Rate (SER) Vs number of iterations
              for different number of sections  
              with a fixed communication rate R = {r}
              and section size B = 4""")
    plt.tight_layout()
    plt.savefig(f"./figures/ser_fig_{r}.png")
    plt.show()
if __name__=="__main__":
    main()