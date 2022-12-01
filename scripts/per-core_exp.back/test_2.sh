#!/bin/bash
sudo perf record -e mem-loads:p -d -c 4096 taskset -c 4 numactl -m 0 ../../mem_hog2 -A 1 -G 1 -I 4
sleep 1
sudo perf script > mem_trace_2.log
