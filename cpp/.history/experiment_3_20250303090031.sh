#! /bin/bash 
# Expriement one, different communication rate for a fixed 
# Block length and block size :) 
t_max=100 # Maximum number of iterations 
L=2048 # Block length 
make # Build the excutable 
# r=1.3
mkdir -p ./data/exp3
for r in 1.3 1.4 1.45 1.6    
do
        echo running with snr = ${snr} r = ${r} and L = ${L}
        echo ...
        ./main_ser.x -l ${L} -r ${r}  -t_max ${t_max} > ./data/exp3/ser_${snr}.csv
        ./main_mse.x -l ${L} -r ${r} -snr ${snr} -t_max ${t_max} > ./data/exp3/mse_${snr}.csv 
done 
echo "Done!"
