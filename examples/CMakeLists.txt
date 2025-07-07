cmake_minimum_required(VERSION 3.18)

add_executable(example_basic example_basic.c)
target_link_libraries(example_basic PRIVATE small_data_structures)

add_executable(example_advanced example_advanced.c)
target_link_libraries(example_advanced PRIVATE small_data_structures)

add_executable(example_strings example_strings.c)
target_link_libraries(example_strings PRIVATE small_data_structures)

add_executable(example_math example_math.c)
target_link_libraries(example_math PRIVATE small_data_structures)

install(TARGETS example_basic example_advanced example_strings example_math
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/examples
)
