#include "dlist.h"
#include <test_suite.h>

int main(int argc, char** argv) {
  test_suite* suite = test_suite_init(argc, argv);

  {
    dlist* lst = dlist_init();
    dlist_deinit(lst);
  }

  return test_suite_finish(suite);
}
