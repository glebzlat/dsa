#ifndef GAL_ALLOCATOR_H
#define GAL_ALLOCATOR_H

#include <stddef.h>

/** Memory allocator
 *
 * Work principle:
 *     - if new_size == 0, frees the pointer and returns NULL
 *     - if new_size > old_size, reallocates memory chunk and returns the
 *       same pointer
 *     - if old_size == 0 and new_size == 0, returns NULL
 *
 * @param ptr pointer
 * @param old_size current chunk size
 * @param new_size size increase or decrease allocated memory to
 * @returns pointer to allocated memory
 */
void* gal_std_allocator(void* ptr, size_t old_size, size_t new_size);

#endif
