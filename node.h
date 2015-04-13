/**
 *  Defines a data structure to represent a Huffman tree.
 */

#ifndef NODE_H
#define NODE_H

// value used in the Huffman tree for a character that has not been used.
#define NOT_SEEN        (-1)

// special value used to indicate the end of the compressed stream.
#define END_OF_STREAM   (-2)


typedef struct node
{
    int frequency;
    int ch;
    struct node *left;
    struct node *right;
}
node_t;


node_t *new_node (int weight, node_t *left, node_t *right);
int size (node_t *node);


#endif // NODE_H

/** vim: set ft=c ts=4 sw=4 et : */
