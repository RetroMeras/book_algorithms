#include "sorting/sorting.h"

// Helper function to visualize sorting steps
void print_step(int *arr, size_t n, int current, const char *msg) {
    printf("%s: ", msg);
    for (size_t i = 0; i < n; i++) {
        if (i == current) {
            printf("[%d] ", arr[i]);  // Highlight current
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22};
    size_t n = ARRAY_SIZE(arr);
    
    printf("Insertion Sort Demonstration\n");
    printf("============================\n\n");
    
    printf("Original array: ");
    print_array(arr, n);
    printf("\n");
    
    // Manual step-through for educational purposes
    printf("Step-by-step process:\n");
    for (size_t i = 1; i < n; i++) {
        printf("\nPass %zu: Inserting element at index %zu\n", i, i);
        print_step(arr, n, i, "Before");
        
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        
        print_step(arr, n, j + 1, "After ");
    }
    
    printf("\n============================\n");
    printf("Final sorted array: ");
    print_array(arr, n);
    
    // Performance comparison
    printf("\n\nPerformance characteristics:\n");
    printf("- Best case (sorted): O(n)\n");
    printf("- Worst case (reverse): O(n²)\n");
    printf("- Space complexity: O(1)\n");
    printf("- Stable: Yes\n");
    printf("- Good for: Small or nearly sorted arrays\n");
    
    return 0;
}
