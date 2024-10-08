#include <stdint.h>
#include <stdlib.h>

#include <check.h>
#include <gal/vector.h>

/********************************* TESTS *************************************/

int is_ten(void const* data) { return *(int*)data == 10; }

int is_twenty(void const* data) { return *(int*)data == 20; }

int cmp_int32_t(void const* a, void const* b) {
  int32_t _a = *(int32_t*)a, _b = *(int32_t*)b;
  if (_a < _b)
    return -1;
  if (_a > _b)
    return 1;
  return 0;
}

START_TEST(test_vector_create_and_delete) {
  vector* v = vector_init(4);
  vector_deinit(v);
}
END_TEST

START_TEST(test_empty_vector) {
  vector* v = vector_init(4);

  ck_assert(vector_is_empty(v));
  ck_assert(vector_size(v) == 0);

  vector_deinit(v);
}
END_TEST

START_TEST(test_push_elements) {
  vector* v = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  int32_t e3 = 3;

  vector_push(v, &e1);
  vector_push(v, &e2);
  vector_push(v, &e3);

  ck_assert(!vector_is_empty(v));
  ck_assert(vector_size(v) == 3);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), 1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), 2);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), 3);

  vector_deinit(v);
}
END_TEST

START_TEST(test_prepend_elements) {
  vector* v = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  int32_t e3 = 3;

  vector_push(v, &e2);
  vector_push(v, &e3);
  vector_prepend(v, &e1);

  ck_assert(vector_size(v) == 3);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), 1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), 2);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), 3);

  vector_deinit(v);
}
END_TEST

START_TEST(test_insert_elements) {
  vector* v = vector_init(4);

  int32_t e0 = 0;
  int32_t e1 = 1;
  int32_t e2 = 2;
  int32_t e3 = 3;

  vector_push(v, &e1);
  vector_push(v, &e3);
  vector_insert(v, &e2, 1);
  vector_insert(v, &e0, 0);

  ck_assert(vector_size(v) == 4);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), 0);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), 1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), 2);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 3), 3);

  vector_deinit(v);
}
END_TEST

START_TEST(test_pop_elements) {
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

  ck_assert_int_eq(*(int32_t*)p1, 3);
  ck_assert_int_eq(*(int32_t*)p2, 2);
  ck_assert_int_eq(*(int32_t*)p3, 1);
  ck_assert(vector_size(v) == 0);

  vector_deinit(v);

  free(p1);
  free(p2);
  free(p3);
}
END_TEST

START_TEST(test_autoresize) {
  vector* v = vector_init(4);

  for (int32_t i = 1; i <= 17; ++i) {
    int32_t el = i | i << 8 | i << 16 | i << 24;
    vector_push(v, &el);
  }

  ck_assert(vector_capacity(v) == 32);

  void* p = vector_pop(v);
  ck_assert_int_eq(*(int32_t*)p, 0x11111111);
  free(p);

  p = vector_pop(v);
  ck_assert_int_eq(*(int32_t*)p, 0x10101010);
  free(p);

  vector_deinit(v);
}
END_TEST

START_TEST(test_unshift_elements) {
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

  ck_assert_int_eq(*(int32_t*)p1, e1);
  ck_assert_int_eq(*(int32_t*)p2, e2);
  ck_assert_int_eq(*(int32_t*)p3, e3);

  free(p1);
  free(p2);
  free(p3);
  ck_assert(vector_size(v) == 0);

  vector_deinit(v);
}
END_TEST

START_TEST(test_delete_at_index) {
  vector* v = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  int32_t e3 = 3;

  vector_push(v, &e1);
  vector_push(v, &e2);
  vector_push(v, &e3);

  vector_delete(v, 1);

  ck_assert(vector_size(v) == 2);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), e3);

  vector_delete(v, 0);
  vector_delete(v, 0);

  ck_assert(vector_size(v) == 0);

  vector_deinit(v);
}
END_TEST

START_TEST(test_remove_on_predicate) {
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

  ck_assert(vector_size(v) == 7);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), e10);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 6), e10);

  vector_remove(v, is_ten);

  ck_assert(vector_size(v) == 3);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), e1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), e3);

  vector_deinit(v);
}
END_TEST

