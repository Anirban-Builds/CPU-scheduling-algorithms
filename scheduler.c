#include "scheduler.h"

void call_FCFS(Process *p, Vector *v, double *tot,int len){
    FCFS(p, v, tot, len);
}

void call_SJF(Process *p, Vector *v, int len){
    SJF(p, v, len);
}

void call_LJF(Process *p, Vector *v, int len){
    LJF(p, v, len);
}

void call_RR(Process *p, Vector *v, int len, int q){
    RR(p, v, len, q);
}

void call_SRTF(Process *p, Vector *v, int len){
    SRTF(p, v, len);
}

void call_LRTF(Process *p, Vector *v, int len){
    LRTF(p, v, len);
}

void call_NPPS(Process *p, Vector *v, int len){
    NPPS(p, v, len);
}

void call_PPS(Process *p, Vector *v, int len){
    PPS(p, v, len);
}

void call_HRRN(Process *p, Vector *v, int len){
    HRRN(p, v, len);
}

