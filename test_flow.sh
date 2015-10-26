#!/bin/bash

# site vacancy probability
prob=$1

# number of averages
times=$2

filename="timing_${prob}_${times}.txt"
> $filename


range=$( seq 10 10 99 && seq 100 100 1000 )

for n in $range; do
    echo "grid size $n ..."
    for (( j = 0; j < $times; j++ )); do
        # iterative flow
        i=$( ./percolation -w $n -h $n -p $prob    | cut -d' ' -f3 )
        # recursive flow
        r=$( ./percolation -w $n -h $n -p $prob -r | cut -d' ' -f3 )
        echo -e "$n\t$r\t$i" >> $filename
    done
done

