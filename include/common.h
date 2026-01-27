#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Utility macros
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Comparison function type
typedef int (*compare_fn)(const void*, const void*);

// Utility functions
void swap(int *a, int *b);

#endif
