#include "../include/small_vec.h"
#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y;
} Point2D;

typedef struct {
    double x, y, z;
} Point3D;

double distance_2d(Point2D a, Point2D b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double distance_3d(Point3D a, Point3D b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
    printf("Small Vector - Mathematical Operations Example\n");
    printf("=============================================\n\n");
    
    printf("1. Working with 2D Points:\n");
    Point2D* points_2d = NULL;
    
    Point2D sample_2d[] = {
        {0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0},
        {-1.0, -1.0}, {2.0, 3.0}, {-2.0, 1.5}
    };
    
    for (int i = 0; i < 7; i++) {
        vec_push(points_2d, sample_2d[i]);
        printf("   Added point: (%.2f, %.2f)\n", sample_2d[i].x, sample_2d[i].y);
    }
    
    printf("\n2. Distances from origin:\n");
    Point2D origin_2d = {0.0, 0.0};
    for (size_t i = 0; i < vec_length(points_2d); i++) {
        double dist = distance_2d(points_2d[i], origin_2d);
        printf("   Point (%.2f, %.2f): distance = %.3f\n", 
               points_2d[i].x, points_2d[i].y, dist);
    }
    
    printf("\n3. Working with 3D Points:\n");
    Point3D* points_3d = NULL;
    
    Point3D sample_3d[] = {
        {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0}, {2.0, 3.0, 1.5}, {-1.0, -2.0, 0.5}
    };
    
    for (int i = 0; i < 7; i++) {
        vec_push(points_3d, sample_3d[i]);
        printf("   Added point: (%.2f, %.2f, %.2f)\n", 
               sample_3d[i].x, sample_3d[i].y, sample_3d[i].z);
    }
    
    printf("\n4. 3D Distances from origin:\n");
    Point3D origin_3d = {0.0, 0.0, 0.0};
    double total_distance = 0.0;
    for (size_t i = 0; i < vec_length(points_3d); i++) {
        double dist = distance_3d(points_3d[i], origin_3d);
        total_distance += dist;
        printf("   Point (%.2f, %.2f, %.2f): distance = %.3f\n", 
               points_3d[i].x, points_3d[i].y, points_3d[i].z, dist);
    }
    
    printf("\n5. Statistical analysis:\n");
    printf("   Total 2D points: %zu\n", vec_length(points_2d));
    printf("   Total 3D points: %zu\n", vec_length(points_3d));
    printf("   Average 3D distance: %.3f\n", total_distance / vec_length(points_3d));
    
    printf("\n6. Mathematical sequence (Fibonacci):\n");
    long long* fibonacci = NULL;
    
    vec_push(fibonacci, 0LL);
    vec_push(fibonacci, 1LL);
    
    for (int i = 2; i < 20; i++) {
        long long next = fibonacci[i-1] + fibonacci[i-2];
        vec_push(fibonacci, next);
    }
    
    printf("   Fibonacci sequence (first 20 numbers):\n");
    for (size_t i = 0; i < vec_length(fibonacci); i++) {
        printf("   F(%zu) = %lld\n", i, fibonacci[i]);
    }
    
    printf("\n7. Prime numbers up to 100:\n");
    int* primes = NULL;
    
    for (int n = 2; n <= 100; n++) {
        int is_prime = 1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            vec_push(primes, n);
        }
    }
    
    printf("   Found %zu prime numbers: ", vec_length(primes));
    for (size_t i = 0; i < vec_length(primes); i++) {
        printf("%d", primes[i]);
        if (i < vec_length(primes) - 1) printf(", ");
    }
    printf("\n");
    
    vec_free(points_2d);
    vec_free(points_3d);
    vec_free(fibonacci);
    vec_free(primes);
    
    printf("\n8. Mathematical operations example completed successfully!\n");
    
    return 0;
}
