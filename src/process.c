#ifndef _PROCESS_
#define _PROCESS_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
int id;
int at;
int ct;
int wt;
int tat;
int burst;
int rt;
int priority;
}Process;

typedef struct{
    int id;
    int ct;
}q;

void process_init(Process *p, int len){

    for(int i=0; i<len; i++){
        p[i].wt = 0;
        p[i].ct = 0;
        p[i].rt = 0;
    }
}

bool cmp_by_at(Process *arr1, Process *arr2, int e){
    switch (e)
    {
    case 1:
        return arr1->at - arr2->at == 0;
    default:
        return arr1->at - arr2->at <= 0;
    }
}

bool cmp_by_prt(Process *arr1, Process *arr2, int e){
    switch (e)
    {
    case 1:
        return arr1->priority - arr2->priority == 0;
    default:
        return arr1->priority - arr2->priority <= 0;
    }
}

#endif