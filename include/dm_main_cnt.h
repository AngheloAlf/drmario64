#ifndef DM_MAIN_CNT_H
#define DM_MAIN_CNT_H

// TODO: figure out a better place for this enum.

typedef enum DmMainCnt {
    /*  -2 */ dm_ret_game_end = -2, /* Original name: dm_ret_game_end */
    /*  -1 */ dm_ret_game_over, /* Original name: dm_ret_game_over */
    /*   0 */ dm_ret_null, /* Original name: dm_ret_null */
    /*   1 */ dm_ret_next_stage, /* Original name: dm_ret_next_stage */
    /*   2 */ dm_ret_retry, /* Original name: dm_ret_retry */
    /*   3 */ dm_ret_virus_wait, /* Original name: dm_ret_virus_wait */
    /*   4 */ dm_ret_pause, /* Original name: dm_ret_pause */
    /*   5 */ dm_ret_black_up, /* Original name: dm_ret_black_up */
    /*   6 */ dm_ret_clear, /* Original name: dm_ret_clear */
    /*   7 */ dm_ret_tr_a, /* Original name: dm_ret_tr_a */
    /*   8 */ dm_ret_tr_b, /* Original name: dm_ret_tr_b */
    /*   9 */ dm_ret_replay, /* Original name: dm_ret_replay */
    /* 100 */ dm_ret_end = 100, /* Original name: dm_ret_end */
} DmMainCnt;

#endif
