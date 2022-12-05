#include "audio/audio_stuff.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"
#include "audio/synthInternals.h"
#include "other_symbols.h"


extern s32 RO_800ACA20[24];

s32 func_8002AA80(void) {
    s32 ret = 0;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(RO_800ACA20); i++) {
        RomOffsetPair *pair = &D_8000E838[RO_800ACA20[i]];
        s32 segmentSize = pair->end - pair->start;

        ret = MAX(segmentSize, ret);
    }
    return ret;
}

void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 index) {
    arg0->unk_0 = 0;
    arg0->index = index;
    arg0->unk_8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AAE8);

bool func_8002AB28(struct_800FACE0_unk_08 *arg0) {
    if ((arg0->unk_0 == NULL) || (func_8002D7E0(arg0->index) != 0)) {
        return false;
    }

    func_8002D720(arg0->index, arg0->unk_0->unk_0);
    func_8002D840(arg0->index, arg0->unk_0->volume);
    func_8002D8A0(arg0->index, arg0->unk_0->unk_1 * 0.125);
    return true;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002ABC0);

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002AC64);

#ifdef NON_EQUIVALENT
// maybe equivalent, but too afraid to tell
/**
 * Changes the audio configuration to stereo or mono
 * 
 * Patches the following statements in `alEnvmixerPull`:
 * e->pan    = param->pan;
 * e->pan = (s16) e->ctrlList->data.i;
 */
void func_8002ACE0(bool setStereo) {
    u32 *funcPtr = (u32*)alEnvmixerPull + 0x10C/4;
    u32 var_v0;

    if (setStereo) {
        var_v0 = 0x8C82000C; // lw          $v0, 0xC($a0)
        *funcPtr = 0x92220012; // lbu         $v0, 0x12($s1)
        //D_8000346C.unk_0 = 0x92220012;
    } else {
        // Set mono via changing the instructions to set the pan to 0x40
        var_v0 = 0x24020040; // addiu       $v0, $zero, 0x40
        *funcPtr = 0x24020040; // addiu       $v0, $zero, 0x40
    }
    //D_8000346C.unk_1E0 = var_v0;
    funcPtr[0x1E0/4] = var_v0;
    osWritebackDCacheAll();
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002ACE0);
#endif

void func_8002AD38(struct_800EB670 *arg0) {
    s32 i;
    struct_800FACE0 *ptr = &B_800FACE0;
    UNK_TYPE val = -1;

    for (i = ARRAY_COUNT(ptr->unk_00)-1; i >= 0; i--) {
        ptr->unk_00[i] = val;
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        func_8002AAD8(&ptr->unk_08[i], i);
    }

    func_8002D170(arg0, &B_800B3640, 0x31000, D_8000E838[1].end - D_8000E838[1].start, func_8002AA80(), 2, D_8000E838[2].end - D_8000E838[2].start, 4, 50);

    func_8002D3B0(D_8000E838[1].start, D_8000E838[1].end - D_8000E838[1].start, (void*)D_8000E838[0].start);
    func_8002D6A4(D_8000E838[2].start, D_8000E838[2].end - D_8000E838[2].start);
}

void func_8002AE58(void) {
    struct_800FACE0 *var_s0 = &B_800FACE0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(var_s0->unk_00); i++) {
        if ((var_s0->unk_00[i] >= 0) && func_8002B194(i)) {
            RomOffsetPair *pair = &D_8000E838[RO_800ACA20[var_s0->unk_00[i]]];

            func_8002D428(i, pair->start, pair->end - pair->start);
            func_8002D4A4(i);
            func_8002D58C(i, 0x80);
            var_s0->unk_00[i] = -1;
        }
    }

    for (i = 0; i < ARRAY_COUNT(var_s0->unk_08); i++) {
        if (var_s0->unk_38[i] != NULL) {
            if (func_8002AB28(var_s0->unk_38[i]) != NULL) {
                var_s0->unk_38[i] = NULL;
            }
        } else {
            func_8002AC64(&var_s0->unk_08[i]);
        }
    }
}

void func_8002AF7C(void) {
    func_8002B0E4();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

bool func_8002AFA4(void) {
    return MusAsk(MUSFLAG_EFFECTS | MUSFLAG_SONGS) == 0;
}

void func_8002AFC4(s32 arg0) {
    func_8002AFE4(0, arg0);
}

void func_8002AFE4(s32 arg0, s32 arg1) {
    func_8002B028(arg0, arg1, 0);
}

void func_8002B000(s32 arg0, s32 arg1) {
    func_8002B028(0, arg0, arg1);
}

void func_8002B028(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == B_800FACE0.unk_00[arg0]) {
        return;
    }

    func_8002D554(arg0, arg2);
    B_800FACE0.unk_00[arg0] = arg1;
}

