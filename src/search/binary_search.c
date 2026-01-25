#include "search/search.h"

size_t _binary_search(int target, int *arr, size_t start, size_t end){
    if (end - start == 0){
        return -1;
    }
    if (end - start == 1){
        if (target == arr[start]){return 0;}
        return -1;
    }
    size_t m = start + (end - start) / 2;
    if (target == arr[m]){
        return m;
    }
    if (target < arr[m]){
        return _binary_search(target, arr, start, m);
    }
    return _binary_search(target, arr, m, end);
}

/**
 * Binary search - goes through all the array one by one and compares target to current element
 * 
 * How it works:
 * 1. From the middle point
 * 2. If target < then current ignore second half, else ignore first half
 * 3. Repeat step 1
 *
 */
size_t binary_search(int target, int *arr, size_t n) {
    return _binary_search(target, arr, 0, n);
}
