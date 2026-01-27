#include "sorting/sorting.h"
#include "test_utils/test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test data
typedef struct {
    int *arr;
    size_t n;
    const char *desc;
} test_data_t;

// Common test cases
static int basic_array[] = {64, 34, 25, 12, 22, 11, 90};
static int sorted_array[] = {1, 2, 3, 4, 5};
static int reverse_array[] = {5, 4, 3, 2, 1};
static int duplicates_array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
static int single_array[] = {42};

static test_data_t test_cases[] = {
    {basic_array, sizeof(basic_array)/sizeof(basic_array[0]), "basic"},
    {sorted_array, sizeof(sorted_array)/sizeof(sorted_array[0]), "already sorted"},
    {reverse_array, sizeof(reverse_array)/sizeof(reverse_array[0]), "reverse sorted"},
    {duplicates_array, sizeof(duplicates_array)/sizeof(duplicates_array[0]), "with duplicates"},
    {single_array, sizeof(single_array)/sizeof(single_array[0]), "single element"}
};

// Generic test function
void test_sort_algorithm(sort_func_t sort_func, const char *algo_name) {
    printf("\n📊 Testing %s:\n", algo_name);
    
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        // Create a copy to preserve original
        int *copy = malloc(test_cases[i].n * sizeof(int));
        copy_array(copy, test_cases[i].arr, test_cases[i].n);
        
        // Sort
        sort_func(copy, test_cases[i].n);
        
        // Verify
        bool ok = check_ordered(copy, test_cases[i].n);
        
        if (ok) {
            printf("  ✓ %s test passed\n", test_cases[i].desc);
        } else {
            printf("  ✗ %s test failed!\n", test_cases[i].desc);
            printf("    Original: ");
            print_array(test_cases[i].arr, test_cases[i].n);
            printf("    Sorted:   ");
            print_array(copy, test_cases[i].n);
        }
        
        free(copy);
    }
}

int main(void) {
    printf("========================================\n");
    printf("        Sorting Algorithm Tests\n");
    printf("========================================\n");
    
    // Test all algorithms
    test_sort_algorithm(bubble_sort, "Bubble Sort");
    test_sort_algorithm(insertion_sort, "Insertion Sort");
    test_sort_algorithm(selection_sort, "Selection Sort");
    test_sort_algorithm(merge_sort, "Merge Sort");
    test_sort_algorithm(heap_sort, "Heap Sort");
    
    printf("\n========================================\n");
    printf("✅ All sorting algorithm tests completed!\n");
    printf("========================================\n");
    
    return 0;
}
