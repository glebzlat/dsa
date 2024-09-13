#include "vector.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int is_ten(void* data) {
  return *(int*)data == 10;
}

int is_twenty(void* data) {
  return *(int*)data == 20;
}

int main(void) {
  {
    printf("TEST: create and delete the vector\n");

    vector* v = vector_init(4);
    vector_deinit(v);
  }

  {
    printf("TEST: vector is empty\n");

    vector* v = vector_init(4);

    assert(vector_is_empty(v));
    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    printf("TEST: push elements to the vector\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    assert(!vector_is_empty(v));
    assert(vector_size(v) == 3);
    assert(*(int32_t*)vector_at(v, 0) == 1);
    assert(*(int32_t*)vector_at(v, 1) == 2);
    assert(*(int32_t*)vector_at(v, 2) == 3);

    vector_deinit(v);
  }

  {
    printf("TEST: prepend elements to the vector\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e2);
    vector_push(v, &e3);
    vector_prepend(v, &e1);

    assert(vector_size(v) == 3);
    assert(*(int32_t*)vector_at(v, 0) == 1);
    assert(*(int32_t*)vector_at(v, 1) == 2);
    assert(*(int32_t*)vector_at(v, 2) == 3);

    vector_deinit(v);
  }

  {
    printf("TEST: insert elements into the vector\n");

    vector* v = vector_init(4);

    int32_t e0 = 0;
    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e3);
    vector_insert(v, &e2, 1);
    vector_insert(v, &e0, 0);

    assert(vector_size(v) == 4);
    assert(*(int32_t*)vector_at(v, 0) == 0);
    assert(*(int32_t*)vector_at(v, 1) == 1);
    assert(*(int32_t*)vector_at(v, 2) == 2);
    assert(*(int32_t*)vector_at(v, 3) == 3);

    vector_deinit(v);
  }

  {
    printf("TEST: pop elements from the vector\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    void* p1 = vector_pop(v);
    void* p2 = vector_pop(v);
    void* p3 = vector_pop(v);

    assert(*(int32_t*)p1 == 3);
    assert(*(int32_t*)p2 == 2);
    assert(*(int32_t*)p3 == 1);
    assert(vector_size(v) == 0);

    vector_deinit(v);

    free(p1);
    free(p2);
    free(p3);
  }

  {
    printf("TEST: vector is resized when an element is popped\n");

    vector* v = vector_init(4);

    for (int32_t i = 1; i <= 17; ++i) {
      int32_t el = i | i << 8 | i << 16 | i << 24;
      vector_push(v, &el);
    }

    assert(vector_capacity(v) == 32);

    void* p = vector_pop(v);
    assert(*(int32_t*)p == 0x11111111);
    free(p);

    p = vector_pop(v);
    assert(*(int32_t*)p == 0x10101010);
    free(p);

    vector_deinit(v);
  }

  {
    printf("TEST: pop elements from the beginning\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    void* p1 = vector_pop_front(v);
    void* p2 = vector_pop_front(v);
    void* p3 = vector_pop_front(v);
    assert(*(int32_t*)p1 == 1);
    assert(*(int32_t*)p2 == 2);
    assert(*(int32_t*)p3 == 3);
    free(p1);
    free(p2);
    free(p3);
    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    printf("TEST: delete element at index\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    vector_delete(v, 1);

    assert(vector_size(v) == 2);
    assert(*(int32_t*)vector_at(v, 1) == 3);

    vector_delete(v, 0);
    vector_delete(v, 0);

    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    printf("TEST: remove all elements on which predicate is true\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;
    int32_t e10 = 10;

    vector_push(v, &e10);
    vector_push(v, &e1);
    vector_push(v, &e10);
    vector_push(v, &e2);
    vector_push(v, &e10);
    vector_push(v, &e3);
    vector_push(v, &e10);

    assert(vector_size(v) == 7);
    assert(*(int32_t*)vector_at(v, 0) == 10);
    assert(*(int32_t*)vector_at(v, 6) == 10);

    vector_remove(v, is_ten);

    assert(vector_size(v) == 3);
    assert(*(int32_t*)vector_at(v, 0) == 1);
    assert(*(int32_t*)vector_at(v, 2) == 3);

    vector_deinit(v);
  }

  {
    printf("TEST: get an index of an element on which predicate is true\n");
    printf("      if there is no such element, returns -1\n");

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;
    int32_t e10 = 10;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e10);
    vector_push(v, &e3);
    vector_push(v, &e10);

    assert(vector_find(v, is_ten) == 2);
    assert(vector_find(v, is_twenty) == VECTOR_NPOS);

    vector_deinit(v);
  }

  {
    printf("TEST: vector allocates more memory when it is full\n");
    printf("      initial capacity = 16 and increases by 2\n");

    vector* v = vector_init(4);

    assert(vector_capacity(v) == 16);

    for (int32_t i = 0; i < 20; ++i) {
      vector_push(v, &i);
    }

    assert(vector_capacity(v) == 32);

    vector_deinit(v);
  }

  return 0;
}
