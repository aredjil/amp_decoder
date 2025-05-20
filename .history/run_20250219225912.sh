#!/bin/bash 

make clean # Clean results from the previous computations  
echo "Building the excutable"
make # Build the excutable 
mkdir -p data # Create a directory if it does not already exist where to save data
mkdir -p figures # Create a directory if it does not already exist where to save figures 
L=4098 # Set the section size to be 2**15 / 4 8192
mse_plot="./src/plot_mse.gp"
ser_plot="./src/plot_ser.gp"
# Iterate over different communication rates 
for r in 1.3 1.4 1.45 1.5 1.6 
do 
    echo "Creating data file"
    touch ./data/data_mse_${r}_.txt
    touch ./data/data_ser_${r}_.txt
    echo "Decoding for r: ${r}"
    ./main_ser.x -l $L -r $r > ./data/data_ser_${r}_.txt 
    ./main_ser.x -l $L -r $r > ./data/data_mse_${r}_.txt 
    echo " "
done 

echo "Generating plots"
gnuplot $mse_plot # Generate MSE plot, it will be saved as mse_figure.png in figures 
gnuplot $ser_plot # Generate MSE plot, it will be saved as mse_figure.png in figures 
echo "Plots saved in ./figures"
