#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "gcc/stdlib.h"
#include "color.h"
#include "unk.h"
#include "alignment.h"
#include "msgwnd.h"


typedef struct struct_800FAF98_unk_64 {
    /* 0x0 */ struct struct_800FAF98_unk_64 *unk_0;
    /* 0x4 */ OSMesgQueue *unk_4;
} struct_800FAF98_unk_64; // size = 0x8


typedef struct struct_800EB670_unk_66C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x00 */ u32 unk_08;
    /* 0x0C */ void *unk_0C; // framebuffer
    /* 0x40 */ OSTask unk_10;
    /* 0x50 */ OSMesgQueue *unk_50;
    /* 0x54 */ OSMesg *unk_54;
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
    /* 0x668 */ struct_800FAF98_unk_64 *unk_668;
    /* 0x66C */ struct_800EB670_unk_66C *unk_66C;
    /* 0x670 */ struct_8002A2B8_sp10 *unk_670;
    /* 0x674 */ UNK_TYPE unk_674;
    /* 0x678 */ UNK_TYPE unk_678;
} struct_800EB670; // size >= 0x67C

typedef void (*StartThreadFunc)(void *);


typedef struct struct_800EBEF0 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x550];
} struct_800EBEF0; // size = 0x550 // or maybe 0x1540, or an array of 4 elements

typedef struct struct_8005FC6C_arg0 {
    /* 0x000 */ UNK_TYPE4 unk_000;
    /* 0x004 */ UNK_TYPE4 unk_004;
    /* 0x008 */ UNK_TYPE4 unk_008;
    /* 0x00C */ UNK_TYPE1 UNK_00C[0x2E8];
} struct_8005FC6C_arg0; // size = 0x2F4

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
    /* 0x000 */ UNK_TYPE1 unk_000[0x394];
    /* 0x394 */ s32 unk_394;
    /* 0x398 */ s32 unk_398;
    /* 0x39C */ UNK_TYPE1 unk_39C[0x28];
    /* 0x3C4 */ s32 unk_3C4;
    /* 0x3C8 */ UNK_TYPE1 unk_3C8[0x5C];
    /* 0x424 */ s32 unk_424;
    /* 0x428 */ UNK_TYPE1 unk_428[0x4F4];
    /* 0x91C */ MessageWnd messageWnd;
    /* 0x99C */ UNK_TYPE1 unk_99C[0x10];
    /* 0x9AC */ s32 unk_9AC;
    /* 0x9B0 */ s32 unk_9B0;
    /* 0x9B4 */ UNK_TYPE1 unk_9B4[0x1AC];
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

// Probably the same one as struct_8007F004_arg0
typedef struct struct_8007F04C_arg0 {
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
} struct_8007F04C_arg0;

typedef struct struct_800F1DF8 {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x1400];
} struct_800F1DF8; // size = 0x1400

typedef struct struct_8002A51C_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ void *unk_0C;
} struct_8002A51C_arg1; // size >= 0x10


typedef struct struct_800EF560 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xD0];
} struct_800EF560; // size = 0xD0

typedef struct struct_800F7470 {
    /* 0x0 */ UNK_TYPE1 unk_0[UNK_SIZE];
} struct_800F7470; // size = ?

typedef struct struct_800E87C0_unk_00 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_800E87C0_unk_00; // size = 0x8

typedef struct struct_800E87C0 {
    /* 0x00 */ struct_800E87C0_unk_00 unk_00[8];
} struct_800E87C0; // size = 0x407

typedef enum enum_main_no {
    /*  0 */ MAIN_NO_0,
    /*  1 */ MAIN_NO_1,
    /*  2 */ MAIN_NO_2,
    /*  3 */ MAIN_NO_3,
    /*  4 */ MAIN_NO_4,
    /*  5 */ MAIN_NO_5,
    /*  6 */ MAIN_NO_6,
    /*  7 */ MAIN_NO_7,
    /*  8 */ MAIN_NO_8, // "no controller connected"
    /*  9 */ MAIN_NO_9, // "game not designed for this system"
    /* 10 */ MAIN_NO_10, // "backup file is damaged"
} enum_main_no;

