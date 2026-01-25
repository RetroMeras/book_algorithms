#include "common.h"
#include "sorting/sorting.h"

/**
 * Selection Sort - builds sorted array one element at a time
 * 
 * How it works:
 * 1. Start from first element (index 0)
 * 2. Search smallest element starting from current
 * 3. Swap current element with smallest
 * 
 */
void selection_sort(int *arr, size_t n){
    for (size_t j = 0; j < n-1; j++){
        size_t smallest_idx = j;
        for (size_t i = j+1; i < n; i++){
            if (arr[smallest_idx] > arr[i]){
                smallest_idx = i;
            }
        }
        swap(&arr[smallest_idx], &arr[j]);
    }
}


/**
 * Loop invariant:
 *  First j elements are already placed correct order
 * Worst case:
 *  inner loop each time must run until n,
 *  for example, with input <2, 3, 4, 5, 1>
 *  T(N) = n-1 + n-2 + ... + 1 = n(n-1)/2 ~ O(n^2)
 *
 * Idea:
 * 1. Check if array is single cycle, if yes, replace 2 parts and finish
 * 2. Split into correctly ordered parts, sort parts based on smalles elements
 * 3. Selection sort with skips of entire parts. 
 *
 */
