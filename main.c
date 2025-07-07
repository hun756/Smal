#include "include/small_vec.h"
#include <stdio.h>

#define MAX_ITERATION 1024

int main(void) {
    int* buf = NULL;

    for (size_t i = 0; i < MAX_ITERATION; i++) {
        vec_push(buf, i);
    }

    assert(vec_length(buf) == MAX_ITERATION);

    for (size_t i = 0; i < vec_length(buf); i++) {
        assert(buf[i] == (int)i);
    }

    vec_free(buf);
}
