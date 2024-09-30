cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_EXTENSIONS OFF)

project(test_suite LANGUAGES C)

add_library(test_suite src/test_suite.c)
target_include_directories(test_suite PUBLIC src)
target_compile_options(test_suite PUBLIC -Wall -Wpedantic -Wextra)

add_executable(test_suite_test src/main.c)
target_link_libraries(test_suite_test test_suite)
