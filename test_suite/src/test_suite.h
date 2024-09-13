#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <stdio.h> // IWYU pragma: keep

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define ASSERT_EQUAL(suite, lhs, rhs, type)                                    \
  {                                                                            \
    if (suite->nop == 0 && (suite->status == 0 || !suite->failfast)) {         \
      type __lhs = (lhs);                                                      \
      type __rhs = (rhs);                                                      \
      char message[] = "expected " STR(lhs) " equal to " STR(rhs);             \
      if (__lhs != __rhs) {                                                    \
        printf("TEST %d: %s\n", suite->test_count, message);                   \
        suite->status = 1;                                                     \
      } else {                                                                 \
        suite->test_count += 1;                                                \
      }                                                                        \
    }                                                                          \
  }

#define ASSERT_NOT_EQUAL(suite, lhs, rhs, type)                                \
  {                                                                            \
    if (suite->nop == 0 && (suite->status == 0 || !suite->failfast)) {         \
      type __lhs = (lhs);                                                      \
      type __rhs = (rhs);                                                      \
      char message[] = "expected " STR(lhs) " not equal to " STR(rhs);         \
      if (__lhs == __rhs) {                                                    \
        printf("TEST %d: %s\n", suite->test_count, message);                   \
        suite->status = 1;                                                     \
      } else {                                                                 \
        suite->test_count += 1;                                                \
      }                                                                        \
    }                                                                          \
  }

typedef struct test_suite {
  int test_count;
  int status;
  int failfast;
  int nop;
} test_suite;

test_suite* test_suite_init(int argc, char** argv);
int test_suite_finish(test_suite* suite);

#endif
