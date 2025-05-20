#! /bin/bash 
rm -r data 
mkdir -p data 
for L in 32 64 1028 256 1024 2048 
do
    rm -r data_${L}
    mkdir -p data_${L} 
    for i in {0..100..1}
    do 
        ./main_ser.x -l ${L} > ./data_1024/data_${L}_${i}.csv 
    done 
done 