#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

/** constants that may be used to specify the scope of functions. */
#define PUBLIC
#define PRIVATE         static

/** define a bool type, and values for true and false. */
typedef int bool;

#define true            1
#define false           0


/** wrapper to malloc that aborts if malloc returns null. */
void * checked_malloc(size_t bytes);


#endif

/** vim: set ts=4 sw=4 et : */
