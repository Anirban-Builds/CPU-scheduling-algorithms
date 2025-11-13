#ifndef _LJF_
#define _LJF_
#include "../process.c"
#include "../sort.c"
#include "../vector.c"
#include "../utils.c"
#include "sjf.c"

void LJF(Process *p, Vector *v, double *tot, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);
    int left = 0;
    int ctr = 1;
    while(left < len){
        while(ctr<len && p[ctr].at <= tct) ctr ++;

        merge_sort(p, left, ctr-1, cmp_by_burst);
        tie_braker_sjf(p, ctr, left);
        rev(p, ctr); // reverse sjf array

        tct+=p[left].burst;

        p[left].ct = tct;
        p[left].tat = p[left].ct - p[left].at;
        p[left].wt = tct- p[left].burst - p[left].at;
        p[left].rt = p[left].wt;

        tat += p[left].tat;
        twt += p[left].wt;
        trt += p[left].rt;

        p[left].complete = true;

        push_back(v, (pq){p[left].id, p[left].ct});
        while(p[left].complete) left++;
    }
    tot[0] = (double)tct/len;
    tot[1] = (double)twt/len;
    tot[2] = (double)trt/len;
    tot[3] = (double)tat/len;
}
#endif