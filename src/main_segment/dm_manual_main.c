/**
 * Original filename: dm_manual_main.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "audio/audio_stuff.h"

void func_80071EF0(struct_800F4890_unk_034 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->messageWnd.unk_28 = arg1 + 8;
    arg0->messageWnd.unk_2C = arg2 + 8;
}

void func_80071F0C(void) {
}

void func_80071F14(struct_800F4890_unk_034 *arg0, UNK_PTR *arg1) {
    arg0->unk_08 = 0;
    arg0->unk_0C = -0.0625f;
    msgWnd_init(&arg0->messageWnd, arg1, 0xD, 4, 0x20, 0x20);
    arg0->messageWnd.unk_30 = 0xA;
    arg0->messageWnd.unk_34 = 0xC;
    arg0->messageWnd.unk_3C = 5;
    arg0->messageWnd.unk_48 = 0xD;
    arg0->messageWnd.unk_54 = 0.16666667f;
    func_80071EF0(arg0, 0x20, 0x20);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80071FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", tutolWnd_draw);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2408);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B240C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2410);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2414);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2418);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B241C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2420);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2424);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2428);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B242C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2430);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2434);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2438);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B243C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2440);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2444);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2448);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B246C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2474);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B247C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B248C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B24C8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B24D4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B24FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B2538);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B2544);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B256C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", D_800B259C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B25B0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_800721A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_800721BC);

void func_800721D8(struct_800F4890_unk_034 *arg0) {
    if (arg0->unk_0C < 0.0f) {
        arg0->unk_0C = -arg0->unk_0C;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072204);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072230);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_8007224C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072268);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B25F0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2618);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2664);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B26B4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B26EC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2738);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2780);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B27D4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2808);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B284C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2894);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B28DC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2914);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2958);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2994);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B29E0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2A20);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2A54);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2A98);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2ADC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2B24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2B58);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2BA8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2BF4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2C44);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2C90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2CDC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D28);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2D90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2DD8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E58);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2E90);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2ED4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2F20);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2F60);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2FAC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B2FE4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B302C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B3054);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", STR_800B3078);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072280);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_800723EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072428);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_8007248C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80072968);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_1_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_2_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_3_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_4_main);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3130);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3134);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3140);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3144);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3150);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074954);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074B08);

INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3178);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B317C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B3180);
INCLUDE_RODATA("asm/nonmatchings/main_segment/dm_manual_main", RO_800B31A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074EF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", func_80074FE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_draw_fg);

const u16 map_x_table_1036[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};
const u8 _seqTbl_1037[] = { 2, 3 };
const u8 map_y_table_1038[] = { 0x2E, 0x2E };
const u8 size_table_1039[] = { 0xA, 8 };

void dm_manual_all_init(void) {
    struct_watchManual *temp_v0_2;
    s32 j;
    s32 i;
    s32 k;
    struct_game_state_data *var_a0_2;
    void **headTopPtr;

    evs_seqnumb = _seqTbl_1037[evs_manual_no % ARRAY_COUNTU(_seqTbl_1037)];
    evs_seqence = 1;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            evs_gamesel = ENUM_EVS_GAMESEL_0;
            evs_playcnt = 1;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            evs_gamesel = ENUM_EVS_GAMESEL_1;
            evs_playcnt = 2;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            evs_gamesel = ENUM_EVS_GAMESEL_2;
            evs_playcnt = 4;
            break;
    }

    evs_gamemode = ENUM_EVS_GAMEMODE_0;
    story_proc_no = STORY_PROC_NO_1;

    dm_game_init_heap();
    headTopPtr = dm_game_heap_top();
    watchManual = ALIGN_PTR(*headTopPtr);

    temp_v0_2 = watchManual;
    bzero(temp_v0_2, sizeof(struct_watchManual));

    *headTopPtr = &watchManual[1];

    _texAll = tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_TUTORIAL_KASA].start,
                            _romDataTbl[ROMDATATBL_TUTORIAL_KASA].end);
    _texKaSa =
        tiLoadTexData(headTopPtr, _romDataTbl[ROMDATATBL_MENU_KASA].start, _romDataTbl[ROMDATATBL_MENU_KASA].end);

    func_80071F14(&temp_v0_2->unk_034, headTopPtr);
    func_800721D8(&temp_v0_2->unk_034);

    dm_game_init_static();
    dm_game_init_snap_bg();
    dm_game_init(false);
    temp_v0_2->unk_00C = 0xFF;
    temp_v0_2->unk_010 = -8;
    temp_v0_2->unk_170 = 0;

    for (i = 0; i < ARRAY_COUNTU(temp_v0_2->unk_01C); i++) {
        temp_v0_2->unk_01C[i] = -0x14;
    }

    temp_v0_2->unk_02C = 0;
    temp_v0_2->unk_014 = 0;
    temp_v0_2->unk_018 = 0;
    temp_v0_2->unk_184 = 0;

    j = 0;
    for (i = 0; i < 3; i++) {
        temp_v0_2->unk_14C[i].unk_0 = 0;
        temp_v0_2->unk_14C[i].unk_4 = 0;
        temp_v0_2->unk_0C4[i].unk_8 = j;
        temp_v0_2->unk_0C4[i].unk_0 = (sinf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * 20) + 45;
        temp_v0_2->unk_0C4[i].unk_4 = (cosf(temp_v0_2->unk_0C4[i].unk_8 * 3.141592654 / 180) * -20) + 155;

        j += 120;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            k = 0;
            j = 0;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            k = 0;
            j = 1;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            k = 1;
            j = 2;
            break;
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        var_a0_2[i].unk_008 = map_y_table_1038[k];
        var_a0_2[i].unk_00A = size_table_1039[k];
        var_a0_2[i].unk_006 = map_x_table_1036[j][i];
    }

    var_a0_2 = game_state_data;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        s8 *gamespeed_ptr = GameSpeed;
        struct_800F4890_unk_0E8 *temp;

        var_a0_2[i].unk_02C = 1;
        var_a0_2[i].unk_02D = gamespeed_ptr[1];
        var_a0_2[i].unk_04D = 0;
        var_a0_2[i].unk_04E = 2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_2:
            case EVS_MANUAL_NO_5:
                var_a0_2[i].unk_02B = 0xC;
                var_a0_2[i].unk_02A = 0;
                break;

            default:
                var_a0_2[i].unk_02B = 8;
                var_a0_2[i].unk_02A = 2;
                break;
        }

        temp_v0_2->unk_174[i] = 0;

        temp = temp_v0_2->unk_0E8[i];
        for (j = 0; j < ARRAY_COUNTU(temp_v0_2->unk_0E8[i]); j++) {
            struct_800F4890_unk_0E8 *temp2 = &temp[j];

            temp2->unk_0 = 0;
            temp2->unk_1 = 0;
            temp2->unk_2 = 0;

            for (k = 0; k < ARRAY_COUNTU(temp2->unk_3); k++) {
                temp2->unk_3[k] = 0;
            }
        }
    }

    temp_v0_2->unk_164 = 0;
    temp_v0_2->unk_168 = 0;
    temp_v0_2->unk_16C = 0;
    temp_v0_2->unk_030 = 0;
}

#ifdef NON_MATCHING
/**
 * Original name: dm_manual_main
 */
