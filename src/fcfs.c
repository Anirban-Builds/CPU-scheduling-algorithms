#ifndef _FCFS_
#define _FCFS_
#include "process.c"
#include "sort.c"
#include <stdio.h>

void FCFS(Process *p, int len){

    int trt, twt, tat, tct =0;

    process_init(p, len);
    // merge_sort(p, 0, len);

    p[0].ct = p[0].burst;
    p[0].tat = p[0].ct - p[0].at;

    trt += p[0].rt;
    twt += p[0].wt;
    tat += p[0].tat;
    tct += p[0].burst;

    for(int i=1; i<len; i++){
        p[i].wt = tct - p[i].at;
        p[i].ct = tct + p[i].burst;
        p[i].tat = p[i].ct - p[i].at;
        p[i].rt = p[i].wt;

        tct += p[i].burst;
        tat += p[i].tat;
        twt += p[i].wt;
        trt += p[i].rt;
    }
}

#endif
