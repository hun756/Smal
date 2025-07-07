#include "../include/small_vec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* data;
    size_t len;
} String;

String string_create(const char* str) {
    String s;
    s.len = strlen(str);
    s.data = malloc(s.len + 1);
    strcpy(s.data, str);
    return s;
}

void string_free(String* s) {
    free(s->data);
    s->data = NULL;
    s->len = 0;
}

int main(void) {
    printf("Small Vector - String Processing Example\n");
    printf("=======================================\n\n");
    
    String* strings = NULL;
    
    printf("1. Adding strings to vector...\n");
    const char* sample_strings[] = {
        "Hello", "World", "CMake", "Professional", "Vector", "Implementation"
    };
    
    for (int i = 0; i < 6; i++) {
        String s = string_create(sample_strings[i]);
        vec_push(strings, s);
        printf("   Added: \"%s\" (length: %zu)\n", s.data, s.len);
    }
    
    printf("\n2. String vector information:\n");
    printf("   Number of strings: %zu\n", vec_length(strings));
    printf("   Vector capacity: %zu\n", vec_capacity(strings));
    
    printf("\n3. Processing all strings:\n");
    size_t total_length = 0;
    for (size_t i = 0; i < vec_length(strings); i++) {
        printf("   [%zu] \"%s\" (%zu chars)\n", i, strings[i].data, strings[i].len);
        total_length += strings[i].len;
    }
    
    printf("\n4. String statistics:\n");
    printf("   Total characters: %zu\n", total_length);
    printf("   Average length: %.2f\n", (double)total_length / vec_length(strings));
    
    size_t max_index = 0;
    for (size_t i = 1; i < vec_length(strings); i++) {
        if (strings[i].len > strings[max_index].len) {
            max_index = i;
        }
    }
    
    printf("   Longest string: \"%s\" (%zu chars)\n", 
           strings[max_index].data, strings[max_index].len);
    
    printf("\n5. Concatenating all strings:\n");
    char* result = malloc(total_length + vec_length(strings) + 1);
    result[0] = '\0';
    
    for (size_t i = 0; i < vec_length(strings); i++) {
        strcat(result, strings[i].data);
        if (i < vec_length(strings) - 1) {
            strcat(result, " ");
        }
    }
    
    printf("   Result: \"%s\"\n", result);
    
    for (size_t i = 0; i < vec_length(strings); i++) {
        string_free(&strings[i]);
    }
    vec_free(strings);
    free(result);
    
    printf("\n6. String processing example completed successfully!\n");
    
    return 0;
}
