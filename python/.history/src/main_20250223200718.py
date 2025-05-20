#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt
import time
import sys 

from decoder.amp import amp 

"""
NOTE: Immplement a function that creates directories to save the data and figures at if not already present 
"""

def main():
    B = 4 # Section size 
    # R =1.3 # Communicat rate 
    snr = 15 # Signal to noise ratio 
    c = 1 # Power allocation 
    L = int (2**15 / B) # Section size 
    t_max = 25 # Maximum number of iterations 
    ep=10**-8 # Convergence threshold 
    seed = 42 # Random seed  
    argc = len(sys.argv) # Get the number of arguments passed to the program 
    # Get the paramters from the user through the command line arrguements 
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
        if sys.argv[i] == "-h": 
            print("Help Message not immplemented yet :)")
            exit(-1)
    
    # rates = [1.3, 1.4, 1.45, 1.5] 
    # xticks = range(0, 26, 5)
    # Run the amp decoder for the specified communication rates 
    # for r in rates:
Q
        #NOTE: Add a line to check if the data directory already exits or not 
        np.savetxt(f"./data/ser_{L}_{r}.txt", ser)
        plt.plot(ser, label=f"R = {r}", linestyle="dashed")
        plt.xlim(0, 25) 
        plt.ylabel("Section Error Rate (SER)")
        plt.xlabel("Iterations")
        plt.xticks(xticks)
        plt.grid(True)
        plt.legend(loc="best")
        plt.yscale("log")
    # Saving and showing the results  
    plt.title("Section error rate vs iterations")
    plt.savefig(f"./figures/ser_{L}.png")
    plt.show()

if __name__ == "__main__":
    main()