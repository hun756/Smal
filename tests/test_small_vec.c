#include "../include/small_vec.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            return 1; \
        } else { \
            printf("PASS: %s\n", message); \
        } \
    } while(0)

int main(void) {
    printf("Running Small Vector Tests...\n");
    
    {
        int* vec = NULL;
        vec_push(vec, 42);
        vec_push(vec, 84);
        
        TEST_ASSERT(vec_length(vec) == 2, "Basic push and length test");
        TEST_ASSERT(vec[0] == 42, "First element value");
        TEST_ASSERT(vec[1] == 84, "Second element value");
        
        vec_free(vec);
    }
    
    {
        int* vec = NULL;
        TEST_ASSERT(vec_length(vec) == 0, "Empty vector length");
        TEST_ASSERT(vec_capacity(vec) == 0, "Empty vector capacity");
    }
    
    {
        int* vec = NULL;
        const size_t count = 1000;
        
        for (size_t i = 0; i < count; i++) {
            vec_push(vec, (int)i);
        }
        
        TEST_ASSERT(vec_length(vec) == count, "Large vector length");
        
        for (size_t i = 0; i < count; i++) {
            TEST_ASSERT(vec[i] == (int)i, "Large vector element values");
        }
        
        vec_free(vec);
    }
    
    {
        int* vec = NULL;
        vec_push(vec, 1);
        size_t cap1 = vec_capacity(vec);
        
        vec_push(vec, 2);
        vec_push(vec, 3);
        size_t cap2 = vec_capacity(vec);
        
        TEST_ASSERT(cap2 >= cap1, "Capacity growth test");
        vec_free(vec);
    }
    
    {
        double* vec = NULL;
        vec_push(vec, 3.14);
        vec_push(vec, 2.71);
        
        TEST_ASSERT(vec_length(vec) == 2, "Double vector length");
        TEST_ASSERT(vec[0] == 3.14, "Double vector first element");
        TEST_ASSERT(vec[1] == 2.71, "Double vector second element");
        
        vec_free(vec);
    }
    
    printf("All tests passed!\n");
    return 0;
}
