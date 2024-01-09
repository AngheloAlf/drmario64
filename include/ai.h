#ifndef AI_H
#define AI_H

#include "libultra.h"
#include "unk.h"

typedef struct struct_aiFlag {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ UNK_TYPE1 unk_05[0x3];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x30];
    /* 0x3C */ UNK_TYPE1 unk_3C[0x3];
    /* 0x3F */ u8 unk_3F;
} struct_aiFlag; // size = 0x40

extern struct_aiFlag aiFlag[];

#define AIROOT_LEN 50

extern u8 aiRoot[AIROOT_LEN][2];

#endif
