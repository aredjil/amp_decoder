import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 

n = 8
sizes = [i for i in range(100*n)]
df = pd.read_csv("./data.csv")
plt.scatter(df["L"], df["SER"], s=sizes)
plt.xlim(0, )
plt.yscale("log")
# plt.xscale("log")
# plt.xticks(range(0, 8192, 8))
plt.grid(True, ls="--")
plt.show()