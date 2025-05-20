import pandas as pd 
import matplotlib.pyplot as plt 

def main():
    # Read the data excluding the last line which contains the time the decodre took 

    for i in [1.3, 1.4, 1.45, 1.5, 1.6]: # Declar the rates in  
        df_ser = pd.read_csv(f"./data/data_ser_{i}_.csv")[:-1]
    # print(df_ser.columns)
        plt.plot(df_ser["Iter"], df_ser["SER"])
        plt.yscale("log")
        plt.xlim(0, )
    plt.show()
if __name__ =="__main__":
    main()