import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 

def main():
    mean_size = 0
    for i in range(0, 101, 1):
        df = pd.read_csv(f"./data_1024/data_1024_{i}.csv", sep=",", dtype=np.float64)
        mean_size += df["SER"].size
    print(mean_size/100)
if __name__=="__main__":
    main()