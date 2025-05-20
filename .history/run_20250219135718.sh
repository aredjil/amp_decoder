#!/bin/bash 

make clean 
make 

for r in 1.3 1.4 1.45 1.6 
do 
    ./main
done 
