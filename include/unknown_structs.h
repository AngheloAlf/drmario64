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
#include "recwritingmsg.h"
#include "char_anime.h"


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


typedef struct struct_watchGame_unk_0B8_unk_00 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x10];
    /* 0x10 */ f32 unk_10;
} struct_watchGame_unk_0B8_unk_00; // size = 0x14

typedef struct struct_watchGame_unk_070 {
    /* 0x00 */ UNK_TYPE *unk_00;
    /* 0x04 */ UNK_TYPE *unk_04;
    /* 0x08 */ s32 unk_08[0x10];
} struct_watchGame_unk_070; // size = 0x48

typedef struct struct_watchGame_unk_0B8 {
    /* 0x00 */ struct_watchGame_unk_0B8_unk_00 unk_00[8];
    /* 0xA0 */ UNK_TYPE4 unk_A0;
} struct_watchGame_unk_0B8; // size = 0xA4

typedef struct struct_watchGame_unk_430_unk_B8 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x4 */ UNK_TYPE unk_4;
} struct_watchGame_unk_430_unk_B8; // size >= 0x8

typedef struct struct_watchGame_unk_430_unk_BC {
    /* 0x0 */ u16 unk_0;
    /* 0x2 */ u16 unk_2;
} struct_watchGame_unk_430_unk_BC; // size >= 0x4

typedef struct struct_watchGame_unk_430_unk_C0 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x4 */ UNK_TYPE unk_4;
} struct_watchGame_unk_430_unk_C0; // size >= 0x8

typedef struct struct_watchGame_unk_430 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xB8];
    /* 0xB8 */ struct_watchGame_unk_430_unk_B8 *unk_B8;
    /* 0xBC */ struct_watchGame_unk_430_unk_BC *unk_BC;
    /* 0xC0 */ struct_watchGame_unk_430_unk_C0 *unk_C0;
    /* 0xC4 */ u16 *unk_C4;
} struct_watchGame_unk_430; // size >= 0xC8

typedef struct struct_watchGame_unk_9D0 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x28];
    /* 0x28 */ s32 unk_28;
} struct_watchGame_unk_9D0; // size = 0x2C

typedef struct struct_watchGame_unk_AAC {
    /* 0x00 */ UNK_TYPE1 unk_00[0x2A];
} struct_watchGame_unk_AAC; // size = 0x2A

