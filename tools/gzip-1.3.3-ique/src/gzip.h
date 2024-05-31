/* gzip.h -- common declarations for all gzip modules
 * Copyright (C) 1997, 1998, 1999, 2001 Free Software Foundation, Inc.
 * Copyright (C) 1992-1993 Jean-loup Gailly.
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License, see the file COPYING.
 */

#if defined(__STDC__) || defined(PROTO)
#  define OF(args)  args
#else
#  define OF(args)  ()
#endif

#ifdef __STDC__
   typedef void *voidp;
#else
   typedef char *voidp;
#endif

/* I don't like nested includes, but the following headers are used
 * too often
 */
#include <stdio.h>
#include <sys/types.h> /* for off_t, time_t */
#if defined HAVE_STRING_H || defined STDC_HEADERS
#  include <string.h>
#  if !defined STDC_HEADERS && defined HAVE_MEMORY_H && !defined __GNUC__
#    include <memory.h>
#  endif
#  define memzero(s, n)     memset ((voidp)(s), 0, (n))
#else
#  include <strings.h>
#  define strchr            index 
#  define strrchr           rindex
#  define memcpy(d, s, n)   bcopy((s), (d), (n)) 
#  define memcmp(s1, s2, n) bcmp((s1), (s2), (n)) 
#  define memzero(s, n)     bzero((s), (n))
#endif

#ifndef RETSIGTYPE
#  define RETSIGTYPE void
#endif

#define local static

typedef unsigned char  uch;
typedef unsigned short ush;
typedef unsigned int   ulg; // used to be long, but we need it to be consistently 32-bit

/* Return codes from gzip */
#define OK      0
#define ERROR   1
#define WARNING 2

/* Compression methods (see algorithm.doc) */
#define STORED      0
#define COMPRESSED  1
#define PACKED      2
#define LZHED       3
/* methods 4 to 7 reserved */
#define DEFLATED    8
#define MAX_METHODS 9
// extern int method;         /* compression method */

/* To save memory for 16 bit systems, some arrays are overlaid between
 * the various modules:
 * deflate:  prev+head   window      d_buf  l_buf  outbuf
 * unlzw:    tab_prefix  tab_suffix  stack  inbuf  outbuf
 * inflate:              window             inbuf
 * unpack:               window             inbuf  prefix_len
 * unlzh:    left+right  window      c_table inbuf c_len
 * For compression, input is done in window[]. For decompression, output
 * is done in window except for unlzw.
 */

#ifndef	INBUFSIZ
#  ifdef SMALL_MEM
#    define INBUFSIZ  0x2000  /* input buffer size */
#  else
#    define INBUFSIZ  0x8000  /* input buffer size */
#  endif
#endif
#define INBUF_EXTRA  64     /* required by unlzw() */

#ifndef	OUTBUFSIZ
#  ifdef SMALL_MEM
#    define OUTBUFSIZ   8192  /* output buffer size */
#  else
#    define OUTBUFSIZ  16384  /* output buffer size */
#  endif
#endif
#define OUTBUF_EXTRA 2048   /* required by unlzw() */

#ifndef DIST_BUFSIZE
#  ifdef SMALL_MEM
#    define DIST_BUFSIZE 0x2000 /* buffer for distances, see trees.c */
#  else
#    define DIST_BUFSIZE 0x8000 /* buffer for distances, see trees.c */
#  endif
#endif

#ifdef DYN_ALLOC
#  define EXTERN(type, array)  extern type * near array
#  define DECLARE(type, array, size)  type * near array
#  define ALLOC(type, array, size) { \
      array = (type*)fcalloc((size_t)(((size)+1L)/2), 2*sizeof(type)); \
      if (array == NULL) error("insufficient memory"); \
   }
#  define FREE(array) {if (array != NULL) fcfree(array), array=NULL;}
#else
#  define EXTERN(type, array)  extern type array[]
#  define DECLARE(type, array, size)  type array[size]
#  define ALLOC(type, array, size)
#  define FREE(array)
#endif

#define tab_suffix window
#ifndef MAXSEG_64K
#  define tab_prefix prev    /* hash link (see deflate.c) */
#  define head (s->prev+WSIZE)  /* hash head (see deflate.c) */
#else
#  define tab_prefix0 prev
#  define head tab_prefix1
#endif

typedef FILE* file_t;     /* Do not use stdio */
#define NO_FILE  (NULL)   /* in memory compression */


