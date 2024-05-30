/* deflate.c -- compress data using the deflation algorithm
 * Copyright (C) 1992-1993 Jean-loup Gailly
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License, see the file COPYING.
 */

/*
 *  PURPOSE
 *
 *      Identify new text as repetitions of old text within a fixed-
 *      length sliding window trailing behind the new text.
 *
 *  DISCUSSION
 *
 *      The "deflation" process depends on being able to identify portions
 *      of the input text which are identical to earlier input (within a
 *      sliding window trailing behind the input currently being processed).
 *
 *      The most straightforward technique turns out to be the fastest for
 *      most input files: try all possible matches and select the longest.
 *      The key feature of this algorithm is that insertions into the string
 *      dictionary are very simple and thus fast, and deletions are avoided
 *      completely. Insertions are performed at each input character, whereas
 *      string matches are performed only when the previous match ends. So it
 *      is preferable to spend more time in matches to allow very fast string
 *      insertions and avoid deletions. The matching algorithm for small
 *      strings is inspired from that of Rabin & Karp. A brute force approach
 *      is used to find longer strings when a small match has been found.
 *      A similar algorithm is used in comic (by Jan-Mark Wams) and freeze
 *      (by Leonid Broukhis).
 *         A previous version of this file used a more sophisticated algorithm
 *      (by Fiala and Greene) which is guaranteed to run in linear amortized
 *      time, but has a larger average cost, uses more memory and is patented.
 *      However the F&G algorithm may be faster for some highly redundant
 *      files if the parameter max_chain_length (described below) is too large.
 *
 *  ACKNOWLEDGEMENTS
 *
 *      The idea of lazy evaluation of matches is due to Jan-Mark Wams, and
 *      I found it in 'freeze' written by Leonid Broukhis.
 *      Thanks to many info-zippers for bug reports and testing.
 *
 *  REFERENCES
 *
 *      APPNOTE.TXT documentation file in PKZIP 1.93a distribution.
 *
 *      A description of the Rabin and Karp algorithm is given in the book
 *         "Algorithms" by R. Sedgewick, Addison-Wesley, p252.
 *
 *      Fiala,E.R., and Greene,D.H.
 *         Data Compression with Finite Windows, Comm.ACM, 32,4 (1989) 490-595
 *
 *  INTERFACE
 *
 *      void lm_init (int pack_level, ush *flags)
 *          Initialize the "longest match" routines for a new file
 *
 *      off_t deflate (void)
 *          Processes a new input file and return its compressed length. Sets
 *          the compressed length, crc, deflate flags and internal file
 *          attributes.
 */

#include "config.h"
#include <stdio.h>

#include "tailor.h"
#include "gzip.h"

#ifdef RCSID
static char rcsid[] = "$Id: deflate.c,v 0.15 1993/06/24 10:53:53 jloup Exp $";
#endif

/* ===========================================================================
 * Configuration parameters
 */

/* Compile with MEDIUM_MEM to reduce the memory requirements or
 * with SMALL_MEM to use as little memory as possible. Use BIG_MEM if the
 * entire input file can be held in memory (not possible on 16 bit systems).
 * Warning: defining these symbols affects HASH_BITS (see below) and thus
 * affects the compression ratio. The compressed output
 * is still correct, and might even be smaller in some cases.
 */

#ifdef SMALL_MEM
#   define HASH_BITS  13  /* Number of bits used to hash strings */
#endif
#ifdef MEDIUM_MEM
#   define HASH_BITS  14
#endif
#ifndef HASH_BITS
#   define HASH_BITS  15
   /* For portability to 16 bit machines, do not use values above 15. */
#endif

/* To save space (see unlzw.c), we overlay prev+head with tab_prefix and
 * window with tab_suffix. Check that we can do this:
 */
#if (WSIZE<<1) > (1<<BITS)
   error: cannot overlay window with tab_suffix and prev with tab_prefix0
#endif
#if HASH_BITS > BITS-1
   error: cannot overlay head with tab_prefix1
#endif

#define HASH_SIZE (unsigned)(1<<HASH_BITS)
#define HASH_MASK (HASH_SIZE-1)
#define WMASK     (WSIZE-1)
/* HASH_SIZE and WSIZE must be powers of two */

