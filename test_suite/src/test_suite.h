#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <assert.h>
#include <stdio.h> // IWYU pragma: keep

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define ASSERT_EQUAL(suite, lhs, rhs, type)                                    \
  {                                                                            \
    assert(suite->test_case_name && "assertion outside the test case");        \
    type __lhs = (lhs);                                                        \
    type __rhs = (rhs);                                                        \
    char message[] = "expected " STR(lhs) " equal to " STR(rhs);               \
    if (__lhs != __rhs) {                                                      \
      printf("Case \"%s\": %s\n", suite->test_case_name, message);             \
      suite->status = 1;                                                       \
      suite->failed_count++;                                                   \
      break;                                                                   \
    }                                                                          \
  }

#define ASSERT_NOT_EQUAL(suite, lhs, rhs, type)                                \
  {                                                                            \
    assert(suite->test_case_name && "assertion outside the test case");        \
    type __lhs = (lhs);                                                        \
    type __rhs = (rhs);                                                        \
    char message[] = "expected " STR(lhs) " not equal to " STR(rhs);           \
    if (__lhs == __rhs) {                                                      \
      printf("Case \"%s\": %s\n", suite->test_case_name, message);             \
      suite->status = 1;                                                       \
      suite->failed_count++;                                                   \
      break;                                                                   \
    }                                                                          \
  }

#define TEST_CASE(suite, name, body)                                           \
  do {                                                                         \
    assert(!suite->test_case_name && "nested test cases are not allowed");     \
    suite->test_case_name = name;                                              \
    do {                                                                       \
      if (!suite->nop && !(suite->status == 0 && suite->failfast)) {           \
        body;                                                                  \
      }                                                                        \
      suite->succeed_count++;                                                  \
    } while (0);                                                               \
    suite->test_case_name = NULL;                                              \
  } while (0)

#define TEST_FAIL(suite, reason)                                               \
  {                                                                            \
    assert(suite->test_case_name && "assertion outside the test case");        \
    suite->status = 1;                                                         \
    suite->failed_count++;                                                     \
    printf("Case \"%s\" failed: %s\n", suite->test_case_name, reason);         \
    break;                                                                     \
  }

#define TEST_SUCCESS(suite)                                                    \
  {                                                                            \
    assert(suite->test_case_name && "assertion outside the test case");        \
    suite->succeed_count++;                                                    \
    break;                                                                     \
  }

#define TEST_SKIP(suite, reason)                                               \
  {                                                                            \
    assert(suite->test_case_name && "assertion outside the test case");        \
    suite->skipped_count++;                                                    \
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
