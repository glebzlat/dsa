#include <stdlib.h>
#include <string.h>

#include "test_suite.h"

test_suite* test_suite_init(int argc, char** argv) {
  char help_long_opt[] = "--help";
  char help_short_opt[] = "-h";
  int nop = 0;

  char failfast_long_opt[] = "--fail-fast";
  char failfast_short_opt[] = "-ff";
  int failfast = 0;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], help_long_opt) == 0 ||
        strcmp(argv[i], help_short_opt) == 0) {
      printf("%s [-h|--help] [-ff|--fail-fast]\n", argv[0]);
      nop = 1;
    } else if (strcmp(argv[i], failfast_long_opt) == 0 ||
               strcmp(argv[i], failfast_short_opt) == 0) {
      failfast = 1;
    }
  }

  test_suite* suite = (test_suite*)malloc(sizeof(test_suite));
  suite->succeed_count = 0;
  suite->skipped_count = 0;
  suite->failed_count = 0;
  suite->failfast = failfast;
  suite->nop = nop;
  suite->status = 0;
  return suite;
}

int test_suite_finish(test_suite* suite) {
  int total = suite->succeed_count + suite->skipped_count + suite->failed_count;
  printf("Ran %d tests\n", total);
  printf("  succeed %d\n", suite->succeed_count);
  printf("  skipped %d\n", suite->skipped_count);
  printf("  failed  %d\n", suite->failed_count);
  int status = suite->status;
  free(suite);
  return status;
}
