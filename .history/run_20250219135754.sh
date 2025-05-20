#!/bin/bash 

make clean 
make 
mkdir -p data 
for r in 1.3 1.4 1.45 1.6 
do 
    
    ./main.x -r $r > data_$r.txt 
done 
