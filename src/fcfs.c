#ifndef _FCFS_
#define _FCFS_
#include "process.c"
#include "sort.c"
#include <stdio.h>

void tie_braker_fcfs(Process *pr, int len){
    int left = 0;
    int right = 0;
    while (right<len){
        if(pr[left].at == pr[right].at){
            right++;
        }
        else{
            merge_sort(pr, left, right-1, cmp_by_prt);
            left = right;
        }
    }
    merge_sort(pr, left, right-1, cmp_by_prt);
}


void gantt_chart_queue(Process *p, q *gc, int len){
    int ctr = 0;
    while(ctr<len){
        gc[ctr].id = p[ctr].id;
        gc[ctr].ct = p[ctr].ct;
        ctr++;
    }
}

void FCFS(Process *p, q* gcq,int len){

    int trt, twt, tat, tct =0;

    process_init(p, len);

    tie_braker_fcfs(p, len);

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

    gantt_chart_queue(p, gcq, len);
}

#endif
