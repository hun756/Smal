cmake_minimum_required(VERSION 3.18)

add_executable(benchmark_performance benchmark_performance.c)
target_link_libraries(benchmark_performance PRIVATE small_data_structures)

add_executable(benchmark_memory benchmark_memory.c)
target_link_libraries(benchmark_memory PRIVATE small_data_structures)

add_executable(benchmark_comparison benchmark_comparison.c)
target_link_libraries(benchmark_comparison PRIVATE small_data_structures)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(NOT MSVC)
        target_compile_options(benchmark_performance PRIVATE -O3 -march=native)
        target_compile_options(benchmark_memory PRIVATE -O3 -march=native)
        target_compile_options(benchmark_comparison PRIVATE -O3 -march=native)
    endif()
endif()

install(TARGETS benchmark_performance benchmark_memory benchmark_comparison
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/benchmarks
)
