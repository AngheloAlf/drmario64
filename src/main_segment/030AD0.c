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

INCLUDE_ASM("asm/nonmatchings/main_segment/030AD0", func_8005A974);

void func_8005AD30(struct_800F3E5C *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    UNK_TYPE *temp_s4 = &arg0->unk_024B8;
    s32 temp_s3;
    s32 i;
    s32 var_s2;

    func_80046844(temp_s4, &gfx);
    func_80077E2C(&gfx, arg0->unk_024C4 + 0.0f, -arg0->unk_024C8 - 120.0f);

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

void func_8005AEF4(struct_800F3E5C *arg0, Gfx **gfxP) {
    u8 color;
    s32 i;

    arg0->unk_02448[B_800FAD2C] = &arg0->unk_00048[B_800FAD2C];
    arg0->unk_02454[B_800FAD2C] = &arg0->unk_00C48[B_800FAD2C];

    color = CLAMP((s32)((((arg0->unk_111DC - 0.5) * 1.2) + 0.5) * 255.0), 0, 255);

    gDPSetEnvColor(gGfxHead++, color, color, color, 255);

    func_8005AD30(arg0, gfxP);
    func_800475A8(&arg0->unk_02548, &gGfxHead);

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
                func_800512AC(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
                func_800522CC(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
                func_8005348C(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
                func_80055CE0(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
                func_80054734(&arg0->unk_02678[index], gfxP);
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
                func_80056990(&arg0->unk_02678[index], gfxP);
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
                func_800596B4(&arg0->unk_02678[index], gfxP);
                break;

            default:
                break;
        }
    }

    func_80038CBC(&arg0->unk_111F8, &gGfxHead);

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
    B_800F3E5C = ptr;
    menuAll_init(ptr, &sp10, arg0);

    evs_playmax = joyResponseCheck();

    value = 0xF30;
    for (i = 3; i >= 0; i--) {
        B_800F6CD8[i] = value;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[B_800FAD2C];
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
    struct_800F3E5C *ptr = B_800F3E5C;

    if ((ptr->unk_111D4 != MAIN_NO_6) && (ptr->unk_111DC == 1.0f)) {
        osSetThreadPri(NULL, 0xF);
        ptr->unk_111F4 = 0xF;
        return;
    }

    if (gGfxHead != gGfxGlist[B_800FAD2C]) {
        gDPFullSync(gGfxHead++);
        gSPEndDisplayList(gGfxHead++);

        osWritebackDCacheAll();
        gfxTaskStart(&B_800FAE80[B_800FAD2C], gGfxGlist[B_800FAD2C], (gGfxHead - gGfxGlist[B_800FAD2C]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
        gGfxHead = gGfxGlist[B_800FAD2C];
    }

    osSetThreadPri(NULL, 0xF);
    F3RCPinitRtn();
    F3ClearFZRtn(0);
    func_8005AEF4(ptr, &gGfxHead);
    osSetThreadPri(NULL, 0x7F);
}
