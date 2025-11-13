#ifndef _LRTF_
#define _LRTF_
#include "../process.c"
#include "../sort.c"
#include "../vector.c"
#include "sjf.c"

void LRTF(Process *p, Vector *v, double *tot, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);
    int left = 0;
    int ctr = 1;
    int arr[len];
    int curr_id = p[left].id;
    for(int i=0; i<len; i++) arr[i] = p[i].burst;
    while(left < len){
        while(ctr<len && p[ctr].at <= tct) ctr ++;
        merge_sort(p, left, ctr-1, cmp_by_burst);
        tie_braker_sjf(p, ctr, left);
        rev(p, ctr); // reverse srtf array
        if(p[left].id != curr_id) {
            if(!p[curr_id].complete) push_back(v, (pq){curr_id, tct});
            curr_id = p[left].id;
        }
        p[left].burst--;
        tct++;
        if(!p[left].burst){ // if process completed
            p[left].complete = true;
            p[left].ct = tct;
            p[left].tat = p[left].ct - p[left].at;
            p[left].wt = tct- 1 - p[left].at;
            tat += p[left].tat;
            twt += p[left].wt;
            push_back(v, (pq){p[left].id, p[left].ct});
        }
        if(p[left].rt == -1) {
        p[left].rt = tct - 1 -p[left].at;
        trt+= p[left].rt;
        }
        while(p[left].complete) left++;
    }
    tot[0] = (double)tct/len;
    tot[1] = (double)twt/len;
    tot[2] = (double)trt/len;
    tot[3] = (double)tat/len;
    for(int i=0; i<len; i++) p[i].burst = arr[i];
}
#endif