#define	PACK_MAGIC     "\037\036" /* Magic header for packed files */
#define	GZIP_MAGIC     "\037\213" /* Magic header for gzip files, 1F 8B */
#define	OLD_GZIP_MAGIC "\037\236" /* Magic header for gzip 0.5 = freeze 1.x */
#define	LZH_MAGIC      "\037\240" /* Magic header for SCO LZH Compress files*/
#define PKZIP_MAGIC    "\120\113\003\004" /* Magic header for pkzip files */

/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#define RESERVED     0xC0 /* bit 6,7:   reserved */

/* internal file attribute */
#define UNKNOWN 0xffff
#define BINARY  0
#define ASCII   1

#ifndef WSIZE
#  define WSIZE 0x8000     /* window size--must be a power of two, and */
#endif                     /*  at least 32K for zip's deflate method */

#define MIN_MATCH  3
#define MAX_MATCH  258
/* The minimum and maximum match lengths */

#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of lookahead, except at the end of the input file.
 * See deflate.c for comments about the MIN_MATCH+1.
 */

#define MAX_DIST  (WSIZE-MIN_LOOKAHEAD)
/* In order to simplify the code, particularly on 16 bit machines, match
 * distances are limited to MAX_DIST instead of WSIZE.
 */

#ifndef BITS
#  define BITS 16
#endif

#ifndef LIT_BUFSIZE
#  ifdef SMALL_MEM
#    define LIT_BUFSIZE  0x2000
#  else
#  ifdef MEDIUM_MEM
#    define LIT_BUFSIZE  0x4000
#  else
#    define LIT_BUFSIZE  0x8000
#  endif
#  endif
#endif
#ifndef DIST_BUFSIZE
#  define DIST_BUFSIZE  LIT_BUFSIZE
#endif
/* Sizes of match buffers for literals/lengths and distances.  There are
 * 4 reasons for limiting LIT_BUFSIZE to 64K:
 *   - frequencies can be kept in 16 bit counters
 *   - if compression is not successful for the first block, all input data is
 *     still in the window so we can still emit a stored block even when input
 *     comes from standard input.  (This can also be done for all blocks if
 *     LIT_BUFSIZE is not greater than 32K.)
 *   - if compression is not successful for a file smaller than 64K, we can
 *     even emit a stored file instead of a stored block (saving 5 bytes).
 *   - creating new Huffman trees less frequently may not provide fast
 *     adaptation to changes in the input data statistics. (Take for
 *     example a binary file with poorly compressible code followed by
 *     a highly compressible string table.) Smaller buffer sizes give
 *     fast adaptation but have of course the overhead of transmitting trees
 *     more frequently.
 *   - I can't count above 4
 * The current code is general and allows DIST_BUFSIZE < LIT_BUFSIZE (to save
 * memory at the expense of compression). Some optimizations would be possible
 * if we rely on DIST_BUFSIZE == LIT_BUFSIZE.
 */
#if LIT_BUFSIZE > INBUFSIZ
    error cannot overlay l_buf and inbuf
#endif

#define HEAP_SIZE (2*L_CODES+1)
/* maximum heap size */

#define MAX_BITS 15
/* All codes must not exceed MAX_BITS bits */

#define MAX_BL_BITS 7
/* Bit length codes must not exceed MAX_BL_BITS bits */

#define LENGTH_CODES 29
/* number of length codes, not counting the special END_BLOCK code */

#define LITERALS  256
/* number of literal bytes 0..255 */

#define END_BLOCK 256
/* end of block literal code */

#define L_CODES (LITERALS+1+LENGTH_CODES)
/* number of Literal or Length codes, including the END_BLOCK code */

#define D_CODES   30
/* number of distance codes */

#define BL_CODES  19
/* number of codes used to transfer the bit lengths */


/* Data structure describing a single value and its code string. */
typedef struct ct_data {
    union {
        ush  freq;       /* frequency count */
        ush  code;       /* bit string */
    } fc;
    union {
        ush  dad;        /* father node in Huffman tree */
        ush  len;        /* length of bit string */
    } dl;
} ct_data;

#define Freq fc.freq
#define Code fc.code
#define Dad  dl.dad
#define Len  dl.len

typedef struct tree_desc {
    ct_data   *dyn_tree;    /* the dynamic tree */
    ct_data   *static_tree; /* corresponding static tree or NULL */
    const int *extra_bits;  /* extra bits for each code or NULL */
    int     extra_base;          /* base index for extra_bits */
    int     elems;               /* max number of elements in the tree */
    int     max_length;          /* max bit length for the codes */
    int     max_code;            /* largest code with non zero frequency */
} tree_desc;

