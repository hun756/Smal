# SMALL VECTOR

## Small Vector Implementation ~50 lines.

### Usage

```cpp
#include "include/small_vec.h"
#include <stdio.h>

int main() {
    int* buf = NULL;

    vec_push(buf, 42);
    vec_push(buf, 1234);

    for (int i = 0; i <vec_length(buf); i++) {
        int x = buf[i];
        printf("%d\n", x);
    }
        
    vec_free(buf);
}
```

```cpp
#define MAX_ITERATION 1024

int main() {
    int* buf = NULL;

    for (size_t i = 0; i < MAX_ITERATION; i++) {
        vec_push(buf, i);
    }

    assert(vec_length(buf) == MAX_ITERATION);

    for (size_t i = 0; i < vec_length(buf); i++) {
        assert(buf[i] == i);
    }
}
```