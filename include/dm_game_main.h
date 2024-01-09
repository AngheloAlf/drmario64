#ifndef DM_GAME_MAIN_H
#define DM_GAME_MAIN_H

#include "libultra.h"
#include "ai.h"
#include "char_anime.h"
#include "gamemap.h"
#include "unk.h"

typedef struct struct_gameGeom {
    /* 0x0000 */ Mtx mtxBuf[3][0x20];
    /* 0x1800 */ Vtx vtxBuf[3][0x80];
} struct_gameGeom; // size = 0x3000

// not sure about this struct
typedef struct struct_game_state_data_unk_0D4_unk_00 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ s32 unk_8;
} struct_game_state_data_unk_0D4_unk_00; // size = 0xC

typedef struct struct_game_state_data_unk_0D4 {
    /* 0x00 */ struct_game_state_data_unk_0D4_unk_00 unk_00[UNK_SIZE];
    /* 0x00 */ UNK_TYPE1 unk_0C[0x60];
} struct_game_state_data_unk_0D4; // size = 0x6C

typedef struct struct_game_state_data_unk_140 {
    /* 0x00 */ UNK_TYPE4 unk_00[UNK_SIZE];
    /* 0x04 */ UNK_TYPE1 unk_04[0x20];
} struct_game_state_data_unk_140; // size = 0x24

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
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ u32 unk_014; // TODO: enum?
    /* 0x018 */ s32 unk_018;
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
    /* 0x0D4 */ struct_game_state_data_unk_0D4 unk_0D4;
    /* 0x140 */ struct_game_state_data_unk_140 unk_140;
    /* 0x164 */ s32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ UNK_TYPE4 unk_170;
    /* 0x174 */ UNK_TYPE4 unk_174;
    /* 0x178 */ struct_game_state_data_unk_178 unk_178;
    /* 0x183 */ UNK_TYPE1 unk_183[1];
    /* 0x184 */ struct_game_state_data_unk_178 unk_184;
    /* 0x18F */ UNK_TYPE1 unk_18F[1];
    /* 0x190 */ struct_aiFlag unk_190;
    /* 0x1D0 */ u8 unk_1D0[AIROOT_LEN][2];
    /* 0x234 */ u8 unk_234;
    /* 0x235 */ u8 unk_235;
    /* 0x236 */ u8 unk_236;
    /* 0x237 */ u8 unk_237;
    /* 0x238 */ u8 unk_238;
    /* 0x239 */ s8 unk_239;
    /* 0x23A */ u8 unk_23A;
    /* 0x23A */ u8 unk_23B;
    /* 0x23C */ u8 unk_23C;
    /* 0x23D */ u8 unk_23D;
    /* 0x23E */ s8 unk_23E;
    /* 0x23F */ u8 unk_23F;
    /* 0x240 */ u8 unk_240;
    /* 0x241 */ u8 unk_241;
    /* 0x242 */ u8 unk_242[0x10];
    /* 0x252 */ UNK_TYPE1 unk_252[2];
    /* 0x254 */ UNK_TYPE1 unk_254[0x1C];
    /* 0x270 */ UNK_TYPE1 unk_270[2];
    /* 0x272 */ s16 unk_272[0x10];
    /* 0x292 */ u8 unk_292;
    /* 0x293 */ u8 unk_293;
    /* 0x294 */ u8 unk_294;
    /* 0x295 */ UNK_TYPE1 unk_295[0x3];
    /* 0x298 */ u8 unk_298;
    /* 0x299 */ UNK_TYPE1 unk_299[0x3];
    /* 0x29C */ u8 unk_29C[GAME_MAP_ROWS][GAME_MAP_COLUMNS][2];
    /* 0x34C */ UNK_TYPE1 unk_3AC[0x10];
    /* 0x3BC */ u8 unk_3BC;
    /* 0x3BD */ u8 unk_3BD;
    /* 0x3BE */ UNK_TYPE1 unk_3BE[0x2];
    /* 0x3C0 */ u8 unk_3C0;
    /* 0x3C1 */ u8 unk_3C1;
    /* 0x3C2 */ UNK_TYPE1 unk_3C2[0x2];
} struct_game_state_data; // size = 0x3C4

extern struct_gameGeom *gameGeom;

#endif
