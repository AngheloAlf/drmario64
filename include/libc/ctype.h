#ifndef LIBC_CTYPE_H
#define LIBC_CTYPE_H

#define CTYPE_ISSPACE       0x01    /* 0x9-0xd , 0x20 */
#define CTYPE_ISUPPER       0x02    /* 'A'-'Z' */
#define CTYPE_ISLOWER       0x04    /* 'a'-'z' */
#define CTYPE_ISDIGIT       0x08    /* '0'-'9' */
#define CTYPE_ISHEX         0x10    /* 'a'-'f' , 'A'-'F' */
#define CTYPE_ISCONTROL     0x20    /* 0x0-0x1f , 0x7f */
#define CTYPE_ISPUNCTUATION 0x40    /* punctuation */
#define CTYPE_ISKANJI       0x80    /* SJIS 1st BYTE */

extern unsigned char __ctype_map[0x100];

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

#endif
