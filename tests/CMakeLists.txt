# Tests CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

# Test executable for small vector
add_executable(test_small_vec test_small_vec.c)
target_link_libraries(test_small_vec PRIVATE small_data_structures)

# Add test to CTest
add_test(NAME SmallVectorTest COMMAND test_small_vec)

# Test executable for comprehensive testing
add_executable(test_comprehensive test_comprehensive.c)
target_link_libraries(test_comprehensive PRIVATE small_data_structures)

# Add comprehensive test to CTest
add_test(NAME ComprehensiveTest COMMAND test_comprehensive)

# Performance test
add_executable(test_performance test_performance.c)
target_link_libraries(test_performance PRIVATE small_data_structures)

# Add performance test to CTest
add_test(NAME PerformanceTest COMMAND test_performance)

# Set test properties
set_tests_properties(SmallVectorTest PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "All tests passed"
)

set_tests_properties(ComprehensiveTest PROPERTIES
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "All comprehensive tests passed"
)

set_tests_properties(PerformanceTest PROPERTIES
    TIMEOUT 120
    PASS_REGULAR_EXPRESSION "Performance tests completed"
)
