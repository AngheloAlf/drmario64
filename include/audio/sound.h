#ifndef AUDIO_SOUND_H
#define AUDIO_SOUND_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "PR/libmus.h"
#include "PR/sched.h"
#include "unk.h"

struct NNSched;


typedef enum SndIndex {
    /*  -1 */ SND_INDEX_INVALID = -1,
    /*   0 */ SND_INDEX_0,
    /*   1 */ SND_INDEX_1,
    /*   2 */ SND_INDEX_2,
    /*   3 */ SND_INDEX_3,
    /*   4 */ SND_INDEX_4,
    /*   5 */ SND_INDEX_5,
    /*   6 */ SND_INDEX_6,
    /*   7 */ SND_INDEX_7,
    /*   8 */ SND_INDEX_8,
    /*   9 */ SND_INDEX_9,
    /*  10 */ SND_INDEX_10,
    /*  11 */ SND_INDEX_11,
    /*  12 */ SND_INDEX_12,
    /*  13 */ SND_INDEX_13,
    /*  14 */ SND_INDEX_14,
    /*  15 */ SND_INDEX_15,
    /*  16 */ SND_INDEX_16,
    /*  17 */ SND_INDEX_17,
    /*  18 */ SND_INDEX_18,
    /*  19 */ SND_INDEX_19,
    /*  20 */ SND_INDEX_20,
    /*  21 */ SND_INDEX_21,
    /*  22 */ SND_INDEX_22,
    /*  23 */ SND_INDEX_23,
    /*  24 */ SND_INDEX_24,
    /*  25 */ SND_INDEX_25,
    /*  26 */ SND_INDEX_26,
    /*  27 */ SND_INDEX_27,
    /*  28 */ SND_INDEX_28,
    /*  29 */ SND_INDEX_29,
    /*  30 */ SND_INDEX_30,
    /*  31 */ SND_INDEX_31,
    /*  32 */ SND_INDEX_32,
    /*  33 */ SND_INDEX_33,
    /*  34 */ SND_INDEX_34,
    /*  35 */ SND_INDEX_35,
    /*  36 */ SND_INDEX_36,
    /*  37 */ SND_INDEX_37,
    /*  38 */ SND_INDEX_38,
    /*  39 */ SND_INDEX_39,
    /*  40 */ SND_INDEX_40,
    /*  41 */ SND_INDEX_41,
    /*  42 */ SND_INDEX_42,
    /*  43 */ SND_INDEX_43,
    /*  44 */ SND_INDEX_44,
    /*  45 */ SND_INDEX_45,
    /*  46 */ SND_INDEX_46,
    /*  47 */ SND_INDEX_47,
    /*  48 */ SND_INDEX_48,
    /*  49 */ SND_INDEX_49,
    /*  50 */ SND_INDEX_50,
    /*  51 */ SND_INDEX_51,
    /*  52 */ SND_INDEX_52,
    /*  53 */ SND_INDEX_53,
    /*  54 */ SND_INDEX_54,
    /*  55 */ SND_INDEX_55,
    /*  56 */ SND_INDEX_56,
    /*  57 */ SND_INDEX_57,
    /*  58 */ SND_INDEX_58,
    /*  59 */ SND_INDEX_59,
    /*  60 */ SND_INDEX_60,
    /*  61 */ SND_INDEX_61,
    /*  62 */ SND_INDEX_62,
    /*  63 */ SND_INDEX_63,
    /*  64 */ SND_INDEX_64,
    /*  65 */ SND_INDEX_65,
    /*  66 */ SND_INDEX_66,
    /*  67 */ SND_INDEX_67,
    /*  68 */ SND_INDEX_68,
    /*  69 */ SND_INDEX_69,
    /*  70 */ SND_INDEX_70,
    /*  71 */ SND_INDEX_71,
    /*  72 */ SND_INDEX_72,
    /*  73 */ SND_INDEX_73,
    /*  74 */ SND_INDEX_74,
    /*  75 */ SND_INDEX_75,
    /*  76 */ SND_INDEX_76,
    /*  77 */ SND_INDEX_77,
    /*  78 */ SND_INDEX_78,
    /*  79 */ SND_INDEX_79,
    /*  80 */ SND_INDEX_80,
    /*  81 */ SND_INDEX_81,
    /*  82 */ SND_INDEX_82,
    /*  83 */ SND_INDEX_83,
    /*  84 */ SND_INDEX_84,
    /*  85 */ SND_INDEX_85,
    /*  86 */ SND_INDEX_86,
    /*  87 */ SND_INDEX_87,
    /*  88 */ SND_INDEX_88,
    /*  89 */ SND_INDEX_89,
    /*  90 */ SND_INDEX_90,
    /*  91 */ SND_INDEX_91,
    /*  92 */ SND_INDEX_92,
    /*  93 */ SND_INDEX_93,
    /*  94 */ SND_INDEX_94,
    /*  95 */ SND_INDEX_95,
    /*  96 */ SND_INDEX_96,
    /*  97 */ SND_INDEX_97,
    /*  98 */ SND_INDEX_98,
    /*  99 */ SND_INDEX_99,
    /* 100 */ SND_INDEX_100,
    /* 101 */ SND_INDEX_101,
    /* 102 */ SND_INDEX_102,
    /* 103 */ SND_INDEX_103,
    /* 104 */ SND_INDEX_MAX
} SndIndex;

