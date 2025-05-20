#! /bin/bash 
# Expriement one, different communication rate for a fixed 
# Block length and block size :) 

t_max=100 # Maximum number of iterations 
L=1024 # Block length 
make # Build the excutable 
r=1.3
for b in 4 8 16 

        ./main_ser.x -l ${L} -r ${r} -b ${b}-t_max ${t_max} > ./data/exp3/ser_${r}.csv
        ./main_mse.x -l ${L} -r ${r} -b ${b} -t_max ${t_max} > ./data/ex3/mse_${r}.csv 
 

echo "Done!"

python visualize_data.py