#define NIL 0
/* Tail of hash chains */

#define FAST 4
#define SLOW 2
/* speed options for the general purpose bit flag */

#ifndef TOO_FAR
#  define TOO_FAR 4096
#endif
/* Matches of length 3 are discarded if their distance exceeds TOO_FAR */

/* ===========================================================================
 * Local data used by the "longest match" routines.
 */

typedef ush Pos;
typedef unsigned IPos;
/* A Pos is an index in the character window. We use short instead of int to
 * save space in the various tables. IPos is used only for parameter passing.
 */


/* Values for max_lazy_match, good_match and max_chain_length, depending on
 * the desired pack level (0..9). The values given below have been tuned to
 * exclude worst case performance for pathological files. Better values may be
 * found for specific files.
 */

typedef struct config {
   ush good_length; /* reduce lazy search above this match length */
   ush max_lazy;    /* do not perform lazy search above this match length */
   ush nice_length; /* quit search above this match length */
   ush max_chain;
} config;

local config configuration_table[10] = {
/*      good lazy nice chain */
/* 0 */ {0,    0,  0,    0},  /* store only */
/* 1 */ {4,    4,  8,    4},  /* maximum speed, no lazy matches */
/* 2 */ {4,    5, 16,    8},
/* 3 */ {4,    6, 32,   32},

/* 4 */ {4,    4, 16,   16},  /* lazy matches */
/* 5 */ {8,   16, 32,   32},
/* 6 */ {8,   16, 128, 128},
/* 7 */ {8,   32, 128, 256},
/* 8 */ {32, 128, 258, 1024},
/* 9 */ {32, 258, 258, 4096}}; /* maximum compression */

/* Note: the deflate() code requires max_lazy >= MIN_MATCH and max_chain >= 4
 * For deflate_fast() (levels <= 3) good is ignored and lazy has a different
 * meaning.
 */

#define EQUAL 0
/* result of memcmp for equal strings */

/* ===========================================================================
 *  Prototypes for local functions.
 */
local void fill_window   OF((gzip_state_t *s));
local off_t deflate_fast OF((gzip_state_t *s));

      int  longest_match OF((gzip_state_t *s, IPos cur_match));

#ifdef DEBUG
local  void check_match OF((gzip_state_t *s, IPos start, IPos match, int length));
#endif

/* ===========================================================================
 * Update a hash value with the given input byte
 * IN  assertion: all calls to to UPDATE_HASH are made with consecutive
 *    input characters, so that a running hash key can be computed from the
 *    previous key instead of complete recalculation each time.
 */
#define UPDATE_HASH(h,c) (h = (((h)<<H_SHIFT) ^ (c)) & HASH_MASK)

/* ===========================================================================
 * Insert string s in the dictionary and set match_head to the previous head
 * of the hash chain (the most recent string with same hash key). Return
 * the previous length of the hash chain.
 * IN  assertion: all calls to to INSERT_STRING are made with consecutive
 *    input characters and the first MIN_MATCH bytes of s are valid
 *    (except for the last MIN_MATCH-1 bytes of the input file).
 */
#define INSERT_STRING(s, strstart, match_head) \
   (UPDATE_HASH(s->ins_h, s->window[(strstart) + MIN_MATCH-1]), \
    s->prev[(strstart) & WMASK] = match_head = head[s->ins_h], \
    head[s->ins_h] = (strstart))

/* ===========================================================================
 * Initialize the "longest match" routines for a new file
 */
