#!/bin/bash
sudo perf record -e mem-loads:p -d -c 4096 -C 0 -o huge1.data &
# sudo perf record -e mem-loads:p -d -c 4096 -C 4 -o huge2.data &
sudo LD_PRELOAD=libhugetlbfs.so LD_LIBRARY_PATH=LIBHUGEFS_DIR:$LD_LIBRARY_PATH HUGETLB_MORECORE=yes taskset -c 0 ../mem_hog -A 1 -G 1 -I 8
# sudo LD_PRELOAD=libhugetlbfs.so LD_LIBRARY_PATH=LIBHUGEFS_DIR:$LD_LIBRARY_PATH HUGETLB_MORECORE=yes taskset -c 4 ../mem_hog -A 1 -G 1 -I 8
sudo pkill -2 perf
# sudo pkill -2 perf
sleep 2
sudo perf script -i huge1.data > huge_trace_1.log
# sudo perf script -i huge2.data > huge_trace_2.log
