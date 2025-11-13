#ifndef __ROUND__ROBIN__
#define __ROUND__ROBIN__
#include "../process.c"
#include "../sort.c"
#include "../vector.c"
#include "fcfs.c"

void RR(Process *p, Vector *v, double *tot, int len, int q){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);
    tie_braker_fcfs(p, len, 0);
    int arr[len];
    for(int i=0; i<len; i++) arr[i] = p[i].burst;
    int left = 0;
    int ctr = 0;
    while(ctr < len){
        if(q > p[left].burst){
            p[left].burst = 0;
            p[left].complete = true;
            ctr++;
            tct+=p[left].burst;
            p[left].ct = tct;
            p[left].tat = p[left].ct - p[left].at;
            p[left].wt = tct- p[left].burst - p[left].at;

            tat += p[left].tat;
            twt += p[left].wt;

            push_back(v, (pq){p[left].id, p[left].ct});
        }
        else{
            p[left].burst -= q;
            tct += q;
            push_back(v, (pq){p[left].id, tct});
        }
        if(p[left].rt == -1) {
            p[left].rt = tct - q -p[left].at;
            trt+= p[left].rt;
        }
        left = (left+1)%len; //circular queue
    }
    tot[0] = (double)tct/len;
    tot[1] = (double)twt/len;
    tot[2] = (double)trt/len;
    tot[3] = (double)tat/len;
    for(int i=0; i<len; i++) p[i].burst = arr[i];
}
#endif