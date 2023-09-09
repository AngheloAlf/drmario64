#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "version.h"
#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "gcc/stdlib.h"
#include "other_types.h"
#include "color.h"
#include "unk.h"
#include "alignment.h"
#include "msgwnd.h"
#include "recwritingmsg.h"
#include "char_anime.h"
#include "mainmenu.h"
#include "gamemap.h"
#include "main.h"

struct TiTexData;
struct TiTexDataEntry;

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


typedef struct struct_watchGame_unk_0B8_unk_00 {
    /* 0x00 */ UNK_TYPE4 unk_00;
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
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

// SnapBg?
typedef struct struct_watchGame_unk_87C {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x26700];
} struct_watchGame_unk_87C; // size = 0x26700

typedef struct struct_watchGame_unk_9D0 {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} struct_watchGame_unk_9D0; // size = 0x2C

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
    /* 0x3BC */ s32 unk_3BC; // enum_evs_gamemode?
    /* 0x3C0 */ s32 unk_3C0;
    /* 0x3C4 */ s32 unk_3C4;
    /* 0x3C8 */ f32 unk_3C8;
    /* 0x3CC */ s32 unk_3CC;
    /* 0x3D0 */ UNK_TYPE1 unk_3D0[0x18];
    /* 0x3E8 */ f32 unk_3E8[3];
    /* 0x3F4 */ f32 unk_3F4[3];
    /* 0x400 */ UNK_TYPE4 unk_400[3]; // bool?
    /* 0x40C */ s32 unk_40C;
    /* 0x410 */ UNK_TYPE unk_410;
    /* 0x414 */ s32 unk_414;
    /* 0x418 */ u8 unk_418[3];
    /* 0x41C */ s32 unk_41C;
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ s32 unk_424;
    /* 0x428 */ UNK_TYPE4 unk_428;
    /* 0x42C */ UNK_TYPE1 unk_42C[0x4];
    /* 0x430 */ struct TiTexData *unk_430;
    /* 0x434 */ struct TiTexData *unk_434;
    /* 0x448 */ struct TiTexData *unk_438;
    /* 0x43C */ struct TiTexData *unk_43C;
    /* 0x440 */ struct TiTexData *unk_440;
    /* 0x444 */ struct TiTexData *unk_444;
    /* 0x448 */ struct TiTexData *unk_448;
    /* 0x44C */ AnimeState animeStates[3];
    /* 0x50C */ AnimeSmog animeSmogs[3];
    /* 0x878 */ UNK_TYPE unk_878;
    /* 0x87C */ struct_watchGame_unk_87C *unk_87C;
    /* 0x880 */ s32 unk_880;
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
    /* 0xAAC */ char unk_AAC[42]; // passwordPrompt?
    /* 0xAD8 */ RecordWritingMessage recMessage;
} struct_watchGame; // size = 0xB60


typedef struct struct_8002A51C_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ void *unk_0C;
} struct_8002A51C_arg1; // size >= 0x10


typedef struct struct_evs_cfg_4p {
    /* 0x00 */ u8 unk_00[5][4];
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
} struct_evs_cfg_4p; // size = 0x16

typedef struct struct_800E87C0_unk_00 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_800E87C0_unk_00; // size = 0x8

typedef struct struct_800E87C0 {
    /* 0x00 */ struct_800E87C0_unk_00 unk_00[8];
} struct_800E87C0; // size = 0x407

// not sure about this struct
typedef struct struct_80123700_unk_0D4_unk_00 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ s32 unk_8;
} struct_80123700_unk_0D4_unk_00; // size = 0xC

typedef struct struct_80123700_unk_0D4 {
    /* 0x00 */ struct_80123700_unk_0D4_unk_00 unk_00[UNK_SIZE];
    /* 0x00 */ UNK_TYPE1 unk_0C[0x60];
} struct_80123700_unk_0D4; // size = 0x6C

typedef struct struct_80123700_unk_140 {
    /* 0x00 */ UNK_TYPE4 unk_00[UNK_SIZE];
    /* 0x04 */ UNK_TYPE1 unk_04[0x20];
} struct_80123700_unk_140; // size = 0x24

