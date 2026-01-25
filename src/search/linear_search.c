#include "search/search.h"

/**
 * Linear search - goes through all the array one by one and compares target to current element
 * 
 * How it works:
 * 1. Start from first element (index 0)
 * 2. Compare current element to target
 * 3. Go to next element and do step 2
 *
 */
size_t linear_search(int target, int *arr, size_t n) {
    // Start from second element
    for (size_t i = 0; i < n; i++){
        if (target == arr[i]){
            return i;
        }
    }
    return -1;
}
