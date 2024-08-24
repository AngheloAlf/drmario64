/**
 * Original filename: replay.c
 */

#include "replay.h"

#include "libultra.h"

#include "macros_defines.h"

#define REPLAY_TOTAL_BUFF_SIZE 0x10000

static u8 *rec_buff;
static u8 *pRecBuff[MAXCONTROLLERS];
static u16 oldCont[MAXCONTROLLERS];
static s32 RecPos[MAXCONTROLLERS];
static s32 PlayPos[MAXCONTROLLERS];
static s32 WaitTime[MAXCONTROLLERS];
static s32 max_rec;
static s32 replay_player;

// TODO: flags

/**
 * Original name: replay_record_init_buffer
 */
void replay_record_init_buffer(void **arg0) {
    void *temp_v0;

    temp_v0 = *arg0;
    rec_buff = temp_v0;
    *arg0 = temp_v0 + REPLAY_TOTAL_BUFF_SIZE;
}

/**
 * Original name: replay_record_init
 */
void replay_record_init(s32 arg0) {
    s32 i;

    replay_player = arg0;

    for (i = 0; i < MAXCONTROLLERS; i++) {
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
            max_rec = REPLAY_TOTAL_BUFF_SIZE / 4;
            pRecBuff[0] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 0;
            pRecBuff[1] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 1;
            pRecBuff[2] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 2;
            pRecBuff[3] = rec_buff + (REPLAY_TOTAL_BUFF_SIZE / 4) * 3;
            break;
    }

    max_rec -= 2;
}

/**
 * Original name: replay_record
 */
bool replay_record(s32 arg0, u32 arg1) {
    u16 temp_a1;
    u8 var_t1;
    u8 *temp_t3;
    u8 a3; //! @bug a3 is used uninitialized

    var_t1 = false;
    temp_t3 = pRecBuff[arg0];
    temp_a1 = arg1 & 0xC730;
    if (RecPos[arg0] == 0) {
        oldCont[arg0] = ~temp_a1;
    }

    if (oldCont[arg0] != temp_a1) {
        a3 = 0;
        if (temp_a1 & 0x200) {
            a3 |= 1;
        }
        if (temp_a1 & 0x100) {
            a3 |= 2;
        }
        if (temp_a1 & 0x400) {
            a3 |= 4;
        }
        if (temp_a1 & 0x8000) {
            a3 |= 0x10;
        }
        if (temp_a1 & 0x4000) {
            a3 |= 0x20;
        }
        if (temp_a1 & 0x30) {
            a3 |= 8;
        }
        oldCont[arg0] = temp_a1;
        var_t1 = true;
    }

    if (RecPos[arg0] < max_rec) {
        if (var_t1) {
            temp_t3[RecPos[arg0]] = WaitTime[arg0];
            RecPos[arg0]++;
            temp_t3[RecPos[arg0]] = a3;
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

/**
 * Original name: replay_play_init
 */
void replay_play_init(void) {
    s32 i;

    for (i = 0; i < replay_player; i++) {
        WaitTime[i] = *pRecBuff[i];
        PlayPos[i] = 1;
        oldCont[i] = 0;
    }
}

/**
 * Original name: replay_play
 */
u16 replay_play(s32 arg0) {
    u8 *temp_t0 = pRecBuff[arg0];
    u8 var_a0;
    u8 a3; //! @bug a3 is used uninitialized

    if (WaitTime[arg0] == 0) {
        if (temp_t0[PlayPos[arg0]] == 0x80) {
            return 0x1000;
        }
    }

    var_a0 = false;

    if (WaitTime[arg0] == 0) {
        a3 = temp_t0[PlayPos[arg0]];
        PlayPos[arg0]++;
        WaitTime[arg0] = temp_t0[PlayPos[arg0]];
        PlayPos[arg0]++;
        var_a0 = a3 != 0x40;
    } else {
        WaitTime[arg0]--;
    }

    if (var_a0) {
        u16 var_a0_2 = 0;

        if (a3 & 1) {
            var_a0_2 |= 0x200;
        }
        if (a3 & 2) {
            var_a0_2 |= 0x100;
        }
        if (a3 & 4) {
            var_a0_2 |= 0x400;
        }
        if (a3 & 8) {
            var_a0_2 |= 0x30;
        }
        if (a3 & 0x10) {
            var_a0_2 |= 0x8000;
        }
        if (a3 & 0x20) {
            var_a0_2 |= 0x4000;
        }
        oldCont[arg0] = var_a0_2;
    }

    return oldCont[arg0];
}
