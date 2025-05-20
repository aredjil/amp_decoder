set terminal png


set output ".plot.png"
set logscale y  
set ylabel "SER"
set xlabel "Iterations"
set title "MSE vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data/data_mse_1.3_.txt" using 1:2 with lines title "R=1.3",\