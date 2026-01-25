#include "common.h"
#include "sorting/sorting.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

void merge(int *arr, size_t p, size_t q, size_t r){
    assert(p <= q && q < r);
    size_t n1 = q - p + 1;
    size_t n2 = r - q;

    int *left = malloc((n1+1) * sizeof(int));
    int *right = malloc((n2+1) * sizeof(int));

    if (!left || !right){
        free(left);
        free(right);
        return;
    }

    for (size_t i = 0; i<n1;i++){
        left[i] = arr[p + i];
    }
    left[n1] = INT_MAX;

    for (size_t i = 0; i<n2;i++){
        right[i] = arr[q + i + 1];
    }
    right[n2] = INT_MAX;

    size_t i = 0;
    size_t j = 0;
    for (size_t k = p; k <= r; k++){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i = i + 1;
        }else{
            arr[k] = right[j];
            j = j + 1;
        }
    }

    free(left);
    free(right);
}

void _merge_sort(int *arr, size_t p, size_t r){
    if (p < r){
        size_t q = p + (r - p)/2;

        _merge_sort(arr, p, q);
        _merge_sort(arr, q+1, r);

        merge(arr, p, q, r);
    } 
}

/**
 * Merge Sort - recurcive algorithm based on divide-and-concure approach
 * 
 * How it works:
 * 1. Check if array slice nois not trivial
 * 2. Split array slice in two halfs
 * 3. Apply for each half itself
 */
void merge_sort(int *arr, size_t n){
    if (n <= 1){ return; }
   _merge_sort(arr, 0, n-1); 
}

/**
 * if n = 1 then T(n) = O(1)
 * else T(n) = 2T(n/2) + cn
 *
 * So we divide log2(n) times, each time we get O(n') additional operations
 * log2(n) divisions each one has c(n/2) + c(n/2) = cn, ..., c(n/2^i) + ... + c(n/2^i) = cn
 * so we have cnlog2(n)
 * So worst time is O(nlog2(n))
 */
