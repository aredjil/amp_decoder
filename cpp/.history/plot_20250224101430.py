import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 


df = pd.read_csv("./data.csv")
plt.scatter(df["L"], df["SER"])
plt.xlim(0, )
plt.yscale("log")
plt.x
# plt.xticks(range(0, 8192, 8))
plt.grid(True, ls="--")
plt.show()