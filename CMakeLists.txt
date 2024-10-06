cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DSA_TESTS "Compile and run tests" OFF)

project(data_structures_algorithms LANGUAGES C)

include(FetchContent)

if(DSA_TESTS)
    enable_testing()
    set(CMAKE_BUILD_TYPE Debug)

    FetchContent_Declare(check
        GIT_REPOSITORY https://github.com/libcheck/check
        GIT_TAG 0.15.2
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
endif()

add_subdirectory(vector)
add_subdirectory(doubly_list)
