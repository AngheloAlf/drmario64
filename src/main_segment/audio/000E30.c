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
#include "buffers.h"

const u8 RO_800ACA10[] = {
    0x5B, 0x51, 0x23, 0x28, 0x2D, 0x0F, 0x19, 0x14, 0x00, 0x05, 0x0A, 0x1E, 0x32, 0x56, 0x60,
};

const s32 RO_800ACA20[] = {
    0x04, 0x09, 0x03, 0x08, 0x05, 0x0A, 0x06, 0x0B, 0x07, 0x0C, 0x0D, 0x0E, 0x0F, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x10, 0x1A,
};

const struct_800ACA80 D_800ACA80[] = {
    { 0x00, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x01, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x02, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x03, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x04, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x05, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x06, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x07, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x08, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x09, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x0A, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x0B, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x0C, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x0D, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x0E, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x0F, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x10, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x11, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x12, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x13, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x14, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x15, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x16, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x17, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x18, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x19, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x1A, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x1B, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x1C, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x1D, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x1E, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x1F, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x20, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x21, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x22, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x23, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x24, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x25, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x26, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x27, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x28, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x29, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x2A, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x2B, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x2C, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x2D, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x2E, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x2F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x30, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x31, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x32, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x33, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x34, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x35, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x36, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x37, 0xF4, 0x00, 0x0A, 0x00, 0x74 }, { 0x38, 0x00, 0x00, 0x0A, 0x00, 0x74 },
    { 0x39, 0xFA, 0xD3, 0x0A, 0x00, 0x74 }, { 0x3A, 0xF4, 0x00, 0x0A, 0x00, 0x78 }, { 0x3B, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    { 0x3C, 0x00, 0x00, 0x0A, 0x00, 0x78 }, { 0x3D, 0xF4, 0x00, 0x0A, 0x00, 0x74 }, { 0x3E, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    { 0x3F, 0xFA, 0xD3, 0x0A, 0x00, 0x78 }, { 0x40, 0xFA, 0xD3, 0x0A, 0x00, 0x78 }, { 0x41, 0xF4, 0x00, 0x0A, 0x00, 0x6A },
    { 0x42, 0xF4, 0x00, 0x0A, 0x00, 0x74 }, { 0x43, 0xFA, 0xD3, 0x0A, 0x00, 0x60 }, { 0x44, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    { 0x45, 0x05, 0x37, 0x0A, 0x00, 0x78 }, { 0x46, 0xF4, 0x00, 0x0A, 0x00, 0x78 }, { 0x47, 0xF4, 0x00, 0x0A, 0x00, 0x78 },
    { 0x48, 0xFA, 0xD3, 0x0A, 0x00, 0x78 }, { 0x49, 0xFA, 0xD3, 0x0A, 0x00, 0x78 }, { 0x4A, 0x00, 0x00, 0x0A, 0x14, 0x74 },
    { 0x4B, 0xFA, 0xD3, 0x28, 0x00, 0x78 }, { 0x4C, 0xFA, 0xD3, 0x28, 0x00, 0x78 }, { 0x4D, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    { 0x4E, 0xFA, 0xD3, 0x28, 0x00, 0x74 }, { 0x4F, 0xFA, 0xD3, 0x28, 0x00, 0x78 }, { 0x50, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    { 0x51, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x52, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x53, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x54, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x55, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x56, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x57, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x58, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x59, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x5A, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x5B, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x5C, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    { 0x5D, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x5E, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x5F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x60, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x61, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x62, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    { 0x63, 0xF4, 0x00, 0x28, 0x00, 0x6C }, { 0x64, 0xFA, 0xD3, 0x28, 0x00, 0x6C }, { 0x65, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    { 0x66, 0x00, 0x00, 0x0A, 0x00, 0x78 }, { 0x67, 0x00, 0x00, 0x0A, 0x00, 0x78 },
};

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

void func_8002AAE8(struct_800FACE0_unk_08 *arg0, const struct_800ACA80 *arg1) {
    func_8002D810(arg0->index, 0);
    arg0->unk_0 = arg1;
    arg0->unk_8 = 0;
}

bool func_8002AB28(struct_800FACE0_unk_08 *arg0) {
    if ((arg0->unk_0 == NULL) || (func_8002D7E0(arg0->index) != 0)) {
        return false;
    }

    func_8002D720(arg0->index, arg0->unk_0->number);
    func_8002D840(arg0->index, arg0->unk_0->volume);
    func_8002D8A0(arg0->index, arg0->unk_0->offset * 0.125);
    return true;
}

bool func_8002ABC0(struct_800FACE0_unk_08 *arg0) {
    if ((arg0->unk_0 == NULL) || (func_8002D7E0(arg0->index) != 0)) {
        return false;
    }

    func_8002D768(arg0->index, arg0->unk_0->number, arg0->unk_0->volume, 0x80, true, arg0->unk_0->priority);
    func_8002D8A0(arg0->index, arg0->unk_0->offset * 0.125);
    return true;
}

void func_8002AC64(struct_800FACE0_unk_08 *arg0) {
    if (arg0->unk_0 == NULL) {
        return;
    }

    if (func_8002D7E0(arg0->index) != 0) {
        if (arg0->unk_0->unk_4 != 0) {
            if (arg0->unk_8 < (arg0->unk_0->unk_4 * 6)) {
                arg0->unk_8++;
            } else {
                func_8002D810(arg0->index, 0);
                arg0->unk_0 = NULL;
            }
        }
    } else {
        arg0->unk_0 = NULL;
    }
}

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
    u32 *funcPtr = (u32 *)alEnvmixerPull + 0x10C / 4;
    u32 var_v0;

    if (setStereo) {
        var_v0 = 0x8C82000C;   // lw          $v0, 0xC($a0)
        *funcPtr = 0x92220012; // lbu         $v0, 0x12($s1)
        // D_8000346C.unk_0 = 0x92220012;
    } else {
        // Set mono via changing the instructions to set the pan to 0x40
        var_v0 = 0x24020040;   // addiu       $v0, $zero, 0x40
        *funcPtr = 0x24020040; // addiu       $v0, $zero, 0x40
    }
    // D_8000346C.unk_1E0 = var_v0;
    funcPtr[0x1E0 / 4] = var_v0;
    osWritebackDCacheAll();
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/audio/000E30", func_8002ACE0);
#endif

void func_8002AD38(struct_800EB670 *arg0) {
    s32 i;
    struct_800FACE0 *ptr = &B_800FACE0;
    UNK_TYPE val = -1;

    for (i = ARRAY_COUNT(ptr->unk_00) - 1; i >= 0; i--) {
        ptr->unk_00[i] = val;
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        func_8002AAD8(&ptr->unk_08[i], i);
    }

    func_8002D170(arg0, &B_800B3640, 0x31000, D_8000E838[1].end - D_8000E838[1].start, func_8002AA80(), 2, D_8000E838[2].end - D_8000E838[2].start, 4, 50);

    func_8002D3B0(D_8000E838[1].start, D_8000E838[1].end - D_8000E838[1].start, (void *)D_8000E838[0].start);
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

void func_8002B098(s32 arg0, s32 arg1) {
    if (D_80088401 == 0) {
        if (arg1 < 10) {
            if (arg1 >= 0) {
                func_8002B100(arg0);
                return;
            }
        }
    }
    func_8002AFE4(arg0, arg1);
}

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

/**
 * Original name: dm_snd_play
 */
void dm_snd_play(s32 arg0) {
    s32 i;
    const struct_800ACA80 *temp_a1 = &D_800ACA80[arg0];
    struct_800FACE0 *ptr = &B_800FACE0;

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] == NULL) {
            continue;
        }

        if ((ptr->unk_08[i].unk_0 != NULL) && (ptr->unk_08[i].unk_0->number == temp_a1->number)) {
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] != NULL) {
            continue;
        }

        if (ptr->unk_08[i].unk_0 == NULL) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            ptr->unk_38[i] = &ptr->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] != NULL) {
            continue;
        }

        if ((ptr->unk_08[i].unk_0 != NULL) && (ptr->unk_08[i].unk_0->priority <= temp_a1->priority)) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            ptr->unk_38[i] = &ptr->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] == NULL) {
            continue;
        }

        if ((ptr->unk_08[i].unk_0 != NULL) && (ptr->unk_08[i].unk_0->priority < temp_a1->priority)) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            return;
        }
    }
}

