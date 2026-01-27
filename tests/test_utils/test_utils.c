#include "test_utils/test_utils.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

bool check_ordered(int *arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }
    return true;
}

bool arrays_equal(int *a, int *b, size_t n) {
    return memcmp(a, b, n * sizeof(int)) == 0;
}

void copy_array(int *dest, int *src, size_t n) {
    memcpy(dest, src, n * sizeof(int));
}

void run_tests(test_case_t *tests, size_t count, const char *suite_name) {
    printf("\n🧪 Running %s tests...\n", suite_name);
    
    size_t passed = 0;
    for (size_t i = 0; i < count; i++) {
        printf("  %s... ", tests[i].name);
        fflush(stdout);
        
        tests[i].test_func();
        printf("✓\n");
        passed++;
    }
    
    printf("\n✅ %s: %zu/%zu tests passed\n", suite_name, passed, count);
}

void print_array(int *arr, size_t n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}
