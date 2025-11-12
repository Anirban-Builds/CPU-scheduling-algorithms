#ifndef _UTILS_
#define _UTILS_
#include <stdlib.h>
#include "process.c"
#include "vector.c"

void free_mem(Vector *v){
    if(v->data) free(v->data);
    free(v);
}

void rev(Process *p, int len){
    int left=0;
    int right=len-1;
    while (p[left].burst < p[right].burst){
        int temp = p[left].burst;
        p[left].burst = p[right].burst;
        p[right].burst = temp;
        left++;
        right--;
    }
}

bool cmp_response_ratio(Process *arr1, Process *arr2, int e){
    double arr1_rr = (double)(arr1->wt + arr1->burst) / arr1->burst;
    double arr2_rr = (double)(arr2->wt + arr2->burst) / arr2->burst;
    switch (e)
        {
        case 1:
            return arr1_rr - arr2_rr == 0;
        default:
            return arr1_rr - arr2_rr <= 0;
        }
}
#endif
