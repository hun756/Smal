#ifndef SMAL_VEC_sh43d9
#define SMAL_VEC_sh43d9

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct BufHdr {
    size_t length;
    size_t capacity;
    char buffer[];
} BufHdr;

#define buf__hdr(b) ((BufHdr*)((char*)b - offsetof(BufHdr, buffer)))

#define vec_fits(b, n) (vec_length(b) + (n) <= vec_capacity(b))
#define vec_fit(b, n) (vec_fits(b, n) ? 0 : ((b) = vec_grow((b), vec_length(b) + (n), sizeof(*(b))))))

#define vec_length(b) ((b)? buf__hdr(b)->length : 0)
#define vec_capacity(b) ((b)? buf__hdr(b)->capacity : 0)

#define vec_push(b, x) ((vec_fit(b, 1), b[vec_length(b)] = (x), buf__hdr(b)->length++)
#define vec_free(b) ((b) ? (free(buf__hdr(b)), (b) = NULL) : (void)0)


extern inline void* vec_grow(const void* buf, size_t new_len, size_t elem_size) {
    size_t new_capacity = MAX(1 + 2 * vec_capacity(buf), new_len);
    assert(new_len <= new_capacity);
    size_t new_size = offsetof(BufHdr, buffer) +  new_capacity * elem_size;

    BufHdr* new_hdr;
    
    if(buf) {
        new_hdr = (BufHdr*)realloc(buf__hdr(buf), new_size);
    } else {
        new_hdr = (BufHdr*)malloc(new_size);
        new_hdr->length = 0;
    } 

    new_hdr->capacity = new_capacity;
    return new_hdr->buffer;
}   

#endif /* end of include guard SMAL_VEC_sh43d9 */