typedef struct struct_80123700 {
    /* 0x000 */ UNK_TYPE unk_000;
    /* 0x004 */ UNK_TYPE2 unk_004;
    /* 0x006 */ UNK_TYPE1 unk_006[0x2];
    /* 0x008 */ UNK_TYPE1 unk_008[0x18];
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ UNK_TYPE1 unk_024[0x2];
    /* 0x026 */ s8 unk_026;
    /* 0x027 */ UNK_TYPE1 unk_027[0x1];
    /* 0x028 */ UNK_TYPE1 unk_028[0x4];
    /* 0x02C */ s8 unk_02C;
    /* 0x02D */ UNK_TYPE1 unk_02D[0x3];
    /* 0x030 */ UNK_TYPE1 unk_030[0x18];
    /* 0x048 */ UNK_TYPE1 unk_048[0x3];
    /* 0x04B */ s8 unk_04B;
    /* 0x04C */ s8 unk_04C;
    /* 0x04D */ s8 unk_04D;
    /* 0x04E */ s8 unk_04E;
    /* 0x04F */ s8 unk_04F;
    /* 0x050 */ UNK_TYPE1 unk_050[0x40];
    /* 0x090 */ s32 unk_090;
    /* 0x094 */ UNK_TYPE1 unk_094[0xD8];
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ UNK_TYPE1 unk_170[0xC4];
    /* 0x234 */ UNK_TYPE1 unk_234[3];
    /* 0x237 */ s8 unk_237;
    /* 0x238 */ s8 unk_238;
    /* 0x239 */ s8 unk_239;
    /* 0x23A */ UNK_TYPE1 unk_23A[2];
    /* 0x23C */ UNK_TYPE1 unk_23C[1];
    /* 0x23D */ s8 unk_23D;
    /* 0x23E */ UNK_TYPE1 unk_23E[2];
    /* 0x240 */ UNK_TYPE1 unk_240[1];
    /* 0x241 */ s8 unk_241;
    /* 0x242 */ UNK_TYPE1 unk_242[2];
    /* 0x244 */ UNK_TYPE1 unk_244[0x180];
} struct_80123700; // size = 0x3C4

typedef struct struct_800F4890 {
    /* 0x000 */ UNK_TYPE1 unk_000[0xC];
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ UNK_TYPE1 unk_01C[0x18];
    /* 0x034 */ UNK_TYPE unk_034;
    /* 0x038 */ UNK_TYPE1 unk_038[0x14C];
    /* 0x184 */ s32 unk_184;
} struct_800F4890; // size >= 0x188

typedef struct struct_800F3E5C_unk_00048 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x400];
} struct_800F3E5C_unk_00048; // size = 0x400

typedef struct struct_800F3E5C_unk_00C48 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x800];
} struct_800F3E5C_unk_00C48; // size = 0x800

typedef struct struct_800F3E5C_unk_02678_unk_0000 {
    /* 0x0 */ UNK_TYPE1 unk_0[UNK_SIZE];
} struct_800F3E5C_unk_02678_unk_0000; // size = ?

typedef struct struct_800F3E5C_unk_02678_unk_590 {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x3C8];
    /* 0x03C8 */ f32 unk_03C8;
    /* 0x03CC */ f32 unk_03CC;
    /* 0x03D0 */ UNK_TYPE1 unk_03D0[0x1C];
    /* 0x03EC */ f32 unk_03EC;
    /* 0x03F0 */ f32 unk_03F0;
    /* 0x03F4 */ UNK_TYPE1 unk_03F4[0x20D4];
} struct_800F3E5C_unk_02678_unk_590; // size = 0x24C8

typedef struct struct_800F3E5C_unk_02470 {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x60000];
} struct_800F3E5C_unk_02470; // size = 0x60000

