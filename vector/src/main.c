#include "vector.h"
#include <assert.h>
#include <stdint.h>

int is_ten(void* data) {
  return *(int*)data == 10;
}

int is_twenty(void* data) {
  return *(int*)data == 20;
}

int main(void) {
  {
    // create and delete the vector

    vector* v = vector_init(4);
    vector_deinit(v);
  }

  {
    // vector is empty

    vector* v = vector_init(4);

    assert(vector_is_empty(v));
    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    // push elements to the vector

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
    // prepend elements to the vector

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
    // insert elements into the vector

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
    // pop elements from the vector

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    assert(*(int32_t*)vector_pop(v) == 3);
    assert(*(int32_t*)vector_pop(v) == 2);
    assert(*(int32_t*)vector_pop(v) == 1);
    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    // pop elements from the beginning

    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    assert(*(int32_t*)vector_pop_front(v) == 1);
    assert(*(int32_t*)vector_pop_front(v) == 2);
    assert(*(int32_t*)vector_pop_front(v) == 3);
    assert(vector_size(v) == 0);

    vector_deinit(v);
  }

  {
    // delete element at index

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
    // remove all elements on which predicate is true

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

    assert(vector_size(v) == 6);
    assert(*(int32_t*)vector_at(v, 0) == 10);
    assert(*(int32_t*)vector_at(v, 5) == 10);

    vector_remove(v, is_ten);

    assert(vector_size(v) == 3);
    assert(*(int32_t*)vector_at(v, 0) == 1);
    assert(*(int32_t*)vector_at(v, 2) == 3);

    vector_deinit(v);
  }

  {
    // get an index of an element on which predicate is true
    // if there is no such element, returns -1

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
    assert(vector_find(v, is_twenty) == -1);

    vector_deinit(v);
  }

  {
    // vector allocates more memory when it is full
    // initial capacity = 16 and increases by 2

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
