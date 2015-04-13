/**
 *  Stream compression program. Data is read from stdin and compressed
 *  using a variant of a Huffman code algorithm, one byte at a time.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "utils.h"
#include "huffman.h"
#include "node.h"
#include "alphabet.h"

/**********************************************************/

PRIVATE void print_codeword (node_t *tree, int ch);
PRIVATE void print_bits (int ch);
PRIVATE void init_stats (void);
PRIVATE void record_length (int codeword_length);
PRIVATE void print_stats (void);

/**********************************************************/

// this array tells us how many codewords there were of each length.
PRIVATE int length_histogram [NUM_CODEWORDS];
PRIVATE int bytes_compressed;

/**********************************************************/

    PUBLIC int
main (int argc, char **argv)
{
    int nextchar;
    node_t *huffman_tree;

    init_stats ();
    huffman_init ();
    initialise_histogram ();

    while ((nextchar = getchar ()) != EOF)
    {
        huffman_tree = build_huffman_tree ();
        print_codeword (huffman_tree, nextchar);
        update_symbol (nextchar);
    }

    huffman_tree = build_huffman_tree ();
    print_codeword (huffman_tree, END_OF_STREAM);

    //print_stats ();

    return 0;
}

/**********************************************************/

/**
 *  Lookup the codeword for a given character, and print the codeword on
 *  stdout, as 0 and 1 numerals. If the character is not found in the
 *  Huffman tree, this function will print the codeword for not found, then
 *  the 8 bit value.
 */
    PRIVATE void
print_codeword (node_t *tree, int ch)
{
    // the maximum length of the codeword is the size of the alphabet,
    // which would occurr when the Huffman tree is a stick.
    char codeword_buffer [ALPHABET_LENGTH];

    if (lookup_codeword (tree, ch, codeword_buffer, ALPHABET_LENGTH) != 1)
    {
        // not found.
        printf ("%s", codeword_buffer);
        print_bits (ch);
        record_length (strlen (codeword_buffer) + 8);
    }
    else
    {
        printf ("%s", codeword_buffer);
        record_length (strlen (codeword_buffer));
    }
}

/**********************************************************/

/**
 *  Print the individual bits of the given 8 bit value. Only the lowest
 *  8 bits of the int are used, and will be printed MSB first.
 */
    PRIVATE void
print_bits (int ch)
{
    // sweep down from the 8th bit to the least significant bit.
    // For each one, test if the bit in ch is 1, and print the appropriate
    // numeral on stdout.
    for (int mask = 0x80; mask != 0x00; mask >>= 1)
    {
        if ((ch & mask) != 0)
        {
            printf ("1");
        }
        else
        {
            printf ("0");
        }
    }
}

/**********************************************************/

/**
 *  Initialise the global variables used to record statistics.
 */
    PRIVATE void
init_stats (void)
{
    bytes_compressed = 0;

    for (int i = 0; i < NUM_CODEWORDS; i ++)
        length_histogram [i] = 0;
}

/**********************************************************/

/**
 *  Record that a codeword of the specified length was printed.
 */
    PRIVATE void
record_length (int codeword_length)
{
    // this assert is mostly for array bounds checking, but we also prevent
    // codewords from being zero length, which would be within the array
    // bounds, but completely illogical.
    assert (codeword_length > 0 && codeword_length < NUM_CODEWORDS);
    bytes_compressed += 1;
    length_histogram [codeword_length] += 1;
}

/**********************************************************/

/**
 *  Print statistics about codeword lengths on stderr. This information
 *  is a useful measure of how well the compression performed: short
 *  codewords means good compression. Some codewords will be longer than
 *  the uncompressed byte, but they should be rare, and the average length
 *  will (hopefully) be small.
 */
    PRIVATE void
print_stats (void)
{
    unsigned int total_compressed_bits = 0;
    unsigned int total_codewords = 0;

    fprintf (stderr, "bytes compressed: %d\n", bytes_compressed);
    fprintf (stderr, "codeword length histogram (in bits):\n\n");

    for (int length = 0; length < NUM_CODEWORDS; length ++)
    {
        fprintf (stderr, "%4d: %10d\n", length, length_histogram [length]);
        total_compressed_bits += length_histogram [length] * length;
        total_codewords += length_histogram [length];
    }

    fprintf (stderr, "compressed size: %10d bytes\n", 
      total_compressed_bits / 8);
    fprintf (stderr, "avg codeword length: %f bits\n", 
      (double) total_compressed_bits / total_codewords);
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
