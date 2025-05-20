#! /bin/bash 
# NOTE: Generate all the data: data/diff_sec data/diff_r data/diff_b 
# Use section lengths of 
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