set terminal png


set output "ser_plot.png"
set logscale y  
set ylabel "SER"
set xlabel "Iterations"
set title "SER vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data_mse_1.3_.txt" using 1:2 with lines title "R=1.3",\
     "./data_mse_1.4_.txt" using 1:2 with lines title "R=1.4",\
     "./data_mse_1.45_.txt" using 1:2 with lines title "R=1.45",\
     "./data_mse_1.6_.txt" using 1:2 with lines title "R=1.6"