typedef struct SndEntry {
    /* 0x0 */ u8 number;
    /* 0x1 */ s8 offset;
    /* 0x2 */ u8 unk_2;
    /* 0x3 */ u8 priority;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 volume;
} SndEntry; // size = 0x6

typedef enum SeqIndex {
    /* -1 */ SEQ_INDEX_NONE = -1,
    /*  0 */ SEQ_INDEX_0,
    /*  1 */ SEQ_INDEX_1,
    /*  2 */ SEQ_INDEX_2,
    /*  3 */ SEQ_INDEX_3,
    /*  4 */ SEQ_INDEX_4,
    /*  5 */ SEQ_INDEX_5,
    /*  6 */ SEQ_INDEX_6,
    /*  7 */ SEQ_INDEX_7,
    /*  8 */ SEQ_INDEX_8,
    /*  9 */ SEQ_INDEX_9,
    /* 10 */ SEQ_INDEX_10,
    /* 11 */ SEQ_INDEX_11,
    /* 12 */ SEQ_INDEX_12,
    /* 13 */ SEQ_INDEX_13,
    /* 14 */ SEQ_INDEX_14,
    /* 15 */ SEQ_INDEX_15,
    /* 16 */ SEQ_INDEX_16,
    /* 17 */ SEQ_INDEX_17,
    /* 18 */ SEQ_INDEX_18,
    /* 19 */ SEQ_INDEX_19,
    /* 20 */ SEQ_INDEX_20,
    /* 21 */ SEQ_INDEX_21,
    /* 22 */ SEQ_INDEX_22,
    /* 23 */ SEQ_INDEX_23,
    /* 24 */ SEQ_INDEX_MAX
} SeqIndex;


typedef struct struct_800FACE0_unk_08 {
    /* 0x0 */ const SndEntry *sndEntry;
    /* 0x4 */ s32 index;
    /* 0x8 */ UNK_TYPE unk_8;
} struct_800FACE0_unk_08; // size = 0xC

typedef struct struct_800FACE0 {
    /* 0x00 */ SeqIndex seqIndex[2];
    /* 0x08 */ struct_800FACE0_unk_08 unk_08[4];
    /* 0x38 */ struct_800FACE0_unk_08 *unk_38[4];
} struct_800FACE0; // size >= 0x3C


/// 000E30.c

s32 func_8002AA80();
void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 index);
void func_8002AAE8(struct_800FACE0_unk_08 *arg0, const SndEntry *arg1);
bool func_8002AB28(struct_800FACE0_unk_08 *arg0);
bool func_8002ABC0(struct_800FACE0_unk_08 *arg0);
void func_8002AC64(struct_800FACE0_unk_08 *arg0);
#if VERSION_US || VERSION_GW || CC_CHECK
void dm_audio_set_stereo(bool setStereo);
#endif
void dm_audio_init_driver(struct NNSched *sc);
void dm_audio_update(void);
void dm_audio_stop(void);
bool dm_audio_is_stopped(void);
void dm_seq_play(SeqIndex seqIndex);
void _dm_seq_play(s32 arg0, SeqIndex seqIndex);
void dm_seq_play_fade(SeqIndex seqIndex, s32 arg1);
void _dm_seq_play_fade(s32 arg0, SeqIndex seqIndex, s32 arg2);
void dm_seq_play_in_game(SeqIndex seqIndex);
void _dm_seq_play_in_game(s32 arg0, SeqIndex seqIndex);
void dm_seq_stop(void);
void _dm_seq_stop(s32 arg0);
void dm_seq_set_volume(s32 volume);
void _dm_seq_set_volume(s32 arg0, s32 volume);
bool func_8002B178(void);
bool func_8002B194(s32 arg0);
void dm_snd_play(SndIndex sndIndex);
void dm_snd_play_in_game(SndIndex sndIndex);
s32 func_8002B370(void);
void dm_snd_play_strange_sound(void);


// rodata

extern const u8 _charSE_tbl[];


// bss

/**
 * Original name: sound_song_seqNo
 */
extern struct_800FACE0 sound_song_id;


#define SND_PLAY_INDEX(index) \
    if (index > SND_INDEX_INVALID) { \
        dm_snd_play(index); \
    }


#endif
