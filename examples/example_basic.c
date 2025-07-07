#include "../include/small_vec.h"
#include <stdio.h>

int main() {
    printf("Small Vector - Basic Example\n");
    printf("============================\n\n");
    
    int* numbers = NULL;
    
    printf("1. Adding numbers to vector...\n");
    for (int i = 1; i <= 10; i++) {
        vec_push(numbers, i * i);
        printf("   Added %d (square of %d)\n", i * i, i);
    }
    
    printf("\n2. Vector information:\n");
    printf("   Length: %zu\n", vec_length(numbers));
    printf("   Capacity: %zu\n", vec_capacity(numbers));
    
    printf("\n3. Printing all elements:\n");
    for (size_t i = 0; i < vec_length(numbers); i++) {
        printf("   numbers[%zu] = %d\n", i, numbers[i]);
    }
    
    printf("\n4. Calculating sum:\n");
    int sum = 0;
    for (size_t i = 0; i < vec_length(numbers); i++) {
        sum += numbers[i];
    }
    printf("   Sum of all elements: %d\n", sum);
    
    // Clean up
    vec_free(numbers);
    
    printf("\n5. Memory cleaned up successfully!\n");
    
    return 0;
}
