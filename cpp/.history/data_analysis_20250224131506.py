import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
import sys 
# Conactinate the data and average the values 
def main():
    # L = 512
    # argc = len(sys.argv)
    # for i in range(1, argc):
    #     if sys.argv[i] =="-L" and i + 1 < argc: 
    #         i += 1 
    #         L = int(sys.argv[i])
    # L = 256
    section_sizes = [256, 512, 1024, 2048, 4096]
    for L in section_sizes:
        path = f"./data/data_{L}"
        mean_size = 0
        number_of_files = 50
        combined_df = pd.DataFrame()
        for i in range(0, number_of_files + 1, 1):
            df = pd.read_csv(f"{path}/data_{L}_{i}.csv", sep=",", dtype=np.float64)
            mean_size += df["SER"].size
        mean_size = int(mean_size //number_of_files)
        # print(mean_size)
        for i in range(0, 51, 1):
            df = pd.read_csv(f"{path}/data_{L}_{i}.csv", sep=",", dtype=np.float64)
            if df["SER"].size <= mean_size:
                combined_df = pd.concat([combined_df, df["SER"]], axis=1) 
        # print(combined_df)
        combined_df = combined_df.mean(axis=1)
        # print(df)
        # combined_df.to_csv(f"./processed_data/sample.csv")
        df = pd.read_csv(f"./processed_data/sample.csv", index_col=False)
        # print(combined_df)
        plt.plot(combined_df, label=f"{L}", ls="--")
        plt.xlim(0, )
        plt.xticks(range(0, 25, 5))
        plt.xlabel("Iteration")
        plt.ylabel("Section Error Rate")
        plt.grid(True, ls="--")
        plt.legend(loc="best")
        plt.yscale("log")
    plt.legend(handles=[one, two, three], title="title",
                    loc=4, fontsize='small', fancybox=True)
    plt.title("Section Error Rate (SER) Vs Iterations")
    plt.savefig("./sample_fig.png")
    plt.show()
if __name__=="__main__":
    main()