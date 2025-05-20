import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt 

def main():
    df = pd.read_csv("./data_1024/data_1024_0.csv") 
    print(df)

if __name__=="__main__":
    main()