#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B20E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B20EC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B20F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2104);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2108);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B210C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2114);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B211C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2120);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2134);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_game_main/03FD40", D_800B2138);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_80069990);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_80069ACC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_80069BCC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_80069E20);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A098);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A198);

#ifdef NON_MATCHING
void push_any_key_draw(s32 arg0, s32 arg1) {
    struct_800F3E50 *temp_s0 = watchGame;
    s32 alpha;
    s32 var_a1_2;
    struct_800F3E50_unk_430_unk_BC *temp_a2;
    struct_800F3E50_unk_430 *temp_a3;

    alpha = sins((temp_s0->unk_424 << 0xA) & 0xFC00) * 0.0077819824f + 127;
    alpha = CLAMP(alpha, 0, 255);

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, alpha);

    temp_a3 = temp_s0->unk_430;
    temp_a2 = temp_a3->unk_BC;
    var_a1_2 = *temp_a3->unk_C4;
    if (temp_a2->unk_0 < (u32)var_a1_2) {
        var_a1_2 = temp_a2->unk_0;
    }

    StretchAlphaTexTile(&gGfxHead, var_a1_2, temp_a2->unk_2, temp_a3->unk_B8->unk_4, temp_a2->unk_0, temp_a3->unk_C0->unk_4, *temp_a3->unk_C4, 0, 0, var_a1_2,
                        temp_a3->unk_BC->unk_2, arg0, arg1, var_a1_2, temp_a3->unk_BC->unk_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", push_any_key_draw);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A480);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A6E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A938);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006A978);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006AC60);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006AE04);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006AEFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_game_main/03FD40", func_8006B0A4);
