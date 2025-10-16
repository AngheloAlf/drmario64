#ifndef AUDIO_SOUND_H
#define AUDIO_SOUND_H

#include "libultra.h"
#include "PR/libmus.h"
#include "PR/sched.h"

#include "libc/stdint.h"
#include "libc/stdbool.h"

#include "macros_defines.h"

#include "snd_seq.h"

struct NNSched;


typedef enum SoundBufNumber {
    /* 0 */ SOUNDBUFNUMBER_0,
    /* 1 */ SOUNDBUFNUMBER_1,
    /* 2 */ SOUNDBUFNUMBER_MAX,
} SoundBufNumber;


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
    /* 0x8 */ s32 unk_8;
} struct_800FACE0_unk_08; // size = 0xC

typedef struct struct_800FACE0 {
    /* 0x00 */ SeqIndex seqIndex[SOUNDBUFNUMBER_MAX];
    /* 0x08 */ struct_800FACE0_unk_08 unk_08[4];
    /* 0x38 */ struct_800FACE0_unk_08 *unk_38[4];
} struct_800FACE0; // size >= 0x3C


s32 func_8002AA80(void);
void func_8002AAD8(struct_800FACE0_unk_08 *arg0, s32 index);
void func_8002AAE8(struct_800FACE0_unk_08 *arg0, const SndEntry *arg1);
bool func_8002AB28(CONST_ARG struct_800FACE0_unk_08 *arg0);
bool func_8002ABC0(CONST_ARG struct_800FACE0_unk_08 *arg0);
void func_8002AC64(struct_800FACE0_unk_08 *arg0);

void dm_audio_set_stereo(bool setStereo);
void dm_audio_init_driver(struct NNSched *sc);
void dm_audio_update(void);
void dm_audio_stop(void);
bool dm_audio_is_stopped(void);
void dm_seq_play(SeqIndex seqIndex);
void _dm_seq_play(SoundBufNumber bufNo, SeqIndex seqIndex);
void dm_seq_play_fade(SeqIndex seqIndex, s32 fade);
void _dm_seq_play_fade(SoundBufNumber bufNo, SeqIndex seqIndex, s32 fade);
void dm_seq_play_in_game(SeqIndex seqIndex);
void _dm_seq_play_in_game(SoundBufNumber bufNo, SeqIndex seqIndex);
void dm_seq_stop(void);
void _dm_seq_stop(SoundBufNumber bufNo);
void dm_seq_set_volume(s32 volume);
void _dm_seq_set_volume(SoundBufNumber bufNo, s32 volume);
bool dm_seq_is_stopped(void);
bool _dm_seq_is_stopped(SoundBufNumber bufNo);
void dm_snd_play(SndIndex sndIndex);
void dm_snd_play_in_game(SndIndex sndIndex);
s32 func_8002B370(void);
void dm_snd_play_strange_sound(void);


// rodata

extern const u8 _charSE_tbl[];


// COMMON

extern struct_800FACE0 sound_song_id;


#define SND_PLAY_INDEX(index) \
    if (index > SND_INDEX_INVALID) { \
        dm_snd_play(index); \
    }


#endif
