#ifndef LIBC_CTYPE_H
#define LIBC_CTYPE_H

#include "attributes.h"

#if VERSION_US || VERSION_GW

#define CTYPE_ISSPACE       0x01    /* 0x9~0xd , 0x20 */
#define CTYPE_ISUPPER       0x02    /* 'A'~'Z' */
#define CTYPE_ISLOWER       0x04    /* 'a'~'z' */
#define CTYPE_ISDIGIT       0x08    /* '0'~'9' */
#define CTYPE_ISHEX         0x10    /* 'a'~'f' , 'A'~'F' */
#define CTYPE_ISCONTROL     0x20    /* 0x0~0x1f , 0x7f */
#define CTYPE_ISPUNCTUATION 0x40    /* punctuation */
#define CTYPE_ISKANJI       0x80    /* SJIS 1st BYTE */
#define CTYPE_ISXDIGIT      0

extern unsigned char __ctype_map[0x100] DATA;

#define isalnum(c)    (__ctype_map[(unsigned char)c] & (CTYPE_ISDIGIT | CTYPE_ISUPPER | CTYPE_ISLOWER))
#define isalpha(c)    (__ctype_map[(unsigned char)c] & (CTYPE_ISUPPER | CTYPE_ISLOWER))
#define isascii(c)    ((unsigned)(c) < 0x80)
#define iscntrl(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISCONTROL)
#define isdigit(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISDIGIT)
#define isgraph(c)    ((c) >= 0x21 && (c) <= 0x7E)
#define islower(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISLOWER)
#define isprint(c)    ((c) >= 0x20 && (c) <= 0x7E)
#define ispunct(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISPUNCTUATION)
#define isspace(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISSPACE)
#define isupper(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISUPPER)
#define isxdigit(c)   (__ctype_map[(unsigned char)c] & (CTYPE_ISDIGIT | CTYPE_ISHEX))
#define iskanji(c)    (__ctype_map[(unsigned char)c] & CTYPE_ISKANJI)

#define _toupper(c)   ((c) + 'A' - 'a')
#define _tolower(c)   ((c) + 'a' - 'A')
#define toascii(c)    ((c) & 0x7f)

#elif VERSION_CN

extern unsigned char __MojiStat[0x101] DATA;

#define CTYPE_ISCONTROL     0x01    /* 0x00~0x1F, 0x7F */
#define CTYPE_ISDIGIT       0x02    /* '0'~'9' */
#define CTYPE_ISLOWER       0x04    /* 'a'~'z' */
#define CTYPE_ISUPPER       0x08    /* 'A'~'Z' */
#define CTYPE_ISXDIGIT      0x10    /* 'A'~'F', 'a'~'f', '0'~'9' */
#define CTYPE_ISSPACE       0x20    /* 0x09~0x0D, 0x20 */
#define CTYPE_ISHEX         0
#define CTYPE_ISPUNCTUATION 0
#define CTYPE_ISKANJI       0


#define iscntrl(c)    ((__MojiStat+1)[c] & CTYPE_ISCONTROL)
#define isdigit(c)    ((__MojiStat+1)[c] & CTYPE_ISDIGIT)
#define islower(c)    ((__MojiStat+1)[c] & CTYPE_ISLOWER)
#define isupper(c)    ((__MojiStat+1)[c] & CTYPE_ISUPPER)
#define isxdigit(c)   ((__MojiStat+1)[c] & CTYPE_ISXDIGIT)
#define isalnum(c)    ((__MojiStat+1)[c] & (CTYPE_ISDIGIT | CTYPE_ISLOWER | CTYPE_ISUPPER))
#define isascii(c)    ((__MojiStat+1)[c] & (CTYPE_ISLOWER | CTYPE_ISUPPER))
#define isspace(c)    ((__MojiStat+1)[c] & CTYPE_ISSPACE)

#endif

#endif
