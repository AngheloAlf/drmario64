#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "gcc/stdlib.h"
#include "unk.h"
#include "alignment.h"


typedef struct struct_80029C04 {
    romoffset_t segmentRom;
    size_t segmentSize;
} struct_80029C04;

typedef struct struct_800EB670_unk_668 {
    /* 0x0 */ struct struct_800EB670_unk_668 *unk_0;
    /* 0x4 */ OSMesgQueue *unk_4;
} struct_800EB670_unk_668; // size >= 0x8


typedef struct struct_8001D7F8 {
    /* 0x0 */ u8 *unk_0; // dstAddr
    /* 0x4 */ size_t unk_4; // uncompressedSize
} struct_8001D7F8; // size >= 0x8

typedef struct struct_800EB670_unk_66C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x10];
    /* 0x40 */ OSTask unk_10;
} struct_800EB670_unk_66C;  // size >= 0x50

// Maybe the same one as struct_800EB670_unk_66C?
typedef struct struct_8002A2B8_sp10 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x10];
    /* 0x40 */ OSTask unk_10;
    /* 0x50 */ OSMesgQueue *unk_50;
    /* 0x54 */ OSMesg *unk_54;
} struct_8002A2B8_sp10; // size >= 0x58

typedef struct struct_800EB670 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ OSMesgQueue unk_004;
    /* 0x01C */ OSMesg unk_01C[8];
    /* 0x03C */ OSMesgQueue unk_03C;
    /* 0x054 */ OSMesg unk_054[8];
    /* 0x074 */ OSMesgQueue unk_074;
    /* 0x08C */ OSMesg unk_08C[8];
    /* 0x0AC */ OSMesgQueue unk_0AC;
    /* 0x0C4 */ OSMesg unk_0C4[8];
    /* 0x0E4 */ OSMesgQueue unk_0E4;
    /* 0x0FC */ OSMesg unk_0FC[8];
    /* 0x11C */ OSMesgQueue unk_11C;
    /* 0x134 */ OSMesg unk_134[8];
    /* 0x154 */ UNK_TYPE1 unk_154[0x4];
    /* 0x158 */ OSThread unk_158;
    /* 0x308 */ OSThread unk_308;
    /* 0x4B8 */ OSThread unk_4B8;
    /* 0x668 */ struct_800EB670_unk_668 *unk_668;
    /* 0x66C */ struct_800EB670_unk_66C *unk_66C;
    /* 0x670 */ struct_8002A2B8_sp10 *unk_670;
    /* 0x674 */ UNK_TYPE unk_674;
    /* 0x678 */ UNK_TYPE unk_678;
} struct_800EB670; // size >= 0x67C

typedef void (*StartThreadFunc)(void *);


typedef struct struct_800FAF98_unk_64 {
    /* 0x0 */ UNK_PTR unk_0;
    /* 0x4 */ OSMesgQueue *unk_4;
} struct_800FAF98_unk_64; // size = 0x8



typedef struct struct_800FACE0_unk_08 {
    /* 0x0 */ UNK_TYPE unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
    /* 0x8 */ UNK_TYPE unk_8;
} struct_800FACE0_unk_08; // size = 0xC


typedef struct struct_8002AB28_arg0_unk_0 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ UNK_TYPE1 unk_1;
    /* 0x2 */ UNK_TYPE1 unk_2;
    /* 0x2 */ UNK_TYPE1 unk_3;
    /* 0x4 */ UNK_TYPE1 unk_4[0x1];
    /* 0x5 */ u8 volume;
} struct_8002AB28_arg0_unk_0; // size >= 0x6

typedef struct struct_8002AB28_arg0 {
    /* 0x0 */ struct_8002AB28_arg0_unk_0 *unk_0;
    /* 0x4 */ s32 index;
} struct_8002AB28_arg0; // size >= 0x8

