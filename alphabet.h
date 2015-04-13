/**
 *  Functions for maintaining the number of times each symbol has appeared
 *  in the input.
 */

#ifndef ALPHABET_H
#define ALPHABET_H

#include "heap.h"

#define ALPHABET_LENGTH 256


void initialise_histogram (void);
void update_symbol (int symbol);
void enqueue_symbols (heap_t *heap);
int seen_symbol (int symbol);


#endif // ALPHABET_H

/** vim: set ft=c ts=4 sw=4 et : */
