#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002EB00);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifMakeBlkWork);
#endif

/**
 * Original name: aifMakeFlagSet
 */
void aifMakeFlagSet(struct_game_state_data *arg0) {
    arg0->unk_23D = 0;
    arg0->unk_241 = 0;
    arg0->unk_237 = 0;
    arg0->unk_238 = 0;
    arg0->unk_239 = 0;
}

/**
 * Original name: aifGameInit
 */
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

#if VERSION_US
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
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifFirstInit);
#endif
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002EFF0);
#endif

bool aifMake2(struct_game_state_data *gameStateData, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 temp_v1;

    if (gameStateData->unk_23D != 0) {
        return false;
    }

    func_8002EB00(gameStateData);
    aifMakeBlkWork(gameStateData);

    MissRate = 0;
    aiGoalX = gameStateData->unk_3BC + 1;

    aiGoalY = gameStateData->unk_3BD;
    if (aiGoalY == 0) {
        aiGoalY++;
    }

    aipn = gameStateData->unk_298;
    temp_v1 = gameStateData->unk_04E;
    gameStateData->unk_23C = temp_v1;

    if (FallSpeed[gameStateData->unk_3C0] > aiSlideFSpeed[aiSelSpeed][temp_v1]) {
        aiMoveSF = 1;
    } else {
        aiMoveSF = 0;
    }

    aifFieldCopy(gameStateData);
    aiFlag[1] = arg3 == 0;
    aiFlag[2] = arg1 + 1;
    aiFlag[3] = arg2;
    aiFlag[4] = arg4 != 0;

    aiFlagCnt = 1;
    decide = 0;
    aifReMoveCheck();
    aifKeyMake(gameStateData);
    gameStateData->unk_234 = 0;
    gameStateData->unk_23D = 1;

    return true;
}

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002F2EC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002F924);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002F9CC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8002FDF0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80030810);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_800308FC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_800310C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80031218);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003135C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_800313F0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003145C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003151C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003157C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_800325AC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80033474);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifFieldCopy);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034310);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034380);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034798);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034AB0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034D54);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80034E80);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_8003510C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifReMoveCheck);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", D_800ACF10);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifKeyMake);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", D_800ACF20);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifKeyOut);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_80035CF4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", func_800362A0);
#endif

/**
 * Original name: aiCOM_MissTake
 */
void aiCOM_MissTake(void) {
    PlayTime++;

    if (PlayTime > 18000) {
        MissRate = (PlayTime - 18000) / 720;
    } else {
        MissRate = 0;
    }
}
