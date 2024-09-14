cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

project(dlist LANGUAGES C)

add_executable(dlist src/main.c src/dlist.c)
target_include_directories(dlist PRIVATE src)
target_compile_options(dlist PRIVATE -Wall -Wpedantic -Wextra)
target_link_libraries(dlist PRIVATE test_suite)