typedef struct struct_800FACE0 {
    /* 0x00 */ UNK_TYPE unk_00[2];
    /* 0x08 */ struct_800FACE0_unk_08 unk_08[4];
    /* 0x38 */ struct_8002AB28_arg0 *unk_38[4];
} struct_800FACE0; // size >= 0x3C

typedef struct struct_800E5A70 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x0C];
    /* 0x0C */ char *unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE1 unk_1C[0x44];
    /* 0x60 */ UNK_TYPE unk_60;
    /* 0x64 */ UNK_TYPE1 unk_64[0x1C];
} struct_800E5A70; // size = 0x80

typedef struct struct_8005D78C_arg0 {
    /* 0x0 */ UNK_TYPE1 unk_0[1];
} struct_8005D78C_arg0; // size = ?

typedef struct struct_800EBEF0 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x550];
} struct_800EBEF0; // size = 0x550

typedef struct struct_8005FC6C_arg0 {
    /* 0x000 */ UNK_TYPE4 unk_000;
    /* 0x004 */ UNK_TYPE4 unk_004;
    /* 0x008 */ UNK_TYPE4 unk_008;
    /* 0x00C */ UNK_TYPE1 UNK_00C[0x2E8];
} struct_8005FC6C_arg0; // size = 0x2F4

typedef struct struct_80205000 {
    /* 0x00 */ UNK_TYPE1 unk_00[UNK_SIZE];
} struct_80205000; // size = ?

typedef struct struct_800EA290_unk_11EC {
    /* 0x0 */ void (*unk_0)(s32);
    /* 0x4 */ s32 unk_4;
} struct_800EA290_unk_11EC; // size = 0x8

typedef struct struct_800EA290 {
    /* 0x0000 */ STACK(stack, 0x1000);
    /* 0x1000 */ OSThread thread;
    /* 0x11B0 */ OSMesgQueue mq;
    /* 0x11C8 */ OSMesg msg[9];
    /* 0x11EC */ struct_800EA290_unk_11EC unk_11EC[10];
    /* 0x123C */ s32 unk_123C;
    /* 0x1240 */ s32 unk_1240;
} struct_800EA290; // size >= 0x1244


typedef struct struct_800F3E50 {
    /* 0x000 */ UNK_TYPE1 unk_000[0xB60];
} struct_800F3E50; // size = 0xB60


struct struct_80041A54_arg0;

typedef void (*struct_80041A54_arg0_unk_30)(struct struct_80041A54_arg0 *arg0);

typedef struct struct_80041A54_arg0 {
    /* 0x00 */ Gfx **unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ TexturePtr unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ struct_80041A54_arg0_unk_30 unk_30;
    /* 0x34 */ struct_80041A54_arg0_unk_30 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ struct_80041A54_arg0_unk_30 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ UNK_TYPE1 unk_58[0x18];
} struct_80041A54_arg0; // size >= 0x70?

// GraphBin?
typedef struct struct_800E8750 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x8];
    /* 0x008 */ u16 unk_008;
    /* 0x00A */ u16 unk_00A;
    /* 0x00C */ UNK_TYPE2 unk_00C;
    /* 0x00E */ u8 unk_00E;
    /* 0x00F */ UNK_TYPE1 unk_00F[0x1];
    /* 0x010 */ UNK_TYPE unk_010;
    /* 0x014 */ UNK_TYPE1 unk_014[0x1FC];
    /* 0x210 */ UNK_TYPE unk_210;
} struct_800E8750; // size >= 0x214

typedef struct struct_80076CA0_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ UNK_PTR unk_0C;
    /* 0x10 */ UNK_PTR unk_10;
    /* 0x14 */ UNK_TYPE1 unk_14[0x4];
} struct_80076CA0_arg0; // size = 0x18

typedef struct struct_8007F004_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
} struct_8007F004_arg0;

typedef struct struct_800F1DF8 {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x1400];
} struct_800F1DF8; // size = 0x1400

#endif
