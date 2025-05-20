set terminal png

set output "./ser_plot.png"
# set logscale y  
set ylabel "SER"
set xlabel "Iterations"
set title "SER vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data_ser.txt" using 1:2 with lines title "R=1.3",\
