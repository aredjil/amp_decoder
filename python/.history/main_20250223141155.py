# Necessary libraries
import numpy as np
import matplotlib.pyplot as plt
import time
from amp import amp 
def main():
    B = 4
    n = 2**15
    R =1.6
    # Number of sections
    L = int(n / B)

    my_amp = amp(L, B)

    snr = 15
    start = time.time()
    ser_13 = my_amp.decode(snr, 1.3)
    end = time.time()
    duration = end - start
    print(f"The decoder took: {duration} s")
    # ser_13 = my_amp.decode(snr, 1.3)
    # ser_14 = my_amp.decode(snr, 1.4)
    # ser_145 = my_amp.decode(snr, 1.45)
    # ser_16 = my_amp.decode(snr, 1.6)

    plt.plot(ser_13, label="R = 1.3", linestyle="dashed")
    plt.xlim(0, 25)
    plt.ylabel("Section Error Rate (SER)")
    plt.xlabel("Iterations")
    plt.grid(True)
    plt.legend(loc="best")
    plt.yscale("log")

if __name__ == "__main__":
    main()