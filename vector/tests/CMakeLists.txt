project(tests LANGUAGES C)

include(CTest)

set(CMAKE_BUILD_TYPE Debug)

set(DEPENDENCIES vector test_suite)
set(EXEC_LIST)

macro(add_test_exec TEST_NAME)
    add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${ARGN})
    target_link_libraries(${TEST_NAME} PRIVATE ${DEPENDENCIES})
    list(APPEND EXEC_LIST ${TEST_NAME})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endmacro()

add_test_exec(vector_test test.c)

add_custom_target(RunTests ALL
    ctest --output-on-failure --timeout 2
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
    VERBATIM
    DEPENDS ${EXEC_LIST}
)
