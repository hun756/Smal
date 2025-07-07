#include "../include/small_vec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SMALL_SIZE 1000
#define MEDIUM_SIZE 100000
#define LARGE_SIZE 10000000

void benchmark_size(const char* name, size_t size) {
    printf("Benchmarking %s (%zu elements):\n", name, size);
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    int* vec = NULL;
    for (size_t i = 0; i < size; i++) {
        vec_push(vec, (int)i);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("  Push operations: %.6f seconds (%.0f ops/sec)\n", 
           cpu_time_used, size / cpu_time_used);
    
    start = clock();
    volatile long sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += vec[i];
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("  Access operations: %.6f seconds (%.0f ops/sec)\n", 
           cpu_time_used, size / cpu_time_used);
    printf("  Sum: %ld (to prevent optimization)\n", sum);
    
    printf("  Memory - Length: %zu, Capacity: %zu, Efficiency: %.1f%%\n",
           vec_length(vec), vec_capacity(vec), 
           (double)vec_length(vec) / vec_capacity(vec) * 100);
    
    vec_free(vec);
    printf("\n");
}

int main(void) {
    printf("Performance Benchmark Suite\n");
    printf("===========================\n\n");
    
    benchmark_size("Small Dataset", SMALL_SIZE);
    benchmark_size("Medium Dataset", MEDIUM_SIZE);
    benchmark_size("Large Dataset", LARGE_SIZE);
    
    printf("All benchmarks completed!\n");
    
    return 0;
}
