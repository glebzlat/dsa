#include <stdint.h>
#include <stdlib.h>

#include <test_suite.h>
#include <vector.h>

int is_ten(void* data) { return *(int*)data == 10; }

int is_twenty(void* data) { return *(int*)data == 20; }

int cmp_int32_t(void* a, void* b) {
  int32_t _a = *(int32_t*)a, _b = *(int32_t*)b;
  if (_a < _b)
    return -1;
  if (_a > _b)
    return 1;
  return 0;
}

int main(int argc, char** argv) {
  test_suite* suite = test_suite_init(argc, argv);

  TEST_CASE(suite, "Create and delete", {
    vector* v = vector_init(4);
    vector_deinit(v);
  });

  TEST_CASE(suite, "Empty vector", {
    vector* v = vector_init(4);

    assert(vector_is_empty(v));
    assert(vector_size(v) == 0);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Push elements", {
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
  });

  TEST_CASE(suite, "Prepend elements", {
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
  });

  TEST_CASE(suite, "Insert elements", {
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
  });

  TEST_CASE(suite, "Pop elements", {
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
  });

  TEST_CASE(suite, "Vector autoresize", {
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
  });

  TEST_CASE(suite, "Unshift elements", {
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
  });

  TEST_CASE(suite, "Delete element at index", {
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
  });

  TEST_CASE(suite, "Remove elements on which predicate is true", {
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
  });

  TEST_CASE(suite, "Find first element on which predicate is true", {
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
  });

  TEST_CASE(suite, "Auto memory allocation", {
    vector* v = vector_init(4);

    assert(vector_capacity(v) == 16);

    for (int32_t i = 0; i < 20; ++i) {
      vector_push(v, &i);
    }

    assert(vector_capacity(v) == 32);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Replace element", {
    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;
    int32_t e4 = 4;

    vector_push(v, &e1);
    vector_push(v, &e2);
    vector_push(v, &e3);

    vector_replace(v, 1, &e4);

    ASSERT_EQUAL(*(int32_t*)vector_at(v, 0), e1, int32_t);
    ASSERT_EQUAL(*(int32_t*)vector_at(v, 1), e4, int32_t);
    ASSERT_EQUAL(*(int32_t*)vector_at(v, 2), e3, int32_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Comparison function", {
    int32_t a = 1;
    int32_t b = 2;

    ASSERT_TRUE(cmp_int32_t(&a, &b) < 0);
    ASSERT_TRUE(cmp_int32_t(&b, &a) > 0);
    ASSERT_TRUE(cmp_int32_t(&a, &a) == 0);
  });

  TEST_CASE(suite, "Vector less than", {
    vector* a = vector_init(4);
    vector* b = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(a, &e1);
    vector_push(a, &e2);

    vector_push(b, &e1);
    vector_push(b, &e2);
    vector_push(b, &e3);

    ASSERT_TRUE(vector_cmp(a, b, cmp_int32_t) == -1);

    vector_deinit(a);
    vector_deinit(b);
  });

  TEST_CASE(suite, "Vector greater than", {
    vector* a = vector_init(4);
    vector* b = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;
    int32_t e4 = 4;

    vector_push(a, &e1);
    vector_push(a, &e2);
    vector_push(a, &e3);
    vector_push(a, &e4);

    vector_push(b, &e1);
    vector_push(b, &e2);
    vector_push(b, &e3);

    ASSERT_TRUE(vector_cmp(a, b, cmp_int32_t) == 1);

    vector_deinit(a);
    vector_deinit(b);
  });

  TEST_CASE(suite, "Equal vectors", {
    vector* a = vector_init(4);
    vector* b = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;

    vector_push(a, &e1);
    vector_push(a, &e2);
    vector_push(a, &e3);

    vector_push(b, &e1);
    vector_push(b, &e2);
    vector_push(b, &e3);

    ASSERT_TRUE(vector_cmp(a, b, cmp_int32_t) == 0);

    vector_deinit(a);
    vector_deinit(b);
  });

  TEST_CASE(suite, "Empty vectors are equal", {
    vector* a = vector_init(4);
    vector* b = vector_init(4);

    ASSERT_TRUE(vector_cmp(a, b, cmp_int32_t) == 0);

    vector_deinit(a);
    vector_deinit(b);
  });

  TEST_CASE(suite, "Quick sort", {
    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    int32_t e3 = 3;
    int32_t e4 = 4;

    vector_push(v, &e3);
    vector_push(v, &e1);
    vector_push(v, &e4);
    vector_push(v, &e2);

    vector_quicksort(v, cmp_int32_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Quick sort sorted vector", {
    vector* v = vector_init(4);
    vector* clue = vector_init(4);

    for (int i = 0; i < 20; ++i) {
      vector_push(v, &i);
      vector_push(clue, &i);
    }

    vector_quicksort(v, cmp_int32_t);
    ASSERT_TRUE(vector_cmp(v, clue, cmp_int32_t) == 0);

    vector_deinit(v);
    vector_deinit(clue);
  });

  TEST_CASE(suite, "Quick sort empty vector", {
    vector* v = vector_init(4);
    vector* clue = vector_init(4);

    vector_quicksort(v, cmp_int32_t);
    ASSERT_TRUE(vector_cmp(v, clue, cmp_int32_t) == 0);

    vector_deinit(v);
    vector_deinit(clue);
  });

  TEST_CASE(suite, "Quick sort vector of one element", {
    vector* v = vector_init(4);
    vector* clue = vector_init(4);

    int32_t e = 1;
    vector_push(v, &e);
    vector_push(clue, &e);

    vector_quicksort(v, cmp_int32_t);
    ASSERT_TRUE(vector_cmp(v, clue, cmp_int32_t) == 0);

    vector_deinit(v);
    vector_deinit(clue);
  });

  TEST_CASE(suite, "Quick sort vector of two unordered elements", {
    vector* v = vector_init(4);
    vector* clue = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    vector_push(v, &e2);
    vector_push(v, &e1);
    vector_push(clue, &e1);
    vector_push(clue, &e2);

    vector_quicksort(v, cmp_int32_t);
    printf("vector_at 0: %d\n", *(int32_t*)vector_at(v, 0));
    printf("vector_at 1: %d\n", *(int32_t*)vector_at(v, 1));
    ASSERT_TRUE(vector_cmp(v, clue, cmp_int32_t) == 0);

    vector_deinit(v);
    vector_deinit(clue);
  });

  TEST_CASE(suite, "Binary search", {
    vector* v = vector_init(4);

    for (int32_t i = 0; i < 20; ++i) {
      vector_push(v, &i);
    }

    int32_t key = 5;
    size_t idx = vector_bsearch(v, &key, cmp_int32_t);

    printf("%zi\n", idx);
    ASSERT_EQUAL(idx, 5, size_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Binary search element not found", {
    vector* v = vector_init(4);

    for (int32_t i = 0; i < 20; i += 2) {
      vector_push(v, &i);
    }

    int32_t key = 5;
    size_t idx = vector_bsearch(v, &key, cmp_int32_t);

    ASSERT_EQUAL(idx, VECTOR_NPOS, size_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Binary search on empty vector", {
    vector* v = vector_init(4);

    int32_t key = 5;
    size_t idx = vector_bsearch(v, &key, cmp_int32_t);

    ASSERT_EQUAL(idx, VECTOR_NPOS, size_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Binary search on vector of one element", {
    vector* v = vector_init(4);

    int32_t e = 1;
    vector_push(v, &e);

    size_t idx = vector_bsearch(v, &e, cmp_int32_t);

    ASSERT_EQUAL(idx, 0, size_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Binary search on vector of two elements", {
    vector* v = vector_init(4);

    int32_t e1 = 1;
    int32_t e2 = 2;
    vector_push(v, &e1);
    vector_push(v, &e2);

    size_t idx = vector_bsearch(v, &e1, cmp_int32_t);
    ASSERT_EQUAL(idx, 0, size_t);

    idx = vector_bsearch(v, &e2, cmp_int32_t);
    ASSERT_EQUAL(idx, 1, size_t);

    vector_deinit(v);
  });

  TEST_CASE(suite, "Binary search on vector of same elements", {
    vector* v = vector_init(4);

    int32_t e = 32;
    for (int i = 0; i < 5; ++i) {
      vector_push(v, &e);
    }

    size_t idx = vector_bsearch(v, &e, cmp_int32_t);

    ASSERT_EQUAL(idx, 2, size_t);

    vector_deinit(v);
  });

  return test_suite_finish(suite);
}