typedef struct struct_watchGame {
    /* 0x000 */ UNK_TYPE4 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C[0xC];
    /* 0x03C */ s32 unk_03C[0xC];
    /* 0x06C */ s32 unk_06C;
    /* 0x070 */ struct_watchGame_unk_070 unk_070;
    /* 0x0B8 */ struct_watchGame_unk_0B8 unk_0B8[4];
    /* 0x348 */ UNK_TYPE4 unk_348[UNK_SIZE];
    /* 0x34C */ UNK_TYPE1 unk_34C[0xC];
    /* 0x358 */ UNK_TYPE4 unk_358[UNK_SIZE];
    /* 0x35C */ UNK_TYPE1 unk_35C[0xC];
    /* 0x368 */ UNK_TYPE4 unk_368[UNK_SIZE];
    /* 0x36C */ UNK_TYPE1 unk_36C[0xC];
    /* 0x378 */ UNK_TYPE4 unk_378;
    /* 0x37C */ s32 unk_37C[4];
    /* 0x38C */ UNK_TYPE unk_38C;
    /* 0x390 */ UNK_TYPE unk_390;
    /* 0x394 */ s32 unk_394;
    /* 0x398 */ s32 unk_398;
    /* 0x39C */ s32 unk_39C[4];
    /* 0x3AC */ s32 unk_3AC;
    /* 0x3B0 */ s32 unk_3B0;
    /* 0x3B4 */ s32 unk_3B4;
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ s32 unk_3BC;
    /* 0x3C0 */ s32 unk_3C0;
    /* 0x3C4 */ s32 unk_3C4;
    /* 0x3C8 */ f32 unk_3C8;
    /* 0x3CC */ s32 unk_3CC;
    /* 0x3D0 */ UNK_TYPE1 unk_3D0[0x18];
    /* 0x3E8 */ f32 unk_3E8[3];
    /* 0x3F4 */ f32 unk_3F4[3];
    /* 0x400 */ UNK_TYPE4 unk_400[3];
    /* 0x40C */ s32 unk_40C;
    /* 0x410 */ UNK_TYPE unk_410;
    /* 0x414 */ s32 unk_414;
    /* 0x418 */ s8 unk_418[3];
    /* 0x41C */ s32 unk_41C;
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ s32 unk_424;
    /* 0x428 */ UNK_TYPE4 unk_428;
    /* 0x42C */ UNK_TYPE1 unk_42C[0x4];
    /* 0x430 */ struct_watchGame_unk_430 *unk_430;
    /* 0x434 */ UNK_TYPE4 unk_434;
    /* 0x448 */ UNK_TYPE4 unk_438;
    /* 0x43C */ UNK_TYPE4 unk_43C;
    /* 0x440 */ UNK_TYPE4 unk_440;
    /* 0x444 */ UNK_TYPE4 unk_444;
    /* 0x448 */ UNK_TYPE4 unk_448;
    /* 0x44C */ AnimeState animeStates[3];
    /* 0x50C */ AnimeSmog animeSmogs[3];
    /* 0x878 */ UNK_TYPE unk_878;
    /* 0x87C */ void *unk_87C;
    /* 0x880 */ UNK_TYPE unk_880;
    /* 0x884 */ UNK_PTR unk_884;
    /* 0x888 */ UNK_TYPE4 unk_888[UNK_SIZE];
    /* 0x88C */ UNK_TYPE1 unk_88C[0xC];
    /* 0x898 */ s32 unk_898;
    /* 0x89C */ s32 unk_89C[4];
    /* 0x8AC */ s32 unk_8AC[2];
    /* 0x8B4 */ s32 unk_8B4[2];
    /* 0x8BC */ s32 unk_8BC;
    /* 0x8C0 */ s32 unk_8C0;
    /* 0x8C4 */ s32 unk_8C4;
    /* 0x8C8 */ s32 unk_8C8;
    /* 0x8CC */ s32 unk_8CC[4];
    /* 0x8DC */ s32 unk_8DC[4][4];
    /* 0x91C */ MessageWnd messageWnd;
    /* 0x99C */ UNK_TYPE1 unk_99C[0x10];
    /* 0x9AC */ s32 unk_9AC;
    /* 0x9B0 */ s32 unk_9B0;
    /* 0x9B4 */ s32 unk_9B4;
    /* 0x9B8 */ s32 unk_9B8;
    /* 0x9BC */ s32 unk_9BC;
    /* 0x9C0 */ UNK_TYPE4 unk_9C0;
    /* 0x9C4 */ UNK_TYPE4 unk_9C4;
    /* 0x9C8 */ s32 unk_9C8;
    /* 0x9CC */ s32 unk_9CC;
    /* 0x9D0 */ struct_watchGame_unk_9D0 unk_9D0[2];
    /* 0xA28 */ MessageWnd unk_A28;
    /* 0xAA8 */ s32 unk_AA8;
    /* 0xAAC */ struct_watchGame_unk_AAC unk_AAC;
    /* 0xAD8 */ RecordWritingMessage recMessage;
} struct_watchGame; // size = 0xB60


struct StretchTexBlock_arg0;

typedef void (*StretchTexBlock_arg0_callback)(struct StretchTexBlock_arg0 *arg0);

typedef struct StretchTexBlock_arg0 {
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
    /* 0x30 */ StretchTexBlock_arg0_callback unk_30;
    /* 0x34 */ StretchTexBlock_arg0_callback unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ StretchTexBlock_arg0_callback unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ UNK_TYPE1 unk_58[0x18];
} StretchTexBlock_arg0; // size >= 0x70?

struct StretchTexTile_arg0;

typedef void (*StretchTexTile_arg0_callback)(struct StretchTexTile_arg0 *arg0);