typedef unsigned int ptr32_t; // pointer emulation

typedef struct
{
    int         level;
    FILE       *ifd;
    FILE       *ofd;
    off_t       ifile_size;     /* input file size, -1 for devices (debug only) */
    time_t      time_stamp;     /* original time stamp (modification time) */
    int         verbose;        /* be verbose (-v) */
    int         save_orig_name; /* set if original name must be saved */
    unsigned    insize;         /* valid bytes in inbuf */
    unsigned    outcnt;         /* bytes in output buffer */
    off_t       bytes_in;       /* number of input bytes */
    off_t       bytes_out;      /* number of output bytes */
    int         remove_ofname;  /* remove output file on error */
    char       *ifname;         /* input file name */
    char       *ofname;         /* output file name */
    char       *progname;

    uch         inbuf[INBUFSIZ +INBUF_EXTRA];
    uch         outbuf[OUTBUFSIZ+OUTBUF_EXTRA];
    ush         d_buf[DIST_BUFSIZE];
    uch         window[2L * WSIZE];
    /* Reproduce the memory layout from the original gzip binary for consistent oob window reads */
    unsigned    inptr;          /* index of next byte to be processed in inbuf */
    unsigned    ifd_;           // = 3
    ptr32_t     z_suffix;       // = 0x08052FB5
    unsigned    bk;             // = 0
    ulg         bb;             // = 0
    ptr32_t     file_type_;     // = 0xFFFFD052, might also be 0xBFFFF052 if the top of the stack were 0xC0000000 instead of 0xFFFFE000
    ptr32_t     file_method_;   // = 0x08054AD0
    int         decrypt;        // = 0
    ptr32_t     key;            // = 0
    unsigned    header_bytes;   /* number of bytes in gzip header */
    char        END_[0x4000];
    /* END Reproduce original gzip */

#ifndef MAXSEG_64K
    ush         tab_prefix[1L << BITS];
#else
    ush         tab_prefix0[1L << (BITS - 1)];
    ush         tab_prefix1[1L << (BITS - 1)];
#endif

    int method;
    int exit_code;
    int quiet;

    void       *real_inbuffer;
    size_t      real_inbuffer_size;
    void       *real_outbuffer;
    size_t      real_outbuffer_size;

    file_t      zfile;      /* output gzip file */
    unsigned short bi_buf;  /* Output buffer. bits are inserted starting at the bottom (least significant bits). */
    int         bi_valid;   /* Number of valid bits in bi_buf.  All bits above the last valid bit are always zero. */
#ifdef DEBUG
    off_t       bits_sent;  /* bit length of the compressed data */
#endif

    ct_data dyn_ltree[HEAP_SIZE];   /* literal and length tree */
    ct_data dyn_dtree[2*D_CODES+1]; /* distance tree */

    ct_data static_ltree[L_CODES+2];
    /* The static literal tree. Since the bit lengths are imposed, there is no
    * need for the L_CODES extra codes used during heap construction. However
    * The codes 286 and 287 are needed to build a canonical tree (see ct_init
    * below).
    */

    ct_data static_dtree[D_CODES];
    /* The static distance tree. (Actually a trivial tree since all codes use
    * 5 bits.)
    */

    ct_data bl_tree[2*BL_CODES+1];
    /* Huffman tree for the bit lengths */

    ush bl_count[MAX_BITS+1];
    /* number of codes at each bit length for an optimal tree */

    int heap[2*L_CODES+1]; /* heap used to build the Huffman trees */
    int heap_len;               /* number of elements in the heap */
    int heap_max;               /* element of largest frequency */
    /* The sons of heap[n] are heap[2*n] and heap[2*n+1]. heap[0] is not used.
    * The same heap array is used to build all trees.
    */

    uch depth[2*L_CODES+1];
    /* Depth of each subtree used as tie breaker for trees of equal frequency */

    uch length_code[MAX_MATCH-MIN_MATCH+1];
    /* length code for each normalized match length (0 == MIN_MATCH) */

    uch dist_code[512];
    /* distance codes. The first 256 values correspond to the distances
    * 3 .. 258, the last 256 values correspond to the top 8 bits of
    * the 15 bit distances.
    */

    int base_length[LENGTH_CODES];
    /* First normalized length for each code (0 = MIN_MATCH) */

    int base_dist[D_CODES];
    /* First normalized distance for each code (0 = distance of 1) */

    #define l_buf s->inbuf
    /* DECLARE(uch, l_buf, LIT_BUFSIZE);  buffer for literals or lengths */

    /* DECLARE(ush, d_buf, DIST_BUFSIZE); buffer for distances */

    uch flag_buf[(LIT_BUFSIZE/8)];
    /* flag_buf is a bit array distinguishing literals from lengths in
    * l_buf, thus indicating the presence or absence of a distance.
    */

    unsigned last_lit;    /* running index in l_buf */
    unsigned last_dist;   /* running index in d_buf */
    unsigned last_flags;  /* running index in flag_buf */
    uch flags;            /* current flags not yet saved in flag_buf */
    uch flag_bit;         /* current bit used in flags */
    /* bits are filled in flags starting at bit 0 (least significant).
    * Note: these flags are overkill in the current code since we don't
    * take advantage of DIST_BUFSIZE == LIT_BUFSIZE.
    */

    ulg opt_len;        /* bit length of current block with optimal trees */
    ulg static_len;     /* bit length of current block with static trees */

    off_t compressed_len; /* total bit length of compressed file */

    off_t input_len;      /* total byte length of input file */
    /* input_len is for debugging only since we can get it by other means. */

    ush *file_type;        /* pointer to UNKNOWN, BINARY or ASCII */
    int *file_method;      /* pointer to DEFLATE or STORE */

/* DECLARE(uch, window, 2L*WSIZE); */
/* Sliding window. Input bytes are read into the second half of the window,
 * and move to the first half later to keep a dictionary of at least WSIZE
 * bytes. With this organization, matches are limited to a distance of
 * WSIZE-MAX_MATCH bytes, but this ensures that IO is always
 * performed with a length multiple of the block size. Also, it limits
 * the window size to 64K, which is quite useful on MSDOS.
 * To do: limit the window size to WSIZE+BSZ if SMALL_MEM (the code would
 * be less efficient).
 */

/* DECLARE(Pos, prev, WSIZE); */
/* Link to older string with same hash index. To limit the size of this
 * array to 64K, this link is maintained only for the last 32K strings.
 * An index in this array is thus a window index modulo 32K.
 */

/* DECLARE(Pos, head, 1<<HASH_BITS); */
/* Heads of the hash chains or NIL. */

    ulg window_size;
    /* window size, 2*WSIZE except for MMAP or BIG_MEM, where it is the
    * input file length plus MIN_LOOKAHEAD.
    */

    long block_start;
    /* window position at the beginning of the current output block. Gets
    * negative when the window is moved backwards.
    */

    unsigned ins_h;  /* hash index of string to be inserted */

    #define H_SHIFT  ((HASH_BITS+MIN_MATCH-1)/MIN_MATCH)
    /* Number of bits by which ins_h and del_h must be shifted at each
    * input step. It must be such that after MIN_MATCH steps, the oldest
    * byte no longer takes part in the hash key, that is:
    *   H_SHIFT * MIN_MATCH >= HASH_BITS
    */

    unsigned int prev_length;
    /* Length of the best match at previous step. Matches not greater than this
    * are discarded. This is used in the lazy match evaluation.
    */

    unsigned strstart;      /* start of string to insert */
    unsigned match_start;   /* start of matching string */
    int           eofile;        /* flag set at end of input file */
    unsigned      lookahead;     /* number of valid bytes ahead in window */

    unsigned max_chain_length;
    /* To speed up deflation, hash chains are never searched beyond this length.
    * A higher limit improves compression ratio but degrades the speed.
    */

    unsigned int max_lazy_match;
    /* Attempt to find a better match only when the current match is strictly
    * smaller than this value. This mechanism is used only for compression
    * levels >= 4.
    */
    #define max_insert_length  max_lazy_match
    /* Insert new strings in the hash table only if the match length
    * is not greater than this length. This saves time but degrades compression.
    * max_insert_length is used only for compression levels <= 3.
    */

    int compr_level;
    /* compression level (1..9) */

    unsigned good_match;
    /* Use a faster search when the previous match is longer than this */

#ifdef  FULL_SEARCH
    # define nice_match MAX_MATCH
#else
    int nice_match; /* Stop searching when current match exceeds this */
#endif

    ulg crc;       /* crc on uncompressed file data */
    tree_desc l_desc;
    tree_desc d_desc;
    tree_desc bl_desc;
} gzip_state_t;

