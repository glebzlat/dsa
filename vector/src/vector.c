#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

vector* vector_init(size_t element_size) {
  vector* v = (vector*)malloc(sizeof(vector));

  v->_element_size = element_size;
  v->_size = 0;
  v->_capacity = 16;
  v->_max_capacity = VECTOR_MAX_SIZE;
  v->_data = malloc(v->_element_size * v->_capacity);

  return v;
}

void vector_deinit(vector* v) {
  if (v->_data) {
    free(v->_data);
  }

  free(v);
}

size_t vector_size(vector* v) { return v->_size; }

size_t vector_capacity(vector* v) { return v->_capacity; }

int vector_is_empty(vector* v) { return v->_size == 0; }

void* vector_at(vector* v, size_t index) {
  assert(index < v->_size && "vector_at");
#ifdef NDEBUG
  if (index < v->_size) {
    return NULL
  }
#endif

  return (char*)v->_data + index * v->_element_size;
}

void vector_push(vector* v, void* item) {
  if (v->_size == v->_capacity) {
    vector_resize(v, v->_capacity * 2);
  }

  char* data = (char*)v->_data + v->_size * v->_element_size;
  memcpy(data, item, v->_element_size);
  v->_size += 1;
}

void vector_insert(vector* v, void* item, size_t index) {
  if (v->_size == v->_capacity) {
    vector_resize(v, v->_capacity * 2);
  }

  size_t element_size = v->_element_size;
  char* dest;
  char* src;

  for (size_t i = v->_size; i > index; --i) {
    dest = (char*)v->_data + i * element_size;
    src = (char*)v->_data + (i - 1) * element_size;
    memcpy(dest, src, element_size);
  }

  v->_size += 1;

  memcpy(src, item, element_size);
}

void vector_prepend(vector* v, void* item) { vector_insert(v, item, 0); }

void* vector_pop(vector* v) {
  assert(!vector_is_empty(v) && "vector_pop");

  size_t element_size = v->_element_size;
  void* el = malloc(element_size);
  void* data = (char*)v->_data + (v->_size - 1) * element_size;
  memcpy(el, data, element_size);
  v->_size -= 1;

  if (v->_size == v->_capacity / 2) {
    vector_resize(v, v->_capacity / 2);
  }

  return el;
}

void* vector_pop_front(vector* v) {
  assert(!vector_is_empty(v) && "vector_pop");

  void* el = malloc(v->_element_size);
  memcpy(el, v->_data, v->_element_size);

  size_t element_size = v->_element_size;
  char* src;
  char* dest;

  for (size_t i = 1; i < v->_size; ++i) {
    dest = (char*)v->_data + (i - 1) * element_size;
    src = (char*)v->_data + i * element_size;
    memcpy(dest, src, element_size);
  }

  v->_size -= 1;

  if (v->_size == v->_capacity / 2) {
    vector_resize(v, v->_capacity / 2);
  }

  return el;
}

void vector_delete(vector* v, size_t index) {
  assert(index < v->_size && "vector_delete");

  size_t element_size = v->_element_size;
  char* src;
  char* dest;

  for (size_t i = index + 1; i < v->_size; ++i) {
    src = (char*)v->_data + i * element_size;
    dest = (char*)v->_data + (i - 1) * element_size;
    memcpy(dest, src, element_size);
  }

  v->_size -= 1;

  if (v->_size == v->_capacity / 2) {
    vector_resize(v, v->_capacity / 2);
  }
}

void vector_remove(vector* v, int (*predicate)(void*)) {
  size_t element_size = v->_element_size;
  char* el;
  for (size_t i = 0; i < v->_size; ++i) {
    el = (char*)v->_data + i * element_size;
    if (predicate(el)) {
      vector_delete(v, i);
    }
  }
}

size_t vector_find(vector* v, int (*predicate)(void*)) {
  size_t element_size = v->_element_size;
  char* el;
  for (size_t i = 0; i < v->_size; ++i) {
    el = (char*)v->_data + i * element_size;
    if (predicate(el)) {
      return i;
    }
  }
  return VECTOR_NPOS;
}

void vector_resize(vector* v, size_t capacity) {
  assert(capacity < v->_max_capacity && "vector_resize");
  assert(v->_size <= capacity && "vector_resize");

  if (capacity == v->_capacity) {
    return;
  }

  v->_data = realloc(v->_data, capacity * v->_element_size);
  v->_capacity = capacity;
}

void vector_replace(vector* v, size_t index, void* data) {
  char* start = (char*)v->_data + index * v->_element_size;
  memcpy(start, data, v->_element_size);
}

static void _quicksort(vector* v, size_t start, size_t end,
                       int (*cmp)(void*, void*));

void vector_quicksort(vector* v, int (*cmp)(void*, void*)) {
  if (vector_is_empty(v))
    return;
  _quicksort(v, 0, vector_size(v) - 1, cmp);
}

static size_t median_of_three(size_t x, size_t y, size_t z);

void _quicksort(vector* v, size_t start, size_t end, int (*cmp)(void*, void*)) {
  if (start >= end)
    return;

  // https://research.google/blog/extra-extra-read-all-about-it-nearly-all-binary-searches-and-mergesorts-are-broken/
  size_t pivot_idx = median_of_three(start, (start + end) >> 1, end);
  void* pivot = vector_at(v, pivot_idx);
  size_t i = start, j = end;
  void* tmp = malloc(v->_element_size);

  while (i <= j) {
    while (cmp(vector_at(v, i), pivot) < 0)
      ++i;
    while (cmp(vector_at(v, j), pivot) > 0)
      --j;

    if (i <= j) {
      memcpy(tmp, vector_at(v, i), v->_element_size);
      vector_replace(v, i, vector_at(v, j));
      vector_replace(v, j, tmp);
      ++i, --j;
    }
  }
  free(tmp);

  if (start < j)
    _quicksort(v, start, j, cmp);
  if (i < end)
    _quicksort(v, i, end, cmp);
}

size_t median_of_three(size_t x, size_t y, size_t z) {
  if ((y > x && z > y) || (y < x && y > z))
    return y;
  if ((x > y && z > x) || (x < y && x > z))
    return x;
  return z;
}

size_t vector_bsearch(vector* v, void* key, int (*cmp)(void*, void*)) {
  if (vector_is_empty(v)) return VECTOR_NPOS;

  size_t start = 0, end = vector_size(v) - 1, mid;

  while (start <= end) {
    mid = start + ((end - start) >> 1);
    int compare = cmp(key, vector_at(v, mid));
    if (compare > 0)
      start = mid + 1;
    else if (compare < 0)
      end = mid - 1;
    else
      return mid;
  }

  return VECTOR_NPOS;
}

int vector_cmp(vector* a, vector* b, int (*cmp)(void*, void*)) {
  if (a->_size < b->_size)
    return -1;
  if (a->_size > b->_size)
    return 1;

  int result = 0;
  for (size_t i = 0; i < a->_size; ++i) {
    result = cmp(vector_at(a, i), vector_at(b, i));
    if (result != 0)
      return result;
  }

  return 0;
}
