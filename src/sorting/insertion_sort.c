#include "sorting/sorting.h"

/**
 * Insertion Sort - builds sorted array one element at a time
 * 
 * How it works:
 * 1. Start from second element (index 1)
 * 2. Compare with elements before it
 * 3. Shift larger elements to the right
 * 4. Insert current element in correct position
 * 
 * Like sorting playing cards in your hand!
 */
void insertion_sort(int *arr, size_t n) {
    // Start from second element
    for (size_t j = 1; j < n; j++){
        int key = arr[j];
        int i = j - 1;
        
        while (i >= 0 && arr[i] > key){
            arr[i+1] = arr[i];
            i = i - 1;
        }
        arr[i+1] = key;
    }

}
