#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "gamemap.h"
#include "aif.h"

#if VERSION_US
void func_8002EB00(struct_game_state_data *gameStateData) {
    gameStateData->unk_3BC = gameStateData->unk_178.unk_0;
    gameStateData->unk_3BD = gameStateData->unk_178.unk_2;
    gameStateData->unk_3C1[0] = (s8)gameStateData->unk_02F;
    gameStateData->unk_3C0 = gameStateData->unk_02D;
    gameStateData->unk_3BE[0] = (s8)(u8)gameStateData->unk_178.unk_6;
    gameStateData->unk_3BE[1] = (s8)(u8)gameStateData->unk_178.unk_7;
    gameStateData->unk_299[2] = (s8)gameStateData->unk_025;
    gameStateData->unk_299[1] = (s8)gameStateData->unk_026;
    gameStateData->unk_299[0] = gameStateData->unk_014 == 0x12;
    gameStateData->unk_298 = gameStateData->unk_04B;

    if (gameStateData->unk_298 == 0) {
        game_state_data[0].unk_04E = game_state_data[1].unk_04E;
    }
}
#endif

/**
 * Original name: aifMakeBlkWork
 */
#if VERSION_US
void aifMakeBlkWork(struct_game_state_data *gameStateData) {
    s32 column;
    s32 row;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        gameStateData->unk_29C[0][column][0] = 10;
        gameStateData->unk_29C[0][column][1] = 3;
    }

    for (row = 1; row < GAME_MAP_ROWS; row++) {
        for (column = 0; column < GAME_MAP_COLUMNS; column++) {
            s32 index = GAME_MAP_GET_INDEX(row - 1, column);

            if (game_map_data[gameStateData->unk_298].cells[index].unk_4[0] != 0) {
                gameStateData->unk_29C[row][column][0] =
                    capsGCnv_122[game_map_data[gameStateData->unk_298].cells[index].unk_2];
                gameStateData->unk_29C[row][column][1] =
                    capsCCnv_123[game_map_data[gameStateData->unk_298].cells[index].unk_3];
            } else {
                gameStateData->unk_29C[row][column][0] = 10;
                gameStateData->unk_29C[row][column][1] = 3;
            }
        }
    }

    if (gameStateData->unk_178.unk_2 != 0) {
        gameStateData->unk_29C[gameStateData->unk_178.unk_2 - 1][gameStateData->unk_178.unk_0][0] = 10;
        gameStateData->unk_29C[gameStateData->unk_178.unk_2 - 1][gameStateData->unk_178.unk_0][1] = 3;
        gameStateData->unk_29C[gameStateData->unk_178.unk_3 - 1][gameStateData->unk_178.unk_1][0] = 10;
        gameStateData->unk_29C[gameStateData->unk_178.unk_3 - 1][gameStateData->unk_178.unk_1][1] = 3;
    }
}
#endif

/**
 * Original name: aifMakeFlagSet
 */
#if VERSION_US
void aifMakeFlagSet(struct_game_state_data *arg0) {
    arg0->unk_23D = 0;
    arg0->unk_241 = 0;
    arg0->unk_237 = 0;
    arg0->unk_238 = 0;
    arg0->unk_239 = 0;
}
#endif

/**
 * Original name: aifGameInit
 */
#if VERSION_US
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
#endif

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

#if VERSION_US
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
#endif

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
#if 0

typedef struct struct_800EB4F8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ UNK_TYPE1 unk_06[2];
    /* 0x08 */ UNK_TYPE1 unk_08[0xC];
} struct_800EB4F8; // size = 0x14

extern struct_800EB4F8 aiRecurData[];
extern u8 B_800EB4F9[];
extern u8 B_800EB50A;
extern u8 B_800EB50B;
extern u8 B_800EB64C[][8][2];
extern u8 B_800EBD15;
extern u8 aiFieldData[][8][2];

void aifFieldCopy(struct_game_state_data *gameStateData) {
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_t0;
    s32 var_t1;
    s32 var_v1;
    s32 var_v1_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 *temp_a0;

    aiNext[0] = (u8) gameStateData->unk_3BE[0];
    aiNext[1] = (u8) gameStateData->unk_3BE[1];
    var_t0 = 0;
    var_t1 = 2;
    while (var_t0 < 8) {
        var_a3 = 0;
        var_a2 = var_t0;
        var_a1 = var_t1;

        while (var_a3 < 0x11) {
            temp_v0 = gameStateData->unk_29C[var_a3][var_t0][1];
            aiFieldData[var_a3][var_t0][0] = temp_v0;
            aiRecurData[var_a3].unk_00 = temp_v0;
            temp_v0_2 = gameStateData->unk_29C[var_a3][var_t0][0];
            aiFieldData[var_a3][var_t0][1] = temp_v0_2;
            B_800EB4F9[var_a1] = temp_v0_2;
            var_a2 += 0x10;
            var_a1 += 0x14;
            var_a3 += 1;
        }
        var_t0 += 1;
        var_t1 += 2;
    }

    var_v1 = 0;
    do {
        B_800EB64C[0][var_v1][0] = 0xFF;
        B_800EB64C[0][var_v1][1] = 0xFF;
        var_v1 += 1;
    } while (var_v1 < 0x14/2);
    var_a3_2 = 0;
    do {
        aiRecurData[var_a3_2].unk_00 = 0xFF;
        aiRecurData[var_a3_2].unk_01 = 0xFF;
        aiRecurData[var_a3_2].unk_02 = 0xFF;
        aiRecurData[var_a3_2].unk_03 = 0xFF;
        var_a3_2 += 1;
    } while (var_a3_2 < 0x12);
}
#else
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifFieldCopy);
#endif
#endif

#if VERSION_US
void func_80034310(void) {
    s32 column;

    for (column = 0; column < GAME_MAP_COLUMNS; column++) {
        s32 row;

        for (row = 0; row < GAME_MAP_ROWS; row++) {
            aiRecurData[row][column + 1].unk_0 = aiFieldData[row][column].unk_0;
            aiRecurData[row][column + 1].unk_1 = aiFieldData[row][column].unk_1;
        }
    }
}
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
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", RO_800ACF10);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/aiset", aifKeyMake);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/aiset", RO_800ACF20);
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

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80030A90_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80030B0C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80030D0C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80030D24_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", aifFirstInit);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80031014_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80031230_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800313D4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80031A54_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80031AF0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80032008_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800329A0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80032A84_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80033280_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800333BC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800334F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80033578_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800335E0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800336A4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80033700_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80034824_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800357CC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80036558_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80034310);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80036710_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80036BD4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80036EE4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800371B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800372E8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80037598_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_800376C8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_8003793C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80037BBC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80038190_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/aiset", func_80038778_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/aiset", RO_800C3FD8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/aiset", RO_800ACF20);
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
