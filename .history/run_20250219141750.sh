#!/bin/bash 

make clean 
make 
mkdir -p data 
mkdir -p figures
L=8192
# Iterate over different communication rates 
for r in 1.3 1.4 1.45 1.6 
do 
    touch ./data/data_$r.txt
    ./main.x -l $L -b 4 -r $r > ./data/data_$r.txt 
done 