enum_main_no dm_manual_main(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    OSMesg sp28[8];
    struct_800FAF98_unk_64 sp48;
    enum_main_no var_v0;
    s32 i;
    s32 var_s3 = 1;
    s32 var_s4 = 0;
    struct_watchManual *temp_s2;

    osCreateMesgQueue(&sp10, sp28, ARRAY_COUNT(sp28));
    func_8002A184(arg0, &sp48, &sp10);
    dm_manual_all_init();

    temp_s2 = watchManual;
    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (var_s4 == 0) {
        joyProcCore();
        osRecvMesg(&sp10, NULL, 1);
        func_80071FA0(&temp_s2->unk_034);
        dm_effect_make();

        temp_s2->unk_184++;
        if (temp_s2->unk_010 > 0) {
            var_s4 = temp_s2->unk_00C == 0xFF;
        }

        temp_s2->unk_00C = CLAMP(temp_s2->unk_00C + temp_s2->unk_010, 0, 0xFF);
        switch (evs_manual_no) {
            case EVS_MANUAL_NO_0:
                var_s3 = dm_manual_1_main();
                break;

            case EVS_MANUAL_NO_1:
                var_s3 = dm_manual_2_main();
                break;

            case EVS_MANUAL_NO_2:
                var_s3 = dm_manual_3_main();
                break;

            case EVS_MANUAL_NO_3:
                var_s3 = dm_manual_4_main();
                break;
        }
        dm_seq_set_volume(0x60);
        dm_audio_update();
        if (temp_s2->unk_018 != 0) {
            temp_s2->unk_014++;
            if (temp_s2->unk_014 >= temp_s2->unk_018) {
                temp_s2->unk_014 = 0;
                temp_s2->unk_018 = 0;
                dm_seq_play_in_game(evs_seqnumb * 2);
            }
        }
        if (temp_s2->unk_00C == 0) {
            s32 temp = ((-(main_old == MAIN_NO_3) & 0xFF3F) | 0x4000);

            var_s3 &= -((gControllerPressedButtons[main_joy[0]] & temp) == 0);
        }

        if (var_s3 == 0) {
            if (temp_s2->unk_010 < 0) {
                temp_s2->unk_010 = -temp_s2->unk_010;
            }
        }
        graphic_no = GRAPHIC_NO_3;
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp10, NULL, 1);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp48);

    var_v0 = MAIN_NO_3;
    if (main_old != MAIN_NO_3) {
        var_v0 = MAIN_NO_6;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_manual_main", dm_manual_main);
#endif

void dm_manual_graphic(void) {
    UNK_TYPE sp28;
    UNK_TYPE sp2C;
    OSScTask *ptr;
    s32 color;
    s32 alpha;
    struct_watchManual *temp_s1 = watchManual;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = &B_800FAE80[gfx_gtask_no];

    sp28 = dm_get_mtx_buf();
    sp2C = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    dm_game_draw_snap_bg(&gGfxHead, &sp28, &sp2C, 0);
    dm_manual_draw_fg(&sp28, &sp2C);

    color = 255;
    alpha = CLAMP((temp_s1->unk_00C - 127) * 1.2 + 127, 0, 255);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(ptr, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}
