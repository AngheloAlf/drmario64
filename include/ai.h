#ifndef AI_H
#define AI_H

#include "libultra.h"
#include "unk.h"

typedef enum ThinkType {
    /*   -1 */ THINKTYPE_INVALID = -1,
    /* 0x00 */ THINKTYPE_0,
    /* 0x01 */ THINKTYPE_1,
    /* 0x02 */ THINKTYPE_2,
    /* 0x03 */ THINKTYPE_3,
    /* 0x04 */ THINKTYPE_4,
    /* 0x05 */ THINKTYPE_5,
    /* 0x06 */ THINKTYPE_6,
    /* 0x07 */ THINKTYPE_7,
    /* 0x08 */ THINKTYPE_8,
    /* 0x09 */ THINKTYPE_9,
    /* 0x0A */ THINKTYPE_A,
    /* 0x0B */ THINKTYPE_B,
    /* 0x0C */ THINKTYPE_C,
    /* 0x0D */ THINKTYPE_D,
    /* 0x0E */ THINKTYPE_E,
    /* 0x0F */ THINKTYPE_F,
    /* 0x10 */ THINKTYPE_MAX,
} ThinkType;

#define AI_CHAR_DATA_LEN (THINKTYPE_MAX)

#define STRUCT_AIFLAG_UNK_LEN 10

typedef struct struct_aiFlag {
    /* 0x00 */ u8 ok; /* Original name: ok */
    /* 0x01 */ u8 tory; /* Original name: tory */
    /* 0x02 */ u8 x; /* Original name: x */
    /* 0x03 */ u8 y; /* Original name: y */
    /* 0x04 */ u8 rev; /* Original name: rev */
    /* 0x05 */ u8 ccnt; /* Original name: ccnt */ // unused
    /* 0x08 */ s32 pri; /* Original name: pri */
    /* 0x0C */ s32 dead; /* Original name: dead */
    /* 0x10 */ u8 hei[2][STRUCT_AIFLAG_UNK_LEN]; /* Original name: hei */
    /* 0x24 */ u8 wid[2][STRUCT_AIFLAG_UNK_LEN]; /* Original name: wid */
    /* 0x38 */ u8 elin[2]; /* Original name: elin */
    /* 0x3A */ u8 only[2]; /* Original name: only */
    /* 0x3C */ u8 wonly[2]; /* Original name: wonly */
    /* 0x3E */ u8 sub; /* Original name: sub */
    /* 0x3F */ u8 rensa; /* Original name: rensa */
} struct_aiFlag; // size = 0x40

typedef struct struct_aiRoot {
    /* 0x0 */ u8 x; /* Original name: x */
    /* 0x1 */ u8 y; /* Original name: y */
} struct_aiRoot; // size = 0x2

#define AIFLAG_LEN 100
extern struct_aiFlag aiFlag[AIFLAG_LEN];

#define AIROOT_LEN 50
extern struct_aiRoot aiRoot[AIROOT_LEN];

#endif
