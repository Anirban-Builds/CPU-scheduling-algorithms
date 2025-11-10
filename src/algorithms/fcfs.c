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

void FCFS(Process *p, Vector *v, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);

    tie_braker_fcfs(p, len, 0);

    p[0].ct = p[0].burst;
    p[0].tat = p[0].ct - p[0].at;

    trt += p[0].rt;
    twt += p[0].wt;
    tat += p[0].tat;
    tct += p[0].burst;

    p[0].complete = true;

    push_back(v, (pq){p[0].id, p[0].ct});

    for(int i=1; i<len; i++){
        p[i].wt = tct - p[i].at;
        p[i].ct = tct + p[i].burst;
        p[i].tat = p[i].ct - p[i].at;
        p[i].rt = p[i].wt;

        tct += p[i].burst;
        tat += p[i].tat;
        twt += p[i].wt;
        trt += p[i].rt;

        p[i].complete = true;

        push_back(v, (pq){p[i].id, p[i].ct});
    }
}

#endif
