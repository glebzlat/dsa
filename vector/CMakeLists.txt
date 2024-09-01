cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

project(vector LANGUAGES C)

add_executable(vector src/main.c src/vector.c)
target_include_directories(vector PRIVATE src)
target_compile_options(vector PRIVATE -Wall -Wpedantic -Wextra)
