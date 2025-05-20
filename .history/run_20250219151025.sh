#!/bin/bash 

make clean # Clean results from the previous computations  
make # Build the excutable 
mkdir -p data # Create a directory if it does not already exist where to save data
mkdir -p figures # Create a directory if it does not already exist where to save figures 
L=8192 # Set the section size to be 2**15 / 4 
# Iterate over different communication rates 
for r in 1.3 1.4 1.45 1.6 
do 
    touch ./data/data_mse_$r_.txt
    touch ./data/data_ser_$r_.txt
    ./main_.x -l $L -b 4 -r $r > ./data/data_$r.txt 
done 
gnuplot plot_mse.gp # Generate MSE plot, it will be saved as mse_figure.png in figures 
