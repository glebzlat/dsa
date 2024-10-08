cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

option(GAL_TESTS "Compile and run tests" OFF)

project(gal LANGUAGES C)

set(SOURCES src/gal/vector.c)

add_library(gal ${SOURCES})
target_include_directories(gal PUBLIC src)
target_compile_options(gal PUBLIC -Wall -Wpedantic -Wextra)

set(FETCHCONTENT_QUIET FALSE)

if(GAL_TESTS)
    enable_testing()
    set(CMAKE_BUILD_TYPE Debug)

    FetchContent_Declare(check
        GIT_REPOSITORY https://github.com/libcheck/check
        GIT_TAG 0.15.2
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(check)

    add_custom_target(tests
        COMMAND ctest
            --exclude-regex ^memcheck_.*
            --test-dir build
            --timeout 2
            --verbose
        USES_TERMINAL
        VERBATIM
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    add_custom_target(memchecks
        COMMAND ctest
            --test-dir build
            --tests-regex ^memcheck_.*
            --verbose
        USES_TERMINAL
        VERBATIM
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    add_subdirectory(tests)
endif()
