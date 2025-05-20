#! /bin/bash 
rm -r data 
mkdir -p data
for L in 256 512
do
    mkdir -p ./data/data_${L} 
    for i in {0..100..1}
    do 
        ./main_ser.x -l ${L} -r 1.3 > ./data/data_${L}/data_${L}_${i}.csv 
    done 
done 

echo "Done!"