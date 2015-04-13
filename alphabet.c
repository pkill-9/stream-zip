/**
 *  Functions used to keep track of the number of times any given 8 bit
 *  value has occurred.
 */

#include <assert.h>

#include "utils.h"
#include "alphabet.h"
#include "node.h"
#include "heap.h"

/**********************************************************/

// we will record frequencies in this array, which conveniently allows fast
// lookup time by virtue of the fact that any 8 bit value i is stored at
// index i in the array.
PRIVATE node_t histogram [ALPHABET_LENGTH];

/**********************************************************/

/**
 *  Initialise the frequency table, setting the number of occurences of
 *  each value to 0.
 */
    PUBLIC void
initialise_histogram (void)
{
    for (int i = 0; i < ALPHABET_LENGTH; i ++)
    {
        histogram [i].frequency = 0;
        histogram [i].ch = i;
        histogram [i].left = NULL;
        histogram [i].right = NULL;
    }
}

/**********************************************************/

/**
 *  This function should be called when any character is read. It will
 *  update the number of occurences of the corresponding character.
 */
    PUBLIC void
update_symbol (int symbol)
{
    assert (symbol >= 0 && symbol < ALPHABET_LENGTH);
    histogram [symbol].frequency += 1;
}

/**********************************************************/

/**
 *  Add all of the symbols that have non zero counts into the specified
 *  heap, for construction of a Huffman tree.
 */
    PUBLIC void
enqueue_symbols (heap_t *heap)
{
    for (int i = 0; i < ALPHABET_LENGTH; i ++)
    {
        if (histogram [i].frequency > 0)
            heap_enqueue (heap, histogram + i);
    }
}

/**********************************************************/

/**
 *  Test if a symbol has been seen yet. If it has, this function will
 *  return 1, if not, returns 0.
 */
    PUBLIC int
seen_symbol (int symbol)
{
    if (histogram [symbol].frequency != 0)
        return 1;

    return 0;
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
