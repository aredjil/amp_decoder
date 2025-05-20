import pandas as pd 
import matplotlib.pyplot as plt 

def main():
    # Read the data excluding the last line which contains the time the decodre took 
    df_ser = pd.read_csv("./data/data_ser_1.3_.csv")[:-1]
    print(df_ser.columns)
    # plt.plot(df_ser["Iter"], df_ser["SER"])
    # plt.show()
if __name__ =="__main__":
    main()