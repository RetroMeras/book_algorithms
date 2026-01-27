#include "test_utils/perf.h"
#include "test_utils/test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Static array of sorting algorithms to test
typedef struct {
    const char *name;
    sort_func_t func;
    bool stable;
    bool in_place;
} sorting_algorithm_t;

static sorting_algorithm_t algorithms[] = {
    {"Bubble Sort", bubble_sort, true, true},
    {"Insertion Sort", insertion_sort, true, true},
    {"Selection Sort", selection_sort, false, true},
    {"Merge Sort", merge_sort, true, false},
    {"Heap Sort", heap_sort, true, true},
};

static const size_t num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

// Generate test data
void generate_random_array(int *arr, size_t n, int min, int max) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    
    for (size_t i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void generate_sorted_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = (int)i;
    }
}

void generate_reverse_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = (int)(n - i - 1);
    }
}

void generate_partially_sorted_array(int *arr, size_t n, float sortedness) {
    // Generate sorted array
    generate_sorted_array(arr, n);
    
    // Introduce some randomness based on sortedness parameter
    size_t num_swaps = (size_t)(n * (1.0 - sortedness));
    
    for (size_t i = 0; i < num_swaps; i++) {
        size_t idx1 = rand() % n;
        size_t idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

// Benchmark a single algorithm
double benchmark_algorithm(sort_func_t sort_func, int *data, size_t n, int num_runs) {
    double total_time = 0.0;
    
    for (int run = 0; run < num_runs; run++) {
        // Create a fresh copy of the data for this run
        int *copy = malloc(n * sizeof(int));
        if (!copy) {
            fprintf(stderr, "Memory allocation failed!\n");
            return -1.0;
        }
        memcpy(copy, data, n * sizeof(int));
        
        // Measure time
        clock_t start = clock();
        sort_func(copy, n);
        clock_t end = clock();
        
        // Verify correctness
        if (!check_ordered(copy, n)) {
            fprintf(stderr, "ERROR: Sorting algorithm produced incorrect result!\n");
            free(copy);
            return -1.0;
        }
        
        // Accumulate time
        total_time += ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0; // Convert to ms
        
        free(copy);
    }
    
    return total_time / num_runs;
}

// Benchmark all algorithms on different array sizes
void benchmark_sorting_algorithms(const perf_config_t *config) {
    printf("==============================================\n");
    printf("        PERFORMANCE BENCHMARK REPORT\n");
    printf("==============================================\n\n");
    
    printf("Configuration:\n");
    printf("  Number of runs per size: %d\n", config->num_runs_per_size);
    printf("  Value range: [%d, %d]\n\n", config->min_value, config->max_value);
    
    printf("%-20s", "Array Size");
    for (size_t i = 0; i < num_algorithms; i++) {
        printf(" | %-15s", algorithms[i].name);
    }
    printf("\n");
    
    for (size_t size_idx = 0; size_idx < config->num_sizes; size_idx++) {
        size_t n = config->sizes[size_idx];
        printf("%-20zu", n);
        
        // Generate test data once for all algorithms
        int *test_data = malloc(n * sizeof(int));
        if (!test_data) {
            fprintf(stderr, "Failed to allocate memory for size %zu\n", n);
            continue;
        }
        generate_random_array(test_data, n, config->min_value, config->max_value);
        
        // Test each algorithm
        for (size_t algo_idx = 0; algo_idx < num_algorithms; algo_idx++) {
            double avg_time = benchmark_algorithm(
                algorithms[algo_idx].func, 
                test_data, 
                n, 
                config->num_runs_per_size
            );
            
            if (avg_time >= 0) {
                printf(" | %-15.3f", avg_time);
            } else {
                printf(" | %-15s", "ERROR");
            }
        }
        printf("\n");
        
        free(test_data);
    }
    
    printf("\nNote: Times are in milliseconds (ms)\n");
}

// Compare all algorithms on the same exact data
void compare_algorithms_same_data(size_t array_size, int num_runs) {
    printf("\n==============================================\n");
    printf("    COMPARISON WITH SAME INPUT DATA\n");
    printf("==============================================\n\n");
    
    printf("Array size: %zu, Number of runs: %d\n\n", array_size, num_runs);
    
    // Generate test data
    int *test_data = malloc(array_size * sizeof(int));
    generate_random_array(test_data, array_size, -10000, 10000);
    
    // Make copies for each algorithm
    int **copies = malloc(num_algorithms * sizeof(int*));
    for (size_t i = 0; i < num_algorithms; i++) {
        copies[i] = malloc(array_size * sizeof(int));
        memcpy(copies[i], test_data, array_size * sizeof(int));
    }
    
    printf("%-20s | %-10s | %-10s | %-10s\n", 
           "Algorithm", "Time (ms)", "Stable", "In-place");
    printf("------------------------------------------------------------\n");
    
    for (size_t i = 0; i < num_algorithms; i++) {
        clock_t start = clock();
        algorithms[i].func(copies[i], array_size);
        clock_t end = clock();
        
        double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        
        printf("%-20s | %-10.3f | %-10s | %-10s\n",
               algorithms[i].name,
               time_ms,
               algorithms[i].stable ? "Yes" : "No",
               algorithms[i].in_place ? "Yes" : "No");
        
        // Verify
        if (!check_ordered(copies[i], array_size)) {
            printf("  ⚠️  Warning: %s may have errors!\n", algorithms[i].name);
        }
    }
    
    // Cleanup
    for (size_t i = 0; i < num_algorithms; i++) {
        free(copies[i]);
    }
    free(copies);
    free(test_data);
}

// Test scalability as array size grows
void scalability_test(size_t start_size, size_t end_size, int multiplier) {
    printf("\n==============================================\n");
    printf("          SCALABILITY TEST\n");
    printf("==============================================\n\n");
    
    printf("Testing from size %zu to %zu (multiplier: %d)\n\n", 
           start_size, end_size, multiplier);
    
    printf("%-10s", "Size");
    for (size_t i = 0; i < num_algorithms; i++) {
        printf(" | %-12s", algorithms[i].name);
    }
    printf(" | %-12s\n", "Relative O(n²)");
    
    for (size_t n = start_size; n <= end_size; n *= multiplier) {
        printf("%-10zu", n);
        
        int *test_data = malloc(n * sizeof(int));
        generate_random_array(test_data, n, -10000, 10000);
        
        double slowest_time = 0.0;
        
        for (size_t i = 0; i < num_algorithms; i++) {
            double time = benchmark_algorithm(algorithms[i].func, test_data, n, 1);
            
            if (time > slowest_time) {
                slowest_time = time;
            }
            
            printf(" | %-12.3f", time);
        }
        
        // Calculate theoretical O(n²) relative time
        double expected = pow((double)n / start_size, 2) * 10.0; // Arbitrary baseline
        printf(" | %-12.3f\n", expected);
        
        free(test_data);
    }
}

// Performance test for different data patterns
void test_data_patterns() {
    printf("\n==============================================\n");
    printf("        DATA PATTERN SENSITIVITY\n");
    printf("==============================================\n\n");
    
    const size_t n = 5000;
    const char *patterns[] = {"Random", "Sorted", "Reverse", "Partially Sorted"};
    const int num_patterns = 4;
    
    printf("Array size: %zu\n\n", n);
    printf("%-20s", "Algorithm/Pattern");
    for (int p = 0; p < num_patterns; p++) {
        printf(" | %-15s", patterns[p]);
    }
    printf("\n");
    
    for (size_t algo_idx = 0; algo_idx < num_algorithms; algo_idx++) {
        printf("%-20s", algorithms[algo_idx].name);
        
        for (int pattern = 0; pattern < num_patterns; pattern++) {
            int *data = malloc(n * sizeof(int));
            
            switch (pattern) {
                case 0: // Random
                    generate_random_array(data, n, -10000, 10000);
                    break;
                case 1: // Sorted
                    generate_sorted_array(data, n);
                    break;
                case 2: // Reverse
                    generate_reverse_array(data, n);
                    break;
                case 3: // Partially sorted (80%)
                    generate_partially_sorted_array(data, n, 0.8f);
                    break;
            }
            
            double time = benchmark_algorithm(algorithms[algo_idx].func, data, n, 3);
            printf(" | %-15.3f", time);
            
            free(data);
        }
        printf("\n");
    }
}

int main(void) {
    // Configuration for benchmark
    size_t sizes[] = {100, 500, 1000, 5000, 10000};
    perf_config_t config = {
        .sizes = sizes,
        .num_sizes = sizeof(sizes) / sizeof(sizes[0]),
        .num_runs_per_size = 5,
        .min_value = -10000,
        .max_value = 10000
    };
    
    // Run all performance tests
    benchmark_sorting_algorithms(&config);
    compare_algorithms_same_data(2000, 3);
    scalability_test(100, 1600, 2);
    test_data_patterns();
    
    printf("\n==============================================\n");
    printf("✅ Performance testing completed!\n");
    printf("==============================================\n");
    
    return 0;
}
