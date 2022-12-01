#!/bin/bash
sudo perf record -e mem-loads:p -d -c 4096 -C 0 &
sudo taskset -c 0 numactl -m 0 ../mem_hog -A 1 -G 1 -I 4
sudo pkill -2 perf
sleep 2
sudo perf script > mem_trace.log
