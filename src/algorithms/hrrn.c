#ifndef _HIGHEST_RESPONSE_RATIO_NEXT_
#define _HIGHEST_RESPONSE_RATIO_NEXT_
#include "../process.c"
#include "../sort.c"
#include "../vector.c"
#include "../utils.c"

// response ratio = (wt + burst)/ burst;
void tie_braker_hrrn(Process *pr, int len, int left){
    int right = left;
    while (right<len){
        double left_rr = (double)(pr[left].wt + pr[left].burst)/pr[left].burst;
        double right_rr = (double)(pr[right].wt + pr[right].burst)/pr[right].burst;
        if( left_rr == right_rr){
            right++;
        }
        else{
            merge_sort(pr, left, right-1, cmp_by_prt);
            left = right;
        }
    }
    merge_sort(pr, left, right-1, cmp_by_prt);
}

void HRRN(Process *p, Vector *v, int len){
    int trt = 0, twt = 0, tat = 0, tct = 0;

    process_init(p, len);
    int left = 0;
    int ctr = 1;
    int arr[len];
    int curr_id = p[left].id;
    for(int i=0; i<len; i++) arr[i] = p[i].burst;
    while(left < len){
        while(ctr<len && p[ctr].at <= tct) ctr ++;
        merge_sort(p, left, ctr-1, cmp_response_ratio);
        tie_braker_hrrn(p, ctr, left);
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
    for(int i=0; i<len; i++) p[i].burst = arr[i];
}
#endif