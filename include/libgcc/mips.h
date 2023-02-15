#ifndef LIBGCC_MIPS_H
#define LIBGCC_MIPS_H

/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.
*/
#define BITS_BIG_ENDIAN 0

/* Define this if most significant byte of a word is the lowest numbered. */
#define BYTES_BIG_ENDIAN (TARGET_BIG_ENDIAN != 0)

/* Define this if most significant word of a multiword number is the lowest. */
#define WORDS_BIG_ENDIAN (TARGET_BIG_ENDIAN != 0)

/* Define this to set the endianness to use in libgcc2.c, which can
   not depend on target_flags.  */
#if !defined(MIPSEL) && !defined(__MIPSEL__)
#define LIBGCC2_WORDS_BIG_ENDIAN 1
#else
#define LIBGCC2_WORDS_BIG_ENDIAN 0
#endif

/* Number of bits in an addressable storage unit */
#define BITS_PER_UNIT 8

#endif