typedef struct StretchTexTile_arg0 {
    /* 0x00 */ Gfx **gfxP;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ UNK_TYPE unk_24;
    /* 0x28 */ UNK_TYPE unk_28;
    /* 0x2C */ UNK_TYPE unk_2C;
    /* 0x30 */ UNK_TYPE unk_30;
    /* 0x34 */ UNK_TYPE unk_34;
    /* 0x38 */ UNK_TYPE unk_38;
    /* 0x3C */ UNK_TYPE unk_3C;
    /* 0x40 */ StretchTexTile_arg0_callback unk_40;
    /* 0x44 */ StretchTexTile_arg0_callback unk_44;
    /* 0x48 */ UNK_TYPE unk_48;
    /* 0x4C */ StretchTexTile_arg0_callback unk_4C;
    /* 0x50 */ UNK_TYPE unk_50;
    /* 0x54 */ UNK_TYPE unk_54;
    /* 0x58 */ UNK_TYPE1 unk_58[0x20];
} StretchTexTile_arg0; // size = 0x78

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

typedef struct struct_800F1DF8 {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x1400];
} struct_800F1DF8; // size = 0x1400

typedef struct struct_8002A51C_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ void *unk_0C;
} struct_8002A51C_arg1; // size >= 0x10


typedef struct struct_800EF560_unk_B4 {
    /* 0x00 */ UNK_TYPE1 unk_00;
    /* 0x01 */ UNK_TYPE1 unk_01;
    /* 0x02 */ UNK_TYPE1 unk_02;
    /* 0x03 */ UNK_TYPE1 unk_03;
    /* 0x04 */ UNK_TYPE1 unk_04;
    /* 0x05 */ UNK_TYPE1 unk_05;
    /* 0x06 */ UNK_TYPE1 unk_06;
    /* 0x07 */ UNK_TYPE1 unk_07;
    /* 0x08 */ UNK_TYPE1 unk_08;
    /* 0x09 */ UNK_TYPE1 unk_09;
    /* 0x0A */ UNK_TYPE1 unk_0A;
    /* 0x0B */ UNK_TYPE1 unk_0B;
    /* 0x0C */ UNK_TYPE1 unk_0C;
    /* 0x0D */ UNK_TYPE1 unk_0D;
    /* 0x0E */ UNK_TYPE1 unk_0E;
    /* 0x0F */ UNK_TYPE1 unk_0F;
    /* 0x10 */ UNK_TYPE1 unk_10;
    /* 0x11 */ UNK_TYPE1 unk_11;
    /* 0x12 */ UNK_TYPE1 unk_12;
    /* 0x13 */ UNK_TYPE1 unk_13;
    /* 0x14 */ UNK_TYPE1 unk_14;
    /* 0x15 */ UNK_TYPE1 unk_15;
    /* 0x16 */ UNK_TYPE1 unk_16;
    /* 0x17 */ UNK_TYPE1 unk_17;
    /* 0x18 */ UNK_TYPE1 unk_18;
    /* 0x19 */ UNK_TYPE1 unk_19;
} struct_800EF560_unk_B4; // size >= 0x1A

typedef struct struct_800EF560_unk_28 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ u8 unk_8;
} struct_800EF560_unk_28; // size = 0xC

typedef struct struct_800EF560_unk_4C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
} struct_800EF560_unk_4C; // size = 0x8

typedef struct struct_800EF560_unk_64 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
} struct_800EF560_unk_64; // size = 0x8

typedef struct struct_800EF560_unk_7C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
    /* 0x4 */ UNK_TYPE unk_8;
} struct_800EF560_unk_7C; // size = 0xC

typedef struct struct_800EF560 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ s32 unk_08[3][2];
    /* 0x20 */ UNK_TYPE1 unk_20[0x8];
    /* 0x28 */ struct_800EF560_unk_28 unk_28[3];
    /* 0x4C */ struct_800EF560_unk_4C unk_4C[UNK_SIZE];
    /* 0x54 */ UNK_TYPE1 unk_54[0x10];
    /* 0x64 */ struct_800EF560_unk_64 unk_64[UNK_SIZE];
    /* 0x6C */ UNK_TYPE1 unk_6C[0x10];
    /* 0x7C */ struct_800EF560_unk_7C unk_7C[UNK_SIZE];
    /* 0x88 */ UNK_TYPE1 unk_88[0x20];
    /* 0xA8 */ u16 unk_A8;
    /* 0xAA */ UNK_TYPE1 unk_AA[0x2];
    /* 0xAC */ UNK_TYPE1 unk_AC[0x8];
    /* 0xB4 */ struct_800EF560_unk_B4 unk_B4;
    /* 0xCE */ UNK_TYPE1 unk_CE[0x2]; // pad?
} struct_800EF560; // size = 0xD0

