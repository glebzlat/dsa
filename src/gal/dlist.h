#ifndef GAL_DLIST_H
#define GAL_DLIST_H

#include <stddef.h>

/** Doubly linked list
 *
 * Has some fields shared between all nodes of a list.
 *
 *
 * @field head
 * A pointer to the leftmost node
 *
 * @field tail
 * A pointer to the rightmost node
 *
 * @field left
 * A pointer to the node on the left of the current node (shared)
 *
 * @field right
 * A pointer to the node on the right of the current node (shared)
 *
 * @field data
 * User data
 */
typedef struct {
  struct dlist* head;
  struct dlist* tail;
  struct dlist* left;
  struct dlist* right;
  void* data;
} dlist;

/** Create a list */
dlist* dlist_init(void);

/** Destroy a list */
void dlist_deinit(dlist* lst);

/** Get the size of a list */
size_t dlist_size(dlist* lst);

/** Check whether the list is empty */
int dlist_empty(dlist* lst);

/** Get a dlist node at an index
 *
 * Starts from the head of a list.
 *
 * Terminates the program if index >= size of a list.
 *
 * Complexity: O(n)
 */
dlist* dlist_at(dlist* lst, size_t index);

/** Add an element to front of a dlist
 *
 * Complexity: O(1)
 */
void dlist_push_front(dlist* lst, void* value);

/** Remove an element from the front of a dlist
 *
 * Complexity: O(1)
 */
void* dlist_pop_front(dlist* lst);

/** Add an element to the back of a dlist
 *
 * Tail pointer makes addition to the end straightforward and constant-time.
 *
 * Complexity: O(1)
 */
void dlist_push_back(dlist* lst, void* value);

/** Remove an element from the back of a dlist
 *
 * Tail pointer makes deletion from the end straightforward and constant-time.
 *
 * Complexity: O(1)
 */
void* dlist_pop_back(dlist* lst);

/** Get an element from the front of a dlist
 *
 * Complexity: O(1)
 */
void* dlist_front(dlist* lst);

/** Get an element from the back of a dlist
 *
 * Complexity: O(1)
 */
void* dlist_back(dlist* lst);

/** Insert an element at an index
 *
 * Inserts new node at an index. Terminates the program if index >= size of a
 * list.
 *
 * Complexity: O(n)
 */
void dlist_insert(dlist* lst, void* value, size_t index);

/** Removes an element at an index
 *
 * Terminates the program if index >= size of a list.
 *
 * Complexity: O(n)
 */
void dlist_remove(dlist* lst, size_t index);

/** Get an element at an index from the end
 *
 * Terminates the program if index >= size of a list.
 *
 * Complexity: O(n)
 */
void* dlist_at_reverse(dlist* lst, size_t index);

/** Insert an element at an index from the end
 *
 * Starts from the tail of a list.
 *
 * Terminates the program if index >= size of a list.
 *
 * Complexity: O(n)
 */
void dlist_insert_reverse(dlist* lst, void* value, size_t index);

/** Removes an element at an index from the end
 *
 * Terminates the program if index >= size of a list.
 *
 * Complexity: O(n)
 */
void dlist_remove_reverse(dlist* lst, size_t index);

/** Reverse a list
 *
 * Complexity: O(n)
 */
void dlist_reverse(dlist* lst);

/** Returns the first node on which predicate returns true
 *
 * Starts from the given node. Can be used in a loop to find all nodes.
 *
 * If there is no such node, then returns NULL pointer.
 *
 * Complexity: O(n)
 */
dlist* dlist_find(dlist* lst, int (*predicate)(size_t, dlist*));

/** Remove all nodes on which predicate returns true
 *
 * Complexity: O(n)
 */
void dlist_delete(dlist* lst, int (*predicate)(size_t, dlist*));

#endif
