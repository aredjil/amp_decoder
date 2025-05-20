#!/bin/bash 

make clean 
make 
mkdir -p data 
for r in 1.3 1.4 1.45 1.6 
do 
    touch ./data/data_$r.txt
    ./main.x -l 4 -b 4 -r $r > ./data/data_$r.txt 
done 
