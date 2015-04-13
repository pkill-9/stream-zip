/**
 *  Functions for constructing a Huffman tree, and translating bytes
 *  into codewords.
 */

#include <stdio.h>
#include <assert.h>

#include "alphabet.h"
#include "node.h"
#include "heap.h"
#include "utils.h"


PRIVATE void build_heap (heap_t *heap);
PRIVATE int do_lookup (const node_t *tree, int ch, char *buffer, int length);


// this is a dummy node in the huffman tree that represents any symbol
// that has not yet been encountered.
node_t not_seen;

// another dummy node used to indicate the end of the compressed stream.
node_t end_stream;


/**
 *  Initialise an array of node_t's one for each of the 256 values that
 *  can be represented with a byte.
 */
    PUBLIC void
huffman_init (void)
{
    // set the values for the not seen dummy symbol.
    not_seen.frequency = 0;
    not_seen.ch = NOT_SEEN;
    not_seen.left = not_seen.right = NULL;

    end_stream.frequency = 0;
    end_stream.ch = END_OF_STREAM;
    end_stream.left = end_stream.right = NULL;
}

/**
 *  Builds a Huffman tree using the collected character frequencies.
 */
    PUBLIC node_t *
build_huffman_tree (void)
{
    node_t *array [ALPHABET_LENGTH + 2];
    node_t *parent, *child1, *child2;
    heap_t heap;

    heap.array = array;
    heap.num_items = 0;
    heap.num_free_slots = ALPHABET_LENGTH + 2;

    build_heap (&heap);

    while (heap.num_items > 1)
    {
        child1 = heap_dequeue (&heap);
        child2 = heap_dequeue (&heap);

        parent = new_node (size (child1) + size (child2), child1, child2);

        heap_enqueue (&heap, parent);
    }

    return heap_dequeue (&heap);
}

/**
 *  Look up the codeword for a given 8 bit value. If the value does not
 *  appear in the tree, this function will provide the codeword for not
 *  seen, and return 0.
 */
    PUBLIC int
lookup_codeword (const node_t *tree, int ch, char *buffer, int length)
{
    if (seen_symbol (ch) != 1 && ch != END_OF_STREAM)
    {
        // look up the codeword for NOT_SEEN
        do_lookup (tree, NOT_SEEN, buffer, length);
        return 0;
    }
    else
    {
        do_lookup (tree, ch, buffer, length);
        return 1;
    }
}

/**
 *  Traverse the Huffman tree searching for the node corresponding to
 *  the given 8 bit value.
 *
 *  Return value is 1 if ch was found, 0 if not found.
 */
    PRIVATE int
do_lookup (const node_t *tree, int ch, char *buffer, int length)
{
    assert (length > 0);

    // have we reached a leaf node? If so, check if it is the
    // one we are looking for.
    if (tree->left == NULL && tree->right == NULL)
    {
        *buffer = '\0';

        if (tree->ch == ch)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // not a leaf node. Continue to search any child of the current node.
    if (tree->left != NULL)
    {
        *buffer = '0';

        if (do_lookup (tree->left, ch, buffer + 1, length - 1) == 1)
            return 1;
    }

    if (tree->right != NULL)
    {
        *buffer = '1';

        if (do_lookup (tree->right, ch, buffer + 1, length - 1) == 1)
            return 1;
    }

    return 0;
}

/**
 *  Constructs a heap out of the character frequency table.
 */
    PRIVATE void
build_heap (heap_t *heap)
{
    enqueue_symbols (heap);
    heap_enqueue (heap, &not_seen);
    heap_enqueue (heap, &end_stream);
}

/**
 *  Traverse the Huffman tree and free all the malloced nodes.
 */
    PUBLIC void
free_huffman_tree (node_t *tree)
{
    // do not free leaf nodes, as they are not allocated with malloc.
    if (tree->left == NULL && tree->right == NULL)
        return;

    // first free the left and right branches, if they exist.
    if (tree->left != NULL)
        free_huffman_tree (tree->left);

    if (tree->right != NULL)
        free_huffman_tree (tree->right);

    // now free the node itself.
    free (tree);
}

/** vim: set ts=4 sw=4 et : */
