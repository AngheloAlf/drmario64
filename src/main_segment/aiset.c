#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002EB00);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002EB74);

/**
 * aifMakeFlagSet
 */
void aifMakeFlagSet(struct_80123700 *arg0) {
    arg0->unk_23D = 0;
    arg0->unk_241 = 0;
    arg0->unk_237 = 0;
    arg0->unk_238 = 0;
    arg0->unk_239 = 0;
}

void aifGameInit(void) {
    s32 i;

    fool_mode = 0;
    s_hard_mode = 0;
    MissRate = 0;
    PlayTime = 0;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s32 j;

        game_state_data[i].unk_23D = 1;
        game_state_data[i].unk_23E = 1;
        game_state_data[i].unk_292 = 0;
        game_state_data[i].unk_294 = 0x64;

        for (j = 0; j < 0x10; j++) {
            game_state_data[i].unk_242[j] = 0;
            game_state_data[i].unk_272[j] = 0;
        }
    }
}

#if 0
typedef struct struct_800F48D0 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x1C0];
} struct_800F48D0; // size = 0x1C0

typedef struct struct_80088660 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x1C0];
} struct_80088660; // size = 0x1C0

typedef struct struct_800890E0_unk_00 {
    /* 0x00 */ UNK_TYPE4 unk_00;
    /* 0x00 */ UNK_TYPE4 unk_04;
    /* 0x00 */ UNK_TYPE4 unk_08;
    /* 0x00 */ UNK_TYPE4 unk_0C;
} struct_800890E0_unk_00; // size = 0x10

typedef struct struct_800E9BC0 {
    /* 0x00 */ struct_800890E0_unk_00 unk_00[6];
    /* 0x60 */ UNK_TYPE1 unk_00[0xC];
} struct_800E9BC0; // size = 0x6C

typedef struct struct_800890E0 {
    /* 0x00 */ struct_800890E0_unk_00 unk_00[6];
    /* 0x60 */ UNK_TYPE1 unk_00[0xC];
} struct_800890E0; // size = 0x6C

//s32 func_8002ED2C(?, s32, ? *, ? *);                /* extern */
extern struct_800E9BC0 B_800E9BC0[];
extern struct_800F48D0 B_800F48D0[];
extern struct_80088660 D_80088660[];
extern struct_800890E0 D_800890E0[];

void aifFirstInit(void) {
    struct_800890E0_unk_00 *var_a2;
    struct_800890E0_unk_00 *var_a3;
    struct_800890E0 *var_t0;
    struct_800F48D0 *var_t1;
    struct_80088660 *var_t2;
    struct_800E9BC0 *var_t2_2;
    ? temp_a0;
    s32 var_a1;
    s32 var_t3;
    s32 var_t5;
    s32 var_t5_2;
    s32 var_t6;
    void *temp_t0;
    void *var_a2_2;
    void *var_a3_2;

    var_t5 = 0;
    var_t6 = 0;
    do {
        var_t3 = 0;
        var_t2 = &D_80088660;
        var_t1 = &B_800F48D0;
loop_2:
        var_a3_2 = var_t6 + var_t1;
        var_a2_2 = var_t6 + var_t2;
        temp_t0 = var_a2_2 + 0x30;
        if (((s32) var_a2_2 | (s32) var_a3_2) & 3) {
            do {
                var_a3_2->unk_0 = (unaligned s32) var_a2_2->unk_0;
                var_a3_2->unk_4 = (unaligned s32) var_a2_2->unk_4;
                var_a3_2->unk_8 = (unaligned s32) var_a2_2->unk_8;
                var_a3_2->unk_C = (unaligned s32) var_a2_2->unk_C;
                var_a2_2 += 0x10;
                var_a3_2 += 0x10;
            } while (var_a2_2 != temp_t0);
        } else {
            do {
                var_a3_2->unk_0 = (s32) var_a2_2->unk_0;
                var_a3_2->unk_4 = (s32) var_a2_2->unk_4;
                var_a3_2->unk_8 = (s32) var_a2_2->unk_8;
                var_a3_2->unk_C = (s32) var_a2_2->unk_C;
                var_a2_2 += 0x10;
                var_a3_2 += 0x10;
            } while (var_a2_2 != temp_t0);
        }
        var_a3_2->unk_0 = (unaligned s32) var_a2_2->unk_0;
        var_a3_2->unk_4 = (unaligned s32) var_a2_2->unk_4;
        var_t2 += 0x1C0;
        var_t3 += 1;
        var_t1 += 0x1C0;
        if (var_t3 < 6) {
            goto loop_2;
        }
        var_t5 += 1;
        var_t6 += 0x38;
    } while (var_t5 < 8);

    var_t5_2 = 0;
    var_t0 = &D_800890E0;
    var_t2_2 = &B_800E9BC0;
    do {
        var_a3 = var_t2_2;
        var_a2 = var_t0;
        if (((s32) var_t0 | (s32) var_t2_2) & 3) {
            do {
                //var_a1 = (unaligned s32) var_a2->unk_C;
                //var_a3->unk_0 = (unaligned s32) var_a2->unk_0;
                //var_a3->unk_4 = (unaligned s32) var_a2->unk_4;
                //var_a3->unk_8 = (unaligned s32) var_a2->unk_8;
                var_a1 = var_a2->unk_0C;
                var_a3->unk_00 = var_a2->unk_00;
                var_a3->unk_04 = var_a2->unk_04;
                var_a3->unk_08 = var_a2->unk_08;
                var_a3->unk_0C = var_a1;
                var_a2 += 0x10;
                var_a3 += 0x10;
            } while (var_a2 != (var_t0 + 0x60));
        } else {
            do {
                var_a1 = var_a2->unk_0C;
                var_a3->unk_00 = (s32) var_a2->unk_00;
                var_a3->unk_04 = (s32) var_a2->unk_04;
                var_a3->unk_08 = (s32) var_a2->unk_08;
                var_a3->unk_0C = var_a1;
                var_a2 += 0x10;
                var_a3 += 0x10;
            } while (var_a2 != (var_t0 + 0x60));
        }
        temp_a0 = (unaligned s32) var_a2->unk_8;
        var_a3->unk_0 = (unaligned s32) var_a2->unk_0;
        var_a3->unk_4 = (unaligned s32) var_a2->unk_4;
        var_a3->unk_8 = temp_a0;
        var_t0 += 0x6C;
        var_t5_2 += 1;
        var_t2_2 += 0x6C;
    } while (var_t5_2 < 0x10);
    return aifGameInit(temp_a0, var_a1, var_a2, var_a3);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", aifFirstInit);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002EFF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002F180);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002F2EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002F924);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002F9CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8002FDF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80030810);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_800308FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_800310C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80031218);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8003135C);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_800313F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8003145C);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8003151C);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8003157C);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_800325AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80033474);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034200);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034310);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034380);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034798);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034AB0);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034D54);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80034E80);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_8003510C);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80035234);

INCLUDE_RODATA("asm/nonmatchings/main_segment/aiset", D_800ACF10);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80035494);

INCLUDE_RODATA("asm/nonmatchings/main_segment/aiset", D_800ACF20);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80035704);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_80035CF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", func_800362A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/aiset", aiCOM_MissTake);