// extern int decrypt;        /* flag to turn on decryption */
// extern int exit_code;      /* program exit code */
// extern int verbose;        /* be verbose (-v) */
// extern int quiet;          /* be quiet (-q) */
// extern int level;          /* compression level */
// extern int test;           /* check .z file integrity */
// extern int to_stdout;      /* output to stdout (-c) */
// extern int save_orig_name; /* set if original name must be saved */

/* put_byte is used for the compressed output, put_ubyte for the
 * uncompressed output. However unlzw() uses window for its
 * suffix table instead of its output buffer, so it does not use put_ubyte
 * (to be cleaned up).
 */
#define put_byte(s, c) {(s)->outbuf[(s)->outcnt++]=(uch)(c); if ((s)->outcnt==OUTBUFSIZ)\
   flush_outbuf(s);}
#define put_ubyte(s, c) {(s)->window[(s)->outcnt++]=(uch)(c); if ((s)->outcnt==WSIZE)\
   flush_window(s);}

/* Output a 16 bit value, lsb first */
#define put_short(s, w) \
{ if ((s)->outcnt < OUTBUFSIZ-2) { \
    (s)->outbuf[(s)->outcnt++] = (uch) ((w) & 0xff); \
    (s)->outbuf[(s)->outcnt++] = (uch) ((ush)(w) >> 8); \
  } else { \
    put_byte(s, (uch)((w) & 0xff)); \
    put_byte(s, (uch)((ush)(w) >> 8)); \
  } \
}

