#!/bin/bash
sudo perf record -e mem-loads:p -d -c 4096 -C 0 -o perf1.data &
sudo perf record -e mem-loads:p -d -c 4096 -C 4 -o perf2.data &
# sudo perf record -e mem_load_retired.l3_miss:p  -e mem_load_retired.l3_hit:p -d -c 4096 -C 0 -o perf1.data &
# sudo perf record -e mem_load_retired.l3_miss:p  -e mem_load_retired.l3_hit:p -d -c 4096 -C 4 -o perf2.data &
sudo taskset -c 0 numactl -m 0 ../mem_hog -A 1 -G 1 -I 8 &
sudo taskset -c 4 numactl -m 0 ../mem_hog -A 1 -G 1 -I 8
sudo pkill -2 perf
sudo pkill -2 perf
sleep 2
sudo perf script -i perf1.data > mem_trace_1.log
sudo perf script -i perf2.data > mem_trace_2.log
