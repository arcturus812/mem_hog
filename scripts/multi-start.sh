#!/bin/bash
MEM_CAP=32
TARGET_CAP=$1
NUM_PROC=$(echo "scale=0; $MEM_CAP/$TARGET_CAP" | bc)

echo "$MEM_CAP = $TARGET_CAP * $NUM_PROC"
for idx in `seq $NUM_PROC`;
do
    numactl -p 0 ../mem_hog -G $TARGET_CAP -A 0 -L 1 -I 1 > /dev/null &
    echo "-999" > /proc/$!/oom_adj
done
read  -n 1 -p "Input Selection:" mainmenuinput
pkill -2 mem_hog
pkill -9 mem_hog
