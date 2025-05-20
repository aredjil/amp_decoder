# Define the data (you can also put this in a separate file called data.txt and use 'plot "data.txt" with lines')
# data="0.17804 0.140667 0.121211 0.101882 0.0879246 0.0761451 0.0686096 0.0596271 0.0512539 0.0391092 0.0316552 0.0230186 0.0138729 0.00586231 0.00164064 0.000666812 0.000448185 0.000440347 0.000464637 0.000470987 0 0 0 0 0 0 0 0 0 0 0"
set terminal png

# Set the output filename
set output "data_plot.png"
set logscale y  
set ylabel "MSE"
set title "Iteration"

# Plot the data using the index as x-values
plot "./data/data_1.3.txt" using 1:2 with lines title "R=1.3",\
     "./data/data_1.3.txt" using 1:2 with lines title "R=1.3",

