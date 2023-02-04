/**
 * Original filename: replay.c
 */

#include "replay.h"
#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"

/**
 * Original name: replay_record_init_buffer
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init_buffer);
#endif

#if VERSION_CN
void replay_record_init_buffer(void **arg0) {
    void *temp_v0;

    temp_v0 = *arg0;
    rec_buff = temp_v0;
    *arg0 = temp_v0 + REPLAY_TOTAL_BUFF_SIZE;
}
#endif

/**
 * Original name: replay_record_init
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record_init);
#endif

#if VERSION_CN
void replay_record_init(s32 arg0) {
    s32 i;

    replay_player = arg0;

    for (i = 0; i < 4; i++) {
        RecPos[i] = 0;
        WaitTime[i] = 0;
        PlayPos[i] = 0;
        oldCont[i] = 0;
    }

    switch (arg0) {
        case 1:
            max_rec = REPLAY_TOTAL_BUFF_SIZE;
            pRecBuff[0] = rec_buff;
            break;

        case 2:
            max_rec = REPLAY_TOTAL_BUFF_SIZE / 2;
            pRecBuff[0] = rec_buff;
            pRecBuff[1] = rec_buff + REPLAY_TOTAL_BUFF_SIZE / 2;
            break;

        case 4:
            max_rec = REPLAY_TOTAL_BUFF_SIZE / 4;
            pRecBuff[0] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 0;
            pRecBuff[1] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 1;
            pRecBuff[2] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 2;
            pRecBuff[3] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 3;
            break;

        default:
            max_rec = 0x4000;
            pRecBuff[0] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 0;
            pRecBuff[1] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 1;
            pRecBuff[2] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 2;
            pRecBuff[3] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 3;
            break;
    }

    max_rec -= 2;
}
#endif

/**
 * Original name: replay_record
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_record);
#endif

#if VERSION_CN
bool replay_record(s32 arg0, s32 arg1, UNK_TYPE arg2 UNUSED, s32 arg3) {
    u16 temp_a1;
    bool var_t1;
    u8 *temp_t3;

    var_t1 = false;
    temp_t3 = pRecBuff[arg0];
    temp_a1 = arg1 & 0xC730;
    if (RecPos[arg0] == 0) {
        oldCont[arg0] = ~temp_a1;
    }

    if (oldCont[arg0] != temp_a1) {
        arg3 = 0;
        if (temp_a1 & 0x200) {
            arg3 = (arg3 | 1) & 0xFF;
        }
        if (temp_a1 & 0x100) {
            arg3 = (arg3 | 2) & 0xFF;
        }
        if (temp_a1 & 0x400) {
            arg3 = (arg3 | 4) & 0xFF;
        }
        if (temp_a1 & 0x8000) {
            arg3 = (arg3 | 0x10) & 0xFF;
        }
        if (temp_a1 & 0x4000) {
            arg3 = (arg3 | 0x20) & 0xFF;
        }
        if (temp_a1 & 0x30) {
            arg3 = (arg3 | 8) & 0xFF;
        }
        oldCont[arg0] = temp_a1;
        var_t1 = true;
    }

    if (RecPos[arg0] < max_rec) {
        if (var_t1) {
            temp_t3[RecPos[arg0]] = WaitTime[arg0];
            RecPos[arg0]++;
            temp_t3[RecPos[arg0]] = arg3;
            RecPos[arg0]++;
            WaitTime[arg0] = 0;
        } else if (WaitTime[arg0] == 0xFF) {
            temp_t3[RecPos[arg0]] = WaitTime[arg0];
            RecPos[arg0]++;
            temp_t3[RecPos[arg0]] = 0x40;
            RecPos[arg0]++;
            WaitTime[arg0] = 0;
        } else {
            WaitTime[arg0]++;
        }
    } else {
        return false;
    }

    temp_t3[RecPos[arg0]] = WaitTime[arg0];
    temp_t3[RecPos[arg0] + 1] = 0x80;

    return true;
}
#endif

/**
 * Original name: replay_play_init
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play_init);
#endif

#if VERSION_CN
void replay_play_init(void) {
    s32 i;

    for (i = 0; i < replay_player; i++) {
        WaitTime[i] = *pRecBuff[i];
        PlayPos[i] = 1;
        oldCont[i] = 0;
    }
}
#endif

/**
 * Original name: replay_play
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/replay", replay_play);
#endif

#if VERSION_CN
u16 replay_play(s32 arg0, UNK_TYPE arg1 UNUSED, UNK_TYPE arg2 UNUSED, s32 arg3) {
    u8 *temp_t0 = pRecBuff[arg0];
    bool var_a0;

    if (WaitTime[arg0] == 0) {
        if (temp_t0[PlayPos[arg0]] == 0x80) {
            return 0x1000;
        }
    }

    var_a0 = false;

    if (WaitTime[arg0] == 0) {
        arg3 = temp_t0[PlayPos[arg0]];
        PlayPos[arg0]++;
        var_a0 = arg3 != 0x40;
        WaitTime[arg0] = temp_t0[PlayPos[arg0]];
        PlayPos[arg0]++;
    } else {
        WaitTime[arg0]--;
    }

    if (var_a0) {
        u16 var_a0_2 = 0;

        if (arg3 & 1) {
            var_a0_2 = (var_a0_2 | 0x200);
        }
        if (arg3 & 2) {
            var_a0_2 = (var_a0_2 | 0x100);
        }
        if (arg3 & 4) {
            var_a0_2 |= 0x400;
        }
        if (arg3 & 8) {
            var_a0_2 |= 0x30;
        }
        if (arg3 & 0x10) {
            var_a0_2 |= 0x8000;
        }
        if (arg3 & 0x20) {
            var_a0_2 |= 0x4000;
        }
        oldCont[arg0] = var_a0_2;
    }

    return oldCont[arg0];
}
#endif