void lm_init (s, pack_level, flags)
    gzip_state_t *s;
    int pack_level; /* 0: store, 1: best speed, 9: best compression */
    ush *flags;     /* general purpose bit flag */
{
    register unsigned j;

    if (pack_level < 1 || pack_level > 9) error(s, "bad pack level");
    s->compr_level = pack_level;

    /* Initialize the hash table. */
#if defined(MAXSEG_64K) && HASH_BITS == 15
    for (j = 0;  j < HASH_SIZE; j++) head[j] = NIL;
#else
    memzero((char*)head, HASH_SIZE*sizeof(*head));
#endif
    /* prev will be initialized on the fly */

    /* Set the default configuration parameters:
     */
    s->max_lazy_match   = configuration_table[pack_level].max_lazy;
    s->good_match       = configuration_table[pack_level].good_length;
#ifndef FULL_SEARCH
    s->nice_match       = configuration_table[pack_level].nice_length;
#endif
    s->max_chain_length = configuration_table[pack_level].max_chain;
    if (pack_level == 1) {
       *flags |= FAST;
    } else if (pack_level == 9) {
       *flags |= SLOW;
    }
    /* ??? reduce max_chain_length for binary files */

    s->strstart = 0;
    s->block_start = 0L;

    s->lookahead = file_read(s, (char*)s->window,
			 sizeof(int) <= 2 ? (unsigned)WSIZE : 2*WSIZE);

    if (s->lookahead == 0 || s->lookahead == (unsigned)EOF) {
       s->eofile = 1, s->lookahead = 0;
       return;
    }
    s->eofile = 0;
    /* Make sure that we always have enough lookahead. This is important
     * if input comes from a device such as a tty.
     */
    while (s->lookahead < MIN_LOOKAHEAD && !s->eofile) fill_window(s);

    s->ins_h = 0;
    for (j=0; j<MIN_MATCH-1; j++) UPDATE_HASH(s->ins_h, s->window[j]);
    /* If lookahead < MIN_MATCH, ins_h is garbage, but this is
     * not important since only literal bytes will be emitted.
     */
}

/* ===========================================================================
 * Set match_start to the longest match starting at the given string and
 * return its length. Matches shorter or equal to prev_length are discarded,
 * in which case the result is equal to prev_length and match_start is
 * garbage.
 * IN assertions: cur_match is the head of the hash chain for the current
 *   string (strstart) and its distance is <= MAX_DIST, and prev_length >= 1
 */
