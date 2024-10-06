cmake_minimum_required(VERSION 3.20)

option(DSA_TESTS "Compile and run tests" OFF)

project(vector LANGUAGES C)

add_library(vector src/vector.c)
target_include_directories(vector PUBLIC src)
target_compile_options(vector PUBLIC -Wall -Wpedantic -Wextra)

if (DSA_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
