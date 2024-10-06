function(add_test_exec TEST_NAME DEPENDENCIES)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} PRIVATE check ${DEPENDENCIES})
    add_test(
        NAME test_${TEST_NAME}
        COMMAND ${TEST_NAME}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
        NAME memcheck_${TEST_NAME}
        COMMAND valgrind
            --error-exitcode=1
            --tool=memcheck
            --leak-check=full
            --errors-for-leak-kinds=definite
            $<TARGET_FILE:${TEST_NAME}>
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
endfunction()
