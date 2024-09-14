#include "test_suite.h"

int main(int argc, char** argv) {
  test_suite* suite = test_suite_init(argc, argv);
  TEST_CASE(suite, "test", {
    ASSERT_EQUAL(suite, 1, 1, int);
    ASSERT_NOT_EQUAL(suite, 1, 2, int);
  });
  TEST_CASE(suite, "fail",
            { TEST_FAIL(suite, "just to test this thing fails"); });
  TEST_CASE(suite, "skip", { TEST_SKIP(suite, "skipped test"); });
  TEST_CASE(suite, "success", { TEST_SUCCESS(suite); });
  int result = test_suite_finish(suite);
  return result;
}