typedef struct struct_800F3E5C_unk_02678 {
    /* 0x0000 */ struct_800F3E5C_unk_02678_unk_0000 *unk_0000;
    /* 0x0004 */ UNK_TYPE unk_0004;
    /* 0x0008 */ UNK_TYPE unk_0008;
    /* 0x000C */ UNK_TYPE unk_000C;
    /* 0x0010 */ UNK_TYPE unk_0010;
    /* 0x0014 */ UNK_TYPE unk_0014;
    /* 0x0018 */ UNK_TYPE unk_0018;
    /* 0x001C */ UNK_TYPE1 unk_001C[0x348];
    /* 0x0364 */ f32 unk_0364;
    /* 0x0368 */ f32 unk_0368;
    /* 0x036C */ UNK_TYPE1 unk_036C[0x224];
    /* 0x0590 */ struct_800F3E5C_unk_02678_unk_590 unk_590[2];
    /* 0x4F20 */ UNK_TYPE1 unk_4F20[0x2684];
} struct_800F3E5C_unk_02678; // size = 0x75A4

typedef enum enum_struct_800F3E5C_unk_111CC {
    /*  0 */ ENUM_STRUCT_800F3E5C_UNK_111CC_0,
    /*  1 */ ENUM_STRUCT_800F3E5C_UNK_111CC_1,
    /*  2 */ ENUM_STRUCT_800F3E5C_UNK_111CC_2,
    /*  3 */ ENUM_STRUCT_800F3E5C_UNK_111CC_3,
    /*  4 */ ENUM_STRUCT_800F3E5C_UNK_111CC_4,
    /*  5 */ ENUM_STRUCT_800F3E5C_UNK_111CC_5,
    /*  6 */ ENUM_STRUCT_800F3E5C_UNK_111CC_6,
    /*  7 */ ENUM_STRUCT_800F3E5C_UNK_111CC_7,
    /*  8 */ ENUM_STRUCT_800F3E5C_UNK_111CC_8,
    /*  9 */ ENUM_STRUCT_800F3E5C_UNK_111CC_9,
    /* 10 */ ENUM_STRUCT_800F3E5C_UNK_111CC_10,
    /* 11 */ ENUM_STRUCT_800F3E5C_UNK_111CC_11,
    /* 12 */ ENUM_STRUCT_800F3E5C_UNK_111CC_12,
    /* 13 */ ENUM_STRUCT_800F3E5C_UNK_111CC_13,
    /* 14 */ ENUM_STRUCT_800F3E5C_UNK_111CC_14,
    /* 15 */ ENUM_STRUCT_800F3E5C_UNK_111CC_15,
    /* 16 */ ENUM_STRUCT_800F3E5C_UNK_111CC_16,
    /* 17 */ ENUM_STRUCT_800F3E5C_UNK_111CC_17,
    /* 18 */ ENUM_STRUCT_800F3E5C_UNK_111CC_18,
    /* 19 */ ENUM_STRUCT_800F3E5C_UNK_111CC_19,
    /* 20 */ ENUM_STRUCT_800F3E5C_UNK_111CC_20,
    /* 21 */ ENUM_STRUCT_800F3E5C_UNK_111CC_21,
    /* 22 */ ENUM_STRUCT_800F3E5C_UNK_111CC_22,
    /* 23 */ ENUM_STRUCT_800F3E5C_UNK_111CC_23,
    /* 24 */ ENUM_STRUCT_800F3E5C_UNK_111CC_24,
    /* 25 */ ENUM_STRUCT_800F3E5C_UNK_111CC_25,
    /* 26 */ ENUM_STRUCT_800F3E5C_UNK_111CC_26,
    /* 27 */ ENUM_STRUCT_800F3E5C_UNK_111CC_27,
    /* 28 */ ENUM_STRUCT_800F3E5C_UNK_111CC_28,
    /* 29 */ ENUM_STRUCT_800F3E5C_UNK_111CC_29,
    /* 30 */ ENUM_STRUCT_800F3E5C_UNK_111CC_30,
    /* 31 */ ENUM_STRUCT_800F3E5C_UNK_111CC_31,
    /* 32 */ ENUM_STRUCT_800F3E5C_UNK_111CC_32,
    /* 33 */ ENUM_STRUCT_800F3E5C_UNK_111CC_33,
    /* 34 */ ENUM_STRUCT_800F3E5C_UNK_111CC_34,
    /* 35 */ ENUM_STRUCT_800F3E5C_UNK_111CC_35,
    /* 36 */ ENUM_STRUCT_800F3E5C_UNK_111CC_36,
    /* 37 */ ENUM_STRUCT_800F3E5C_UNK_111CC_37,
    /* 38 */ ENUM_STRUCT_800F3E5C_UNK_111CC_38,
    /* 39 */ ENUM_STRUCT_800F3E5C_UNK_111CC_39,
    /* 40 */ ENUM_STRUCT_800F3E5C_UNK_111CC_40,
    /* 41 */ ENUM_STRUCT_800F3E5C_UNK_111CC_41,
    /* 42 */ ENUM_STRUCT_800F3E5C_UNK_111CC_42,
    /* 43 */ ENUM_STRUCT_800F3E5C_UNK_111CC_43,
    /* 44 */ ENUM_STRUCT_800F3E5C_UNK_111CC_44,
    /* 45 */ ENUM_STRUCT_800F3E5C_UNK_111CC_45,
    /* 46 */ ENUM_STRUCT_800F3E5C_UNK_111CC_46,
    /* 47 */ ENUM_STRUCT_800F3E5C_UNK_111CC_47,
    /* 48 */ ENUM_STRUCT_800F3E5C_UNK_111CC_48,
    /* 49 */ ENUM_STRUCT_800F3E5C_UNK_111CC_49,
    /* 50 */ ENUM_STRUCT_800F3E5C_UNK_111CC_50,
    /* 51 */ ENUM_STRUCT_800F3E5C_UNK_111CC_51,
    /* 52 */ ENUM_STRUCT_800F3E5C_UNK_111CC_52,
    /* 53 */ ENUM_STRUCT_800F3E5C_UNK_111CC_53,
    /* 54 */ ENUM_STRUCT_800F3E5C_UNK_111CC_54,
    /* 55 */ ENUM_STRUCT_800F3E5C_UNK_111CC_55,
    /* 56 */ ENUM_STRUCT_800F3E5C_UNK_111CC_56,
    /* 57 */ ENUM_STRUCT_800F3E5C_UNK_111CC_57,
    /* 58 */ ENUM_STRUCT_800F3E5C_UNK_111CC_58,
    /* 59 */ ENUM_STRUCT_800F3E5C_UNK_111CC_59,
    /* 60 */ ENUM_STRUCT_800F3E5C_UNK_111CC_60,
    /* 61 */ ENUM_STRUCT_800F3E5C_UNK_111CC_61,
    /* 62 */ ENUM_STRUCT_800F3E5C_UNK_111CC_62,
    /* 63 */ ENUM_STRUCT_800F3E5C_UNK_111CC_63,
    /* 64 */ ENUM_STRUCT_800F3E5C_UNK_111CC_64,
} enum_struct_800F3E5C_unk_111CC;

