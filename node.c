/**
 *  Functions that operate on nodes of a Huffman tree.
 */

#include <assert.h>

#include "node.h"
#include "utils.h"

/**********************************************************/

/**
 *  Creates a new Huffman tree node with the specified weight and two child
 *  nodes. This function should be used to create tree nodes; the leaf nodes
 *  should already be allocated.
 */
    PUBLIC node_t *
new_node (int weight, node_t *left, node_t *right)
{
    node_t *created = checked_malloc (sizeof (node_t));
    created->frequency = weight;
    created->left = left;
    created->right = right;

    return created;
}

/**********************************************************/

/**
 *  Returns the weight of the specified node. In this case, the weight is
 *  the number of times the corresponding byte has occurred.
 */
    PUBLIC int
size (node_t *node)
{
    return node->frequency;
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
