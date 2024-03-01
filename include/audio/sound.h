#ifndef AUDIO_SOUND_H
#define AUDIO_SOUND_H

#include "libultra.h"
#include "PR/libmus.h"
#include "PR/sched.h"

#include "libc/stdint.h"
#include "libc/stdbool.h"

#include "snd_seq.h"

#include "unk.h"

struct NNSched;

typedef struct SndEntry {
    /* 0x0 */ u8 number;
    /* 0x1 */ s8 offset;
    /* 0x2 */ u8 unk_2;
    /* 0x3 */ u8 priority;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 volume;
} SndEntry; // size = 0x6

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


s32 func_8002AA80();
void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 index);
void func_8002AAE8(struct_800FACE0_unk_08 *arg0, const SndEntry *arg1);
bool func_8002AB28(struct_800FACE0_unk_08 *arg0);
bool func_8002ABC0(struct_800FACE0_unk_08 *arg0);
void func_8002AC64(struct_800FACE0_unk_08 *arg0);
void dm_audio_set_stereo(bool setStereo);
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
