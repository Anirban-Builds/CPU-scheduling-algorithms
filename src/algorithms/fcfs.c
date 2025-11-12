#ifndef _FCFS_
#define _FCFS_
#include "../process.c"
#include "../sort.c"
#include "../vector.c"

void tie_braker_fcfs(Process *pr, int len, int left){
    int right = left;
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

void FCFS(Process *p, Vector *v, double *tot, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);

    tie_braker_fcfs(p, len, 0);

    for(int i=0; i<len; i++){
        tct += p[i].burst;

        p[i].ct = tct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = tct -p[i].burst -p[i].at;
        p[i].rt = p[i].wt;

        tat += p[i].tat;
        twt += p[i].wt;
        trt += p[i].rt;

        p[i].complete = true;

        push_back(v, (pq){p[i].id, p[i].ct});
    }
    tot[0] = (double)tct/len;
    tot[1] = (double)twt/len;
    tot[2] = (double)trt/len;
    tot[3] = (double)tat/len;
}

#endif
