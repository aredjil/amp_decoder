#! /bin/bash 
t_max=100 # Maximum number of iterations 
L=8192 # Block length 
make # Build the excutable 
for r in 1.3 1.4 1.45 1.6    
do
echo Using R = ${r}
    # mkdir -p ./data/mse_${r}/mse_${L} 
        # ./main_ser.x -l ${L} -r ${r} -t_max ${t_max} > ./data/ser_${r}.csv
        ./main_mse.x -l ${L} -r ${r} -t_max ${t_max} > ./data/mse_${L}/mse_${L}_${i}.csv 
done 

echo "Done!"