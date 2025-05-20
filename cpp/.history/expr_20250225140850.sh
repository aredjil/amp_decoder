#! /bin/bash 
mkdir -p data
for L in 512
do
    mkdir -p ./data/data_${L} 
    for i in {0..100..1}
    do 
        ./main_mse.x -l ${L} -r 1.3  > ./data/data_${L}/data_${L}_${i}.csv 
    done 
done 

echo "Done!"