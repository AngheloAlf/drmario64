#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003A9A0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003ACB4);
#endif

void func_8003AD88(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    init_objMtx();
    gSPMatrix(gfx++, OS_K0_TO_PHYSICAL(&B_800E5818), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPSegment(gfx++, 0x05, osVirtualToPhysical(B_800E53CC));
    *gfxP = gfx;
}

UNK_TYPE func_8003AE08(Gfx **gfxP, s32 arg1, UNK_TYPE arg2) {
    Mtx mtx;
    Gfx *gfx = *gfxP;
    s32 var_a1;
    s32 var_a2;
    UNK_TYPE ret;

    gSPDisplayList(gfx++, D_8008D0E8);

    switch (B_800E53C0) {
        case 1:
            var_a1 = 0;
            var_a2 = 0;
            break;

        case 2:
            var_a1 = D_8008D0C0[arg1];
            var_a2 = 0;
            break;

        default:
            var_a1 = D_8008D0C8[arg1];
            var_a2 = 0;
            break;
    }

    makeTransrateMatrix(&mtx, var_a1 << 15, var_a2 << 15, 0xFE0C << 16);
    ret = lws_anim(&gfx, &mtx, B_800E53F4, arg2, B_800E53CC);

    *gfxP = gfx;
    return ret;
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003AEE4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003B054);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003B1C4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003B30C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003B454);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003B59C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003BA98);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003BEF8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003BFD8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C094);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C1A4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C2B4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C3C0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C600);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/010D50", func_8003C6F4);
#endif
