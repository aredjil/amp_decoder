#! /bin/bash 
# Use 50 data points for each 
# Generate all the data: data/diff_sec data/diff_r data/diff_b 
# Use section lengths of L = 2048, 4096, 8192 (Do this for the rates 1.3, 1.4, 1.45, 1.6)
# Use rates R = 1.3, 1.4, 1.45, 1.6 
# Fix the rate and length and change section size B = 2 4 8 ... 
mkdir -p data
for L in 8192
do
    mkdir -p ./data/data_${L} 
    for i in {12..100..1}
    do 
        ./main_mse.x -l ${L} -r 1.3 -t_max 30 > ./data/data_${L}/data_${L}_${i}.csv 
    done 
done 

echo "Done!"