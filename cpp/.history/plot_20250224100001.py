import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 


df = pd.read_csv("./data.csv")
plt.plot(df["L"], df["SER"])
plt.yscale("log")
plt.grid(True, ls="")
plt.show()