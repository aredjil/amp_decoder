#!/bin/bash 

make clean # Clean results from the previous computations  
echo "Building the excutable\n"
make # Build the excutable 
mkdir -p data # Create a directory if it does not already exist where to save data
mkdir -p figures # Create a directory if it does not already exist where to save figures 
L= # Set the section size to be 2**15 / 4 
# Iterate over different communication rates 
for r in 1.3 1.4 1.45 1.6 
do 
    echo "Creating data files\n"
    touch ./data/data_mse_${r}_.txt
    touch ./data/data_ser_${r}_.txt
    printf("Decoding for r=%f", $r)
    ./main_ser.x -l $L -r $r > ./data/data_ser_${r}_.txt 
    ./main_ser.x -l $L -r $r > ./data/data_mse_${r}_.txt 
done 
echo "Generating plots \n"
gnuplot ./src/plot_mse.gp # Generate MSE plot, it will be saved as mse_figure.png in figures 
gnuplot ./src/plot_ser.gp # Generate MSE plot, it will be saved as mse_figure.png in figures 
