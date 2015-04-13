/**
 *  Functions for constructing a Huffman tree, and translating bytes
 *  into codewords.
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "node.h"
#include "alphabet.h"

#define NUM_CODEWORDS   (ALPHABET_LENGTH + 1)


void huffman_init (void);
node_t * build_huffman_tree (void);
int lookup_codeword (const node_t *tree, int ch, char *buffer, int length);
void free_huffman_tree (node_t *tree);


#endif // HUFFMAN_H

/** vim: set ft=c ts=4 sw=4 et : */
