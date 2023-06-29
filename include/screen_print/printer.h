#ifndef SCREEN_PRINT_PRINTER_H
#define SCREEN_PRINT_PRINTER_H

#include "libultra.h"
#include "libc/stdarg.h"
#include "libc/stddef.h"

struct struct_8008E364;

typedef s32 (*struct_8008E364_unk_0_unk_0)(struct struct_8008E364 *, va_list);

typedef s32 (*struct_8008E364_unk_0_unk_4)(void);

typedef s32 (*struct_8008E364_unk_0_unk_8)(struct struct_8008E364 *, char *, size_t);

typedef struct struct_8008E364_unk_0 {
    /* 0x0 */ struct_8008E364_unk_0_unk_0 unk_0;
    /* 0x0 */ struct_8008E364_unk_0_unk_4 unk_4;
    /* 0x0 */ struct_8008E364_unk_0_unk_8 unk_8;
} struct_8008E364_unk_0; // size = 0xC

typedef void (*struct_8008E364_unk_4_unk_04)(Gfx **, s32, s32, char);

typedef struct struct_8008E364_unk_4 {
    /* 0x00 */ Gfx **gfxP;
    /* 0x00 */ struct_8008E364_unk_4_unk_04 unk_04;
    /* 0x00 */ s16 unk_08;
    /* 0x00 */ s16 unk_0A;
    /* 0x00 */ s16 unk_0C;
    /* 0x00 */ s16 unk_0E;
    /* 0x00 */ s16 unk_10;
} struct_8008E364_unk_4; // size = 0x12

typedef struct struct_8008E364 {
    /* 0x0 */ struct_8008E364_unk_0 *unk_0;
    /* 0x4 */ struct_8008E364_unk_4 *unk_4;
} struct_8008E364; // size = 4

s32 func_8003CDA0(struct_8008E364 *arg0, ...);
s32 func_8003CDD4(struct_8008E364 *arg0);
s32 func_8003CDF8(struct_8008E364 *arg0, char *arg1, size_t arg2);

#endif
