#ifndef SORTING_H
#define SORTING_H

#include "common.h"

// Insertion Sort
// Time: O(n^2) worst, O(n) best | Space: O(1)
void insertion_sort(int *arr, size_t n);

// Selection Sort
// Time: O(n^2) worst, O(n) best | Space: O(1)
void selection_sort(int *arr, size_t n);

// Merge Sort
// Time: O(nlog2(n)) worst, O(nlog2(n)) best | Space: O(n)
void merge_sort(int *arr, size_t n);

// Bubble Sort
// Time: O(n^2) worst, O(n^2) best | Space: O(1)
void bubble_sort(int *arr, size_t n);


#endif
