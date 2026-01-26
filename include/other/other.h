#ifndef OTHER_H
#define OTHER_H

#include "common.h"

typedef struct MaxSubarray{
    size_t low, high;
    int sum;
} MaxSubarray;

MaxSubarray max_subarray(int *arr, size_t low, size_t high);

#endif
