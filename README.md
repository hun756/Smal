# Smal

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/SmallDataStructures)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![CMake](https://img.shields.io/badge/CMake-3.18%2B-blue.svg)](https://cmake.org/)

A high-performance, header-only C library providing lightweight data structures optimized for small to medium-sized datasets. Currently features a dynamic array (vector) implementation with plans for hash maps, linked lists, and other essential data structures.

## Features

- **Header-only library** - Easy integration, no separate compilation required
- **High performance** - Optimized for speed with minimal memory overhead
- **Type-safe macros** - Generic implementation that works with any data type
- **Memory efficient** - Smart capacity growth strategy (2x + 1)
- **Professional build system** - CMake-based with comprehensive testing and examples
- **Cross-platform** - Works on Windows, Linux, and macOS
- **Comprehensive testing** - Unit tests, performance tests, and memory validation

## Quick Start

### Basic Usage

```c
#include "small_vec.h"
#include <stdio.h>

int main() {
    // Create a vector of integers
    int* numbers = NULL;
    
    // Add elements
    vec_push(numbers, 42);
    vec_push(numbers, 84);
    vec_push(numbers, 126);
    
    // Access elements
    printf("Length: %zu\n", vec_length(numbers));
    for (size_t i = 0; i < vec_length(numbers); i++) {
        printf("numbers[%zu] = %d\n", i, numbers[i]);
    }
    
    // Clean up
    vec_free(numbers);
    
    return 0;
}
```

### Working with Structures

```c
typedef struct {
    int id;
    double value;
    char name[32];
} DataPoint;

int main() {
    DataPoint* data = NULL;
    
    DataPoint point = {1, 3.14, "Pi"};
    vec_push(data, point);
    
    printf("ID: %d, Value: %.2f, Name: %s\n", 
           data[0].id, data[0].value, data[0].name);
    
    vec_free(data);
    return 0;
}
```

## Building

### Prerequisites

- CMake 3.18 or higher
- C11 compatible compiler (GCC, Clang, MSVC)

### Quick Build

#### Windows:
```cmd
build.bat
```

#### Linux/macOS:
```bash
./build.sh
```

### Manual Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Build Options

```bash
# Debug build with all features
./build.sh --build-type Debug --with-benchmarks --with-docs

# Release build for production
./build.sh --build-type Release --no-tests --install

# Clean build with custom job count
./build.sh --clean -j 8
```

## API Reference

### Vector Operations

| Function | Description | Time Complexity |
|----------|-------------|-----------------|
| `vec_push(vec, item)` | Add element to end of vector | O(1) amortized |
| `vec_length(vec)` | Get number of elements | O(1) |
| `vec_capacity(vec)` | Get current capacity | O(1) |
| `vec_free(vec)` | Free vector memory | O(1) |

### Memory Management

The vector automatically manages memory allocation and reallocation:
- Initial capacity: 1 element
- Growth strategy: `new_capacity = max(2 * old_capacity + 1, required_capacity)`
- Memory is automatically freed when `vec_free()` is called

## Performance

### Benchmarks

Run performance tests to see how the library performs on your system:

```bash
./build.sh --with-benchmarks
./build/benchmarks/benchmark_performance
```

### Expected Performance

- **Push operations**: ~100M ops/sec on modern hardware
- **Access operations**: ~1B ops/sec (native array access)
- **Memory efficiency**: ~90-95% (depends on growth pattern)

## Testing

The library includes comprehensive tests:

```bash
# Run all tests
./build.sh
ctest

# Run specific test
./build/tests/test_small_vec
./build/tests/test_comprehensive
./build/tests/test_performance
```

## Examples

Explore the `examples/` directory for more usage patterns:

- `example_basic.c` - Basic vector operations
- `example_advanced.c` - Working with structures

```bash
./build/examples/example_basic
./build/examples/example_advanced
```

## Integration

### Using in Your Project

1. **Copy header**: Include `include/small_vec.h` in your project
2. **CMake integration**: Use `find_package(SmallDataStructures)` if installed
3. **Direct inclusion**: Simply `#include "small_vec.h"`

### CMake Integration

```cmake
find_package(SmallDataStructures REQUIRED)
target_link_libraries(your_target PRIVATE SmallDataStructures::small_data_structures)
```

## Roadmap

- [ ] **Hash Map** - Fast key-value storage
- [ ] **Linked List** - Dynamic list with O(1) insertion/deletion
- [ ] **String Buffer** - Efficient string manipulation
- [ ] **Ring Buffer** - Circular buffer for streaming data
- [ ] **Priority Queue** - Heap-based priority queue
- [ ] **Graph Structures** - Adjacency list/matrix representations

### Development Guidelines

- Follow C11 standard
- Add tests for new features
- Update documentation
- Ensure all tests pass
- Use consistent coding style

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Note**: This library is designed for small to medium-sized datasets. For very large datasets (millions of elements), consider specialized libraries or database solutions.