typedef struct struct_800F7470 {
    /* 0x00 */ UNK_TYPE1 unk_00[5][4];
    /* 0x14 */ UNK_TYPE1 unk_14;
    /* 0x15 */ UNK_TYPE1 unk_15;
} struct_800F7470; // size = 0x16

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

typedef struct struct_80123700_unk_0D4 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x6C];
} struct_80123700_unk_0D4; // size = 0x6C

typedef struct struct_80123700_unk_140 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x24];
} struct_80123700_unk_140; // size = 0x24

typedef struct struct_game_state_data_unk_178 {
    /* 0x0 */ UNK_TYPE1 unk_0;
    /* 0x0 */ UNK_TYPE1 unk_1;
    /* 0x0 */ s8 unk_2;
    /* 0x0 */ UNK_TYPE1 unk_3;
    /* 0x0 */ UNK_TYPE1 unk_4;
    /* 0x0 */ UNK_TYPE1 unk_5;
    /* 0x0 */ UNK_TYPE1 unk_6;
    /* 0x0 */ UNK_TYPE1 unk_7;
    /* 0x0 */ UNK_TYPE1 unk_8;
    /* 0x0 */ UNK_TYPE1 unk_9;
    /* 0x0 */ UNK_TYPE1 unk_A;
} struct_game_state_data_unk_178; // size >= 0xB

typedef struct struct_game_state_data {
    /* 0x000 */ UNK_TYPE unk_000;
    /* 0x004 */ u16 unk_004;
    /* 0x006 */ u16 unk_006;
    /* 0x008 */ u16 unk_008;
    /* 0x008 */ s8 unk_00A;
    /* 0x008 */ UNK_TYPE1 unk_00B[0x1];
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ UNK_TYPE1 unk_010[0x4];
    /* 0x014 */ UNK_TYPE4 unk_014;
    /* 0x018 */ UNK_TYPE1 unk_018[0x4];
    /* 0x01C */ UNK_TYPE4 unk_01C;
    /* 0x020 */ u32 unk_020;
    /* 0x024 */ u8 unk_024;
    /* 0x025 */ u8 unk_025;
    /* 0x026 */ u8 unk_026;
    /* 0x027 */ u8 unk_027;
    /* 0x028 */ s8 unk_028;
    /* 0x029 */ u8 unk_029;
    /* 0x02A */ u8 unk_02A;
    /* 0x02B */ u8 unk_02B;
    /* 0x02C */ u8 unk_02C;
    /* 0x02D */ u8 unk_02D;
    /* 0x02E */ u8 unk_02E;
    /* 0x02F */ u8 unk_02F;
    /* 0x030 */ u8 unk_030;
    /* 0x031 */ u8 unk_031;
    /* 0x032 */ u8 unk_032;
    /* 0x033 */ u8 unk_033;
    /* 0x034 */ u8 unk_034;
    /* 0x035 */ u8 unk_035;
    /* 0x036 */ u8 unk_036;
    /* 0x037 */ u8 unk_037;
    /* 0x038 */ u8 unk_038;
    /* 0x039 */ u8 unk_039;
    /* 0x03A */ u8 unk_03A;
    /* 0x03B */ UNK_TYPE1 unk_03B[0x1];
    /* 0x03C */ u8 unk_03C[4];
    /* 0x040 */ UNK_TYPE1 unk_040[0x4];
    /* 0x040 */ UNK_TYPE unk_044;
    /* 0x048 */ u8 unk_048;
    /* 0x048 */ u8 unk_049;
    /* 0x048 */ u8 unk_04A;
    /* 0x04B */ u8 unk_04B;
    /* 0x04C */ u8 unk_04C;
    /* 0x04D */ s8 unk_04D;
    /* 0x04E */ s8 unk_04E;
    /* 0x04F */ u8 unk_04F;
    /* 0x050 */ u16 unk_050[0x10][2];
    /* 0x090 */ s32 unk_090; // CharAnimeMode?
    /* 0x094 */ AnimeState unk_094;
    /* 0x0D4 */ struct_80123700_unk_0D4 unk_0D4;
    /* 0x140 */ struct_80123700_unk_140 unk_140;
    /* 0x164 */ s32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ UNK_TYPE4 unk_170;
    /* 0x174 */ UNK_TYPE4 unk_174;
    /* 0x178 */ struct_game_state_data_unk_178 unk_178;
    /* 0x183 */ UNK_TYPE1 unk_183[0x1];
    /* 0x184 */ UNK_TYPE1 unk_184[0xB0];
    /* 0x234 */ UNK_TYPE1 unk_234[3];
    /* 0x237 */ s8 unk_237;
    /* 0x238 */ s8 unk_238;
    /* 0x239 */ s8 unk_239;
    /* 0x23A */ UNK_TYPE1 unk_23A[2];
    /* 0x23C */ UNK_TYPE1 unk_23C[1];
    /* 0x23D */ s8 unk_23D;
    /* 0x23E */ s8 unk_23E;
    /* 0x23F */ UNK_TYPE1 unk_23F[1];
    /* 0x240 */ UNK_TYPE1 unk_240[1];
    /* 0x241 */ s8 unk_241;
    /* 0x242 */ s8 unk_242[0x10];
    /* 0x252 */ UNK_TYPE1 unk_252[2];
    /* 0x254 */ UNK_TYPE1 unk_254[0x1C];
    /* 0x270 */ UNK_TYPE1 unk_270[2];
    /* 0x272 */ s16 unk_272[0x10];
    /* 0x292 */ s8 unk_292;
    /* 0x293 */ UNK_TYPE1 unk_293[0x1];
    /* 0x294 */ s8 unk_294;
    /* 0x295 */ UNK_TYPE1 unk_295[0x3];
    /* 0x298 */ UNK_TYPE1 unk_298[0x12C];
} struct_game_state_data; // size = 0x3C4

