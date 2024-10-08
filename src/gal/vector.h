/** vector.h - mutable array with automatic resizing */

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define VECTOR_MAX_SIZE ((size_t) - 1)
#define VECTOR_NPOS ((size_t) - 2)

typedef struct {
  size_t _element_size;
  size_t _size;
  size_t _capacity;
  size_t _max_capacity;
  void* _data;
} vector;

/** Create a new vector */
vector* vector_init(size_t element_size);

/** Destroy a vector
 *
 * Frees underlying array.
 */
void vector_deinit(vector* v);

/** Get the size of a vector */
size_t vector_size(vector* v);

/** Get vector's capacity
 *
 * Capacity of a vector is an amount of elements that can be added without
 * vector resizing.
 */
size_t vector_capacity(vector* v);

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
void* vector_at(vector* v, size_t index);

/** Add element to the end of a vector
 *
 * Complexity: O(1), O(n) if the vector is resized
 */
void vector_push(vector* v, void const* item);

/** Insert element at index
 *
 * Inserts element at `index` and shifts trailing elements right.
 *
 * Complexity: O(n) in common case, O(n^2) if the vector is resized
 */
void vector_insert(vector* v, void const* item, size_t index);

/** Prepend element to the beginning
 *
 * Inserts element at index 0 and shifts trailing elements right.
 *
 * Complexity: O(n), O(n^2) if the vector is resized
 */
void vector_prepend(vector* v, void const* item);

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
void vector_delete(vector* v, size_t index);

/** Remove all elements on which predicate is true
 *
 * Complexity: O(n^2) in common case, O(n^3) if the vector is shrunk
 */
void vector_remove(vector* v, int (*predicate)(void const*));

/** Return an index of the first element on which predicate is true
 *
 * If there is no element on which predicate returns true, VECTOR_NPOS is
 * returned.
 *
 * Complexity: O(n)
 */
size_t vector_find(vector* v, int (*predicate)(void const*));

/** Resize vector to the new capacity
 *
 * Complexity: O(n)
 */
void vector_resize(vector* v, size_t capacity);

/** Replace element at index */
void vector_replace(vector* v, size_t idx, void const* data);

/** Sort the vector using quicksort algorithm
 *
 * Comparison function must return integer value that is less than 0 if the
 * first argument is less than the second, value greater than 0 if the first
 * element is greater, and 0 if they are equal.
 *
 * @param v vector
 * @param cmp comparison function
 */
void vector_quicksort(vector* v, int (*cmp)(void const*, void const*));

/** Search the key in a vector using binary search algorithm
 *
 * Comparison function must return integer value that is less than 0 if the
 * first argument is less than the second, value greater than 0 if the first
 * element is greater, and 0 if they are equal.
 *
 * If the vector is empty, returns VECTOR_NPOS.
 *
 * @param v vector
 * @param key key to search
 * @param cmp comparison function
 * @returns index of an element or VECTOR_NPOS if not found
 */
size_t vector_bsearch(vector* v, void const* key,
                      int (*cmp)(void const*, void const*));

/** Check whether vectors are equal
 *
 * Comparison function must return integer value that is less than 0 if the
 * first argument is less than the second, value greater than 0 if the first
 * element is greater, and 0 if they are equal.
 *
 * @returns 0 if a and b are equal, <0 if a is less than b, >0 if a is greater
 * than b
 */
int vector_cmp(vector* a, vector* b, int (*cmp)(void const*, void const*));

#endif
