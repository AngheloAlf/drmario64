#ifndef ASSETS_ETC_H
#define ASSETS_ETC_H

#include "ultra64.h"

#include "graphbin.h"

#define ETC_ATTACK_SPRITES_WIDTH (32)
#define ETC_ATTACK_SPRITES_HEIGHT (32)


DECLARE_VARIABLE_GRAPHBIN_u16(etc_00, 64, 34);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_01, 64, 34);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_02, 64, 50);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_03, 64, 19);
DECLARE_VARIABLE_GRAPHBIN_u16(etc_04, 64, 34);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_05, 64, 34);
DECLARE_VARIABLE_GRAPHBIN_u16(etc_06, 64, 50);
DECLARE_VARIABLE_GRAPHBIN_u16(etc_07, 64, 50);
DECLARE_VARIABLE_GRAPHBIN_u16(etc_08, 64, 34);
DECLARE_VARIABLE_GRAPHBIN_u16(etc_09, 64, 50);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_10, 32, 32);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_11, 32, 32);
DECLARE_VARIABLE_GRAPHBIN_u4 (etc_12, 48, 15);
extern u8 game_etc_lws[];
extern u8 etc_attack_sprites[2][10][ETC_ATTACK_SPRITES_WIDTH*ETC_ATTACK_SPRITES_HEIGHT/2];

#endif
