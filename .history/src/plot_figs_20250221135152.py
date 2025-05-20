import pandas as pd 
import matplotlib.pyplot as plt 

def main():
    # Get the data 
    df_ser = pd.read_csv("../data/data_ser_1.3_.csv")
    print(df_ser.head())

if __name__ =="__main__":
    main()