typedef struct struct_game_state_data_unk_178 {
    /* 0x0 */ s8 unk_0[2];
    /* 0x0 */ s8 unk_2[2];
    /* 0x0 */ s8 unk_4[2];
    /* 0x0 */ s8 unk_6[2];
    /* 0x0 */ s8 unk_8;
    /* 0x0 */ s8 unk_9;
    /* 0x0 */ s8 unk_A;
} struct_game_state_data_unk_178; // size = 0xB

typedef struct struct_game_state_data_unk_050 {
    /* 0x0 */ u16 unk_0;
    /* 0x2 */ u16 unk_2;
} struct_game_state_data_unk_050; // size = 0x4

typedef struct struct_game_state_data {
    /* 0x000 */ u32 unk_000;
    /* 0x004 */ u16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
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
    /* 0x034 */ s8 unk_034;
    /* 0x035 */ u8 unk_035;
    /* 0x036 */ u8 unk_036;
    /* 0x037 */ u8 unk_037;
    /* 0x038 */ u8 unk_038;
    /* 0x039 */ u8 unk_039;
    /* 0x03A */ u8 unk_03A;
    /* 0x03B */ u8 unk_03B;
    /* 0x03C */ u8 unk_03C[4];
    /* 0x040 */ u8 unk_040;
    /* 0x041 */ UNK_TYPE1 unk_041[0x3];
    /* 0x040 */ UNK_TYPE unk_044;
    /* 0x048 */ u8 unk_048;
    /* 0x048 */ u8 unk_049;
    /* 0x048 */ u8 unk_04A;
    /* 0x04B */ u8 unk_04B;
    /* 0x04C */ u8 unk_04C;
    /* 0x04D */ s8 unk_04D;
    /* 0x04E */ u8 unk_04E;
    /* 0x04F */ u8 unk_04F;
    /* 0x050 */ struct_game_state_data_unk_050 unk_050[0x10];
    /* 0x090 */ CharAnimeMode unk_090;
    /* 0x094 */ AnimeState unk_094;
    /* 0x0D4 */ struct_80123700_unk_0D4 unk_0D4;
    /* 0x140 */ struct_80123700_unk_140 unk_140;
    /* 0x164 */ s32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ UNK_TYPE4 unk_170;
    /* 0x174 */ UNK_TYPE4 unk_174;
    /* 0x178 */ struct_game_state_data_unk_178 unk_178;
    /* 0x183 */ UNK_TYPE1 unk_183[1];
    /* 0x184 */ struct_game_state_data_unk_178 unk_184;
    /* 0x18F */ UNK_TYPE1 unk_18F[1];
    /* 0x190 */ s32 unk_190[4][4];
    /* 0x1D0 */ u8 unk_1D0[0x32][2];
    /* 0x234 */ u8 unk_234;
    /* 0x235 */ UNK_TYPE1 unk_235[2];
    /* 0x237 */ s8 unk_237;
    /* 0x238 */ s8 unk_238;
    /* 0x239 */ s8 unk_239;
    /* 0x23A */ UNK_TYPE1 unk_23A[2];
    /* 0x23C */ u8 unk_23C;
    /* 0x23D */ u8 unk_23D;
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
    /* 0x294 */ u8 unk_294;
    /* 0x295 */ UNK_TYPE1 unk_295[0x3];
    /* 0x298 */ u8 unk_298;
    /* 0x299 */ UNK_TYPE1 unk_299[0x3];
    /* 0x29C */ u8 unk_29C[17][8][2]; // [GAME_MAP_ROWS][GAME_MAP_COLUMNS][2]
    /* 0x34C */ UNK_TYPE1 unk_3AC[0x10];
    /* 0x3BC */ u8 unk_3BC;
    /* 0x3BD */ u8 unk_3BD;
    /* 0x3BE */ UNK_TYPE1 unk_3BE[0x2];
    /* 0x3C0 */ u8 unk_3C0;
    /* 0x3C1 */ UNK_TYPE1 unk_3C1[0x3];
} struct_game_state_data; // size = 0x3C4

