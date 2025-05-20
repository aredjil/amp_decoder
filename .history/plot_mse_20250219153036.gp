set terminal png


set output "./figures/mse_plot.png"
set logscale y  
set ylabel "MSE"
set xlabel "Iterations"
set title "MSE vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data/data_mse_1.3_.txt" using 1:2 with lines title "R=1.3",\
     "./data/data_mse_1.4_.txt" using 1:2 with lines title "R=1.4",\
     "./data_mse_1.45_.txt" using 1:2 with lines title "R=1.45",\
     "./data_mse_1.6_.txt" using 1:2 with lines title "R=1.6"