typedef struct struct_800F3E5C {
    /* 0x00000 */ struct_800EB670 *unk_00000;
    /* 0x00004 */ struct_800FAF98_unk_64 unk_00004;
    /* 0x0000C */ OSMesgQueue unk_0000C;
    /* 0x00024 */ OSMesg unk_00024[8];
    /* 0x00044 */ UNK_TYPE1 unk_00044[4];
    /* 0x00048 */ struct_800F3E5C_unk_00048 unk_00048[3];
    /* 0x00C48 */ struct_800F3E5C_unk_00C48 unk_00C48[3];
    /* 0x02448 */ struct_800F3E5C_unk_00048 *unk_02448[3];
    /* 0x02454 */ struct_800F3E5C_unk_00C48 *unk_02454[3];
    /* 0x02460 */ UNK_PTR unk_02460;
    /* 0x02464 */ UNK_TYPE unk_02464;
    /* 0x02468 */ struct_800F3E5C_unk_02470 *unk_02468[2];
    /* 0x02470 */ struct_800F3E5C_unk_02470 *unk_02470[2];
    /* 0x02478 */ UNK_TYPE unk_02478;
    /* 0x0247C */ UNK_TYPE unk_0247C;
    /* 0x02480 */ UNK_TYPE1 unk_02480[4];
    /* 0x02484 */ UNK_TYPE unk_02484;
    /* 0x02488 */ UNK_TYPE unk_02488;
    /* 0x0248C */ UNK_TYPE unk_0248C;
    /* 0x02490 */ UNK_TYPE unk_02490;
    /* 0x02494 */ UNK_TYPE unk_02494;
    /* 0x02498 */ UNK_TYPE unk_02498;
    /* 0x0249C */ UNK_TYPE unk_0249C;
    /* 0x024A0 */ UNK_TYPE unk_024A0;
    /* 0x024A4 */ UNK_TYPE unk_024A4;
    /* 0x024A8 */ UNK_TYPE unk_024A8;
    /* 0x024AC */ UNK_TYPE unk_024AC;
    /* 0x024B0 */ UNK_TYPE unk_024B0;
    /* 0x024B4 */ UNK_TYPE unk_024B4;
    /* 0x024B8 */ UNK_TYPE unk_024B8;
    /* 0x024BC */ UNK_TYPE1 unk_024BC[0x8];
    /* 0x024C4 */ f32 unk_024C4;
    /* 0x024C8 */ f32 unk_024C8;
    /* 0x024CC */ UNK_TYPE1 unk_024CC[0x7C];
    /* 0x02548 */ UNK_TYPE unk_02548;
    /* 0x0254C */ UNK_TYPE1 unk_0254C[0x12C];
    /* 0x02678 */ struct_800F3E5C_unk_02678 unk_02678[2];
    /* 0x111C0 */ UNK_TYPE unk_111C0;
    /* 0x111C4 */ UNK_TYPE unk_111C4;
    /* 0x111C8 */ UNK_TYPE unk_111C8;
    /* 0x111CC */ enum_struct_800F3E5C_unk_111CC unk_111CC;
    /* 0x111D0 */ UNK_TYPE unk_111D0;
    /* 0x111D4 */ enum_main_no unk_111D4;
    /* 0x111D8 */ UNK_TYPE unk_111D8;
    /* 0x111DC */ f32 unk_111DC;
    /* 0x111E0 */ f32 unk_111E0;
    /* 0x111E4 */ UNK_TYPE unk_111E4;
    /* 0x111E8 */ UNK_TYPE unk_111E8;
    /* 0x111EC */ UNK_TYPE unk_111EC;
    /* 0x111F0 */ UNK_TYPE unk_111F0;
    /* 0x111F4 */ UNK_TYPE unk_111F4; // thread priority?
    /* 0x111F8 */ UNK_TYPE unk_111F8;
    /* 0x111FC */ UNK_TYPE1 unk_111FC[0x84];
} struct_800F3E5C; // size = 0x11280

typedef enum enum_graphic_no {
    /* 0 */ GRAPHIC_NO_0, // NONE?
    /* 1 */ GRAPHIC_NO_1,
    /* 2 */ GRAPHIC_NO_2,
    /* 3 */ GRAPHIC_NO_3,
    /* 4 */ GRAPHIC_NO_4,
    /* 5 */ GRAPHIC_NO_5,
    /* 6 */ GRAPHIC_NO_6,
    /* 7 */ GRAPHIC_NO_7 // ERROR?
} enum_graphic_no;


#endif