typedef struct struct_800F4890_unk_034 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ MessageWnd messageWnd;
} struct_800F4890_unk_034; // size = 0x90

typedef struct struct_800F4890_unk_0E8 {
    /* 0x0 */ s8 unk_0;
    /* 0x0 */ s8 unk_1;
    /* 0x0 */ s8 unk_2;
    /* 0x0 */ s8 unk_3[3];
} struct_800F4890_unk_0E8; // size = 0x6

typedef struct struct_800F4890_unk_0C4 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x4 */ s32 unk_8;
} struct_800F4890_unk_0C4; // size = 0xC

typedef struct struct_800F4890_unk_14C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} struct_800F4890_unk_14C; // size = 0x8

typedef struct struct_watchManual {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ s32 unk_01C[4];
    /* 0x02C */ s32 unk_02C;
    /* 0x030 */ s32 unk_030;
    /* 0x034 */ struct_800F4890_unk_034 unk_034;
    /* 0x0C4 */ struct_800F4890_unk_0C4 unk_0C4[3];
    /* 0x0E8 */ struct_800F4890_unk_0E8 unk_0E8[4][4];
    /* 0x148 */ UNK_TYPE1 unk_148[0x4];
    /* 0x14C */ struct_800F4890_unk_14C unk_14C[3];
    /* 0x164 */ u32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ s32 unk_174[4];
    /* 0x184 */ s32 unk_184;
} struct_watchManual; // size = 0x188

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

typedef struct struct_800F3E5C_unk_024B8 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ UNK_TYPE1 unk_14[0x58];
    /* 0x6C */ f32 unk_6C[3];
    /* 0x78 */ UNK_TYPE1 unk_78[0x4];
    /* 0x7C */ f32 unk_7C[3];
} struct_800F3E5C_unk_024B8; // size >= 0x88

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