void func_8002B344(s32 arg0) {
    if (D_80088406 < 6) {
        dm_snd_play(arg0);
    }
}

s32 func_8002B370(void) {
    return MusFxBankNumberOfEffects(func_8002D710());
}

void func_8002B394(void) {
    s32 sp10[4];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(sp10); i++) {
        s32 j;

        sp10[i] = rand() % ARRAY_COUNT(RO_800ACA10);
        for (j = 0; j < i; j++) {
            if (sp10[i] == sp10[j]) {
                i -= 1;
                break;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNTU(sp10); i++) {
        dm_snd_play(RO_800ACA10[sp10[i]] + 3);
    }
}

void func_8002B490(UNK_PTR arg0 UNUSED) {
    B_800ED430 = 2;
    B_800E9BB6 = 4;
    graphic_no = 0;
    B_800FAD2C = 0;
}

void func_8002B4BC(struct_800EB670 *arg0) {
    s16 *sp10 = NULL;

    D_80088128 = 0;
    osCreateMesgQueue(&B_800F4898, B_800EBED0, ARRAY_COUNT(B_800EBED0));
    func_8002A184(arg0, &B_800F48B0, &B_800F4898);
    B_800FAF94 = func_8002A0D4(arg0);

    while (true) {
        osRecvMesg(&B_800F4898, (OSMesg *)&sp10, OS_MESG_BLOCK);

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
    switch (graphic_no) {
        case 0:
            break;

        case 1:
            if (D_80088128 < 2) {
                func_8007AEF4();
            }
            break;

        case 2:
            if (D_80088128 < 2) {
                dm_title_graphic();
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
                graphic_boot_error();
            }
            break;
    }
}

void func_8002B710(void) {
    D_80088128 -= 1;
}

void func_8002B728(void) {
    if (graphic_no == 4) {
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

    osRecvMesg(&B_800F4898, (OSMesg *)&sp10, OS_MESG_BLOCK);
    return *sp10;
}

/**
 * Original name: gfxTaskStart
 */
void gfxTaskStart(OSScTask *scTask, void *data_ptr, size_t data_size, s32 arg3, u32 flags) {
    scTask->list.t.type = M_GFXTASK;
    scTask->list.t.flags = OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST;
    scTask->list.t.data_ptr = data_ptr;
    scTask->list.t.data_size = data_size;
    scTask->list.t.ucode_boot = (void *)rspbootTextStart;
    scTask->list.t.ucode_boot_size = (u8 *)rspbootTextEnd - (u8 *)rspbootTextStart;
    scTask->list.t.ucode = D_80088110[arg3][0];
    scTask->list.t.ucode_data = D_80088110[arg3][1];
    scTask->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    scTask->list.t.dram_stack = B_800FAFA0;
    scTask->list.t.dram_stack_size = sizeof(B_800FAFA0);
    scTask->list.t.output_buff = B_801136F0;
    scTask->list.t.output_buff_size = (u64 *)&B_801236F0;
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
    scTask->framebuffer = &gFramebuffers[gCurrentFramebufferIndex];
    osSendMesg(B_800FAF94, scTask, OS_MESG_BLOCK);
    if (flags & OS_SC_SWAPBUFFER) {
        gCurrentFramebufferIndex ^= 1;
    }
    B_800FAD2C = (B_800FAD2C + 1) % 3;
}

/**
 * Original name: F3RCPinitRtn
 */
void F3RCPinitRtn(void) {
    gSPSegment(gGfxHead++, 0x00, 0x00000000);
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088328));
    gSPViewport(gGfxHead++, &D_80088130);

    if (D_80088140 == 1) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088228));
        D_80088140 = 0;
    }

    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088308));
    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
}

/**
 * Original name: F3ClearFZRtn
 */
void F3ClearFZRtn(u8 arg0) {
    gDPSetCycleType(gGfxHead++, G_CYC_FILL);
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));

    if (arg0) {
        gDPSetFillColor(gGfxHead++, (GPACK_RGBA5551(0, 0, 0, 1) << 16) | GPACK_RGBA5551(0, 0, 0, 1));
        gDPFillRectangle(gGfxHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }

    gDPPipeSync(gGfxHead++);
    gDPSetCycleType(gGfxHead++, G_CYC_1CYCLE);
}

/**
 * Original name: S2RDPinitRtn
 */
void S2RDPinitRtn(u8 arg0) {
    gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_80088150));
    if (arg0) {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, 319, 239);
    } else {
        gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 12, 8, 307, 231);
    }
}

/**
 * Original name: S2ClearCFBRtn
 */
void S2ClearCFBRtn(u8 arg0) {
    gDPSetColorImage(gGfxHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(gFramebuffers[gCurrentFramebufferIndex]));
    if (arg0) {
        gSPDisplayList(gGfxHead++, OS_K0_TO_PHYSICAL(D_800881B8));
        gDPFillRectangle(gGfxHead++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }
}
