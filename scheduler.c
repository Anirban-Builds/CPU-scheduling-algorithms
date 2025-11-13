#include "scheduler.h"

void call_FCFS(Process *p, Vector *v, double *tot,int len){
    FCFS(p, v, tot, len);
}

void call_SJF(Process *p, Vector *v, double *tot, int len){
    SJF(p, v, tot, len);
}

void call_LJF(Process *p, Vector *v, double *tot, int len){
    LJF(p, v, tot, len);
}

void call_RR(Process *p, Vector *v, double *tot, int len, int q){
    RR(p, v, tot, len, q);
}

void call_SRTF(Process *p, Vector *v, double *tot, int len){
    SRTF(p, v, tot, len);
}

void call_LRTF(Process *p, Vector *v, double *tot, int len){
    LRTF(p, v, tot, len);
}

void call_NPPS(Process *p, Vector *v, double *tot, int len){
    NPPS(p, v, tot, len);
}

void call_PPS(Process *p, Vector *v, double *tot, int len){
    PPS(p, v, tot, len);
}

void call_HRRN(Process *p, Vector *v, double *tot, int len){
    HRRN(p, v, tot, len);
}

