#include "common.h"
#include "sorting/sorting.h"
#include <assert.h>
#include <string.h>

void test_bubble_sort_basic() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    size_t n = ARRAY_SIZE(arr);
    
    bubble_sort(arr, n);

    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("✓ Basic bubble sort test passed\n");
}

void test_bubble_sort_already_sorted() {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t n = ARRAY_SIZE(arr);
    
    bubble_sort(arr, n);
    
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("✓ Already sorted test passed\n");
}

void test_bubble_sort_reverse() {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    size_t n = ARRAY_SIZE(arr);
    
    bubble_sort(arr, n);
    
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("✓ Reverse sorted test passed\n");
}

void test_bubble_sort_duplicates() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
    size_t n = ARRAY_SIZE(arr);
    
    bubble_sort(arr, n);
    
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("✓ Duplicates test passed\n");
}

void test_bubble_sort_single() {
    int arr[] = {42};
    int expected[] = {42};
    
    bubble_sort(arr, 1);
    
    assert(arr[0] == expected[0]);
    printf("✓ Single element test passed\n");
}

int main() {
    test_bubble_sort_basic();
    test_bubble_sort_already_sorted();
    test_bubble_sort_reverse();
    test_bubble_sort_duplicates();
    test_bubble_sort_single();
    
    printf("\n✅ All bubble sort tests passed!\n");
    return 0;
}
