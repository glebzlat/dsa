cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

option(TESTS "Compile and run tests" OFF)

project(vector LANGUAGES C)

add_library(vector src/vector.c)
target_include_directories(vector PUBLIC src)
target_compile_options(vector PUBLIC -Wall -Wpedantic -Wextra)

if (TESTS)
    add_subdirectory(tests)
endif()
