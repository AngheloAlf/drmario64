/**
 * Original filename: sound.c
 */

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
    SND_INDEX_94 - 3, SND_INDEX_84 - 3, SND_INDEX_38 - 3, SND_INDEX_43 - 3, SND_INDEX_48 - 3,
    SND_INDEX_18 - 3, SND_INDEX_28 - 3, SND_INDEX_23 - 3, SND_INDEX_3 - 3,  SND_INDEX_8 - 3,
    SND_INDEX_13 - 3, SND_INDEX_33 - 3, SND_INDEX_53 - 3, SND_INDEX_89 - 3, SND_INDEX_99 - 3,
};

const RomDataTblIndex RO_800ACA20[] = {
    ROMDATATBL_INDEX4,  ROMDATATBL_INDEX9,  ROMDATATBL_INDEX3,  ROMDATATBL_INDEX8,  ROMDATATBL_INDEX5,
    ROMDATATBL_INDEX10, ROMDATATBL_INDEX6,  ROMDATATBL_INDEX11, ROMDATATBL_INDEX7,  ROMDATATBL_INDEX12,
    ROMDATATBL_INDEX13, ROMDATATBL_INDEX14, ROMDATATBL_INDEX15, ROMDATATBL_INDEX17, ROMDATATBL_INDEX18,
    ROMDATATBL_INDEX19, ROMDATATBL_INDEX20, ROMDATATBL_INDEX21, ROMDATATBL_INDEX22, ROMDATATBL_INDEX23,
    ROMDATATBL_INDEX24, ROMDATATBL_INDEX25, ROMDATATBL_INDEX16, ROMDATATBL_INDEX26,
};

