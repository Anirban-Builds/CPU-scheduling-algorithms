#ifndef _VECTOR_
#define _VECTOR_
#include <stdlib.h>
#include "process.c"

typedef struct{
    pq* data;
    size_t size;
    size_t capacity;
}Vector;

Vector* create_vector(){
    Vector* v = malloc(sizeof(Vector));
    v->data = NULL; // (*v).data
    v->size = 0;
    v->capacity = 0;
    return v;
}

void push_back(Vector *v, pq val){
    if(v->data == NULL){
        v->data = malloc(sizeof(pq));
        v->capacity = 1;
    }

    else if(v->size >= v->capacity){
            v->capacity *= 2;
            v->data = realloc(v->data, v->capacity*sizeof(pq));
    }
    v->data[v->size] = val;
    v->size++;
}

void pop_back(Vector *v){
    if(v->size >0){
        v->size--;
    }
}

pq vector_at(Vector *v, size_t i){
    if(i >= v->size){
        fprintf(stderr, "Index out of bounds access\n");
        exit(1);
    }
    return v->data[i];
}

size_t vector_size(Vector* v) {
    return v->size;
}

int vector_is_empty(Vector* v) {
    return v->size == 0;
}

#endif


