#include "../include/small_vec.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            exit(1); \
        } else { \
            printf("PASS: %s\n", message); \
        } \
    } while(0)

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    int* vec = NULL;
    TEST_ASSERT(vec_length(vec) == 0, "NULL pointer length");
    TEST_ASSERT(vec_capacity(vec) == 0, "NULL pointer capacity");
    
    vec_push(vec, 42);
    TEST_ASSERT(vec_length(vec) == 1, "Single element length");
    TEST_ASSERT(vec[0] == 42, "Single element value");
    
    vec_free(vec);
}

void test_memory_management() {
    printf("Testing memory management...\n");
    
    for (int iter = 0; iter < 10; iter++) {
        int* vec = NULL;
        
        for (int i = 0; i < 100; i++) {
            vec_push(vec, i);
        }
        
        TEST_ASSERT(vec_length(vec) == 100, "Memory management iteration");
        vec_free(vec);
    }
}

void test_different_sizes() {
    printf("Testing different data sizes...\n");
    
    char* char_vec = NULL;
    for (char c = 'a'; c <= 'z'; c++) {
        vec_push(char_vec, c);
    }
    TEST_ASSERT(vec_length(char_vec) == 26, "Char vector length");
    vec_free(char_vec);
    
    long long* ll_vec = NULL;
    vec_push(ll_vec, 1000000000000LL);
    vec_push(ll_vec, -1000000000000LL);
    TEST_ASSERT(vec_length(ll_vec) == 2, "Long long vector length");
    TEST_ASSERT(ll_vec[0] == 1000000000000LL, "Long long positive value");
    TEST_ASSERT(ll_vec[1] == -1000000000000LL, "Long long negative value");
    vec_free(ll_vec);
}

void test_capacity_doubling() {
    printf("Testing capacity doubling strategy...\n");
    
    int* vec = NULL;
    size_t prev_capacity = 0;
    
    for (int i = 0; i < 100; i++) {
        vec_push(vec, i);
        size_t current_capacity = vec_capacity(vec);
        
        if (current_capacity > prev_capacity) {
            if (prev_capacity > 0) {
                TEST_ASSERT(current_capacity >= prev_capacity * 2, "Capacity doubling");
            }
            prev_capacity = current_capacity;
        }
    }
    
    vec_free(vec);
}

int main() {
    printf("Running Comprehensive Small Vector Tests...\n");
    
    test_edge_cases();
    test_memory_management();
    test_different_sizes();
    test_capacity_doubling();
    
    printf("All comprehensive tests passed!\n");
    return 0;
}
