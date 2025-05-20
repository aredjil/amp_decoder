#! /bin/bash 
# Use 10 data files for each then increase the number of points used if necessary 
# There was a problem with using 50 files, 10 files seems to be an optimal number to get results that resemble
# The expected theortical beahvior 
# Generate all the data: data/diff_sec data/diff_r data/diff_b 
# Use section lengths of L = 2048, 4096, 8192 (Do this for the rates 1.3, 1.4, 1.45, 1.6)
# Use rates R = 1.3, 1.4, 1.45, 1.6 
# Fix the rate and length and change section size B = 2 4 8 ... 
# Time the algorithm for different sizes 
r=1.4
make clean 
make 
mkdir -p data/data_${r}
for L in 8192 
do
    mkdir -p ./data/ser_${L} 
    mkdir -p ./data/mse_${L} 
    for i in {0..50..1}
    do 
        ./main_ser.x -l ${L} -r 1.3 -t_max 30 > ./data/ser_${L}/ser_${L}_${i}.csv 
        ./main_mse.x -l ${L} -r 1.3 -t_max 30 > ./data/mse_${L}/mse_${L}_${i}.csv 
    done 
done 

echo "Done!"