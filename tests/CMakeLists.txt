project(gal_tests LANGUAGES C)

include(CTest)
include(${CMAKE_SOURCE_DIR}/modules/TestUtility.cmake)

add_test_exec(vector_test gal vector.c)
