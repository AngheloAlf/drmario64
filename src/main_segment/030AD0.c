#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "buffers.h"

void func_8005A720(struct_800F3E5C *arg0) {
    s32 index = arg0->unk_111C0;

    if ((arg0->unk_111E0 > 0.0f) && (arg0->unk_111DC > 0.0f)) {
        func_8005A2EC(arg0);
        return;
    }

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            func_8004F358(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            func_80051A28(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            func_80052E48(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            func_800556E0(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
            func_800541CC(&arg0->unk_02678[index]);
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
            func_800560F0(&arg0->unk_02678[index]);
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
            func_800592D4(&arg0->unk_02678[index]);
            break;

        default:
            break;
    }
}

// Maybe menuAll_update
void func_8005A974(struct_800F3E5C *arg0) {
    enum_struct_800F3E5C_unk_111CC var_a0;
    f32 temp_f2_2;
    f32 var_f2;
    struct_800F3E5C_unk_024B8 *var_v1 = &arg0->unk_024B8;
    s32 var_s0;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - 0.5) * 1.2 + 0.5;
    if (temp_f2_2 < 0.0f) {
        var_f2 = 1.0f;
    } else if (temp_f2_2 > 1.0f) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 1.0 - temp_f2_2;
    }

    temp_f2_2 = var_f2;
    for (var_s0 = 0; var_s0 < ARRAY_COUNT(var_v1->unk_7C); var_s0++) {
        var_v1->unk_7C[var_s0] = temp_f2_2;
        var_v1->unk_6C[var_s0] = temp_f2_2;
    }

    func_800464F8(&arg0->unk_024B8, 1, 0);
    func_80047584(&arg0->unk_02548, &arg0->unk_024B8);

    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        if (var_s0 != 0) {
            var_v1_2 = arg0->unk_111C0;
        } else {
            var_v1_2 = arg0->unk_111C4;
        }
        if (var_v1_2 < 0) {
            continue;
        }

        if (var_s0 != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        switch (var_a0) {
            case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
                func_800508BC(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
                func_80051E94(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
                func_80053194(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
                func_80055C08(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
                func_800544C4(&arg0->unk_02678[var_v1_2]);
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
                func_80056824(&arg0->unk_02678[var_v1_2]);
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
                func_8005954C(&arg0->unk_02678[var_v1_2]);
                break;

            default:
                break;
        }
    }

    arg0->unk_111E4 = 0;
    arg0->unk_111EC++;
}

void menuAll_drawBg(struct_800F3E5C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    struct_800F3E5C_unk_024B8 *temp_s4 = &arg0->unk_024B8;
    s32 temp_s3;
    s32 i;
    s32 var_s2;

    func_80046844(temp_s4, &gfx);
    draw_menu_bg(&gfx, arg0->unk_024B8.unk_0C + 0.0f, -arg0->unk_024B8.unk_10 - 120.0f);

    gSPDisplayList(gfx++, RO_800ADC60);
    func_80046844(temp_s4, &gfx);

    var_s2 = 0;
    temp_s3 = func_80059D04(arg0, 2);
    for (i = 0; i < 5; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i << 6), 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
    }

    *gfxP = gfx;
}

void menuAll_draw(struct_800F3E5C *arg0, Gfx **gfxP) {
    u8 color;
    s32 i;

    arg0->unk_02448[gfx_gtask_no] = &arg0->unk_00048[gfx_gtask_no];
    arg0->unk_02454[gfx_gtask_no] = &arg0->unk_00C48[gfx_gtask_no];

    color = CLAMP((s32)((((arg0->unk_111DC - 0.5) * 1.2) + 0.5) * 255.0), 0, 255);

    gDPSetEnvColor(gGfxHead++, color, color, color, 255);

    menuAll_drawBg(arg0, gfxP);
    menuTitle_draw(&arg0->unk_02548, &gGfxHead);

    for (i = 0; i < 2; i++) {
        enum_struct_800F3E5C_unk_111CC var_a0;
        s32 index;

        if (i != 0) {
            index = arg0->unk_111C0;
        } else {
            index = arg0->unk_111C4;
        }
        if (index < 0) {
            continue;
        }

        if (i != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        gDPSetEnvColor(gGfxHead++, color, color, color, 255);

        switch (var_a0) {
            case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
                menuMain_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
                menuStory_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
                menuLvSel_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
                menuPlay2_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
                menuChSel_draw(&arg0->unk_02678[index], gfxP);
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
                menuNmEnt_draw(&arg0->unk_02678[index], gfxP);
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
                menuRank_draw(&arg0->unk_02678[index], gfxP);
                break;

            default:
                break;
        }
    }

    RecWritingMsg_draw(&arg0->recMessage, &gGfxHead);

    arg0->unk_111E8 = 0;
    arg0->unk_111F0++;
}

/**
 * Original name: main_menu
 */
enum_main_no main_menu(struct_800EB670 *arg0) {
    UNK_PTR sp10 = Heap_bufferp;
    struct_800F3E5C *ptr = ALIGN_PTR(Heap_bufferp);
    s32 i;
    u16 value;

    if (main_old == MAIN_NO_3) {
        D_8008E8B4 = 0;
        D_8008E788 = 0;
        B_800EB4F4 = 0;
        B_800EFCB0 = 0;
    }
    func_80040A64();
    sp10 = &ptr[1];
    bzero(ptr, sizeof(struct_800F3E5C));
    watchMenu = ptr;
    menuAll_init(ptr, &sp10, arg0);

    evs_playmax = joyResponseCheck();

    value = 0xF30;
    for (i = ARRAY_COUNT(joyflg) - 1; i >= 0; i--) {
        joyflg[i] = value;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[gfx_gtask_no];
    dm_seq_play(0xC);

    while ((ptr->unk_111D4 == MAIN_NO_6) || (ptr->unk_111DC < 1.0f)) {
        if (graphic_no == GRAPHIC_NO_0) {
            while ((pendingGFX != 0) || (func_80040BA4() != 0)) {
                func_80059CA0(ptr);
            }

            func_8005A434(ptr);
        }

        if (ptr->unk_111D8 > 0) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                B_800F48C4[i] = 0;
                gControllerPressedButtons[i] = 0;
                gControllerPrevHoldButtons[i] = 0;
                gControllerHoldButtons[i] = 0;
            }
        } else {
            joyProcCore();
        }
        func_80059CA0(ptr);
        func_8005A720(ptr);
        func_8005A974(ptr);
        dm_audio_update();

        if (ptr->unk_111CC != ptr->unk_111D0) {
            ptr->unk_111C8 = ptr->unk_111CC;
            ptr->unk_111CC = ptr->unk_111D0;
            ptr->unk_111C4 = ptr->unk_111C0;
            ptr->unk_111C0 ^= 1;
            graphic_no = GRAPHIC_NO_0;
        } else {
            graphic_no = GRAPHIC_NO_5;
        }
    }

    graphic_no = GRAPHIC_NO_5;

    while (ptr->unk_111F4 != 0xF) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    dm_seq_stop();

    while ((pendingGFX != 0) || !func_8002B178() || (func_80040BA4() != 0)) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8005A2AC(ptr);
    func_80040AE4();

    return ptr->unk_111D4;
}

void graphic_menu(void) {
    struct_800F3E5C *ptr = watchMenu;

    if ((ptr->unk_111D4 != MAIN_NO_6) && (ptr->unk_111DC == 1.0f)) {
        osSetThreadPri(NULL, 0xF);
        ptr->unk_111F4 = 0xF;
        return;
    }

    if (gGfxHead != gGfxGlist[gfx_gtask_no]) {
        gDPFullSync(gGfxHead++);
        gSPEndDisplayList(gGfxHead++);

        osWritebackDCacheAll();
        gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no],
                     (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
        gGfxHead = gGfxGlist[gfx_gtask_no];
    }

    osSetThreadPri(NULL, 0xF);
    F3RCPinitRtn();
    F3ClearFZRtn(0);
    menuAll_draw(ptr, &gGfxHead);
    osSetThreadPri(NULL, 0x7F);
}
