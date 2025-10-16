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

#define REC_DATA_LEFT (1 << 0)
#define REC_DATA_RIGHT (1 << 1)
#define REC_DATA_DOWN (1 << 2)
#define REC_DATA_TRIGGER (1 << 3)
#define REC_DATA_A (1 << 4)
#define REC_DATA_B (1 << 5)
#define REC_DATA_40 (1 << 6)
#define REC_DATA_80 (1 << 7)

/**
 * Original name: replay_record_init_buffer
 */
void replay_record_init_buffer(void **heap) {
    rec_buff = *heap;
    *heap = rec_buff + REPLAY_TOTAL_BUFF_SIZE;
}

/**
 * Original name: replay_record_init
 */
void replay_record_init(s32 player) {
    s32 i;

    replay_player = player;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        RecPos[i] = 0;
        WaitTime[i] = 0;
        PlayPos[i] = 0;
        oldCont[i] = 0;
    }

    switch (player) {
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
bool replay_record(s32 player, u16 pad) {
    u8 flg = false;
    u8 *pRec = pRecBuff[player];
    u8 data; //! @bug `data` is used uninitialized

    // Only allow certain inputs.
    pad &= A_BUTTON | B_BUTTON | D_JPAD | L_JPAD | R_JPAD | L_TRIG | R_TRIG;

    if (RecPos[player] == 0) {
        oldCont[player] = ~pad;
    }

    if (oldCont[player] != pad) {
        data = 0;
        if (pad & L_JPAD) {
            data |= REC_DATA_LEFT;
        }
        if (pad & R_JPAD) {
            data |= REC_DATA_RIGHT;
        }
        if (pad & D_JPAD) {
            data |= REC_DATA_DOWN;
        }
        if (pad & A_BUTTON) {
            data |= REC_DATA_A;
        }
        if (pad & B_BUTTON) {
            data |= REC_DATA_B;
        }
        if (pad & (L_TRIG | R_TRIG)) {
            data |= REC_DATA_TRIGGER;
        }
        oldCont[player] = pad;
        flg = true;
    }

    if (RecPos[player] < max_rec) {
        if (flg) {
            pRec[RecPos[player]] = WaitTime[player];
            RecPos[player]++;

            pRec[RecPos[player]] = data;
            RecPos[player]++;

            WaitTime[player] = 0;
        } else if (WaitTime[player] == 0xFF) {
            pRec[RecPos[player]] = WaitTime[player];
            RecPos[player]++;

            pRec[RecPos[player]] = REC_DATA_40;
            RecPos[player]++;

            WaitTime[player] = 0;
        } else {
            WaitTime[player]++;
        }
    } else {
        return false;
    }

    pRec[RecPos[player]] = WaitTime[player];
    pRec[RecPos[player] + 1] = REC_DATA_80;

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
u16 replay_play(s32 player) {
    u8 *pRec = pRecBuff[player];
    u8 flg;
    u8 data; //! @bug `data` is used uninitialized

    if (WaitTime[player] == 0) {
        if (pRec[PlayPos[player]] == REC_DATA_80) {
            return START_BUTTON;
        }
    }

    flg = false;

    if (WaitTime[player] == 0) {
        data = pRec[PlayPos[player]];
        PlayPos[player]++;

        WaitTime[player] = pRec[PlayPos[player]];
        PlayPos[player]++;

        flg = data != REC_DATA_40;
    } else {
        WaitTime[player]--;
    }

    if (flg) {
        u16 cont = 0;

        if (data & REC_DATA_LEFT) {
            cont |= L_JPAD;
        }
        if (data & REC_DATA_RIGHT) {
            cont |= R_JPAD;
        }
        if (data & REC_DATA_DOWN) {
            cont |= D_JPAD;
        }
        if (data & REC_DATA_TRIGGER) {
            cont |= L_TRIG | R_TRIG;
        }
        if (data & REC_DATA_A) {
            cont |= A_BUTTON;
        }
        if (data & REC_DATA_B) {
            cont |= B_BUTTON;
        }
        oldCont[player] = cont;
    }

    return oldCont[player];
}
