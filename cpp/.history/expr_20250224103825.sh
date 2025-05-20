#! /bin/bash 

mkdir data_1024 
for i in {0..10..1}
do 
 ./main_ser.x -l 1024 
done 