#! /bin/bash 
rm -r data 
mkdir -p data
for L in 50
do
    mkdir -p ./data/data_${L} 
    for i in {0..100..1}
    do 
        ./main_ser.x -l ${L} -r 1.45 > ./data/data_${L}/data_${L}_${i}.csv 
    done 
done 

echo "Done!"