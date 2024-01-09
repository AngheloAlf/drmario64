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
#include "gamemap.h"
#include "main.h"
#include "dm_game_main.h"

struct TiTexData;
struct TiTexData;

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
    /* 0x000 */ struct struct_virus_map_data *virusMapData;
    /* 0x004 */ u8 *virusMapDispOrder;
    /* 0x008 */ s32 virusCount;
    /* 0x00C */ u8 unk_00C[UNK_SIZE];
    /* 0x00D */ UNK_TYPE1 unk_00D[0x3];
    /* 0x010 */ UNK_TYPE1 unk_010[0x5C];
    /* 0x06C */ u8 unk_06C[UNK_SIZE][0x20];
    /* 0x08C */ UNK_TYPE1 unk_08C[0x40];
    /* 0x0CC */ s32 unk_0CC[3];
    /* 0x0D8 */ u8 unk_0D8[UNK_SIZE][0x20];
    /* 0x0F8 */ UNK_TYPE1 unk_0F8[0x40];
    /* 0x138 */ s32 unk_138[UNK_SIZE];
    /* 0x13C */ UNK_TYPE1 unk_13C[0x8];
    /* 0x144 */ u8 unk_144[UNK_SIZE][0x20];
    /* 0x164 */ UNK_TYPE1 unk_164[0x40];
    /* 0x1A4 */ s32 unk_1A4[UNK_SIZE];
    /* 0x1A8 */ UNK_TYPE1 unk_1A8[0x8];
    /* 0x1B0 */ u8 unk_1B0[UNK_SIZE][0x20];
    /* 0x1D0 */ UNK_TYPE1 unk_1D0[0x40];
    /* 0x210 */ s32 unk_210[UNK_SIZE];
    /* 0x214 */ UNK_TYPE1 unk_214[0x8];
    /* 0x21C */ u8 unk_21C[UNK_SIZE][0x20];
    /* 0x23C */ UNK_TYPE1 unk_23C[0x40];
    /* 0x27C */ s32 unk_27C[UNK_SIZE];
    /* 0x280 */ UNK_TYPE1 unk_280[0x8];
    /* 0x288 */ u8 unk_288[UNK_SIZE][0x20];
    /* 0x2A8 */ UNK_TYPE1 unk_2A8[0x40];
    /* 0x2E8 */ s32 unk_2E8[UNK_SIZE];
    /* 0x2EC */ UNK_TYPE1 unk_2EC[0x8];
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

#define ANIMES_COUNT 3

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
    /* 0x3CC */ f32 unk_3CC;
    /* 0x3D0 */ f32 unk_3D0[ANIMES_COUNT][2];
    /* 0x3E8 */ f32 unk_3E8[3];
    /* 0x3F4 */ f32 unk_3F4[ANIMES_COUNT];
    /* 0x400 */ UNK_TYPE4 unk_400[3]; // bool?
    /* 0x40C */ s32 unk_40C;
    /* 0x410 */ UNK_TYPE unk_410;
    /* 0x414 */ s32 unk_414;
    /* 0x418 */ u8 unk_418[3];
    /* 0x41B */ UNK_TYPE1 pad_41B[1]; // pad?
    /* 0x41C */ s32 unk_41C;
    /* 0x420 */ s32 unk_420;
    /* 0x424 */ s32 unk_424;
    /* 0x428 */ UNK_TYPE4 unk_428;
    /* 0x42C */ UNK_TYPE1 unk_42C[0x4];
    /* 0x430 */ struct TiTexData *unk_430;
    /* 0x434 */ struct TiTexData *unk_434;
    /* 0x438 */ struct TiTexData *unk_438;
    /* 0x43C */ struct TiTexData *unk_43C;
    /* 0x440 */ struct TiTexData *unk_440;
    /* 0x444 */ struct TiTexData *unk_444;
    /* 0x448 */ struct TiTexData *unk_448;
    /* 0x44C */ AnimeState animeStates[ANIMES_COUNT];
    /* 0x50C */ AnimeSmog animeSmogs[ANIMES_COUNT];
    /* 0x878 */ UNK_TYPE unk_878;
    /* 0x87C */ TexturePtr unk_87C; // SnapBg?
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
    /* 0x99C */ s32 unk_99C;
    /* 0x9A0 */ s32 unk_9A0[3];
    /* 0x9AC */ s32 unk_9AC; // TODO: func_8006A938 implies this member is part of unk_9A0, but it doesn't seem to make much sense to do so
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
    /* 0xAAC */ unsigned char unk_AAC[42]; // passwordPrompt?
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

// GameStateBackup?
typedef struct struct_gameBackup {
    /* 0x0000 */ struct_watchGame unk_0000;
    /* 0x0B60 */ struct_game_state_data unk_0B60[4];
    /* 0x1A70 */ GameMapCell unk_1A70[4][GAME_MAP_ROWS * GAME_MAP_COLUMNS];
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

typedef struct struct_virus_map_data {
    /* 0x0 */ s8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
} struct_virus_map_data; // size = 0x3

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
