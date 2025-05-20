set terminal png

set output "./figures/ser_plot.png"
set logscale y  
set ylabel "SER"
set xlabel "Iterations"
set title "SER vs Number of Iterations"

# Plot the data using the index as x-values
plot "./data/data_ser_1.3_.txt" using 1:2 with lines title "R=1.3",\
     "./data/data_ser_1.4_.txt" using 1:2 with lines title "R=1.4",\
     "./data/data_ser_1.45_.txt" using 1:2 with lines title "R=1.45",\
          "./data/data_ser_1.45_.txt" using 1:2 with lines title "R=1.45",\
     "./data/data_ser_1.6_.txt" using 1:2 with lines title "R=1.6"
