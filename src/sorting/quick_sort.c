#include "common.h"
#include "rng.h"
#include "sorting/sorting.h"

size_t _partition(int *arr, size_t start, size_t end) {
  size_t m = rand_basic(start, end);
  // size_t m = end - 1;
  int x = arr[m]; // pivot
  swap(&arr[m], &arr[end-1]);
  size_t i = start;
  for (size_t j = start; j < end - 1; j++) {
    if (arr[j] <=
        x) { // if less then pivot, then must be to the left of _partition
      swap(&arr[i], &arr[j]);
      i = i + 1;
    }
  }
  swap(&arr[i], &arr[end - 1]); // put pivot in the middle
  return i;
}

void _quick_sort(int *arr, size_t start, size_t end) {
  if (end <= start)
    return;

  size_t q = _partition(arr, start, end);
  _quick_sort(arr, start, q);
  _quick_sort(arr, q + 1, end);
}

/**
 * Quick Sort - breaks array into two parts and sorts them
 *
 */
void quick_sort(int *arr, size_t n) { _quick_sort(arr, 0, n); }

void _tail_quick_sort(int *arr, size_t start, size_t end){
  size_t p = start;
  while (p < end){
    size_t q = _partition(arr, p, end);
    _tail_quick_sort(arr, p, q);
    p = q + 1;
  }

}


/**
 * Tail Quick Sort - breaks array into two parts and sorts them
 *
 */
void tail_quick_sort(int *arr, size_t n) { _tail_quick_sort(arr, 0, n); }
