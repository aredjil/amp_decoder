#!/bin/bash 

make clean # Clean results from the previous computations  
echo "Building the excutable"
echo ""
make  # Build the excutable 
echo "Creating directories..."
echo " "
mkdir -p data # Create a directory if it does not already exist where to save data
mkdir -p figures # Create a directory if it does not already exist where to save figures 
echo "Drectories data and figures created :)"
echo " "
conda activate numeric_env 
L=2048 # Set the section size to be 2**15 / 4 8192
# mse_plot="./src/plot_mse.gp"
ser_plot="./src/plot_ser.gp"
# Iterate over different communication rates 
echo "Running ..."
for r in 1.3 1.4 1.45 1.6 
do 
    echo "Creating data file"
    touch ./data/data_mse_${r}_.csv
    touch ./data/data_ser_${r}_.csv
    echo "Decoding for r: ${r}"
    ./main_ser.x -l $L -r $r -b 4 > ./data/data_ser_${r}_.csv 
    ./main_mse.x -l $L -r $r -b 4 > ./data/data_mse_${r}_.csv 
done 
echo " "
echo "Generating plots"
# gnuplot $mse_plot # Generate MSE plot, it will be saved as mse_figure.png in figures 
python ./src/plot_figs.py