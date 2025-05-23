#! /bin/bash 
# Expriement one, different communication rate for a fixed 
# Block length and block size :) 

t_max=100 # Maximum number of iterations 
L=8192 # Block length 
make # Build the excutable 
for r in 1.3    
do
echo Using R = ${r}
        ./main_ser.x -l ${L} -r ${r} -t_max ${t_max} > ./data/ser_${r}.csv
        ./main_mse.x -l ${L} -r ${r} -t_max ${t_max} > ./data/mse_${r}.csv 
done 

echo "Done!"

python visualize_data.py