/**
 * Original filename: game_etc.c
 */

#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", initEtcWork);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", initEtcWork);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003ACB4);
#endif

#if VERSION_US
void disp_logo_setup(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    init_objMtx();
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&etc_viewMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(etcLwsAddress));
    *gfxP = gfx;
}
#endif

#if VERSION_US
UNK_TYPE disp_count_logo(Gfx **gfxP, s32 arg1, UNK_TYPE arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 var_a1;
    s32 var_a2;
    UNK_TYPE ret;

    gSPDisplayList(gfx++, etc_setup);

    switch (binCount) {
        case 1:
            var_a1 = 0;
            var_a2 = 0;
            break;

        case 2:
            var_a1 = x2p[arg1];
            var_a2 = 0;
            break;

        default:
            var_a1 = x4p[arg1];
            var_a2 = 0;
            break;
    }

    makeTransrateMatrix(&mtx, var_a1 << 15, var_a2 << 15, 0xFE0C << 16);
    ret = lws_anim(&gfx, &mtx, etcLwsTbl.unk_24, arg2, etcLwsAddress);

    *gfxP = gfx;
    return ret;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003AEE4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B054);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B1C4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B30C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B454);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003B59C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BA98);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BEF8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003BFD8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C094);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C1A4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C2B4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", disp_timestop_logo);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C600);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/game_etc", func_8003C6F4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DC5C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DD28_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DDCC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003DEC4_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E06C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E214_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E370_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E4CC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003E628_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003EB68_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F038_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F120_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F1DC_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F30C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F43C_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F568_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F820_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/game_etc", func_8003F90C_cn);
#endif