/* Output a 32 bit value to the bit stream, lsb first */
#define put_long(s, n) { \
    put_short(s, (n) & 0xffff); \
    put_short(s, ((ulg)(n)) >> 16); \
}

#define seekable()    0  /* force sequential output */
#define translate_eol 0  /* no option -a yet */

#define tolow(c)  (isupper (c) ? tolower (c) : (c))  /* force to lower case */

/* Macros for getting two-byte and four-byte header values */
#define SH(p) ((ush)(uch)((p)[0]) | ((ush)(uch)((p)[1]) << 8))
#define LG(p) ((ulg)(SH(p)) | ((ulg)(SH((p)+2)) << 16))

/* Diagnostic functions */
#ifdef DEBUG
#  define Assert(cond,msg) {if(!(cond)) error(s, msg);}
#  define Trace(x) fprintf x
#  define Tracev(x) {if (s->verbose) fprintf x ;}
#  define Tracevv(x) {if (s->verbose>1) fprintf x ;}
#  define Tracec(c,x) {if (s->verbose && (c)) fprintf x ;}
#  define Tracecv(c,x) {if (s->verbose>1 && (c)) fprintf x ;}
#else
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#endif

#define WARN(msg) {if (!s->quiet) fprintf msg ; \
		   if (s->exit_code == OK) s->exit_code = WARNING;}

	/* in zip.c: */
extern int zip        OF((gzip_state_t *s));
extern int file_read  OF((gzip_state_t *s, char *buf,  unsigned size));

	/* in gzip.c */
RETSIGTYPE abort_gzip OF((void));

        /* in deflate.c */
void lm_init OF((gzip_state_t *s, int pack_level, ush *flags));
off_t deflate OF((gzip_state_t *s));

        /* in trees.c */
void ct_init     OF((gzip_state_t *s, ush *attr, int *method));
int  ct_tally    OF((gzip_state_t *s, int dist, int lc));
off_t flush_block OF((gzip_state_t *s, char *buf, ulg stored_len, int eof));

        /* in bits.c */
void     bi_init    OF((gzip_state_t *s, file_t zipfile));
void     send_bits  OF((gzip_state_t *s, int value, int length));
unsigned bi_reverse OF((unsigned value, int length));
void     bi_windup  OF((gzip_state_t *s));
void     copy_block OF((gzip_state_t *s, char *buf, unsigned len, int header));

	/* in util.c: */
extern int copy           OF((FILE *in, FILE *out));
extern ulg  updcrc        OF((uch *s, unsigned n));
extern void clear_bufs    OF((gzip_state_t *s));
extern void flush_outbuf  OF((gzip_state_t *s));
extern void flush_window  OF((void));
extern void write_buf     OF((gzip_state_t *s, FILE *fd, voidp buf, unsigned cnt));
extern char *strlwr       OF((char *s));
extern char *base_name    OF((char *fname));
extern int xunlink        OF((char *fname));
extern void error         OF((gzip_state_t *s, char *m));
extern void warning       OF((gzip_state_t *s, char *m));
extern void read_error    OF((gzip_state_t *s));
extern void write_error   OF((gzip_state_t *s));
extern void display_ratio OF((off_t num, off_t den, FILE *file));

	/* in inflate.c */
extern int inflate OF((void));

	/* in yesno.c */
extern int yesno OF((void));
