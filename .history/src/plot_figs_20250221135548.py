import pandas as pd 
import matplotlib.pyplot as plt 

def main():
    # Read the data excu
    df_ser = pd.read_csv("./data/data_ser_1.3_.csv")[:-1]
    print(df_ser)

if __name__ =="__main__":
    main()