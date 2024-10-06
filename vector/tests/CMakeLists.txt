project(tests LANGUAGES C)

include(CTest)
include(${CMAKE_SOURCE_DIR}/modules/TestUtility.cmake)

set(DEPENDENCIES vector)

add_test_exec(vector_test "${DEPENDENCIES}" test.c)
