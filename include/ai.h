#ifndef AI_H
#define AI_H

#include "libultra.h"
#include "unk.h"

#define STRUCT_AIFLAG_UNK_LEN 10

typedef struct struct_aiFlag {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ UNK_TYPE1 unk_05[0x3];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[STRUCT_AIFLAG_UNK_LEN];
    /* 0x1A */ u8 unk_1A[STRUCT_AIFLAG_UNK_LEN];
    /* 0x24 */ u8 unk_24[STRUCT_AIFLAG_UNK_LEN];
    /* 0x2E */ u8 unk_2E[STRUCT_AIFLAG_UNK_LEN];
    /* 0x38 */ u8 unk_38[UNK_SIZE]; // TODO: at least size 2
    /* 0x39 */ u8 unk_39;
    /* 0x3A */ u8 unk_3A;
    /* 0x3B */ u8 unk_3B;
    /* 0x3C */ u8 unk_3C;
    /* 0x3D */ u8 unk_3D;
    /* 0x3E */ u8 unk_3E;
    /* 0x3F */ u8 unk_3F;
} struct_aiFlag; // size = 0x40

#define AIFLAG_LEN 100
extern struct_aiFlag aiFlag[AIFLAG_LEN];

#define AIROOT_LEN 50
extern u8 aiRoot[AIROOT_LEN][2];

#endif
