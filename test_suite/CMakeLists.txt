cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

project(test_suite LANGUAGES C)

add_executable(test_suite src/main.c src/test_suite.c)
target_include_directories(test_suite PRIVATE src)
target_compile_options(test_suite PRIVATE -Wall -Wpedantic -Wextra)