START_TEST(test_find_on_predicate) {
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

  ck_assert_uint_eq(vector_find(v, is_ten), 2);
  ck_assert_uint_eq(vector_find(v, is_twenty), VECTOR_NPOS);

  vector_deinit(v);
}
END_TEST

START_TEST(test_auto_alloc) {
  vector* v = vector_init(4);

  ck_assert(vector_capacity(v) == 16);

  for (int32_t i = 0; i < 20; ++i) {
    vector_push(v, &i);
  }

  ck_assert(vector_capacity(v) == 32);

  vector_deinit(v);
}
END_TEST

START_TEST(test_replace_element) {
  vector* v = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  int32_t e3 = 3;
  int32_t e4 = 4;

  vector_push(v, &e1);
  vector_push(v, &e2);
  vector_push(v, &e3);

  vector_replace(v, 1, &e4);

  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), e1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), e4);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), e3);

  vector_deinit(v);
}
END_TEST

START_TEST(test_comparison_function) {
  int32_t a = 1;
  int32_t b = 2;

  ck_assert(cmp_int32_t(&a, &b) < 0);
  ck_assert(cmp_int32_t(&b, &a) > 0);
  ck_assert(cmp_int32_t(&a, &a) == 0);
}
END_TEST

START_TEST(test_vector_less_than) {
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

  ck_assert(vector_cmp(a, b, cmp_int32_t) == -1);

  vector_deinit(a);
  vector_deinit(b);
}
END_TEST

START_TEST(test_vector_greater_than) {

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

  ck_assert(vector_cmp(a, b, cmp_int32_t) == 1);

  vector_deinit(a);
  vector_deinit(b);
}
END_TEST

START_TEST(test_equal_vectors) {

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

  ck_assert(vector_cmp(a, b, cmp_int32_t) == 0);

  vector_deinit(a);
  vector_deinit(b);
}
END_TEST

START_TEST(test_empty_vectors_are_equal) {
  vector* a = vector_init(4);
  vector* b = vector_init(4);

  ck_assert(vector_cmp(a, b, cmp_int32_t) == 0);

  vector_deinit(a);
  vector_deinit(b);
}
END_TEST

START_TEST(test_quick_sort) {
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

  ck_assert_int_eq(*(int32_t*)vector_at(v, 0), e1);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 1), e2);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 2), e3);
  ck_assert_int_eq(*(int32_t*)vector_at(v, 3), e4);

  vector_deinit(v);
}
END_TEST

START_TEST(test_quick_sort_sorted_vector) {

  vector* v = vector_init(4);
  vector* clue = vector_init(4);

  for (int i = 0; i < 20; ++i) {
    vector_push(v, &i);
    vector_push(clue, &i);
  }

  vector_quicksort(v, cmp_int32_t);
  ck_assert(vector_cmp(v, clue, cmp_int32_t) == 0);

  vector_deinit(v);
  vector_deinit(clue);
}
END_TEST

START_TEST(test_quick_sort_empty_vector) {
  vector* v = vector_init(4);
  vector* clue = vector_init(4);

  vector_quicksort(v, cmp_int32_t);
  ck_assert(vector_cmp(v, clue, cmp_int32_t) == 0);

  vector_deinit(v);
  vector_deinit(clue);
}
END_TEST

START_TEST(test_quick_sort_vector_of_one_element) {

  vector* v = vector_init(4);
  vector* clue = vector_init(4);

  int32_t e = 1;
  vector_push(v, &e);
  vector_push(clue, &e);

  vector_quicksort(v, cmp_int32_t);
  ck_assert(vector_cmp(v, clue, cmp_int32_t) == 0);

  vector_deinit(v);
  vector_deinit(clue);
}
END_TEST

START_TEST(test_quick_sort_vector_of_two_unordered_elements) {
  vector* v = vector_init(4);
  vector* clue = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  vector_push(v, &e2);
  vector_push(v, &e1);
  vector_push(clue, &e1);
  vector_push(clue, &e2);

  vector_quicksort(v, cmp_int32_t);
  ck_assert(vector_cmp(v, clue, cmp_int32_t) == 0);

  vector_deinit(v);
  vector_deinit(clue);
}
END_TEST

