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
