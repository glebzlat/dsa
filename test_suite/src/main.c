#include "test_suite.h"

int main(int argc, char** argv) {
  test_suite* suite = test_suite_init(argc, argv);
  TEST_CASE(suite, "test", {
    ASSERT_EQUAL(1, 1, int);
    ASSERT_NOT_EQUAL(1, 2, int);
  });
  TEST_CASE(suite, "fail", { TEST_FAIL("just to test this thing fails"); });
  TEST_CASE(suite, "skip", { TEST_SKIP("skipped test"); });
  TEST_CASE(suite, "success", { TEST_SUCCESS(); });
  int result = test_suite_finish(suite);
  return result;
}
