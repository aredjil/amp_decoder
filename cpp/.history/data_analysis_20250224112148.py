import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 

def main():
    path = "./data_1024"
    mean_size = 0
    combined_df = pd.DataFrame()
    for i in range(0, 101, 1):
        df = pd.read_csv(f"{path}/data_1024_{i}.csv", sep=",", dtype=np.float64)
        mean_size += df["SER"].size
    for i in range(0, 101, 1):
        df = pd.read_csv(f"{path}/data_1024_{i}.csv", sep=",", dtype=np.float64)
        if df["SER"].size < mean_size:
            print(df["SER"].size)
            # combined_df = pd.concat([combined_df, df])
    # print(combined_df)
    # print(mean_size//100)
if __name__=="__main__":
    main()