int longest_match(s, cur_match)
    gzip_state_t *s;
    IPos cur_match;                             /* current match */
{
    unsigned chain_length = s->max_chain_length;   /* max hash chain length */
    register uch *scan = s->window + s->strstart;  /* current string */
    register uch *match;                        /* matched string */
    register int len;                           /* length of current match */
    int best_len = s->prev_length;                 /* best match length so far */
    IPos limit = s->strstart > (IPos)MAX_DIST ? s->strstart - (IPos)MAX_DIST : NIL;
    /* Stop when cur_match becomes <= limit. To simplify the code,
     * we prevent matches with the string of window index 0.
     */

/* The code is optimized for HASH_BITS >= 8 and MAX_MATCH-2 multiple of 16.
 * It is easy to get rid of this optimization if necessary.
 */
#if HASH_BITS < 8 || MAX_MATCH != 258
   error: Code too clever
#endif

#ifdef UNALIGNED_OK
    /* Compare two bytes at a time. Note: this is not always beneficial.
     * Try with and without -DUNALIGNED_OK to check.
     */
    register uch *strend = s->window + s->strstart + MAX_MATCH - 1;
    register ush scan_start = *(ush*)scan;
    register ush scan_end   = *(ush*)(scan+best_len-1);
#else
    register uch *strend = s->window + s->strstart + MAX_MATCH;
    register uch scan_end1  = scan[best_len-1];
    register uch scan_end   = scan[best_len];
#endif

    /* Do not waste too much time if we already have a good match: */
    if (s->prev_length >= s->good_match) {
        chain_length >>= 2;
    }
    // Assert(strstart <= window_size-MIN_LOOKAHEAD, "insufficient lookahead");

    do {
        Assert(cur_match < s->strstart, "no future");
        match = s->window + cur_match;

        /* Skip to next match if the match length cannot increase
         * or if the match length is less than 2:
         */
#if (defined(UNALIGNED_OK) && MAX_MATCH == 258)
        /* This code assumes sizeof(unsigned short) == 2. Do not use
         * UNALIGNED_OK if your compiler uses a different size.
         */
        if (*(ush*)(match+best_len-1) != scan_end ||
            *(ush*)match != scan_start) continue;

        /* It is not necessary to compare scan[2] and match[2] since they are
         * always equal when the other bytes match, given that the hash keys
         * are equal and that HASH_BITS >= 8. Compare 2 bytes at a time at
         * strstart+3, +5, ... up to strstart+257. We check for insufficient
         * lookahead only every 4th comparison; the 128th check will be made
         * at strstart+257. If MAX_MATCH-2 is not a multiple of 8, it is
         * necessary to put more guard bytes at the end of the window, or
         * to check more often for insufficient lookahead.
         */
        scan++, match++;
        do {
        } while (*(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 scan < strend);
        /* The funny "do {}" generates better code on most compilers */

        /* Here, scan <= window+strstart+257 */
        Assert(scan <= window+(unsigned)(window_size-1), "wild scan");
        if (*scan == *match) scan++;

        len = (MAX_MATCH - 1) - (int)(strend-scan);
        scan = strend - (MAX_MATCH-1);

#else /* UNALIGNED_OK */

        if (match[best_len]   != scan_end  ||
            match[best_len-1] != scan_end1 ||
            *match            != *scan     ||
            *++match          != scan[1])      continue;

        /* The check at best_len-1 can be removed because it will be made
         * again later. (This heuristic is not always a win.)
         * It is not necessary to compare scan[2] and match[2] since they
         * are always equal when the other bytes match, given that
         * the hash keys are equal and that HASH_BITS >= 8.
         */
        scan += 2, match++;

        /* We check for insufficient lookahead only every 8th comparison;
         * the 256th check will be made at strstart+258.
         */
        do {
        } while (*++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 scan < strend);

        len = MAX_MATCH - (int)(strend - scan);
        scan = strend - MAX_MATCH;

#endif /* UNALIGNED_OK */

        if (len > best_len) {
            s->match_start = cur_match;
            best_len = len;
            if (len >= s->nice_match) break;
#ifdef UNALIGNED_OK
            scan_end = *(ush*)(scan+best_len-1);
#else
            scan_end1  = scan[best_len-1];
            scan_end   = scan[best_len];
#endif
        }
    } while ((cur_match = s->prev[cur_match & WMASK]) > limit
	     && --chain_length != 0);

    return best_len;
}

#ifdef DEBUG
/* ===========================================================================
 * Check that the match at match_start is indeed a match.
 */
local void check_match(s, start, match, length)
    gzip_state_t *s;
    IPos start, match;
    int length;
{
    /* check that the match is indeed a match */
    if (memcmp((char*)s->window + match,
                (char*)s->window + start, length) != EQUAL) {
        fprintf(stderr,
            " start %d, match %d, length %d\n",
            start, match, length);
        error(s, "invalid match");
    }
    if (s->verbose > 1) {
        fprintf(stderr,"\\[%d,%d]", start-match, length);
        do { putc(s->window[start++], stderr); } while (--length != 0);
    }
}
#else
#  define check_match(s, start, match, length)
#endif

/* ===========================================================================
 * Fill the window when the lookahead becomes insufficient.
 * Updates strstart and lookahead, and sets eofile if end of input file.
 * IN assertion: lookahead < MIN_LOOKAHEAD && strstart + lookahead > 0
 * OUT assertions: at least one byte has been read, or eofile is set;
 *    file reads are performed for at least two bytes (required for the
 *    translate_eol option).
 */
local void fill_window(s)
    gzip_state_t *s;
{
    register unsigned n, m;
    unsigned more = (unsigned)(s->window_size - (ulg)s->lookahead - (ulg)s->strstart);
    /* Amount of free space at the end of the window. */

    /* If the window is almost full and there is insufficient lookahead,
     * move the upper half to the lower one to make room in the upper half.
     */
    if (more == (unsigned)EOF) {
        /* Very unlikely, but possible on 16 bit machine if strstart == 0
         * and lookahead == 1 (input done one byte at time)
         */
        more--;
    } else if (s->strstart >= WSIZE+MAX_DIST) {
        /* By the IN assertion, the window is not empty so we can't confuse
         * more == 0 with more == 64K on a 16 bit machine.
         */
        Assert(s->window_size == (ulg)2*WSIZE, "no sliding with BIG_MEM");

        memcpy((char*)s->window, (char*)s->window+WSIZE, (unsigned)WSIZE);
        s->match_start -= WSIZE;
        s->strstart    -= WSIZE; /* we now have strstart >= MAX_DIST: */

        s->block_start -= (long) WSIZE;

        for (n = 0; n < HASH_SIZE; n++) {
            m = head[n];
            head[n] = (Pos)(m >= WSIZE ? m-WSIZE : NIL);
        }
        for (n = 0; n < WSIZE; n++) {
            m = s->prev[n];
            s->prev[n] = (Pos)(m >= WSIZE ? m-WSIZE : NIL);
            /* If n is not on any hash chain, prev[n] is garbage but
             * its value will never be used.
             */
        }
        more += WSIZE;
    }
    /* At this point, more >= 2 */
    if (!s->eofile) {
        n = file_read(s, (char*)s->window+s->strstart+s->lookahead, more);
        if (n == 0 || n == (unsigned)EOF) {
            s->eofile = 1;
        } else {
            s->lookahead += n;
        }
    }
}

/* ===========================================================================
 * Flush the current block, with given end-of-file flag.
 * IN assertion: strstart is set to the end of the current match.
 */
#define FLUSH_BLOCK(s, eof) \
   flush_block(s, s->block_start >= 0L ? (char*)&s->window[(unsigned)s->block_start] : \
                (char*)NULL, (long)s->strstart - s->block_start, (eof))

/* ===========================================================================
 * Processes a new input file and return its compressed length. This
 * function does not perform lazy evaluationof matches and inserts
 * new strings in the dictionary only for unmatched strings or for short
 * matches. It is used only for the fast compression options.
 */
local off_t deflate_fast(s)
    gzip_state_t *s;
{
    IPos hash_head; /* head of the hash chain */
    int flush;      /* set if current block must be flushed */
    unsigned match_length = 0;  /* length of best match */

    s->prev_length = MIN_MATCH-1;
    while (s->lookahead != 0) {
        /* Insert the string window[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        INSERT_STRING(s, s->strstart, hash_head);

        /* Find the longest match, discarding those <= prev_length.
         * At this point we have always match_length < MIN_MATCH
         */
        if (hash_head != NIL && s->strstart - hash_head <= MAX_DIST) {
            /* To simplify the code, we prevent matches with the string
             * of window index 0 (in particular we have to avoid a match
             * of the string with itself at the start of the input file).
             */
            match_length = longest_match (s, hash_head);
            /* longest_match() sets match_start */
            if (match_length > s->lookahead) match_length = s->lookahead;
        }
        if (match_length >= MIN_MATCH) {
            check_match(s, s->strstart, s->match_start, match_length);

            flush = ct_tally(s, s->strstart-s->match_start, match_length - MIN_MATCH);

            s->lookahead -= match_length;

	    /* Insert new strings in the hash table only if the match length
             * is not too large. This saves time but degrades compression.
             */
            if (match_length <= s->max_insert_length) {
                match_length--; /* string at strstart already in hash table */
                do {
                    s->strstart++;
                    INSERT_STRING(s, s->strstart, hash_head);
                    /* strstart never exceeds WSIZE-MAX_MATCH, so there are
                     * always MIN_MATCH bytes ahead. If lookahead < MIN_MATCH
                     * these bytes are garbage, but it does not matter since
                     * the next lookahead bytes will be emitted as literals.
                     */
                } while (--match_length != 0);
	        s->strstart++; 
            } else {
	        s->strstart += match_length;
	        match_length = 0;
	        s->ins_h = s->window[s->strstart];
	        UPDATE_HASH(s->ins_h, s->window[s->strstart+1]);
#if MIN_MATCH != 3
                Call UPDATE_HASH() MIN_MATCH-3 more times
#endif
            }
        } else {
            /* No match, output a literal byte */
            Tracevv((stderr,"%c",s->window[s->strstart]));
            flush = ct_tally (s, 0, s->window[s->strstart]);
            s->lookahead--;
	    s->strstart++; 
        }
        if (flush) FLUSH_BLOCK(s, 0), s->block_start = s->strstart;

        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * for the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        while (s->lookahead < MIN_LOOKAHEAD && !s->eofile) fill_window(s);

    }
    return FLUSH_BLOCK(s, 1); /* eof */
}

/* ===========================================================================
 * Same as above, but achieves better compression. We use a lazy
 * evaluation for matches: a match is finally adopted only if there is
 * no better match at the next window position.
 */
off_t deflate(s)
    gzip_state_t *s;
{
    IPos hash_head;          /* head of hash chain */
    IPos prev_match;         /* previous match */
    int flush;               /* set if current block must be flushed */
    int match_available = 0; /* set if previous match exists */
    register unsigned match_length = MIN_MATCH-1; /* length of best match */

    if (s->compr_level <= 3) return deflate_fast(s); /* optimized for speed */

    /* Process the input block. */
    while (s->lookahead != 0) {
        /* Insert the string window[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        INSERT_STRING(s, s->strstart, hash_head);

        /* Find the longest match, discarding those <= prev_length.
         */
        s->prev_length = match_length, prev_match = s->match_start;
        match_length = MIN_MATCH-1;

        if (hash_head != NIL && s->prev_length < s->max_lazy_match &&
            s->strstart - hash_head <= MAX_DIST /* &&
            strstart <= window_size - MIN_LOOKAHEAD */) {
            /* To simplify the code, we prevent matches with the string
             * of window index 0 (in particular we have to avoid a match
             * of the string with itself at the start of the input file).
             */
            match_length = longest_match (s, hash_head);
            /* longest_match() sets match_start */
            if (match_length > s->lookahead) match_length = s->lookahead;

            /* Ignore a length 3 match if it is too distant: */
            if (match_length == MIN_MATCH && s->strstart-s->match_start > TOO_FAR){
                /* If prev_match is also MIN_MATCH, match_start is garbage
                 * but we will ignore the current match anyway.
                 */
                match_length--;
            }
        }
        /* If there was a match at the previous step and the current
         * match is not better, output the previous match:
         */
        if (s->prev_length >= MIN_MATCH && match_length <= s->prev_length) {

            check_match(s, s->strstart-1, prev_match, s->prev_length);

            flush = ct_tally(s, s->strstart-1-prev_match, s->prev_length - MIN_MATCH);

            /* Insert in hash table all strings up to the end of the match.
             * strstart-1 and strstart are already inserted.
             */
            s->lookahead -= s->prev_length-1;
            s->prev_length -= 2;
            do {
                s->strstart++;
                INSERT_STRING(s, s->strstart, hash_head);
                /* strstart never exceeds WSIZE-MAX_MATCH, so there are
                 * always MIN_MATCH bytes ahead. If lookahead < MIN_MATCH
                 * these bytes are garbage, but it does not matter since the
                 * next lookahead bytes will always be emitted as literals.
                 */
            } while (--s->prev_length != 0);
            match_available = 0;
            match_length = MIN_MATCH-1;
            s->strstart++;
            if (flush) FLUSH_BLOCK(s, 0), s->block_start = s->strstart;

        } else if (match_available) {
            /* If there was no match at the previous position, output a
             * single literal. If there was a match but the current match
             * is longer, truncate the previous match to a single literal.
             */
            Tracevv((stderr,"%c",s->window[s->strstart-1]));
            if (ct_tally (s, 0, s->window[s->strstart-1])) {
                FLUSH_BLOCK(s, 0), s->block_start = s->strstart;
            }
            s->strstart++;
            s->lookahead--;
        } else {
            /* There is no previous match to compare with, wait for
             * the next step to decide.
             */
            match_available = 1;
            s->strstart++;
            s->lookahead--;
        }
        Assert (s->strstart <= s->bytes_in && s->lookahead <= s->bytes_in, "a bit too far");

        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * for the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        while (s->lookahead < MIN_LOOKAHEAD && !s->eofile) fill_window(s);
    }
    if (match_available) ct_tally (s, 0, s->window[s->strstart-1]);

    return FLUSH_BLOCK(s, 1); /* eof */
}
