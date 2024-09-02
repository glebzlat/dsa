#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

vector* vector_init(u64 element_size) {
  vector* v = (vector*)malloc(sizeof(vector));

  v->_element_size = element_size;
  v->_size = 0;
  v->_capacity = 16;
  v->_max_capacity = (u64)0 - 1;
  v->_data = malloc(v->_element_size * v->_capacity);

  return v;
}

void vector_deinit(vector* v) {
  if (v->_data) {
    free(v->_data);
  }

  free(v);
}

u64 vector_size(vector* v) { return v->_size; }

u64 vector_capacity(vector* v) { return v->_capacity; }

int vector_is_empty(vector* v) { return v->_size == 0; }

void* vector_at(vector* v, u64 index) {
  assert(index < v->_size && "vector_at");
#ifdef NDEBUG
  if (index < v->_size) {
    return NULL
  }
#endif
  // OMG this is so DANGEROUS
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

void vector_insert(vector* v, void* item, u64 index) {
  if (v->_size == v->_capacity) {
    vector_resize(v, v->_capacity * 2);
  }

  u64 element_size = v->_element_size;
  char* dest;
  char* src;

  for (u64 i = v->_size; i > index; --i) {
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

  u64 element_size = v->_element_size;
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

  u64 element_size = v->_element_size;
  char* src;
  char* dest;

  for (u64 i = 1; i < v->_size; ++i) {
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

void vector_delete(vector* v, u64 index) {
  assert(index < v->_size && "vector_delete");

  u64 element_size = v->_element_size;
  char* src;
  char* dest;

  for (u64 i = index + 1; i < v->_size; ++i) {
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
  u64 element_size = v->_element_size;
  char* el;
  for (u64 i = 0; i < v->_size; ++i) {
    el = (char*)v->_data + i * element_size;
    if (predicate(el)) {
      vector_delete(v, i);
    }
  }
}

i64 vector_find(vector* v, int (*predicate)(void*)) {
  u64 element_size = v->_element_size;
  char* el;
  for (u64 i = 0; i < v->_size; ++i) {
    el = (char*)v->_data + i * element_size;
    if (predicate(el)) {
      return i;
    }
  }
  return -1;
}

void vector_resize(vector* v, u64 capacity) {
  assert(capacity < v->_max_capacity && "vector_resize");
  assert(v->_size <= capacity && "vector_resize");

  if (capacity == v->_capacity) {
    return;
  }

  v->_data = realloc(v->_data, capacity * v->_element_size);
  v->_capacity = capacity;
}
