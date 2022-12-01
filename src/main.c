/*
 * Added by     PHW, 210317
 * Edited by    PHW,
 * contacts     hwpark@dgist.ac.kr
 */

#include <main.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <ctype.h>
#include <unistd.h>  // [PHW] for "option parser"

extern char *optarg;
extern int optind;

int err_no;

int main(int argc, char *argv[]) {
    // definition of common variables
    int opt;
    int ret = 0;
    unsigned long long req_mem = 0;
    float tmp = 0;
    int seq_acc = 0;
    int iter=1;
    int loop=0;
    char *pos=NULL;
    srand(time(NULL));
    struct timeval ts_start;
    struct timeval ts_end;
    struct timeval ts_diff;

    // abort if parameter gone wrong
    if (argc < 5) {
        printf(
            "usage: mem_hog <-G mem_to_alloc( e.g. -G 1 is 1GB )> \
            <-A sequential_access 1:enable 0:disable> \
            \n");
        err_no = ERROR_PARAM;
        goto ERROR;
    }
    // start parce
    while ((opt = getopt(argc, argv, "G:A:I:L:")) != -1) {
        switch (opt) {
            case 'G':
                /* unsigned long long tmp = strtoull(optarg, &pos, 10); */
                tmp = strtof(optarg, &pos);
                printf("%0.2f GB\n", tmp);
                printf("%llu MB\n", (unsigned long long)(tmp*1024));
                printf("%llu KB\n", (unsigned long long)(tmp*1024*1024));
                printf("%llu B\n", (unsigned long long)(tmp*1024*1024*1024));
                req_mem = (unsigned long long)(tmp*1024*1024*1024);
                printf("tmp:%f\n", tmp);
                printf("req_mem:%llu\n", req_mem);
                break;
            case 'A':
                seq_acc = atoi(optarg);
                break;
            case 'I':
                iter = atoi(optarg);
                break;
            case 'L':
                loop = atoi(optarg);
                break;
            case '?':
                err_no = ERROR_PARAM;
                goto ERROR;
        }
    }
    // end parce
    // main loop start
    // init memory
    int **pt;
    int *pt2;
    float gb = (float)(req_mem / (1024*1024*1024));
    printf("gb:%0.2f\n", gb);
    printf("req_mem:%llu\n", req_mem);
    if(gb < 1){
        pt2 = (int*)calloc((req_mem/4), sizeof(int));
        for(int j = 0;j<(req_mem/4);j++){
            pt2[j] = rand();
        }
    }else{
        pt = (int**)calloc((int)gb,sizeof(int*));
        for(int i=0;i<(int)gb;i++){
            pt[i] = (int*)calloc((1024*1024*256),sizeof(int));
            for(int j=0;j<(1024*1024*256);j++){
                pt[i][j] = rand();
            }
        }
    }
    printf("memory initialized\n");
    if(seq_acc){
        printf("start seq access\n");
        gettimeofday(&ts_start,NULL);
        int dummy;
        /* int r = 123; */
        if(gb < 1){
            for(int k=0;k<iter;k++){
                for(int j=0;j<(req_mem/4);j+=16){
                    dummy = pt2[j];
                    dummy = pt2[j+1];
                    dummy = pt2[j+2];
                    dummy = pt2[j+3];
                    dummy = pt2[j+4];
                    dummy = pt2[j+5];
                    dummy = pt2[j+6];
                    dummy = pt2[j+7];
                    dummy = pt2[j+8];
                    dummy = pt2[j+9];
                    dummy = pt2[j+10];
                    dummy = pt2[j+11];
                    dummy = pt2[j+12];
                    dummy = pt2[j+13];
                    dummy = pt2[j+14];
                    dummy = pt2[j+15];
   
                }
                if(loop > 0){
                    k=0;
                }
            }
        }else{
            for(int k=0;k<iter;k++){
                for(int i=0;i<(int)gb;i++){
                    for(int j=0;j<(1024*1024*256);j+=16){
                        dummy = pt[i][j];
                        dummy = pt[i][j+1];
                        dummy = pt[i][j+2];
                        dummy = pt[i][j+3];
                        dummy = pt[i][j+4];
                        dummy = pt[i][j+5];
                        dummy = pt[i][j+6];
                        dummy = pt[i][j+7];
                        dummy = pt[i][j+8];
                        dummy = pt[i][j+9];
                        dummy = pt[i][j+10];
                        dummy = pt[i][j+11];
                        dummy = pt[i][j+12];
                        dummy = pt[i][j+13];
                        dummy = pt[i][j+14];
                        dummy = pt[i][j+15];
                    }
                }
                if(loop > 0){
                    k=0;
                }
            }
        }
        gettimeofday(&ts_end,NULL);
        ts_diff.tv_sec = ts_end.tv_sec - ts_start.tv_sec;
        ts_diff.tv_usec = ts_end.tv_usec - ts_start.tv_usec;
        if(ts_diff.tv_usec < 0){
            ts_diff.tv_sec = ts_diff.tv_sec - 1;
            ts_diff.tv_usec = ts_diff.tv_usec + 1000000;
        }
        printf("[seq access time]%ld.%ld\n",ts_diff.tv_sec, ts_diff.tv_usec);
        printf("[iteration] %d\n", iter);
    }else{
        printf("enter to exit\n");
        getchar();
    }

    if(gb < 1){
        free(pt2);
    }else{
        free(pt);
    }
    return 0;
ERROR:
    switch (err_no) {
        case ERROR_PARAM:
            printf("parameter error\n");
            break;
        case ERROR_ALLOC:
            printf("allocation error\n");
            break;
    }
    return -1;
}