typedef struct struct_watchMenu {
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
    /* 0x024B8 */ struct_800F3E5C_unk_024B8 unk_024B8;
    /* 0x02540 */ UNK_TYPE1 unk_02540[0x8];
    /* 0x02548 */ UNK_TYPE unk_02548;
    /* 0x0254C */ UNK_TYPE1 unk_0254C[0x12C];
    /* 0x02678 */ struct_800F3E5C_unk_02678 unk_02678[2];
    /* 0x111C0 */ UNK_TYPE unk_111C0;
    /* 0x111C4 */ UNK_TYPE unk_111C4;
    /* 0x111C8 */ enum_struct_800F3E5C_unk_111CC unk_111C8;
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
    /* 0x111F8 */ RecordWritingMessage recMessage;
} struct_watchMenu; // size = 0x11280

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

typedef struct struct_800365B0_arg0 {
    /* 0x00 */ UNK_PTR unk_00;
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
    /* 0x14 */ UNK_TYPE1 unk_14[0x4];
} struct_800365B0_arg0; // size <= 0x18?

typedef enum enum_evs_gamesel {
    /* 0 */ ENUM_EVS_GAMESEL_0,
    /* 1 */ ENUM_EVS_GAMESEL_1,
    /* 2 */ ENUM_EVS_GAMESEL_2,
    /* 3 */ ENUM_EVS_GAMESEL_3,
    /* 4 */ ENUM_EVS_GAMESEL_4,
    /* 5 */ ENUM_EVS_GAMESEL_5,
    /* 6 */ ENUM_EVS_GAMESEL_6
} enum_evs_gamesel;

typedef struct struct_virus_map_data_unk_000 {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
} struct_virus_map_data_unk_000; // size = 0x3

typedef struct struct_virus_map_data {
    /* 0x000 */ struct_virus_map_data_unk_000 unk_000[0x80];
} struct_virus_map_data; // size = 0x180

typedef struct struct_virus_map_disp_order {
    /* 0x00 */ u8 unk_00[0x60];
} struct_virus_map_disp_order; // size = 0x60

typedef struct dm_calc_erase_score_pos_arg2 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
} dm_calc_erase_score_pos_arg2; // size >= 0x8

typedef enum enum_evs_gamemode {
    /* 0 */ ENUM_EVS_GAMEMODE_0,
    /* 1 */ ENUM_EVS_GAMEMODE_1,
    /* 2 */ ENUM_EVS_GAMEMODE_2,
    /* 3 */ ENUM_EVS_GAMEMODE_3
} enum_evs_gamemode;

// Maybe same enum as `BgRomDataIndex`
typedef enum enum_story_proc_no {
    /*  0 */ STORY_PROC_NO_0,
    /*  1 */ STORY_PROC_NO_1,
    /*  2 */ STORY_PROC_NO_2,
    /*  3 */ STORY_PROC_NO_3,
    /*  4 */ STORY_PROC_NO_4,
    /*  5 */ STORY_PROC_NO_5,
    /*  6 */ STORY_PROC_NO_6,
    /*  7 */ STORY_PROC_NO_7,
    /*  8 */ STORY_PROC_NO_8,
    /*  9 */ STORY_PROC_NO_9,
    /* 10 */ STORY_PROC_NO_10,
    /* 11 */ STORY_PROC_NO_11,
    /* 12 */ STORY_PROC_NO_12,
    /* 13 */ STORY_PROC_NO_13,
    /* 14 */ STORY_PROC_NO_14,
    /* 15 */ STORY_PROC_NO_15,
    /* 16 */ STORY_PROC_NO_16,
    /* 17 */ STORY_PROC_NO_17,
    /* 18 */ STORY_PROC_NO_18,
    /* 19 */ STORY_PROC_NO_19,
    /* 20 */ STORY_PROC_NO_20,
    /* 21 */ STORY_PROC_NO_21,
    /* 22 */ STORY_PROC_NO_22,
    /* 23 */ STORY_PROC_NO_23,
    /* 24 */ STORY_PROC_NO_24
} enum_story_proc_no;

typedef enum enum_evs_manual_no {
    /* 0 */ EVS_MANUAL_NO_0,
    /* 1 */ EVS_MANUAL_NO_1,
    /* 2 */ EVS_MANUAL_NO_2,
    /* 3 */ EVS_MANUAL_NO_3,
    /* 4 */ EVS_MANUAL_NO_4,
    /* 5 */ EVS_MANUAL_NO_5
} enum_evs_manual_no;

#endif
