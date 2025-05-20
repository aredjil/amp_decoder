import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 
# Conactinate the data and average the values 
def main():
    path = "./data/data_1024"
    mean_size = 0
    combined_df = pd.DataFrame()
    for i in range(0, 101, 1):
        df = pd.read_csv(f"{path}/data_1024_{i}.csv", sep=",", dtype=np.float64)
        mean_size += df["SER"].size
    mean_size = int(mean_size//100)
    for i in range(0, 101, 1):
        df = pd.read_csv(f"{path}/data_1024_{i}.csv", sep=",", dtype=np.float64)
        if df["SER"].size == mean_size:
            combined_df = pd.concat([combined_df, df["SER"]], axis=1) 
    combined_df = combined_df.mean(axis=1)
    # print(combined_df)
    combined_df.to_csv(f"./processed_data/sample.csv")
    df = pd.read_csv(f"./processed_data/sample.csv")
    plt.plot(df.iloc[0], df.iloc[1])
    plt.show()
if __name__=="__main__":
    main()