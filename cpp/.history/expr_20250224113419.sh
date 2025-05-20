#! /bin/bash 
rm -r data 
mkdir -p data 
for L in 32 64 128 256 1024 2048 
do
    mkdir -p ./data/data_${L} 
    for i in {0..100..1}
    do 
        ./main_ser.x -l ${L} > ./data/data_${L}/data_${L}_${i}.csv 
    done 
done 

echo "DOne!"