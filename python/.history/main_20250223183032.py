#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import time
import sys 

from amp import amp 


def main():
    B = 4
    # n = 2 **15 
    R =1.3
    # Number of sections
    # L = 1024
    snr = 15
    c = 1 # Power allocation 
    L = int (2**15 / B)
    t_max = 25
    ep=10**-8
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
        if sys.argv[i] == "-ep" and i + 1 < argc: 
            i += 1
            ep = float(sys.argv[i])
        if sys.argv[i] == "-t_max" and i + 1 < argc: 
            i += 1
            ep = float(sys.argv[i])
    start = time.time()
    for r in [1.3, 1.4, 1.45, 1.5]:
        my_amp = amp(   L, 
                        B, 
                        snr, 
                        R, 
                        c)
        ser = my_amp.decode(snr, 
                           t_max, 
                           ep)
    end = time.time()
    duration = end - start
    print(f"The decoder took: {duration} s")
    #Plotting the results 
    plt.plot(ser, label="R = 1.3", linestyle="dashed")
    plt.xlim(0, 25)
    plt.ylabel("Section Error Rate (SER)")
    plt.xlabel("Iterations")
    plt.grid(True)
    plt.legend(loc="best")
    plt.yscale("log")
    plt.show()

if __name__ == "__main__":
    main()