#ifndef ROM_OFFSETS_H
#define ROM_OFFSETS_H

#include "libc/stdint.h"


typedef struct struct_8000E778 {
    /* 0x0 */ romoffset_t unk_0;
    /* 0x4 */ romoffset_t unk_4;
} struct_8000E778; // size = 0x8

typedef struct struct_8000E838 {
    /* 0x0 */ romoffset_t start;
    /* 0x4 */ romoffset_t end;
} struct_8000E838; // size = 0x8


extern romoffset_t D_8000E740;
extern romoffset_t D_8000E744;
extern romoffset_t D_8000E748;
extern romoffset_t D_8000E74C;
extern romoffset_t D_8000E750;
extern romoffset_t D_8000E754;
extern romoffset_t D_8000E758;
extern romoffset_t D_8000E75C;
extern romoffset_t D_8000E760;
extern romoffset_t D_8000E764;
extern romoffset_t D_8000E768;
extern romoffset_t D_8000E76C;
extern romoffset_t D_8000E770;
extern romoffset_t D_8000E774;

extern struct_8000E778 D_8000E778[];

extern struct_8000E838 D_8000E838[];
/*
extern romoffset_t D_8000E9B0;
extern romoffset_t D_8000E9B4[];
extern romoffset_t D_8000E9D8;
extern romoffset_t D_8000E9DC;
extern romoffset_t D_8000E9E0;
extern romoffset_t D_8000E9E4[];
extern romoffset_t D_8000EA40;
extern romoffset_t D_8000EA44;
*/

extern romoffset_t D_8000EA48;
extern romoffset_t D_8000EA4C;

#endif
