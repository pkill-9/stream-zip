/**
 *  Defines functions relevant to constructing a Huffman tree using a heap
 *  as a priority queue.
 */

#ifndef HEAP_H
#define HEAP_H

#include "node.h"

#define MAX_HEAP_SIZE   257


typedef struct
{
    node_t **array;
    int num_items;
    int num_free_slots;
}
heap_t;


void heap_enqueue (heap_t *heap, node_t *item);
node_t * heap_dequeue (heap_t *heap);


#endif // HEAP_H

/** vim: set ft=c ts=4 sw=4 et : */
