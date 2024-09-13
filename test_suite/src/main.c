#include "test_suite.h"

int main(int argc, char** argv) {
  test_suite* suite = test_suite_init(argc, argv);
  ASSERT_EQUAL(suite, 1, 1, int);
  ASSERT_NOT_EQUAL(suite, 1, 2, int);
  return test_suite_finish(suite);
}
