#include "other/other.h"
#include "limits.h"

MaxSubarray _max_crossing(int *arr, size_t low, size_t mid, size_t high){
    int left_sum = -INT_MAX;
    int sum = 0;
    size_t max_left = mid;

    for (size_t i = mid; i >= low; i--){
        sum = sum + arr[i];
        if (sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }
    
    int right_sum = -INT_MAX;
    size_t max_right = mid;
    sum = 0;
    for (size_t i = mid; i < high; i++){
        sum = sum + arr[i];
        if (sum > right_sum){
            right_sum = sum;
            max_right = i;
        }
    }
    return (MaxSubarray){max_left, max_right, left_sum + right_sum};
}


MaxSubarray max_subarray(int *arr, size_t low, size_t high){
    if (high == low)
        return (MaxSubarray){low, high, arr[low]};
    
    size_t mid = low + (high-low)/2;
    MaxSubarray left_max = max_subarray(arr, low, mid);
    MaxSubarray right_max = max_subarray(arr, mid+1, high);

    MaxSubarray crossing_max = _max_crossing(arr, low, mid, high);

    if (left_max.sum >= right_max.sum &&  left_max.sum >= crossing_max.sum)
        return left_max;
    if (right_max.sum >= crossing_max.sum)
        return right_max;
    return crossing_max;
}