START_TEST(test_binary_search) {
  vector* v = vector_init(4);

  for (int32_t i = 0; i < 20; ++i) {
    vector_push(v, &i);
  }

  int32_t key = 5;
  size_t idx = vector_bsearch(v, &key, cmp_int32_t);

  ck_assert_uint_eq(idx, 5);

  vector_deinit(v);
}
END_TEST

START_TEST(test_binary_search_element_not_found) {
  vector* v = vector_init(4);

  for (int32_t i = 0; i < 20; i += 2) {
    vector_push(v, &i);
  }

  int32_t key = 5;
  size_t idx = vector_bsearch(v, &key, cmp_int32_t);

  ck_assert_uint_eq(idx, VECTOR_NPOS);

  vector_deinit(v);
}
END_TEST

START_TEST(test_binary_search_empty_vector) {
  vector* v = vector_init(4);

  int32_t key = 5;
  size_t idx = vector_bsearch(v, &key, cmp_int32_t);

  ck_assert_uint_eq(idx, VECTOR_NPOS);

  vector_deinit(v);
}
END_TEST

START_TEST(test_binary_search_one_element) {

  vector* v = vector_init(4);

  int32_t e = 1;
  vector_push(v, &e);

  size_t idx = vector_bsearch(v, &e, cmp_int32_t);

  ck_assert_uint_eq(idx, 0);

  vector_deinit(v);
}
END_TEST

START_TEST(test_binary_search_two_elements) {

  vector* v = vector_init(4);

  int32_t e1 = 1;
  int32_t e2 = 2;
  vector_push(v, &e1);
  vector_push(v, &e2);

  size_t idx = vector_bsearch(v, &e1, cmp_int32_t);
  ck_assert_uint_eq(idx, 0);

  idx = vector_bsearch(v, &e2, cmp_int32_t);
  ck_assert_uint_eq(idx, 1);

  vector_deinit(v);
}
END_TEST

START_TEST(test_binary_search_same_elements) {

  vector* v = vector_init(4);

  int32_t e = 32;
  for (int i = 0; i < 5; ++i) {
    vector_push(v, &e);
  }

  size_t idx = vector_bsearch(v, &e, cmp_int32_t);

  ck_assert_uint_eq(idx, 2);

  vector_deinit(v);
}
END_TEST

/******************************* END TESTS ***********************************/

Suite* vector_test_suite(void) {
  Suite* s = suite_create("vector");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_vector_create_and_delete);
  tcase_add_test(tc_core, test_empty_vector);
  tcase_add_test(tc_core, test_push_elements);
  tcase_add_test(tc_core, test_prepend_elements);
  tcase_add_test(tc_core, test_insert_elements);
  tcase_add_test(tc_core, test_pop_elements);
  tcase_add_test(tc_core, test_autoresize);
  tcase_add_test(tc_core, test_unshift_elements);
  tcase_add_test(tc_core, test_delete_at_index);
  tcase_add_test(tc_core, test_remove_on_predicate);
  tcase_add_test(tc_core, test_find_on_predicate);
  tcase_add_test(tc_core, test_auto_alloc);
  tcase_add_test(tc_core, test_replace_element);
  tcase_add_test(tc_core, test_comparison_function);
  tcase_add_test(tc_core, test_vector_less_than);
  tcase_add_test(tc_core, test_vector_greater_than);
  tcase_add_test(tc_core, test_equal_vectors);
  tcase_add_test(tc_core, test_empty_vectors_are_equal);
  tcase_add_test(tc_core, test_quick_sort);
  tcase_add_test(tc_core, test_quick_sort_sorted_vector);
  tcase_add_test(tc_core, test_quick_sort_empty_vector);
  tcase_add_test(tc_core, test_quick_sort_vector_of_one_element);
  tcase_add_test(tc_core, test_quick_sort_vector_of_two_unordered_elements);
  tcase_add_test(tc_core, test_binary_search);
  tcase_add_test(tc_core, test_binary_search_element_not_found);
  tcase_add_test(tc_core, test_binary_search_empty_vector);
  tcase_add_test(tc_core, test_binary_search_one_element);
  tcase_add_test(tc_core, test_binary_search_two_elements);
  tcase_add_test(tc_core, test_binary_search_same_elements);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* s = vector_test_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
