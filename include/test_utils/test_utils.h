#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>
#include <stddef.h>

// Type for sorting function
typedef void (*sort_func_t)(int *arr, size_t n);

// Test utilities
bool check_ordered(int *arr, size_t n);
bool arrays_equal(int *a, int *b, size_t n);
void copy_array(int *dest, int *src, size_t n);
void print_array(int *arr, size_t n);

// Test runner
typedef struct {
    const char *name;
    void (*test_func)(void);
} test_case_t;

void run_tests(test_case_t *tests, size_t count, const char *suite_name);

#endif