void func_8002B078(s32 arg0) {
    func_8002B098(0, arg0);
}

#ifdef NON_MATCHING
void func_8002B098(s32 arg0, s32 arg1) {
    if ((D_80088401 == 0) && (arg1 < 0xA) && (arg1 >= 0)) {
        func_8002B100(arg0);
    } else {
        func_8002AFE4(arg0, arg1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B098);
#endif

void func_8002B0E4(void) {
    func_8002B100(0);
}

void func_8002B100(s32 arg0) {
    func_8002D554(arg0, 0);
    B_800FACE0.unk_00[arg0] = -1;
}

s32 func_8002B13C(s32 arg0) {
    return func_8002B15C(0, arg0);
}

s32 func_8002B15C(s32 arg0, s32 arg1) {
    return func_8002D58C(arg0, arg1);
}

bool func_8002B178(void) {
    return func_8002B194(0);
}

bool func_8002B194(s32 arg0) {
    return func_8002D51C(arg0) == 0;
}

extern struct_800ACA80 D_800ACA80[];

void func_8002B1B4(s32 arg0) {
    s32 i;
    struct_800ACA80 *temp_a1 = &D_800ACA80[arg0];
    struct_800FACE0 *var_a3 = &B_800FACE0;

    for (i = 0; i < ARRAY_COUNT(var_a3->unk_08); i++) {
        if (var_a3->unk_38[i] == NULL) {
            continue;
        }

        if ((var_a3->unk_08[i].unk_0 != NULL) && (var_a3->unk_08[i].unk_0->unk_0 == temp_a1->unk_0)) {
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(var_a3->unk_08); i++) {
        if (var_a3->unk_38[i] != NULL) {
            continue;
        }

        if (var_a3->unk_08[i].unk_0 == NULL) {
            func_8002AAE8(&var_a3->unk_08[i], temp_a1);
            var_a3->unk_38[i] = &var_a3->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(var_a3->unk_08); i++) {
        if (var_a3->unk_38[i] != NULL) {
            continue;
        }

        if ((var_a3->unk_08[i].unk_0 != NULL) && (var_a3->unk_08[i].unk_0->unk_3 <= temp_a1->unk_3)) {
            func_8002AAE8(&var_a3->unk_08[i], temp_a1);
            var_a3->unk_38[i] = &var_a3->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(var_a3->unk_08); i++) {
        if (var_a3->unk_38[i] == NULL) {
            continue;
        }

        if ((var_a3->unk_08[i].unk_0 != NULL) && (var_a3->unk_08[i].unk_0->unk_3 < temp_a1->unk_3)) {
            func_8002AAE8(&var_a3->unk_08[i], temp_a1);
            return;
        }
    }
}

void func_8002B344(s32 arg0) {
    if (D_80088406 < 6) {
        func_8002B1B4(arg0);
    }
}

s32 func_8002B370(void) {
    return MusFxBankNumberOfEffects(func_8002D710());
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002B394);

void func_8002B490(struct_80205000 *arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    D_80088124 = 0;
    B_800FAD2C = 0;
}

void func_8002B4BC(struct_800EB670 *arg0) {
    s16 *sp10 = NULL;

    D_80088128 = 0;
    osCreateMesgQueue(&B_800F4898, B_800EBED0, ARRAY_COUNT(B_800EBED0));
    func_8002A184(arg0, &B_800F48B0, &B_800F4898);
    B_800FAF94 = func_8002A0D4(arg0);

    while (true) {
        osRecvMesg(&B_800F4898, (OSMesg*)&sp10, OS_MESG_BLOCK);

        switch (*sp10) {
            case 1:
                func_8002B5E4();
                break;

            case 2:
                func_8002B710();
                break;

            case 4:
                func_8002B728();
                break;

            case 3:
                func_8002B754();
                break;
        }
    }
}

void func_8002B5E4(void) {
    switch (D_80088124) {
        case 0:
            break;

        case 1:
            if (D_80088128 < 2) {
                func_8007AEF4();
            }
            break;

        case 2:
            if (D_80088128 < 2) {
                func_8007636C();
            }
            break;

        case 3:
            if (D_80088128 < 2) {
                func_80075CF8();
            }
            break;

        case 4:
            if (D_80088128 == 0) {
                func_8007023C();
            }
            break;

        case 5:
            if (D_80088128 < 2) {
                func_8005B658();
            }
            break;

        case 6:
            if (D_80088128 < 2) {
                func_80071CE0();
            }
            break;

        case 7:
            if (D_80088128 < 2) {
                func_800767DC();
            }
            break;
    }
}

void func_8002B710(void) {
    D_80088128 -= 1;
}

void func_8002B728(void) {
    if (D_80088124 == 4) {
        func_80071A44();
    }
}

void func_8002B754(void) {
    osViSetYScale(1.0f);
    D_80088128 += 2;
    osViBlack(true);
    func_80000468();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

void func_8002B7A8(struct_800EB670 *arg0) {
    osCreateThread(&B_800EBD20, 5, (StartThreadFunc)func_8002B4BC, arg0, STACK_TOP(B_800F1E30), 0xF);
    osStartThread(&B_800EBD20);
}

s16 func_8002B800(void) {
    s16 *sp10 = NULL;

    osRecvMesg(&B_800F4898, (OSMesg*) &sp10, OS_MESG_BLOCK);
    return *sp10;
}

void func_8002B834(OSScTask *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags) {
    scTask->list.t.type = M_GFXTASK;
    scTask->list.t.flags = OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    scTask->list.t.data_ptr = data_ptr;
    scTask->list.t.data_size = data_size;
    scTask->list.t.ucode_boot = (void*)rspbootTextStart;
    scTask->list.t.ucode_boot_size = (u8*)rspbootTextEnd - (u8*)rspbootTextStart;
    scTask->list.t.ucode = D_80088110[arg3][0];
    scTask->list.t.ucode_data = D_80088110[arg3][1];
    scTask->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    scTask->list.t.dram_stack = B_800FAFA0;
    scTask->list.t.dram_stack_size = sizeof(B_800FAFA0);
    scTask->list.t.output_buff = B_801136F0;
    scTask->list.t.output_buff_size = (u64*)&B_801236F0;
    scTask->list.t.yield_data_ptr = B_800F7490;
    scTask->list.t.yield_data_size = sizeof(B_800F7490);
    scTask->next = NULL;
    scTask->msgQ = &B_800F4898;
    scTask->flags = flags;
    if (flags & OS_SC_SWAPBUFFER) {
        scTask->msg = &B_800ED430;
        D_80088128++;
    } else {
        scTask->msg = &B_800E9BB6;
    }
    scTask->framebuffer = &gFramebuffers[D_80088120];
    osSendMesg(B_800FAF94, scTask, OS_MESG_BLOCK);
    if (flags & OS_SC_SWAPBUFFER) {
        D_80088120 ^= 1;
    }
    B_800FAD2C = (B_800FAD2C + 1) % 3;
}

void func_8002B9D8(void) {
    gSPSegment(B_800EBCF4++, 0x00, 0x00000000);
    gSPDisplayList(B_800EBCF4++, OS_K0_TO_PHYSICAL(D_80088328));
    gSPViewport(B_800EBCF4++, &D_80088130);

    if (D_80088140 == 1) {
        gSPDisplayList(B_800EBCF4++, OS_K0_TO_PHYSICAL(D_80088228));
        D_80088140 = 0;
    }

    gSPDisplayList(B_800EBCF4++, OS_K0_TO_PHYSICAL(D_80088308));
    gDPSetScissor(B_800EBCF4++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002BAB8);

void func_8002BBD8(u8 arg0) {
    gSPDisplayList(B_800EBCF4++, OS_K0_TO_PHYSICAL(D_80088150));
    if (arg0) {
        gDPSetScissor(B_800EBCF4++, G_SC_NON_INTERLACE, 0, 0, 319, 239);
    } else {
        gDPSetScissor(B_800EBCF4++, G_SC_NON_INTERLACE, 12, 8, 307, 231);
    }
}

void func_8002BC58(u8 arg0) {
    gDPSetColorImage(B_800EBCF4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gFramebuffers[D_80088120]));
    if (arg0) {
        gSPDisplayList(B_800EBCF4++, OS_K0_TO_PHYSICAL(D_800881B8));
        gDPFillRectangle(B_800EBCF4++, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
    }
}
