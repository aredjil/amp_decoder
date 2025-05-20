#! /bin/bash 
# Expriement one, different communication rate for a fixed 
# Block length and block size :) 
t_max=100 # Maximum number of iterations 
L=2048 # Block length 
make # Build the excutable 
r=1.4
mkdir -p ./data/exp3
for snr in 4 8 16 
do
        echo running with b = ${b} r = ${r} and L = ${L}
        echo ...
        ./main_ser.x -l ${L} -r ${r} -b ${b} -t_max ${t_max} > ./data/exp3/ser_${b}.csv
        ./main_mse.x -l ${L} -r ${r} -b ${b} -t_max ${t_max} > ./data/exp3/mse_${b}.csv 
done 
echo "Done!"
