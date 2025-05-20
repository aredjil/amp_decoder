# import pandas as pd 
# import numpy as np 
# import matplotlib.pyplot as plt 
# import sys 

# # NOTE: Clean the code and generlize it to produce all the plots 
# def main():
#     # L = 512
#     number_of_files = 50
#     r = 1.3
#     errpr_type ="SER"
#     figname = f"ser_fig_{r}"
#     argc = len(sys.argv)
#     for i in range(1, argc):
#         if sys.argv[i] =="-n" and i + 1 < argc: 
#             i += 1 
#             number_of_files = int(sys.argv[i])
#     # L = 256
#     section_sizes = [1024, 2048, 4096]
#     ax, fig = plt.subplots(figsize=(12, 6))
#     for L in section_sizes:
#         path = f"./data/ser_{L}"
#         filename = f"ser_{L}"
#         mean_size = 0
#         combined_df = pd.DataFrame()
#         for i in range(0, number_of_files + 1, 1):
#             df = pd.read_csv(f"{path}/{filename}_{i}.csv", sep=",", dtype=np.float64)
#             mean_size += df[f"{errpr_type}"].size
#         mean_size = int(mean_size //number_of_files)
#         # print(f"The size for L = {L} is: {mean_size}")
#         # print(mean_size)
#         for i in range(0, number_of_files + 1, 1):
#             df = pd.read_csv(f"{path}/{filename}_{i}.csv", sep=",", dtype=np.float64)
#             if df[f"{errpr_type}"].size <= mean_size:
#                 combined_df = pd.concat([combined_df, df[f"{errpr_type}"]], axis=1) 
#         # print(combined_df)
#         combined_df = combined_df.mean(axis=1)
#         # idx_min = combined_df.idxmin()
#         # min_pt = combined_df.min()
#         # print(df)
#         # combined_df.to_csv(f"./processed_data/sample.csv")
#         # df = pd.read_csv(f"./processed_data/sample.csv", index_col=False)
#         # print(combined_df)
#         # plt.plot(combined_df, marker="+",  markersize=20)
#         plt.plot(combined_df, label=f"{L}", ls="--")
#         # plt.scatter(idx_min, min_pt, marker=".", s=200)
#         plt.xlim(0, )
#         plt.xticks(range(0, 30, 5))
#         plt.xlabel("Iteration")
#         plt.ylabel("SER")
#         plt.grid(True, which="both", ls="-")
#         plt.yscale("log")
#     plt.legend(title="Number of Sections",
#                     loc="best", fontsize='small', fancybox=True)
#     plt.title(f"""Section Error Rate (SER) Vs number of iterations
#               for different number of sections  
#               with a fixed communication rate R = {r}
#               and section size B = 4""")
#     plt.tight_layout()
#     plt.savefig(f"./figures/{figname}.png")
#     plt.show()

# if __name__=="__main__":
#     main()
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
import os

def main():
    number_of_files = 50
    r = 1.3
    error_type = "SER"
    figname = f"ser_fig_{r}"
    section_sizes = [1024, 2048, 4096]

    # Parse command-line arguments
    argc = len(sys.argv)
    for i in range(1, argc):
        if sys.argv[i] == "-n" and i + 1 < argc:
            number_of_files = int(sys.argv[i + 1])

    plt.figure(figsize=(12, 6))

    for L in section_sizes:
        path = f"./data/ser_{L}"
        filename = f"ser_{L}"

        # Collect lengths of all SER columns
        all_lengths = []
        for i in range(number_of_files + 1):
            filepath = os.path.join(path, f"{filename}_{i}.csv")
            if os.path.exists(filepath):
                df = pd.read_csv(filepath, sep=",", dtype=np.float64)
                all_lengths.append(len(df[error_type]))

        # Calculate the mean length
        if all_lengths:
            mean_length = int(np.mean(all_lengths))
        else:
            mean_length = 0

        # Collect and truncate dataframes
        all_dfs = []
        for i in range(number_of_files + 1):
            filepath = os.path.join(path, f"{filename}_{i}.csv")
            if os.path.exists(filepath):
                df = pd.read_csv(filepath, sep=",", dtype=np.float64)
                all_dfs.append(df[error_type][:mean_length]) # truncate to mean length

        # Combine and calculate the mean
        if all_dfs:
            combined_df = pd.concat(all_dfs, axis=1)
            mean_series = combined_df.mean(axis=1)
            plt.plot(mean_series, label=f"{L}", ls="--")

        else:
            print(f"No data found for L = {L}")

    plt.xlim(0, )
    plt.xticks(range(0, 30, 5))
    plt.xlabel("Iteration")
    plt.ylabel("SER")
    plt.grid(True, which="both", ls="-")
    plt.yscale("log")
    plt.legend(title="Number of Sections", loc="best", fontsize='small', fancybox=True)
    plt.title(f"""Section Error Rate (SER) Vs number of iterations
              for different number of sections
              with a fixed communication rate R = {r}
              and section size B = 4""")
    plt.tight_layout()
    plt.savefig(f"./figures/{figname}.png")
    plt.show()

if __name__ == "__main__":
    main()