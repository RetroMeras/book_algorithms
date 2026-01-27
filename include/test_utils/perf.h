#ifndef PERF_H
#define PERF_H

#include <stddef.h>
#include <stdbool.h>
#include "sorting/sorting.h"

// Performance measurement structure
typedef struct {
    const char *algorithm;
    size_t array_size;
    double time_ms;
    int num_runs;
    bool stable;
    bool in_place;
} perf_result_t;

// Performance test configuration
typedef struct {
    size_t *sizes;
    size_t num_sizes;
    int num_runs_per_size;
    int min_value;
    int max_value;
} perf_config_t;

// Performance testing functions
void benchmark_sorting_algorithms(const perf_config_t *config);
void compare_algorithms_same_data(size_t array_size, int num_runs);
void scalability_test(size_t start_size, size_t end_size, int multiplier);

// Utility functions
void generate_random_array(int *arr, size_t n, int min, int max);
void generate_sorted_array(int *arr, size_t n);
void generate_reverse_array(int *arr, size_t n);
void generate_partially_sorted_array(int *arr, size_t n, float sortedness);

#endif
