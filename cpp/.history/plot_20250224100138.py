import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 


df = pd.read_csv("./data.csv")
plt.plot(df["L"], df["SER"])
plt.xlim(0, )
plt.yscale("log")
plt.xticks(ra)
plt.grid(True, ls="--")
plt.show()