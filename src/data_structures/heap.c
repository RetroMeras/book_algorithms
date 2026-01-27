#include "data_structures/heap.h"
#include "common.h"
#include <limits.h>

size_t Heap_parent(size_t i) { return (i - 1) >> 1; }
size_t Heap_left(size_t i) { return (i << 1) + 1; }
size_t Heap_right(size_t i) { return (i << 1) + 2; }

// Running time is O(log2(n))
void Heap_heapify(Heap *heap, size_t i) {
  size_t l = Heap_left(i);
  size_t r = Heap_right(i);
  size_t largest = i;
  if (l < heap->length && heap->values[l] > heap->values[i]) {
    largest = l;
  }
  if (r < heap->length && heap->values[r] > heap->values[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(&heap->values[i], &heap->values[largest]);
    Heap_heapify(heap, largest);
  }
}

Heap Heap_build(int *arr, size_t n) {
  Heap heap = (Heap){arr, n, n};

  for (size_t i = (n >> 1); i > 0; i--) {
    Heap_heapify(&heap, i - 1);
  }
  return heap;
}

int Heap_maximum(Heap *heap){
    return heap->values[0];
}

int Heap_extract_max(Heap *heap){
    if (heap->length < 1){
        return -INT_MAX;
    }
    int max = Heap_maximum(heap);
    heap->values[0] = heap->values[heap->length - 1];
    Heap_heapify(heap, 0);
    return max;
}

void _Heap_increase_key(Heap *heap, size_t i, int key){
    if (key < heap->values[i]){
        return;
    }

    heap->values[i] = key;
    size_t parent = Heap_parent(i);
    while (i > 0 && heap->values[parent] < heap->values[i]){
        swap(&heap->values[i], &heap->values[parent]);
        i = parent;
        parent = Heap_parent(i);
    }
}

void Heap_insert(Heap *heap, int key){
    if (heap->capacity <= heap->length) return;
    heap->length++;
    heap->values[heap->length - 1] = -INT_MAX;
    _Heap_increase_key(heap, heap->length - 1, key);
}
