#! /bin/bash 

mkdir -p data_1024 
for i in {0..10..1}
do 
 ./main_ser.x -l 1024 > data_1024/data_{1024}_${i} 
done 