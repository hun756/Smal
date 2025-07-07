#include "../include/small_vec.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define BENCHMARK_ITERATIONS 1000000

void benchmark_push_operations(void) {
    printf("Benchmarking push operations...\n");
    
    clock_t start = clock();
    
    int* vec = NULL;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        vec_push(vec, i);
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Push operations: %d elements in %f seconds\n", 
           BENCHMARK_ITERATIONS, cpu_time_used);
    printf("Operations per second: %.0f\n", 
           BENCHMARK_ITERATIONS / cpu_time_used);
    
    vec_free(vec);
}

void benchmark_access_operations(void) {
    printf("Benchmarking access operations...\n");
    
    int* vec = NULL;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        vec_push(vec, i);
    }
    
    clock_t start = clock();
    
    volatile int sum = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        sum += vec[i];
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Access operations: %d elements in %f seconds\n", 
           BENCHMARK_ITERATIONS, cpu_time_used);
    printf("Operations per second: %.0f\n", 
           BENCHMARK_ITERATIONS / cpu_time_used);
    printf("Sum (to prevent optimization): %d\n", sum);
    
    vec_free(vec);
}

void benchmark_memory_usage(void) {
    printf("Benchmarking memory usage patterns...\n");
    
    int* vec = NULL;
    size_t prev_capacity = 0;
    int realloc_count = 0;
    
    for (int i = 0; i < 10000; i++) {
        vec_push(vec, i);
        size_t current_capacity = vec_capacity(vec);
        
        if (current_capacity > prev_capacity) {
            realloc_count++;
            printf("Realloc %d: capacity %zu -> %zu (length: %zu)\n", 
                   realloc_count, prev_capacity, current_capacity, vec_length(vec));
            prev_capacity = current_capacity;
        }
    }
    
    printf("Total reallocations: %d\n", realloc_count);
    printf("Final capacity: %zu\n", vec_capacity(vec));
    printf("Final length: %zu\n", vec_length(vec));
    printf("Memory efficiency: %.2f%%\n", 
           (double)vec_length(vec) / vec_capacity(vec) * 100);
    
    vec_free(vec);
}

int main(void) {
    printf("Running Performance Tests...\n");
    
    benchmark_push_operations();
    printf("\n");
    
    benchmark_access_operations();
    printf("\n");
    
    benchmark_memory_usage();
    printf("\n");
    
    printf("Performance tests completed!\n");
    return 0;
}
