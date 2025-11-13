#ifndef _SORT_
#define _SORT_
#include "process.c"

void merge(Process *arr, int left, int mid, int right,
            bool (*f)(Process *a, Process *b, int e)){
    int lIdx = left;
    int rIdx = mid+1;

    //temp arr
    Process *sortArr = malloc(sizeof(Process)*(right+1));
    int idx = left;

    while(lIdx <=mid && rIdx <=right){
        if(f(&arr[lIdx], &arr[rIdx], -1)){
            sortArr[idx++] = arr[lIdx++];
        }
        else{
            sortArr[idx++] = arr[rIdx++];
        }
    }

    // if left arr is exhausted
    if(lIdx > mid){
        for(int i=rIdx; i<= right; i++){
            sortArr[idx++] = arr[i];
        }
    }

    // if right arr is exhausted
    else{
        for(int i=lIdx; i<= mid; i++){
            sortArr[idx++] = arr[i];
        }
    }

    // pass value into calling array
    for(int i=left; i<=right; i++){
        arr[i] = sortArr[i];
    }

    free(sortArr); // free temp array
}

void merge_sort(Process *arr, int left, int right,
                 bool (*f)(Process *a, Process *b, int e)){
    int mid;

    if(left< right){
        mid = (left + right) >> 1;

        merge_sort(arr, left, mid, f);
        merge_sort(arr, mid+1, right, f);

        merge(arr, left, mid, right, f);
    }
}

#endif