# Necessary libraries
import numpy as np
import matplotlib.pyplot as plt
import time
import sys 


from amp import amp 


def main():
    B = 4
    n = 2048
    R =1.6
    # Number of sections
    # L = 1024
    snr = 15

    argc = len(sys.argv) # Get the number of arguments passed to the program 
    for i in range(1, argc): 
        if sys.argv[i] == "-l" and i + 1 < argc: 
            i += 1
            L = int(sys.argv[i])
        if sys.argv[i] == "-b" and i + 1 < argc: 
            i += 1
            B = int(sys.argv[i])
        if sys.argv[i] == "-r" and i + 1 < argc: 
            i += 1
            R = float(sys.argv[i])
        if sys.argv[i] == "-snr" and i + 1 < argc: 
            i += 1
            snr = float(sys.argv[i])
    
    my_amp = amp(L, B)
    snr = 15
    start = time.time()
    ser_13 = my_amp.decode(snr, 1.3)
    end = time.time()
    duration = end - start
    print(f"The decoder took: {duration} s")

    # plt.plot(ser_13, label="R = 1.3", linestyle="dashed")
    # plt.xlim(0, 25)
    # plt.ylabel("Section Error Rate (SER)")
    # plt.xlabel("Iterations")
    # plt.grid(True)
    # plt.legend(loc="best")
    # plt.yscale("log")

if __name__ == "__main__":
    main()