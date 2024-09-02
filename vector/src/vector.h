/** vector.h - mutable array with automatic resizing */

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

/** Create a new vector */
vector* vector_init(u64 element_size);

/** Destroy a vector
 *
 * Frees underlying array.
 */
void vector_deinit(vector* v);

/** Get the size of a vector */
u64 vector_size(vector* v);

/** Get vector's capacity
 *
 * Capacity of a vector is an amount of elements that can be added without
 * vector resizing.
 */
u64 vector_capacity(vector* v);

/** Check if vector is empty
 *
 * Returns 1 if vector is empty and 0 otherwise.
 */
int vector_is_empty(vector* v);

/** Get an element at index
 *
 * Returns a pointer if index < size, otherwise causes program termination.
 * If NDEBUG is set, returns NULL pointer.
 */
void* vector_at(vector* v, u64 index);

/** Add element to the end of a vector
 *
 * Complexity: O(1), O(n) if the vector is resized
 */
void vector_push(vector* v, void* item);

/** Insert element at index
 *
 * Inserts element at `index` and shifts trailing elements right.
 *
 * Complexity: O(n) in common case, O(n^2) if the vector is resized
 */
void vector_insert(vector* v, void* item, u64 index);

/** Prepend element to the beginning
 *
 * Inserts element at index 0 and shifts trailing elements right.
 *
 * Complexity: O(n), O(n^2) if the vector is resized
 */
void vector_prepend(vector* v, void* item);

/** Remove element from the end of a vector and return it
 *
 * Allocates memory to store the removed element and returns a pointer to it.
 *
 * Terminates program if the vector is empty.
 *
 * Complexity: O(1) in common case, O(n) in case if vector is resized
 */
void* vector_pop(vector* v);

/** Remove element from the beginning of a vector and return it
 *
 * Allocates memory to store the removed element and returns a pointer to it.
 *
 * Terminates program if the vector is empty.
 *
 * Complexity: O(n) in common case, O(n) in case if vector is resized
 */
void* vector_pop_front(vector* v);

/** Return element at index
 *
 * Terminates program if the vector is empty.
 *
 * Complexity: O(n)
 */
void vector_delete(vector* v, u64 index);

/** Remove all elements on which predicate is true
 *
 * Complexity: O(n^2) in common case, O(n^3) if the vector is shrunk
 */
void vector_remove(vector* v, int (*predicate)(void*));

/** Return an index of the first element on which predicate is true
 *
 * If there is no element on which predicate returns true, -1 is returned.
 *
 * Complexity: O(n)
 */
i64 vector_find(vector* v, int (*predicate)(void*));

/** Resize vector to the new capacity
 *
 * Complexity: O(n)
 */
void vector_resize(vector* v, u64 capacity);

#endif
