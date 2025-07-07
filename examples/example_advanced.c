#include "../include/small_vec.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double value;
    char name[32];
} DataPoint;

void print_datapoint(const DataPoint* dp) {
    printf("ID: %d, Value: %.2f, Name: %s\n", dp->id, dp->value, dp->name);
}

int main() {
    printf("Small Vector - Advanced Example with Structs\n");
    printf("============================================\n\n");
    
    DataPoint* data = NULL;
    
    printf("1. Creating sample data points...\n");
    
    DataPoint samples[] = {
        {1, 3.14, "Pi"},
        {2, 2.71, "Euler"},
        {3, 1.41, "Sqrt2"},
        {4, 1.61, "Golden"},
        {5, 0.57, "Euler-Mascheroni"}
    };
    
    for (int i = 0; i < 5; i++) {
        vec_push(data, samples[i]);
        printf("   Added: ");
        print_datapoint(&samples[i]);
    }
    
    printf("\n2. Vector statistics:\n");
    printf("   Number of data points: %zu\n", vec_length(data));
    printf("   Vector capacity: %zu\n", vec_capacity(data));
    printf("   Memory per element: %zu bytes\n", sizeof(DataPoint));
    printf("   Total memory used: %zu bytes\n", vec_capacity(data) * sizeof(DataPoint));
    
    printf("\n3. Processing all data points:\n");
    double total_value = 0.0;
    for (size_t i = 0; i < vec_length(data); i++) {
        printf("   [%zu] ", i);
        print_datapoint(&data[i]);
        total_value += data[i].value;
    }
    
    printf("\n4. Statistical analysis:\n");
    printf("   Total value: %.6f\n", total_value);
    printf("   Average value: %.6f\n", total_value / vec_length(data));
    
    size_t max_index = 0;
    for (size_t i = 1; i < vec_length(data); i++) {
        if (data[i].value > data[max_index].value) {
            max_index = i;
        }
    }
    
    printf("   Maximum value: %.6f (%s)\n", 
           data[max_index].value, data[max_index].name);
    
    printf("\n5. Dynamic data addition:\n");
    for (int i = 6; i <= 10; i++) {
        DataPoint new_point = {i, (double)i / 2.0, "Computed"};
        vec_push(data, new_point);
        printf("   Added computed point: ");
        print_datapoint(&new_point);
    }
    
    printf("\n6. Final vector state:\n");
    printf("   Final length: %zu\n", vec_length(data));
    printf("   Final capacity: %zu\n", vec_capacity(data));
    printf("   Memory efficiency: %.1f%%\n", 
           (double)vec_length(data) / vec_capacity(data) * 100);
    
    vec_free(data);
    
    printf("\n7. Advanced example completed successfully!\n");
    
    return 0;
}
