/**
 *  Program to decompress a stream of bytes compressed with huffman-encode.
 */

#include <stdio.h>

#include "utils.h"
#include "huffman.h"
#include "node.h"
#include "alphabet.h"

/**********************************************************/

PRIVATE int decode_next_codeword (const node_t *tree);
PRIVATE int traverse_tree (const node_t *tree);
PRIVATE int read_next_byte (void);
PRIVATE int next_codeword_bit (void);

/**********************************************************/

    int
main (int argc, char **argv)
{
    int nextchar;
    node_t *huffman_tree;

    huffman_init ();
    initialise_histogram ();
    huffman_tree = build_huffman_tree ();

    while ((nextchar = decode_next_codeword (huffman_tree)) != -1)
    {
        putchar (nextchar);
        update_symbol (nextchar);
        huffman_tree = build_huffman_tree ();
    }

    return 0;
}

/**********************************************************/

/**
 *  Reads the next codeword from stdin and returns the byte that was 
 *  encoded.
 *
 *  This function will check for an end of stream sequence, and if
 *  encountered will return -1.
 */
    PRIVATE int
decode_next_codeword (const node_t *tree)
{
    int byte = traverse_tree (tree);

    if (byte == NOT_SEEN)
        byte = read_next_byte ();

    if (byte == END_OF_STREAM)
        return -1;

    return byte;
}

/**********************************************************/

/**
 *  Decodes a Huffman codeword by traversing the Huffman tree.
 *
 *  Return value is the decoded value. This function may also return
 *  special values for NOT_SEEN, indicating that the next 8 bits of the
 *  compressed stream are a literal byte value, or END_OF_STREAM,
 *  indicating that there are no more codewords.
 */
    PRIVATE int
traverse_tree (const node_t *tree)
{
    int value;

    // if we have reached a leaf node, then we have decoded a codeword, so
    // return the value.
    if (tree->left == NULL && tree->right == NULL)
        return tree->ch;

    // otherwise, select the left or right branch depending on whether the
    // next bit of the codeword is a 0 or 1.
    switch (next_codeword_bit ())
    {
    case 1:
        value = traverse_tree (tree->right);
        break;

    case 0:
        value = traverse_tree (tree->left);
        break;

    default:
        fprintf (stderr, "Error reading codeword bits.\n");
        value = END_OF_STREAM;
    }

    return value;
}

/**********************************************************/

/**
 *  Reads the next 8 bits from stdin and returns them as an int. The value
 *  is read MSB first.
 */
    PRIVATE int
read_next_byte (void)
{
    int byte = 0x0;

    for (int mask = 0x80; mask != 0x00; mask >>= 1)
    {
        // is the next bit a 1? if so, set the bit in byte.
        if (getchar () == '1')
            byte |= mask;
    }

    return byte;
}

/**********************************************************/

/**
 *  Gets the next bit from the compressed stream. Returns 0 or 1 for the
 *  bit value, or -1 if EOF is encountered.
 */
    PRIVATE int
next_codeword_bit (void)
{
    int numeral = getchar ();

    if (numeral == '1')
        return 1;

    if (numeral == '0')
        return 0;

    return numeral;
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
