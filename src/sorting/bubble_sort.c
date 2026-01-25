#include "common.h"
#include "sorting/sorting.h"

/**
 * Bubble Sort - swaps elements until sorted
 * 
 */
void bubble_sort(int *arr, size_t n){
    for (size_t j = 0; j < n; j++){
        for (size_t i = n - 1; i > j; i--){
            if (arr[i] < arr[i-1]){
                swap(&arr[i], &arr[i-1]);
            }
        }
    }
}

