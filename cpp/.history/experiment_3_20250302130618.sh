#! /bin/bash 
# Expriement one, different communication rate for a fixed 
# Block length and block size :) 

t_max=100 # Maximum number of iterations 
L=1024 # Block length 
make # Build the excutable 
r=1.3
for b in 4 8 16 

        ./main_ser.x -b ${L} -r ${r} -t_max ${t_max} > ./data/ser_${r}.csv
        ./main_mse.x -b ${L} -r ${r} -t_max ${t_max} > ./data/mse_${r}.csv 
 

echo "Done!"

python visualize_data.py