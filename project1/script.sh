#! /bin/bash

dmesg -c

for i in $(seq 1 5)
do  
    ./main < OS_PJ1_Test/FIFO_${i}.txt > output/FIFO_${i}_stdout.txt
    dmesg -c | grep project1 > output/FIFO_${i}_dmesg.txt
done

for i in $(seq 1 5)
do  
    ./main < OS_PJ1_Test/RR_${i}.txt > output/RR_${i}_stdout.txt
    dmesg -c | grep project1 > output/RR_${i}_dmesg.txt
done

for i in $(seq 1 5)
do  
    ./main < OS_PJ1_Test/SJF_${i}.txt > output/SJF_${i}_stdout.txt
    dmesg -c | grep project1 > output/SJF_${i}_dmesg.txt
done

for i in $(seq 1 5)
do  
    ./main < OS_PJ1_Test/PSJF_${i}.txt > output/PSJF_${i}_stdout.txt
    dmesg -c | grep project1 > output/PSJF_${i}_dmesg.txt
done

./main < OS_PJ1_Test/TIME_MEASUREMENT.txt > output/TIME_MEASUREMENT_stdout.txt
dmesg -c | grep project1 > output/TIME_MEASUREMENT_dmesg.txt