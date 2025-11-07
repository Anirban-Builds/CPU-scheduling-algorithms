#include "scheduler.h"

void call_FCFS(Process *p, Vector *v, int len){
    FCFS(p, v, len);
}

void call_SJF(Process *p, Vector *v, int len){
    SJF(p, v, len);
}