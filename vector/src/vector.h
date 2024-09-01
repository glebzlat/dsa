/* vector.h - mutable array with automatic resizing
 *
 * methods:
 *   int size()
 *       number of items
 *   int capacity()
 *       number of items it can hold
 *   bool is_empty()
 *       return 1 if vector is empty
 *   void* at(int index)
 *       returns an item at a given index or nullptr if index out of bounds
 *   void push(void* item)
 *       add an item to the end
 *   void insert(void* item, int index)
 *       insert item at index, shift the element at index and all trailing
 *       elements right
 *   void prepend(void* item)
 *       add element to the beginning
 *   void* pop()
 *       remove an element from the end
 *   void* pop_front()
 *       remove an element from the beginning, shift trailing elements left
 *   void delete(int index)
 *       delete item at index, shift trailing elements left
 *   void remove(bool (*predicate)(void*))
 *       remove all elements on which predicate returns true
 *   int find(bool (*predicate)(void*))
 *       return the first index of an element on which predicate returned true
 *   void resize(int capacity)
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef uint64_t u64;
typedef int64_t i64;

typedef struct {
  u64 _element_size;
  u64 _size;
  u64 _capacity;
  u64 _max_capacity;
  void* _data;
} vector;

vector* vector_init(u64 element_size);
void vector_deinit(vector* v);

u64 vector_size(vector* v);
u64 vector_capacity(vector* v);
int vector_is_empty(vector* v);
void* vector_at(vector* v, u64 index);
void vector_push(vector* v, void* item);
void vector_insert(vector* v, void* item, u64 index);
void vector_prepend(vector* v, void* item);
void* vector_pop(vector* v);
void* vector_pop_front(vector* v);
void vector_delete(vector* v, u64 index);
void vector_remove(vector* v, int (*predicate)(void*));
i64 vector_find(vector* v, int (*predicate)(void*));
void vector_resize(vector* v, u64 capacity);

#endif
