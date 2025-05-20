set terminal png


set output "./figures/ser_plot.png"
set logscale y  
set ylabel "MSE"
set xlabel "Iterations"
set title "SER vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data.txt" using 1:2 with lines title "R=1.3",\