// GameStateBackup?
typedef struct struct_gameBackup {
    /* 0x0000 */ struct_watchGame unk_0000;
    /* 0x0B60 */ struct_game_state_data unk_0B60[4];
    /* 0x1A70 */ GameMapGrid unk_1A70[4];
    /* 0x2FB0 */ s32 highScore;
    /* 0x2FB4 */ s32 gameTime;
} struct_gameBackup; // size = 0x2FB8

typedef struct struct_800F4890_unk_034 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08; // alpha, 0.0f ~ 1.0f
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
    /* 0x148 */ u8 unk_148[3];
    /* 0x14C */ struct_800F4890_unk_14C unk_14C[3];
    /* 0x164 */ u32 unk_164;
    /* 0x168 */ u32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ s32 unk_174[4];
    /* 0x184 */ s32 unk_184;
} struct_watchManual; // size = 0x188


typedef struct struct_watchMenu_unk_02470 {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x60000];
} struct_watchMenu_unk_02470; // size = 0x60000

typedef struct struct_watchMenu {
    /* 0x00000 */ struct_800EB670 *unk_00000;
    /* 0x00004 */ struct_800FAF98_unk_64 unk_00004;
    /* 0x0000C */ OSMesgQueue unk_0000C;
    /* 0x00024 */ OSMesg unk_00024[8];
    /* 0x00044 */ UNK_TYPE1 unk_00044[4];
    /* 0x00048 */ Mtx unk_00048[3][0x10];
    /* 0x00C48 */ Vtx unk_00C48[3][0x80];
    /* 0x02448 */ Mtx *unk_02448[3];
    /* 0x02454 */ Vtx *unk_02454[3];
    /* 0x02460 */ UNK_PTR unk_02460;
    /* 0x02464 */ UNK_TYPE unk_02464;
    /* 0x02468 */ struct_watchMenu_unk_02470 *unk_02468[2];
    /* 0x02470 */ struct_watchMenu_unk_02470 *unk_02470[2];
    /* 0x02478 */ struct TiTexData *unk_02478;
    /* 0x0247C */ struct TiTexData *unk_0247C;
    /* 0x02480 */ UNK_TYPE1 unk_02480[4];
    /* 0x02484 */ struct TiTexData *unk_02484;
    /* 0x02488 */ struct TiTexData *unk_02488;
    /* 0x0248C */ struct TiTexData *unk_0248C;
    /* 0x02490 */ struct TiTexData *unk_02490;
    /* 0x02494 */ struct TiTexData *unk_02494;
    /* 0x02498 */ struct TiTexData *unk_02498;
    /* 0x0249C */ struct TiTexData *unk_0249C;
    /* 0x024A0 */ struct TiTexData *unk_024A0;
    /* 0x024A4 */ struct TiTexData *unk_024A4;
    /* 0x024A8 */ struct TiTexData *unk_024A8;
    /* 0x024AC */ struct TiTexData *unk_024AC;
    /* 0x024B0 */ struct TiTexData *unk_024B0;
    /* 0x024B4 */ struct TiTexData *unk_024B4;
    /* 0x024B8 */ MenuItem unk_024B8[1];
    /* 0x02548 */ UNK_TYPE unk_02548;
    /* 0x0254C */ UNK_TYPE1 unk_0254C[0x12C];
    /* 0x02678 */ MenusUnion unk_02678[2];
    /* 0x111C0 */ UNK_TYPE unk_111C0;
    /* 0x111C4 */ UNK_TYPE unk_111C4;
    /* 0x111C8 */ MainMenuMode unk_111C8;
    /* 0x111CC */ MainMenuMode unk_111CC;
    /* 0x111D0 */ MainMenuMode unk_111D0;
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

typedef enum enum_evs_gamesel {
    /* 0 */ ENUM_EVS_GAMESEL_0,
    /* 1 */ ENUM_EVS_GAMESEL_1,
    /* 2 */ ENUM_EVS_GAMESEL_2,
    /* 3 */ ENUM_EVS_GAMESEL_3,
    /* 4 */ ENUM_EVS_GAMESEL_4,
    /* 5 */ ENUM_EVS_GAMESEL_5,
    /* 6 */ ENUM_EVS_GAMESEL_6,
    /* 7 */ ENUM_EVS_GAMESEL_MAX
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

#if VERSION_CN
typedef struct struct_8010ACB0_cn {
    /* 0x000 */ s32 unk_000;
    /* 0x000 */ s32 unk_004;
    /* 0x008 */ u64 unk_008;
    /* 0x010 */ u64 unk_010[8];
    /* 0x050 */ u64 unk_050[8];
    /* 0x090 */ u64 unk_090[8];
    /* 0x0D0 */ u64 unk_0D0[4];
    /* 0x0F0 */ u64 unk_0F0[4];
    /* 0x110 */ UNK_TYPE1 unk_110[0x8];
} struct_8010ACB0_cn; // size = 0x118
#endif

typedef enum enum_800E5930 {
    /* 0 */ ENUM_800E5930_0,
    /* 1 */ ENUM_800E5930_1,
    /* 2 */ ENUM_800E5930_2,
    /* 3 */ ENUM_800E5930_MAX
} enum_800E5930;

typedef struct struct_ai_param {
    /* 0x00 */ UNK_TYPE2 unk_00;
    /* 0x02 */ UNK_TYPE2 unk_02;
    /* 0x04 */ UNK_TYPE2 unk_04;
    /* 0x06 */ UNK_TYPE2 unk_06;
    /* 0x08 */ UNK_TYPE2 unk_08;
    /* 0x0A */ UNK_TYPE2 unk_0A;
    /* 0x0C */ UNK_TYPE2 unk_0C;
    /* 0x0E */ UNK_TYPE2 unk_0E;
    /* 0x10 */ UNK_TYPE2 unk_10;
    /* 0x12 */ UNK_TYPE2 unk_12;
    /* 0x14 */ UNK_TYPE2 unk_14;
    /* 0x16 */ UNK_TYPE2 unk_16;
    /* 0x18 */ UNK_TYPE2 unk_18;
    /* 0x1A */ UNK_TYPE2 unk_1A;
    /* 0x1C */ UNK_TYPE2 unk_1C;
    /* 0x1E */ UNK_TYPE2 unk_1E;
    /* 0x20 */ UNK_TYPE2 unk_20;
    /* 0x22 */ UNK_TYPE2 unk_22;
    /* 0x24 */ UNK_TYPE2 unk_24;
    /* 0x26 */ UNK_TYPE2 unk_26;
    /* 0x28 */ UNK_TYPE2 unk_28;
    /* 0x2A */ UNK_TYPE2 unk_2A;
    /* 0x2C */ UNK_TYPE2 unk_2C;
    /* 0x2E */ UNK_TYPE2 unk_2E;
    /* 0x30 */ UNK_TYPE2 unk_30;
    /* 0x32 */ UNK_TYPE2 unk_32;
    /* 0x34 */ UNK_TYPE2 unk_34;
    /* 0x36 */ UNK_TYPE2 unk_36;
} struct_ai_param; // size = 0x38

#define AI_PARAM_LEN1 6
#define AI_PARAM_LEN2 8

#define STRUCT_AI_CHAR_DATA_LEN 16

typedef struct struct_ai_char_data {
    /* 0x00 */ UNK_TYPE1 unk_00;
    /* 0x01 */ UNK_TYPE1 unk_01;
    /* 0x02 */ UNK_TYPE2 unk_02;
    /* 0x04 */ s8 unk_04[8];
    /* 0x0C */ s8 unk_0C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x1C */ s16 unk_1C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x3C */ s8 unk_3C[STRUCT_AI_CHAR_DATA_LEN];
    /* 0x4C */ s16 unk_4C[STRUCT_AI_CHAR_DATA_LEN];
} struct_ai_char_data; // size = 0x6C

#define AI_CHAR_DATA_LEN 16

typedef struct struct_800E5938 {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ s8 unk_1;
    /* 0x2 */ u16 unk_2;
} struct_800E5938; // size = 0x4

typedef struct struct_800E5968 {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ s8 unk_1;
} struct_800E5968; // size = 0x2

typedef struct struct_8007E260_arg0 {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_8007E260_arg0; // size >= 0xC

typedef struct struct_8007E260_arg1 {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_8007E260_arg1; // size >= 0xC

typedef struct struct_8007E260_arg2 {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 unk_4;
    /* 0x8 */ f32 unk_8;
} struct_8007E260_arg2; // size >= 0xC

#endif
