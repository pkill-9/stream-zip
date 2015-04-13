/**
 *  Heap functions used for constructing a Huffman tree.
 */

#include <assert.h>

#include "utils.h"
#include "heap.h"
#include "node.h"

/**********************************************************/

PRIVATE void trickle_up (heap_t *heap, int index);
PRIVATE void trickle_down (heap_t *heap, int index);
PRIVATE void swap_items (node_t **a, node_t **b);

/**********************************************************/

/**
 *  Add a new item to the specified heap. This is done by appending the
 *  new item to the end of the heap array, and trickling up.
 */
    PUBLIC void
heap_enqueue (heap_t *heap, node_t *item)
{
    assert (heap->num_free_slots > 0);

    heap->num_items += 1;
    heap->num_free_slots -= 1;
    heap->array [heap->num_items - 1] = item;
    trickle_up (heap, heap->num_items - 1);
}

/**********************************************************/

/**
 *  Remove an item from the heap by swapping with the last item in the
 *  array and then trickling down the new root. Returns the previous root
 *  item which was removed from the heap.
 */
    PUBLIC node_t *
heap_dequeue (heap_t *heap)
{
    node_t *removed = heap->array [0];
    swap_items (heap->array, heap->array + heap->num_items - 1);
    heap->num_items -= 1;
    heap->num_free_slots += 1;
    trickle_down (heap, 0);

    return removed;
}

/**********************************************************/

/**
 *  Trickle a new item up until the heap property is reestablished.
 */
    PRIVATE void
trickle_up (heap_t *heap, int index)
{
    int parent = index / 2;

    // constructing a min heap, so if the current node is smaller than it's
    // parent, we need to swap them, then trickle up the parent.
    if (size (heap->array [parent]) > size (heap->array [index]))
    {
        swap_items (heap->array + parent, heap->array + index);
        trickle_up (heap, parent);
    }
}

/**********************************************************/

/**
 *  Trickle down the specified item to reestablish the heap property.
 */
    PRIVATE void
trickle_down (heap_t *heap, int index)
{
    int child = 2 * index + 1;

    // check that the child exists. If the index is out of bounds, we have
    // trickled down as far as possible, and are done.
    if (child > heap->num_items - 1)
        return;

    // choose the smallest child to trickle down with.
    if (child + 1 < heap->num_items && 
      size (heap->array [child]) > size (heap->array [child + 1]))
    {
        child += 1;
    }

    // if the current node is bigger than the smallest child, swap the
    // child to the current node's position, and continue to trickle down
    if (size (heap->array [index]) > size (heap->array [child]))
    {
        swap_items (heap->array + index, heap->array + child);
        trickle_down (heap, child);
    }
}

/**********************************************************/

/**
 *  Swaps two pointers to node_t's.
 */
    PRIVATE void
swap_items (node_t **a, node_t **b)
{
    node_t *temp = *a;
    *a = *b;
    *b = temp;
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
