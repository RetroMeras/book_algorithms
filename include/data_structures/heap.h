#ifndef HEAP_H
#define HEAP_H

#include "common.h"

typedef struct{
    int *values;
    size_t length;
    size_t capacity;
} Heap;

size_t Heap_parent(size_t i);
size_t Heap_left(size_t i);
size_t Heap_right(size_t i);
void Heap_heapify(Heap *heap, size_t i);
Heap Heap_build(int *arr, size_t n);
int Heap_maximum(Heap *heap);
int Heap_extract_max(Heap *heap);
void Heap_insert(Heap *heap, int key);
 

#endif
