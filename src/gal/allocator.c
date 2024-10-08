#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"

void* gal_std_allocator(void* ptr, size_t old_size, size_t new_size) {
  if (old_size == 0 && new_size == 0)
    return NULL;
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  void* p = realloc(ptr, new_size);
  if (!p) {
    fprintf(stderr,
            "gal_std_allocator error: old size %zu, new size %zu, error %s",
            old_size, new_size, strerror(errno));
    return NULL;
  }

  return p;
}
