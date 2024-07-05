#include "assets/game_etc/etc.h"

GraphBin_u16_64_34 etc_00 = {
    {
        "GraphBin",
        64,
        34,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_00_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_00_tex.rgba16.inc"
    },
};

GraphBin_u4_64_34 etc_01 = {
    {
        "GraphBin",
        64,
        34,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_01.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_01.ci4.inc"
    },
};

GraphBin_u4_64_50 etc_02 = {
    {
        "GraphBin",
        64,
        50,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_02.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_02.ci4.inc"
    },
};

GraphBin_u4_64_19 etc_03 = {
    {
        "GraphBin",
        64,
        19,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_03.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_03.ci4.inc"
    },
};

GraphBin_u16_64_34 etc_04 = {
    {
        "GraphBin",
        64,
        34,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_04_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_04_tex.rgba16.inc"
    },
};

GraphBin_u4_64_34 etc_05 = {
    {
        "GraphBin",
        64,
        34,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_05.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_05.ci4.inc"
    },
};

GraphBin_u16_64_50 etc_06 = {
    {
        "GraphBin",
        64,
        50,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_06_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_06_tex.rgba16.inc"
    },
};

GraphBin_u16_64_50 etc_07 = {
    {
        "GraphBin",
        64,
        50,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_07_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_07_tex.rgba16.inc"
    },
};

GraphBin_u16_64_34 etc_08 = {
    {
        "GraphBin",
        64,
        34,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_08_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_08_tex.rgba16.inc"
    },
};

GraphBin_u16_64_50 etc_09 = {
    {
        "GraphBin",
        64,
        50,
        1,
        16,
        {
#include "assets/game_etc/graphbin/etc_09_tlut.rgba16.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_09_tex.rgba16.inc"
    },
};

GraphBin_u4_32_32 etc_10 = {
    {
        "GraphBin",
        32,
        32,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_10.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_10.ci4.inc"
    },
};

GraphBin_u4_32_32 etc_11 = {
    {
        "GraphBin",
        32,
        32,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_11.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_11.ci4.inc"
    },
};

GraphBin_u4_48_15 etc_12 = {
    {
        "GraphBin",
        48,
        15,
        1,
        4,
        {
#include "assets/game_etc/graphbin/etc_12.palette.inc"
        },
    },
    {
#include "assets/game_etc/graphbin/etc_12.ci4.inc"
    },
};

u8 game_etc_lws[] = {
#include "src/assets/game_etc/etc_lws.subseg.inc"
};

u8 etc_attack_sprites[2][10][ETC_ATTACK_SPRITES_WIDTH * ETC_ATTACK_SPRITES_HEIGHT / 2] = {
    {
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_0.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_1.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_2.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_3.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_4.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_5.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_6.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_7.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_8.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_0_9.i4.inc"
        },
    },
    {
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_0.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_1.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_2.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_3.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_4.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_5.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_6.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_7.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_8.i4.inc"
        },
        {
#include "assets/game_etc/attack_sprites/attack_sprite_1_9.i4.inc"
        },
    },
};
