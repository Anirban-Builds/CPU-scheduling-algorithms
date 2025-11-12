#ifndef _SJF_
#define _SJF_
#include "../process.c"
#include "../sort.c"
#include "../vector.c"

void tie_braker_sjf(Process *pr, int len, int left){
    int right = left;
    while (right<len){
        if(pr[left].burst == pr[right].burst){
            right++;
        }
        else{
            merge_sort(pr, left, right-1, cmp_by_prt);
            left = right;
        }
    }
    merge_sort(pr, left, right-1, cmp_by_prt);
}

void SJF(Process *p, Vector *v, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);
    int left = 0;
    int ctr = 1;
    while(left < len){
        while(ctr<len && p[ctr].at <= tct) ctr ++;

        merge_sort(p, left, ctr-1, cmp_by_burst);
        tie_braker_sjf(p, ctr, left);

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
}
#endif