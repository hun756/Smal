cmake_minimum_required(VERSION 3.18)

project(SmallDataStructures 
    VERSION 1.0.0
    DESCRIPTION "High-performance small data structures library"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    if(NOT MSVC)
        add_compile_options(-g -O0)
    endif()
else()
    add_compile_definitions(NDEBUG)
    if(NOT MSVC)
        add_compile_options(-O3)
    endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(small_data_structures INTERFACE)
target_include_directories(small_data_structures INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(HEADER_FILES
    include/small_vec.h
)

set(SOURCE_FILES
)

add_executable(small_vec_demo
    main.c
    ${HEADER_FILES}
)

target_link_libraries(small_vec_demo PRIVATE small_data_structures)

option(BUILD_TESTS "Build test programs" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

option(BUILD_BENCHMARKS "Build benchmark programs" OFF)
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    else()
        message(WARNING "Doxygen not found, documentation will not be built")
    endif()
endif()

include(GNUInstallDirs)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

install(TARGETS small_data_structures
    EXPORT SmallDataStructuresTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS small_vec_demo
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT SmallDataStructuresTargets
    FILE SmallDataStructuresTargets.cmake
    NAMESPACE SmallDataStructures::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmallDataStructures
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    SmallDataStructuresConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SmallDataStructuresConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SmallDataStructuresConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmallDataStructures
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SmallDataStructuresConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SmallDataStructuresConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmallDataStructures
)

set(CPACK_PACKAGE_NAME "SmallDataStructures")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR "SmallDataStructures Team")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building tests: ${BUILD_TESTS}")
message(STATUS "Building examples: ${BUILD_EXAMPLES}")
message(STATUS "Building benchmarks: ${BUILD_BENCHMARKS}")
message(STATUS "Building documentation: ${BUILD_DOCS}")
