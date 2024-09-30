cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TESTS "Compile and run tests" OFF)

project(data_structures_algorithms LANGUAGES C)

add_subdirectory(test_suite)
add_subdirectory(vector)
add_subdirectory(doubly_list)
