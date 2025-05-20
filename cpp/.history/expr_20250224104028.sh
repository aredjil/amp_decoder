#! /bin/bash 

L=1024
mkdir -p data_${L} 
for i in {0..10..1}
do 
 ./main_ser.x -l ${L} > ./data_1024/data_{1024}_${i}.txt 
done 