#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <assert.h>
#include <stdio.h> // IWYU pragma: keep

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define ASSERT_EQUAL(lhs, rhs, type)                                           \
  {                                                                            \
    assert(__test_suite->test_case_name && "assertion outside the test case"); \
    type __lhs = (lhs);                                                        \
    type __rhs = (rhs);                                                        \
    char message[] = "expected " STR(lhs) " equal to " STR(rhs);               \
    if (__lhs != __rhs) {                                                      \
      printf("Case \"%s\": %s\n", __test_suite->test_case_name, message);      \
      __test_suite->status = 1;                                                \
      __test_suite->failed_count++;                                            \
      break;                                                                   \
    }                                                                          \
  }

#define ASSERT_NOT_EQUAL(lhs, rhs, type)                                       \
  {                                                                            \
    assert(__test_suite->test_case_name && "assertion outside the test case"); \
    type __lhs = (lhs);                                                        \
    type __rhs = (rhs);                                                        \
    char message[] = "expected " STR(lhs) " not equal to " STR(rhs);           \
    if (__lhs == __rhs) {                                                      \
      printf("Case \"%s\": %s\n", __test_suite->test_case_name, message);      \
      __test_suite->status = 1;                                                \
      __test_suite->failed_count++;                                            \
      break;                                                                   \
    }                                                                          \
  }

#define TEST_CASE(suite, name, body)                                           \
  do {                                                                         \
    assert(!suite->test_case_name && "nested test cases are not allowed");     \
    if (suite->nop || (suite->status != 0 && suite->failfast)) {               \
      break;                                                                   \
    }                                                                          \
    test_suite* __test_suite = suite;                                          \
    __test_suite->test_case_name = name;                                       \
    do {                                                                       \
      body;                                                                    \
      __test_suite->succeed_count++;                                           \
    } while (0);                                                               \
    __test_suite->test_case_name = NULL;                                       \
  } while (0)

#define TEST_FAIL(reason)                                                      \
  {                                                                            \
    assert(__test_suite->test_case_name && "assertion outside the test case"); \
    __test_suite->status = 1;                                                  \
    __test_suite->failed_count++;                                              \
    printf("Case \"%s\" failed: %s\n", __test_suite->test_case_name, reason);  \
    break;                                                                     \
  }

#define TEST_SUCCESS()                                                         \
  {                                                                            \
    assert(__test_suite->test_case_name && "assertion outside the test case"); \
    __test_suite->succeed_count++;                                             \
    break;                                                                     \
  }

#define TEST_SKIP(reason)                                                      \
  {                                                                            \
    assert(__test_suite->test_case_name && "assertion outside the test case"); \
    __test_suite->skipped_count++;                                             \
    break;                                                                     \
  }

typedef struct test_suite {
  int status;
  int failfast;
  int nop;
  int test_case;
  int succeed_count;
  int skipped_count;
  int failed_count;
  char* test_case_name;
} test_suite;

test_suite* test_suite_init(int argc, char** argv);
int test_suite_finish(test_suite* suite);

#endif
