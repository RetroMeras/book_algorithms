#include "common.h"
#include "data_structures/heap.h"
#include "sorting/sorting.h"

/**
 * Heap Sort - build max-heap,
 * since first element is max we can swap it with last
 * now we set length of heap as length - 1
 * then we heapify first element. And repeat until finished
 */
void heap_sort(int *arr, size_t n) {
  if (n <= 1)
    return;
  Heap heap = Heap_build(arr, n);
  size_t len = heap.length;
  for (size_t i = len - 1; i > 0; i--) {
    swap(&heap.values[0], &heap.values[i]);
    heap.length--;
    Heap_heapify(&heap, 0);
  }
}
