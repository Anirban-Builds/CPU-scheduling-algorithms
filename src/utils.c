#ifndef _UTILS_
#define _UTILS_
#include <stdlib.h>
#include "process.c"
#include "vector.c"

void free_mem(Vector *v){
    if(v->data) free(v->data);
    free(v);
}

void rev(Process *p, int left, int len){
    int right=len-1;
    while (left < right){
        Process temp = p[left];
        p[left] = p[right];
        p[right] = temp;
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
