
set terminal png

# Set the output filename
set output "./figures/mse_plot.png"
set logscale y  
set ylabel "MSE"
set xlabel "Iterations"
set title "MSE vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data/data_1.3.txt" using 1:2 with lines title "R=1.3",\
     "./data/data_1.4.txt" using 1:2 with lines title "R=1.4",\
     "./data/data_1.45.txt" using 1:2 with lines title "R=1.45",\
     "./data/data_1.6.txt" using 1:2 with lines title "R=1.6"