const SndEntry gSndsEntries[SND_INDEX_MAX] = {
    /*   SND_INDEX_0 */ { 0x00, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_1 */ { 0x01, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_2 */ { 0x02, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_3 */ { 0x03, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_4 */ { 0x04, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_5 */ { 0x05, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_6 */ { 0x06, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_7 */ { 0x07, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_8 */ { 0x08, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*   SND_INDEX_9 */ { 0x09, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_10 */ { 0x0A, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_11 */ { 0x0B, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_12 */ { 0x0C, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_13 */ { 0x0D, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_14 */ { 0x0E, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_15 */ { 0x0F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_16 */ { 0x10, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_17 */ { 0x11, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_18 */ { 0x12, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_19 */ { 0x13, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_20 */ { 0x14, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_21 */ { 0x15, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_22 */ { 0x16, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_23 */ { 0x17, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_24 */ { 0x18, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_25 */ { 0x19, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_26 */ { 0x1A, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_27 */ { 0x1B, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_28 */ { 0x1C, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_29 */ { 0x1D, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_30 */ { 0x1E, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_31 */ { 0x1F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_32 */ { 0x20, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_33 */ { 0x21, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_34 */ { 0x22, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_35 */ { 0x23, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_36 */ { 0x24, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_37 */ { 0x25, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_38 */ { 0x26, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_39 */ { 0x27, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_40 */ { 0x28, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_41 */ { 0x29, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_42 */ { 0x2A, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_43 */ { 0x2B, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_44 */ { 0x2C, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_45 */ { 0x2D, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_46 */ { 0x2E, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_47 */ { 0x2F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_48 */ { 0x30, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_49 */ { 0x31, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_50 */ { 0x32, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_51 */ { 0x33, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_52 */ { 0x34, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_53 */ { 0x35, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_54 */ { 0x36, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_55 */ { 0x37, 0xF4, 0x00, 0x0A, 0x00, 0x74 },
    /*  SND_INDEX_56 */ { 0x38, 0x00, 0x00, 0x0A, 0x00, 0x74 },
    /*  SND_INDEX_57 */ { 0x39, 0xFA, 0xD3, 0x0A, 0x00, 0x74 },
    /*  SND_INDEX_58 */ { 0x3A, 0xF4, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_59 */ { 0x3B, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_60 */ { 0x3C, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_61 */ { 0x3D, 0xF4, 0x00, 0x0A, 0x00, 0x74 },
    /*  SND_INDEX_62 */ { 0x3E, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_63 */ { 0x3F, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_64 */ { 0x40, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_65 */ { 0x41, 0xF4, 0x00, 0x0A, 0x00, 0x6A },
    /*  SND_INDEX_66 */ { 0x42, 0xF4, 0x00, 0x0A, 0x00, 0x74 },
    /*  SND_INDEX_67 */ { 0x43, 0xFA, 0xD3, 0x0A, 0x00, 0x60 },
    /*  SND_INDEX_68 */ { 0x44, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_69 */ { 0x45, 0x05, 0x37, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_70 */ { 0x46, 0xF4, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_71 */ { 0x47, 0xF4, 0x00, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_72 */ { 0x48, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_73 */ { 0x49, 0xFA, 0xD3, 0x0A, 0x00, 0x78 },
    /*  SND_INDEX_74 */ { 0x4A, 0x00, 0x00, 0x0A, 0x14, 0x74 },
    /*  SND_INDEX_75 */ { 0x4B, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    /*  SND_INDEX_76 */ { 0x4C, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    /*  SND_INDEX_77 */ { 0x4D, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    /*  SND_INDEX_78 */ { 0x4E, 0xFA, 0xD3, 0x28, 0x00, 0x74 },
    /*  SND_INDEX_79 */ { 0x4F, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    /*  SND_INDEX_80 */ { 0x50, 0xFA, 0xD3, 0x28, 0x00, 0x78 },
    /*  SND_INDEX_81 */ { 0x51, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_82 */ { 0x52, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_83 */ { 0x53, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_84 */ { 0x54, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_85 */ { 0x55, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_86 */ { 0x56, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_87 */ { 0x57, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_88 */ { 0x58, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_89 */ { 0x59, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_90 */ { 0x5A, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_91 */ { 0x5B, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_92 */ { 0x5C, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_93 */ { 0x5D, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_94 */ { 0x5E, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_95 */ { 0x5F, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_96 */ { 0x60, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_97 */ { 0x61, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_98 */ { 0x62, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /*  SND_INDEX_99 */ { 0x63, 0xF4, 0x00, 0x28, 0x00, 0x6C },
    /* SND_INDEX_100 */ { 0x64, 0xFA, 0xD3, 0x28, 0x00, 0x6C },
    /* SND_INDEX_101 */ { 0x65, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    /* SND_INDEX_102 */ { 0x66, 0x00, 0x00, 0x0A, 0x00, 0x78 },
    /* SND_INDEX_103 */ { 0x67, 0x00, 0x00, 0x0A, 0x00, 0x78 },
};

s32 func_8002AA80(void) {
    s32 ret = 0;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(RO_800ACA20); i++) {
        RomOffsetPair *pair = &_romDataTbl[RO_800ACA20[i]];
        s32 segmentSize = pair->end - pair->start;

        ret = MAX(segmentSize, ret);
    }
    return ret;
}

void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 index) {
    arg0->sndEntry = 0;
    arg0->index = index;
    arg0->unk_8 = 0;
}

void func_8002AAE8(struct_800FACE0_unk_08 *arg0, const SndEntry *arg1) {
    func_8002D810(arg0->index, 0);
    arg0->sndEntry = arg1;
    arg0->unk_8 = 0;
}

bool func_8002AB28(struct_800FACE0_unk_08 *arg0) {
    if ((arg0->sndEntry == NULL) || (func_8002D7E0(arg0->index) != 0)) {
        return false;
    }

    func_8002D720(arg0->index, arg0->sndEntry->number);
    func_8002D840(arg0->index, arg0->sndEntry->volume);
    func_8002D8A0(arg0->index, arg0->sndEntry->offset * 0.125);
    return true;
}

bool func_8002ABC0(struct_800FACE0_unk_08 *arg0) {
    if ((arg0->sndEntry == NULL) || (func_8002D7E0(arg0->index) != 0)) {
        return false;
    }

    func_8002D768(arg0->index, arg0->sndEntry->number, arg0->sndEntry->volume, 0x80, true, arg0->sndEntry->priority);
    func_8002D8A0(arg0->index, arg0->sndEntry->offset * 0.125);
    return true;
}

void func_8002AC64(struct_800FACE0_unk_08 *arg0) {
    if (arg0->sndEntry == NULL) {
        return;
    }

    if (func_8002D7E0(arg0->index) != 0) {
        if (arg0->sndEntry->unk_4 != 0) {
            if (arg0->unk_8 < (arg0->sndEntry->unk_4 * 6)) {
                arg0->unk_8++;
            } else {
                func_8002D810(arg0->index, 0);
                arg0->sndEntry = NULL;
            }
        }
    } else {
        arg0->sndEntry = NULL;
    }
}

#if VERSION_US
#ifdef NON_EQUIVALENT
// maybe equivalent, but too afraid to tell
/**
 * Changes the audio configuration to stereo or mono
 *
 * Patches the following statements in `alEnvmixerPull`:
 * e->pan    = param->pan;
 * e->pan = (s16) e->ctrlList->data.i;
 *
 * Original name: dm_audio_set_stereo
 */
void dm_audio_set_stereo(bool setStereo) {
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
INCLUDE_ASM("asm/us/nonmatchings/main_segment/sound", dm_audio_set_stereo);
#endif
#endif

/**
 * Original name: dm_audio_init_driver
 */
void dm_audio_init_driver(struct_800EB670 *arg0) {
    s32 i;
    struct_800FACE0 *ptr = &B_800FACE0;
    UNK_TYPE val = -1;

    for (i = ARRAY_COUNT(ptr->unk_00) - 1; i >= 0; i--) {
        ptr->unk_00[i] = val;
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        func_8002AAD8(&ptr->unk_08[i], i);
    }

    func_8002D170(arg0, B_800B3640, sizeof(B_800B3640),
                  _romDataTbl[ROMDATATBL_N64_PTR_TABLES].end - _romDataTbl[ROMDATATBL_N64_PTR_TABLES].start,
                  func_8002AA80(), 2, _romDataTbl[ROMDATATBL_INDEX2].end - _romDataTbl[ROMDATATBL_INDEX2].start, 4, 50);

    func_8002D3B0(_romDataTbl[ROMDATATBL_N64_PTR_TABLES].start,
                  _romDataTbl[ROMDATATBL_N64_PTR_TABLES].end - _romDataTbl[ROMDATATBL_N64_PTR_TABLES].start,
                  (void *)_romDataTbl[ROMDATATBL_N64_WAVE_TABLES].start);
    func_8002D6A4(_romDataTbl[ROMDATATBL_INDEX2].start,
                  _romDataTbl[ROMDATATBL_INDEX2].end - _romDataTbl[ROMDATATBL_INDEX2].start);
}

/**
 * Original name: dm_audio_update
 */
void dm_audio_update(void) {
    struct_800FACE0 *var_s0 = &B_800FACE0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(var_s0->unk_00); i++) {
        if ((var_s0->unk_00[i] >= 0) && func_8002B194(i)) {
            RomOffsetPair *pair = &_romDataTbl[RO_800ACA20[var_s0->unk_00[i]]];

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

/**
 * Original name: dm_audio_stop
 */
void dm_audio_stop(void) {
    dm_seq_stop();
    MusStop(MUSFLAG_EFFECTS | MUSFLAG_SONGS, 0);
}

/**
 * Original name: dm_audio_is_stopped
 */
bool dm_audio_is_stopped(void) {
    return MusAsk(MUSFLAG_EFFECTS | MUSFLAG_SONGS) == 0;
}

/**
 * Original name: dm_seq_play
 */
void dm_seq_play(s32 arg0) {
    _dm_seq_play(0, arg0);
}

/**
 * Original name: _dm_seq_play
 */
void _dm_seq_play(s32 arg0, s32 arg1) {
    _dm_seq_play_fade(arg0, arg1, 0);
}

/**
 * Original name: dm_seq_play_fade
 */
void dm_seq_play_fade(s32 arg0, s32 arg1) {
    _dm_seq_play_fade(0, arg0, arg1);
}

/**
 * Original name: _dm_seq_play_fade
 */
void _dm_seq_play_fade(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == B_800FACE0.unk_00[arg0]) {
        return;
    }

    func_8002D554(arg0, arg2);
    B_800FACE0.unk_00[arg0] = arg1;
}

/**
 * Original name: dm_seq_play_in_game
 */
void dm_seq_play_in_game(s32 arg0) {
    _dm_seq_play_in_game(0, arg0);
}

/**
 * Original name: dm_seq_play_in_game
 */
void _dm_seq_play_in_game(s32 arg0, s32 arg1) {
    if (evs_seqence == 0) {
        if (arg1 < 10) {
            if (arg1 >= 0) {
                _dm_seq_stop(arg0);
                return;
            }
        }
    }
    _dm_seq_play(arg0, arg1);
}

/**
 * Original name: dm_seq_stop
 */
void dm_seq_stop(void) {
    _dm_seq_stop(0);
}

/**
 * Original name: _dm_seq_stop
 */
void _dm_seq_stop(s32 arg0) {
    func_8002D554(arg0, 0);
    B_800FACE0.unk_00[arg0] = -1;
}

/**
 * Original name: dm_seq_set_volume
 */
s32 dm_seq_set_volume(s32 arg0) {
    return _dm_seq_set_volume(0, arg0);
}

/**
 * Original name: _dm_seq_set_volume
 */
s32 _dm_seq_set_volume(s32 arg0, s32 volume) {
    return func_8002D58C(arg0, volume);
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
void dm_snd_play(SndIndex sndIndex) {
    s32 i;
    const SndEntry *temp_a1 = &gSndsEntries[sndIndex];
    struct_800FACE0 *ptr = &B_800FACE0;

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] == NULL) {
            continue;
        }

        if ((ptr->unk_08[i].sndEntry != NULL) && (ptr->unk_08[i].sndEntry->number == temp_a1->number)) {
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] != NULL) {
            continue;
        }

        if (ptr->unk_08[i].sndEntry == NULL) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            ptr->unk_38[i] = &ptr->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] != NULL) {
            continue;
        }

        if ((ptr->unk_08[i].sndEntry != NULL) && (ptr->unk_08[i].sndEntry->priority <= temp_a1->priority)) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            ptr->unk_38[i] = &ptr->unk_08[i];
            return;
        }
    }

    for (i = 0; i < ARRAY_COUNT(ptr->unk_08); i++) {
        if (ptr->unk_38[i] == NULL) {
            continue;
        }

        if ((ptr->unk_08[i].sndEntry != NULL) && (ptr->unk_08[i].sndEntry->priority < temp_a1->priority)) {
            func_8002AAE8(&ptr->unk_08[i], temp_a1);
            return;
        }
    }
}

/**
 * Original name: dm_snd_play_in_game
 */
void dm_snd_play_in_game(SndIndex sndIndex) {
    if (evs_gamespeed < 6) {
        dm_snd_play(sndIndex);
    }
}

s32 func_8002B370(void) {
    return MusFxBankNumberOfEffects(func_8002D710());
}

/**
 * Original name: dm_snd_play_strange_sound
 */
void dm_snd_play_strange_sound(void) {
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
