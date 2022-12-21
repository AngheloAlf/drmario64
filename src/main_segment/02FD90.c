#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/02FD90", D_800B1430);
INCLUDE_RODATA("asm/nonmatchings/main_segment/02FD90", D_800B1438);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_800599E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059AA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059AF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059B5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059BC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059C34);

void func_80059CA0(struct_800F3E5C *arg0) {
    osRecvMesg(&arg0->unk_0000C, NULL, OS_MESG_BLOCK);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CDC);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059CF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D04);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D14);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D24);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D34);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D44);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D54);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D64);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D74);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D84);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059D94);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059DF4);

u16 func_80059DFC(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return gControllerHoldButtons[B_800EBD16[arg1]];
}

u16 func_80059E1C(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return gControllerPressedButtons[B_800EBD16[arg1]];
}

u16 func_80059E3C(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return B_800F48C4[B_800EBD16[arg1]];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059E8C);

void func_80059E9C(struct_800F3E5C *arg0, enum_struct_800F3E5C_unk_111CC arg1) {
    func_80047420(&arg0->unk_02548, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/02FD90", func_80059EB8);

/**
 * Original name: menuAll_init
 */
void menuAll_init(struct_800F3E5C *arg0, UNK_PTR *arg1, struct_800EB670 *arg2) {
    UNK_PTR sp10 = *arg1;
    UNK_PTR temp_v0;
    s32 i;
    RomOffsetPair *pairArray = _romDataTbl;

    arg0->unk_00000 = arg2;
    arg0->unk_02460 = sp10;
    osCreateMesgQueue(&arg0->unk_0000C, arg0->unk_00024, ARRAY_COUNT(arg0->unk_00024));
    func_8002A184(arg2, &arg0->unk_00004, &arg0->unk_0000C);

    for (i = 0; i < ARRAY_COUNT(arg0->unk_00048); i++) {
        arg0->unk_02448[i] = &arg0->unk_00048[i];
        arg0->unk_02454[i] = &arg0->unk_00C48[i];
    }

    sp10 = init_menu_bg(sp10, evs_level_21 != 0);
    arg0->unk_02478 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CHAR].start, pairArray[ROMDATATBL_MENU_CHAR].end);
    arg0->unk_0247C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_COMMON].start, pairArray[ROMDATATBL_MENU_COMMON].end);
    arg0->unk_02484 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_LEVEL].start, pairArray[ROMDATATBL_MENU_LEVEL].end);
    arg0->unk_02488 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_MAIN].start, pairArray[ROMDATATBL_MENU_MAIN].end);
    arg0->unk_0248C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_NAME].start, pairArray[ROMDATATBL_MENU_NAME].end);
    arg0->unk_02490 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P2].start, pairArray[ROMDATATBL_MENU_P2].end);
    arg0->unk_02494 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P4].start, pairArray[ROMDATATBL_MENU_P4].end);
    arg0->unk_02498 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_RANK].start, pairArray[ROMDATATBL_MENU_RANK].end);
    arg0->unk_0249C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_SETUP].start, pairArray[ROMDATATBL_MENU_SETUP].end);
    arg0->unk_024A0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_STORY].start, pairArray[ROMDATATBL_MENU_STORY].end);
    arg0->unk_024A4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_AL].start, pairArray[ROMDATATBL_GAME_AL].end);
    arg0->unk_024A8 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_P1].start, pairArray[ROMDATATBL_GAME_P1].end);
    arg0->unk_024AC = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CONT].start, pairArray[ROMDATATBL_MENU_CONT].end);
    arg0->unk_024B0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_TUTORIAL_KASA].start, pairArray[ROMDATATBL_TUTORIAL_KASA].end);
    arg0->unk_024B4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_KASA].start, pairArray[ROMDATATBL_MENU_KASA].end);

    func_80046250(&arg0->unk_024B8, 0, 0);
    func_800474EC(&arg0->unk_02548, arg0, 0x70, 0x12);

    arg0->unk_111D0 = D_8008E8B4;
    arg0->unk_111CC = D_8008E8B4;
    arg0->unk_111C8 = D_8008E8B4;
    arg0->unk_111DC = 1.0f;
    arg0->unk_111C0 = 0;
    arg0->unk_111D8 = 0;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;
    arg0->unk_111C4 = -1;
    arg0->unk_111D4 = MAIN_NO_6;
    arg0->unk_111E4 = 1;
    arg0->unk_111E0 = -(1.0f / 30.0f);
    arg0->unk_111E8 = 1;
    arg0->unk_111F4 = 0x7F;

    RecWritingMsg_init(&arg0->recMessage, &sp10);
    arg0->unk_02464 = sizeof(struct_800F3E5C_unk_02470);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_02470); i++) {
        temp_v0 = ALIGN_PTR(sp10);
        arg0->unk_02468[i] = arg0->unk_02470[i] = temp_v0;
        sp10 = temp_v0 + arg0->unk_02464;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].unk_000 = 0;
        game_state_data[i].unk_004 = 0;
    }

    D_8008840E = 0;
    *arg1 = sp10;
}

void func_8005A2AC(struct_800F3E5C *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
    D_8008E8B4 = arg0->unk_111CC;
}

void func_8005A2EC(struct_800F3E5C *arg0) {
    s32 index = arg0->unk_111C0;

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            func_8004F2D8(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            func_80051974(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            func_80052DF0(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            func_800550F4(&arg0->unk_02678[index]);
            break;

        default:
            break;
    }
}

void func_8005A434(struct_800F3E5C *arg0) {
    s32 index = arg0->unk_111C0;

    arg0->unk_02470[index] = arg0->unk_02468[index];
    bzero(arg0->unk_02470[index], arg0->unk_02464);
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;

    if (arg0->unk_111CC != ENUM_STRUCT_800F3E5C_UNK_111CC_0) {
        func_80059E9C(arg0, arg0->unk_111CC);
    }

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            func_8004EEC8(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            func_80051540(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            func_80052A40(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            func_80054B60(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
            func_80053850(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_3:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_6:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_9:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_12:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_15:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_19:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_24:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_28:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_32:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_63:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_64:
            func_80055E40(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_49:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_50:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_51:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_52:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_53:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_54:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_56:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_57:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_58:
            func_8005911C(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        default:
            break;
    }
}
