#ifndef ASSETS_ETC_H
#define ASSETS_ETC_H

#include "ultra64.h"

#include "graphbin.h"

#define ETC_ATTACK_SPRITES_WIDTH (32)
#define ETC_ATTACK_SPRITES_HEIGHT (32)


extern GraphBin_u16_64_34 etc_00;
extern GraphBin_u4_64_34 etc_01;
extern GraphBin_u4_64_50 etc_02;
extern GraphBin_u4_64_19 etc_03;
extern GraphBin_u16_64_34 etc_04;
extern GraphBin_u4_64_34 etc_05;
extern GraphBin_u16_64_50 etc_06;
extern GraphBin_u16_64_50 etc_07;
extern GraphBin_u16_64_34 etc_08;
extern GraphBin_u16_64_50 etc_09;
extern GraphBin_u4_32_32 etc_10;
extern GraphBin_u4_32_32 etc_11;
extern GraphBin_u4_48_15 etc_12;
extern u8 game_etc_lws[];
extern u8 etc_attack_sprites[2][10][ETC_ATTACK_SPRITES_WIDTH*ETC_ATTACK_SPRITES_HEIGHT/2];

#endif
