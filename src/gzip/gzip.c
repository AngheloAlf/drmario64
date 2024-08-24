#include "gzip.h"

/**
 * Original name: inbuf
 */
u8 inbuf[INBUFSIZ];

/**
 * Original name: insize
 */
u32 insize;

/**
 * Original name: inptr
 */
u32 inptr;

/**
 * Original name: outcnt
 */
size_t outcnt;

/**
 * Original name: window
 */
u8 window[WSIZE];
