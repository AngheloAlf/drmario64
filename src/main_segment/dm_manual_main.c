/**
 * Original filename: dm_manual_main.c
 */

#include "dm_manual_main.h"

#include "libultra.h"
#include "libc/assert.h"

#include "macros_defines.h"

#include "audio/sound.h"
#include "graphic.h"
#include "msgwnd.h"
#include "joy.h"
#include "main1x.h"
#include "tex_func.h"
#include "main_story.h"
#include "nnsched.h"
#include "static.h"
#include "dm_virus_init.h"
#include "util.h"

#if VERSION_US || VERSION_GW || CC_CHECK
#include "aiset.h"
#endif

#define STRUCT_WATCHGAME_MANUAL_UNK_LEN 3
#define STRUCT_WATCHGAME_MANUAL_UNK_LEN2 4

/* Original name: STutolWnd */
typedef struct STutolWnd {
    /* 0x00 */ s32 x;                                /* Original name: pos[2] */
    /* 0x04 */ s32 y;                                /* Original name: pos[2] */
    /* 0x08 */ f32 alpha; /* Original name: alpha */ // 0.0f ~ 1.0f
    /* 0x0C */ f32 alphaStep;                        /* Original name: alphaStep */
    /* 0x10 */ MessageWnd messageWnd;                /* Original name: msgWnd */
} STutolWnd;                                         // size = 0x90

typedef struct BigVirusPos {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x4 */ s32 unk_8;
} BigVirusPos; // size = 0xC

typedef struct AttackCapsel {
    /* 0x0 */ s8 pos_a_x;         /* Original name: pos_a_x */
    /* 0x0 */ s8 pos_a_y;         /* Original name: pos_a_y */
    /* 0x0 */ s8 capsel_a_p;      /* Original name: capsel_a_p */
    /* 0x0 */ s8 capsel_a_flg[3]; /* Original name: capsel_a_flg */
} AttackCapsel;                   // size = 0x6

typedef struct BigVirusFlg {
    /* 0x0 */ bool unk_0;
    /* 0x4 */ bool unk_4;
} BigVirusFlg; // size = 0x8

typedef enum WatchManualMode {
    /*   0 */ WATCHMANUALMODE_0,
    /*   1 */ WATCHMANUALMODE_1,
    /*  10 */ WATCHMANUALMODE_10 = 10,
    /*  20 */ WATCHMANUALMODE_20 = 20,
    /*  21 */ WATCHMANUALMODE_21,
    /*  30 */ WATCHMANUALMODE_30 = 30,
    /*  40 */ WATCHMANUALMODE_40 = 40,
    /*  41 */ WATCHMANUALMODE_41,
    /*  42 */ WATCHMANUALMODE_42,
    /*  43 */ WATCHMANUALMODE_43,
    /*  50 */ WATCHMANUALMODE_50 = 50,
    /*  51 */ WATCHMANUALMODE_51,
    /*  52 */ WATCHMANUALMODE_52,
    /*  53 */ WATCHMANUALMODE_53,
    /*  60 */ WATCHMANUALMODE_60 = 60,
    /*  61 */ WATCHMANUALMODE_61,
    /*  62 */ WATCHMANUALMODE_62,
    /*  63 */ WATCHMANUALMODE_63,
    /*  64 */ WATCHMANUALMODE_64,
    /*  70 */ WATCHMANUALMODE_70 = 70,
    /*  71 */ WATCHMANUALMODE_71,
    /*  72 */ WATCHMANUALMODE_72,
    /*  73 */ WATCHMANUALMODE_73,
    /*  74 */ WATCHMANUALMODE_74,
    /*  80 */ WATCHMANUALMODE_80 = 80,
    /*  81 */ WATCHMANUALMODE_81,
    /*  90 */ WATCHMANUALMODE_90 = 90,
    /*  91 */ WATCHMANUALMODE_91,
    /* 100 */ WATCHMANUALMODE_100 = 100,
    /* 110 */ WATCHMANUALMODE_110 = 110,
    /* 120 */ WATCHMANUALMODE_120 = 120,
    /* 130 */ WATCHMANUALMODE_130 = 130,
    /* 140 */ WATCHMANUALMODE_140 = 140,
    /* 150 */ WATCHMANUALMODE_150 = 150,

    /* 777 */ MODE_CAPSEL_PROC = 777, /* Original name: MODE_CAPSEL_PROC */
    /* 778 */ MODE_WAIT_MESSAGE,      /* Original name: MODE_WAIT_MESSAGE */
    /* 779 */ MODE_WAIT_CAPSEL_FALL,  /* Original name: MODE_WAIT_CAPSEL_FALL */
    /* 780 */ MODE_EXIT,              /* Original name: MODE_EXIT */
} WatchManualMode;

typedef struct struct_watchManual {
    /* 0x000 */ s32 pino_dir;                                               /* Original name: pino_dir */
    /* 0x004 */ s32 pino_pos_x;                                             /* Original name: pino_pos[2] */
    /* 0x008 */ s32 pino_pos_y;                                             /* Original name: pino_pos[2] */
    /* 0x00C */ s32 fade_count;                                             /* Original name: fade_count */
    /* 0x010 */ s32 fade_step;                                              /* Original name: fade_step */
    /* 0x014 */ s32 bgm_timer;                                              /* Original name: bgm_timer */
    /* 0x018 */ s32 bgm_timeout;                                            /* Original name: bgm_timeout */
    /* 0x01C */ s32 key_flash_count[STRUCT_WATCHGAME_MANUAL_UNK_LEN2];      /* Original name: key_flash_count */
    /* 0x02C */ s32 logo_timer;                                             /* Original name: logo_timer */
    /* 0x030 */ s32 capsel_flow; /* Original name: capsel_flow */           // TODO: enum?
    /* 0x034 */ STutolWnd msgWnd;                                           /* Original name: msgWnd */
    /* 0x0C4 */ BigVirusPos big_virus_pos[STRUCT_WATCHGAME_MANUAL_UNK_LEN]; /* Original name: big_virus_pos */
    /* 0x0E8 */ AttackCapsel attack_cap[4][4];                              /* Original name: attack_cap */
    /* 0x148 */ u8 big_virus_count[3]; /* Original name: big_virus_count */ // rgb colors
    /* 0x14C */ BigVirusFlg big_virus_flg[STRUCT_WATCHGAME_MANUAL_UNK_LEN]; /* Original name: big_virus_flg */
    /* 0x164 */ WatchManualMode mode;                                       /* Original name: mode */
    /* 0x168 */ WatchManualMode next_mode;                                  /* Original name: next_mode */
    /* 0x16C */ s32 mode_stop_flg;                                          /* Original name: mode_stop_flg */
    /* 0x170 */ s32 last3_flg;                                              /* Original name: last3_flg */
    /* 0x174 */ s32 attack_cap_count[4];                                    /* Original name: attack_cap_count */
    /* 0x184 */ s32 animeCount;                                             /* Original name: animeCount */
} struct_watchManual;                                                       // size = 0x188

/**
 * Original name: watchManual
 */
struct_watchManual *watchManual;

/**
 * Original name: _texAll
 */
static struct TiTexData *_texAll;
/**
 * Original name: _texKaSa
 */
static struct TiTexData *_texKaSa;

/**
 * Original name: tutolWnd_setPos
 */
void tutolWnd_setPos(STutolWnd *wnd, s32 x, s32 y) {
    wnd->x = x;
    wnd->y = y;
    wnd->messageWnd.posX = x + 8;
    wnd->messageWnd.posY = y + 8;
}

/**
 * Original name: tutolWnd_setAlpha
 */
void tutolWnd_setAlpha(void) {
}

#if VERSION_US || VERSION_GW
#define TUTOLWND_INIT_ROW_STEP 0xD
#elif VERSION_CN
#define TUTOLWND_INIT_ROW_STEP 0xE
#endif

/**
 * Original name: tutolWnd_init
 */
void tutolWnd_init(STutolWnd *wnd, void **heapP) {
    wnd->alpha = 0;
    wnd->alphaStep = (-1 / 16.0f);
    msgWnd_init(&wnd->messageWnd, heapP, 13, 4, 32, 32);
    wnd->messageWnd.fntW = 0xA;
    wnd->messageWnd.fntH = 0xC;
    wnd->messageWnd.colStep = 5;
    wnd->messageWnd.rowStep = TUTOLWND_INIT_ROW_STEP;
    wnd->messageWnd.msgSpeed = 1.0f / 6.0f;
    tutolWnd_setPos(wnd, 32, 32);
}

/**
 * Original name: tutolWnd_update
 */
void tutolWnd_update(STutolWnd *wnd) {
    wnd->alpha = CLAMP(wnd->alpha + wnd->alphaStep, 0.0f, 1.0f);

    if (wnd->alpha == DOUBLE_LITERAL(1)) {
        msgWnd_update(&wnd->messageWnd);
    }
}

/**
 * Original name: tutolWnd_draw
 */
void tutolWnd_draw(STutolWnd *wnd, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    s32 alpha = wnd->alpha * 255.0f;
    TiTexData *texC;

    if (alpha == 0) {
        return;
    }

    gSPDisplayList(gfx++, normal_texture_init_dl);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (alpha < 0xFF) {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);

    texC = &_texAll[8];
    tiStretchTexBlock(&gfx, texC, false, wnd->x, wnd->y, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT]);

    if (wnd->alpha != 0.0f) {
        wnd->messageWnd.alpha = alpha;
        msgWnd_draw(&wnd->messageWnd, &gfx);
    }

    *gfxP = gfx;
}

/**
 * Original name: tutolWnd_clear
 */
void tutolWnd_clear(STutolWnd *wnd) {
    msgWnd_clear(&wnd->messageWnd);
}

/**
 * Original name: tutolWnd_addStr
 */
void tutolWnd_addStr(STutolWnd *wnd, const char *str) {
    msgWnd_addStr(&wnd->messageWnd, str);
}

/**
 * Original name: tutolWnd_fadeIn
 */
void tutolWnd_fadeIn(STutolWnd *wnd) {
    if (wnd->alphaStep < 0.0f) {
        wnd->alphaStep = -wnd->alphaStep;
    }
}

/**
 * Original name: tutolWnd_fadeOut
 */
void tutolWnd_fadeOut(STutolWnd *wnd) {
    if (wnd->alphaStep > 0.0f) {
        wnd->alphaStep = -wnd->alphaStep;
    }
}

/**
 * Original name: tutolWnd_isEnd
 */
bool tutolWnd_isEnd(const STutolWnd *wnd) {
    return msgWnd_isEnd(&wnd->messageWnd);
}

/**
 * Original name: tutolWnd_isSpeaking
 */
bool tutolWnd_isSpeaking(const STutolWnd *wnd) {
    return msgWnd_isSpeaking(&wnd->messageWnd);
}

/**
 * Original name: dm_manual_set_attack_capsel
 */
void dm_manual_set_attack_capsel(AttackCapsel *cap, s32 pos_x, s32 color) {
    cap->pos_a_x = pos_x;
    cap->pos_a_y = 1;
    cap->capsel_a_p = color;
    cap->capsel_a_flg[0] = 1;
}

const s32 RO_800B2408[] = { 0xC8, 0x28 };

const s32 RO_800B2410[] = { 0x6C, 0x28 };

const s32 RO_800B2418[] = { 0x24, 0x28 };

const s32 RO_800B2420[] = { 0xB4, 0x28 };

const s32 RO_800B2428[] = { 0xD8, 0x70 };

const s32 RO_800B2430[] = { 0x7C, 0x70 };

const s32 RO_800B2438[] = { 0x34, 0x70 };

const s32 RO_800B2440[] = { 0xC4, 0x70 };

const u8 virus_1_1[][3] = {
    { 1, 1, 0x10 }, { 2, 2, 0xD }, { 2, 2, 0xE }, { 0, 5, 0xF }, { 0, 1, 6 }, { 0, 5, 6 },
    { 2, 0, 6 },    { 2, 4, 6 },   { 1, 2, 6 },   { 1, 3, 6 },   { 1, 6, 6 }, { 1, 7, 6 },
};

const u8 RO_800B246C[] = { 0x12, 0x20, 0, 0x10, 0x21 };

const u8 RO_800B2474[] = { 0x21, 0x10, 0x20, 0, 0x21 };

const u8 position_1_1[][4] = {
    { 3, 5, 1, 0 },
    { 3, 3, 0, 0 },
    { 3, 2, 0, 0 },
    { 3, 1, 0, 0 },
};

const u8 virus_2_1[][3] = {
    { 0, 0, 0xE }, { 0, 2, 0xA }, { 0, 2, 0xB }, { 0, 5, 8 },    { 0, 5, 9 },    { 0, 6, 0xC }, { 0, 6, 0xE },
    { 2, 3, 0xE }, { 2, 4, 7 },   { 2, 4, 8 },   { 2, 5, 0xB },  { 2, 5, 0xC },  { 2, 5, 0xE }, { 2, 5, 0xF },
    { 1, 1, 7 },   { 1, 1, 0xA }, { 1, 1, 0xB }, { 1, 1, 0x10 }, { 1, 2, 0x10 }, { 1, 7, 0xF },
};

const u8 capsel_2_1[] = {
    0x21, 0x02, 0x10, 0x12, 0x21, 0x00, 0x01, 0x20, 0x21, 0x12, 0x10, 0x10,
};

const u8 position_2_1[][4] = {
    { 4, 6, 0, 0 },   { 4, 5, 0, 1 }, { 7, 0xE, 1, 0 }, { 6, 0xB, 0, 1 }, { 5, 0xD, 0, 0 },
    { 0, 0xD, 1, 0 }, { 0, 9, 0, 0 }, { 3, 0xD, 1, 0 }, { 2, 9, 0, 1 },   { 1, 8, 0, 0 },
};

const u8 virus_3_1[][3] = {
    { 0, 0, 0xC }, { 0, 1, 0xD }, { 0, 1, 0xF }, { 0, 4, 0xF }, { 0, 6, 0xD },  { 0, 6, 8 },    { 0, 7, 0x10 },
    { 2, 3, 8 },   { 2, 3, 9 },   { 2, 3, 0xB }, { 2, 3, 0xC }, { 2, 7, 0xE },  { 2, 7, 0xF },  { 1, 1, 0x10 },
    { 1, 2, 8 },   { 1, 2, 0xC }, { 1, 4, 0xD }, { 1, 4, 0xE }, { 1, 4, 0x10 }, { 1, 5, 0x10 },
};

const u8 capsel_3_1[] = {
    0x12, 0x22, 0x12, 0, 0x10, 2, 0x21, 0, 0x12, 1, 0,
};

const u8 position_3_1[][4] = {
    { 4, 0xC, 0, 0 }, { 3, 0xA, 0, 0 }, { 1, 0xB, 0, 1 }, { 1, 0xA, 1, 0 },  { 2, 0xA, 1, 0 },
    { 6, 0xC, 0, 0 }, { 6, 0xB, 0, 1 }, { 6, 0xA, 1, 0 }, { 2, 0x10, 1, 1 }, { 3, 0x10, 1, 0 },
};

const u8 virus_4_1[][3] = {
    { 0, 0, 0xD }, { 0, 2, 7 },   { 0, 5, 0xA }, { 0, 5, 0xB }, { 0, 7, 0x10 }, { 2, 2, 0xE },
    { 2, 2, 0xF }, { 2, 3, 0xA }, { 2, 3, 0xD }, { 2, 5, 8 },   { 1, 1, 0xD },  { 1, 4, 8 },
    { 1, 4, 9 },   { 1, 5, 0xE }, { 1, 5, 0xF }, { 1, 6, 0xA },
};

const u8 capsel_4_1[] = {
    0x10, 0x11, 0x20, 1, 0x12, 0x20, 1, 0x10, 0, 0x20, 0, 0x21, 1, 0x20, 0x22, 0, 0x10,
};

const u8 position_4_1[][4] = {
    { 4, 7, 1, 0 },   { 5, 7, 0, 1 },   { 5, 6, 1, 0 },   { 5, 8, 0, 0 },   { 5, 7, 0, 1 },   { 3, 0xC, 1, 0 },
    { 0, 0xC, 0, 0 }, { 1, 0xB, 1, 0 }, { 0, 0xB, 1, 0 }, { 2, 0xD, 1, 0 }, { 7, 0xF, 1, 0 }, { 6, 0xD, 0, 0 },
    { 2, 6, 0, 0 },   { 3, 5, 1, 0 },   { 3, 3, 0, 0 },   { 2, 5, 1, 0 },
};

#include "dm_manual_main.msg.inc"

/**
 * Original name: dm_manual_attack_capsel_down
 */
void dm_manual_attack_capsel_down(void) {
    struct_watchManual *watchManualP = watchManual;
    s32 i;
    bool playSound = false;

    for (i = 0; i < 4; i++) {
        watchManualP->attack_cap_count[i]++;
        if (watchManualP->attack_cap_count[i] >= 0xE) {
            s32 j;

            watchManualP->attack_cap_count[i] = 0;

            for (j = 0; j < 4; j++) {
                if (watchManualP->attack_cap[i][j].capsel_a_flg[0] == 0) {
                    continue;
                }

                if (get_map_info(game_map_data[i], watchManualP->attack_cap[i][j].pos_a_x,
                                 watchManualP->attack_cap[i][j].pos_a_y + 1)) {
                    set_map(game_map_data[i], watchManualP->attack_cap[i][j].pos_a_x,
                            watchManualP->attack_cap[i][j].pos_a_y, 4, watchManualP->attack_cap[i][j].capsel_a_p);
                    watchManualP->attack_cap[i][j].capsel_a_flg[0] = 0;
                } else {
                    playSound = true;

                    if (watchManualP->attack_cap[i][j].pos_a_y < 0x10) {
                        watchManualP->attack_cap[i][j].pos_a_y++;
                    }

                    if (watchManualP->attack_cap[i][j].pos_a_y == 0x10) {
                        set_map(game_map_data[i], watchManualP->attack_cap[i][j].pos_a_x, 0x10, 4,
                                watchManualP->attack_cap[i][j].capsel_a_p);
                        watchManualP->attack_cap[i][j].capsel_a_flg[0] = 0;
                    }
                }
            }
        }
    }

    if (playSound) {
        SND_PLAY_INDEX(SND_INDEX_55);
    }
}

/**
 * Original name: dm_manual_effect_cnt
 */
void dm_manual_effect_cnt(struct_game_state_data *state, GameMapCell *mapCells, s32 arg2 UNUSED) {
    if ((state->unk_014 != GAMESTATEDATA_UNK_014_1) && (state->unk_014 != GAMESTATEDATA_UNK_014_D)) {
        dm_black_up(state, mapCells);
    }
}

/**
 * Original name: dm_manual_update_virus_anime
 */
void dm_manual_update_virus_anime(struct_game_state_data *state) {
    s32 i;

    for (i = 0; i < ANIMES_COUNT; i++) {
        animeState_update(get_virus_anime_state(i));
        animeSmog_update(get_virus_smog_state(i));
    }

    dm_calc_big_virus_pos(state);
}

/**
 * Original name: dm_manual_main_cnt
 */
DmManualMainCntRet dm_manual_main_cnt(struct_game_state_data *state, GameMapCell *mapCells, u8 player_no,
                                      s32 arg3 UNUSED) {
    struct_watchManual *st = watchManual;
    s32 i;
    s32 out;

    switch (state->unk_00C) {
        case GAMESTATEDATA_UNK_00C_1:
        case GAMESTATEDATA_UNK_00C_2:
            return dm_ret_virus_wait;

        case GAMESTATEDATA_UNK_00C_4:
            dm_capsel_down(state, mapCells);
            break;

        case GAMESTATEDATA_UNK_00C_5:
            if (dm_check_game_over(state, mapCells)) {
                state->unk_014 = GAMESTATEDATA_UNK_014_4;
                state->unk_00C = GAMESTATEDATA_UNK_00C_B;
                return dm_ret_game_over;
            }

            if (dm_h_erase_chack(mapCells) || dm_w_erase_chack(mapCells)) {
                if (state->unk_049 == 0) {
                    state->unk_00C = GAMESTATEDATA_UNK_00C_6;
                } else {
                    state->unk_00C = GAMESTATEDATA_UNK_00C_15;
                }
                state->unk_02F = 0;
            } else if (state->unk_049 == 0) {
                state->unk_00C = GAMESTATEDATA_UNK_00C_9;
            } else {
                state->unk_00C = GAMESTATEDATA_UNK_00C_16;
            }
            break;

        case GAMESTATEDATA_UNK_00C_6:
            state->unk_02F++;
            if (state->unk_02F >= 0x12U) {
                state->unk_02F = 0;
                state->unk_00C = GAMESTATEDATA_UNK_00C_7;
                dm_h_erase_chack_set(state, mapCells);
                dm_w_erase_chack_set(state, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);
                state->unk_025 = get_virus_color_count(mapCells, &st->big_virus_count[0], &st->big_virus_count[1],
                                                       &st->big_virus_count[2]);

                switch (evs_manual_no) {
                    case EVS_MANUAL_NO_0:
                    case EVS_MANUAL_NO_3:
                        for (i = 0; i < ARRAY_COUNT(st->big_virus_flg); i++) {
                            if (st->big_virus_count[i] == 0) {
                                if (!st->big_virus_flg[i].unk_0) {
                                    st->big_virus_flg[i].unk_0 = true;
                                    animeState_set(get_virus_anime_state(i), ANIMENO_4);
                                    animeSmog_start(get_virus_smog_state(i));
                                    if (state->unk_025 != 0) {
                                        dm_snd_play(SND_INDEX_74);
                                    }
                                }
                            } else if (state->unk_03C[3] & (0x10 << i)) {
                                animeState_set(get_virus_anime_state(i), ANIMENO_2);
                                dm_snd_play(SND_INDEX_74);
                            }
                        }
                        break;

                    default:
                        break;
                }

                state->unk_03C[3] &= 0xF;

                if (state->unk_025 == 0) {
                    dm_make_score(state);
                    state->unk_014 = GAMESTATEDATA_UNK_014_3;
                    state->unk_00C = GAMESTATEDATA_UNK_00C_A;
                    return dm_ret_clear;
                }
                if (((state->unk_025 != 0) && (state->unk_025 < 4U)) && !st->last3_flg) {
                    st->last3_flg = true;
                    dm_snd_play(SND_INDEX_80);
                    dm_seq_play_in_game((evs_seqnumb * 2) | 1);
                }

                state->unk_039++;
                if (state->unk_03C[3] & 8) {
                    state->unk_03C[3] &= ~8;
                    dm_snd_play(SND_INDEX_56);
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_7:
            dm_capsel_erase_anime(state, mapCells);
            break;

        case GAMESTATEDATA_UNK_00C_8:
            go_down(state, mapCells, 0xE);
            break;

        case GAMESTATEDATA_UNK_00C_9:
            dm_attack_se(state, player_no);
            dm_warning_h_line(state, mapCells);
            aifMakeFlagSet(state);
            dm_set_capsel(state);
            dm_capsel_speed_up(state);
            state->unk_03A = 0;
            state->unk_039 = 0;
            state->unk_037 = 0;

            for (i = 0; i < ARRAY_COUNT(state->unk_03C); i++) {
                state->unk_03C[i] = 0;
            }

            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            break;

        case GAMESTATEDATA_UNK_00C_A:
            st->logo_timer++;
            if (st->logo_timer > 120) {
                st->logo_timer = 0;
                return dm_ret_next_stage;
            }
            break;

        case GAMESTATEDATA_UNK_00C_B:
        case GAMESTATEDATA_UNK_00C_D:
        case GAMESTATEDATA_UNK_00C_F:
        case GAMESTATEDATA_UNK_00C_11:
            st->logo_timer++;
            if (st->logo_timer > 120) {
                st->logo_timer = 0;
                return dm_ret_end;
            }
            break;

        case GAMESTATEDATA_UNK_00C_15:
            state->unk_02F++;
            if (state->unk_02F >= 0x12U) {
                state->unk_02F = 0;
                state->unk_00C = GAMESTATEDATA_UNK_00C_7;
                dm_h_erase_chack_set(state, mapCells);
                dm_w_erase_chack_set(state, mapCells);
                dm_h_ball_chack(mapCells);
                dm_w_ball_chack(mapCells);

                state->unk_039 += 1;
                if (state->unk_03C[3] & 8) {
                    state->unk_03C[3] &= ~8;
                } else {
                    dm_snd_play(SND_INDEX_61);
                }
            }
            break;

        case GAMESTATEDATA_UNK_00C_16:
            dm_attack_se(state, player_no);
            dm_warning_h_line(state, mapCells);

            out = true;
            //! @bug reading i non initialized
            if ((game_state_data[i].unk_04A != 0) && dm_broken_set(state, mapCells)) {
                state->unk_00C = GAMESTATEDATA_UNK_00C_8;
                out = false;
            }
            if (out) {
                dm_set_capsel(state);
                dm_capsel_speed_up(state);
                state->unk_03A = 0;
                state->unk_039 = 0;
                state->unk_037 = 0;

                for (i = 0; i < ARRAY_COUNT(state->unk_03C); i++) {
                    state->unk_03C[i] = 0;
                }

                state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            }
            break;

        default:
            break;
    }

    return dm_ret_null;
}

/**
 * Original name: dm_manual_make_key
 */
void dm_manual_make_key(struct_game_state_data *state, GameMapCell *mapCells) {
    struct_watchManual *st = watchManual;
    struct_game_state_data_unk_178 *cap = &state->unk_178;
    u16 key;

    aifKeyOut(state);

    key = joygam[state->unk_04B];

    if (key & B_BUTTON) {
        rotate_capsel(mapCells, cap, -1);
        st->key_flash_count[3] = 8;
    } else if (key & CONT_A) {
        rotate_capsel(mapCells, cap, 1);
        st->key_flash_count[2] = 8;
    }

    if (key & L_JPAD) {
        translate_capsel(mapCells, state, -1, main_joy[state->unk_04B]);
        st->key_flash_count[0] = 8;
    } else if (key & R_JPAD) {
        translate_capsel(mapCells, state, 1, main_joy[state->unk_04B]);
        st->key_flash_count[1] = 8;
    }

    state->unk_030 = 1;
    if ((key & D_JPAD) && (cap->pos_y[0] > 0)) {
        s32 temp_v1;

        temp_v1 = FallSpeed[state->unk_02D];
        temp_v1 = (temp_v1 >> 1) + (temp_v1 & 1);
        state->unk_030 = temp_v1;
    }
}

/**
 * Original name: dm_manual_1_main
 */
bool dm_manual_1_main(void) {
    struct_watchManual *st = watchManual;
    bool res = true;
    GameMapCell *mapCells = game_map_data[0];
    struct_game_state_data *state = game_state_data;
    struct_game_state_data_unk_178 *cap = &state->unk_178;
    DmManualMainCntRet ret;
    s32 i;

#if PRESERVE_UB
    ret = dm_ret_null;
#endif

    for (i = 0; i < ARRAY_COUNTU(st->key_flash_count); i++) {
        if (st->key_flash_count[i] != -0x14) {
            st->key_flash_count[i]--;
        }
    }

    if (st->mode_stop_flg != 0) {
        ret = dm_manual_main_cnt(state, mapCells, 0, 0);
        dm_manual_make_key(state, mapCells);
    }

    dm_manual_effect_cnt(state, mapCells, 0);

    dm_virus_anime(state, mapCells);
    dm_manual_update_virus_anime(state);
    dm_warning_h_line_se();

    switch (st->mode) {
        case WATCHMANUALMODE_0:
            tutolWnd_setPos(&st->msgWnd, RO_800B2408[0], RO_800B2408[1]);
            st->pino_dir = 1;
            st->pino_pos_x = RO_800B2428[0];
            st->pino_pos_y = RO_800B2428[1];

            tutolWnd_fadeOut(&st->msgWnd);

            st->mode++; // WATCHMANUALMODE_1

            for (i = 0; i < ARRAY_COUNTU(RO_800B246C); i++) {
                CapsMagazine[i + 1] = RO_800B246C[i];
            }

            state->unk_032 = 1;
            dm_set_capsel(state);
            break;

        case WATCHMANUALMODE_1:
            set_virus(mapCells, virus_1_1[state->unk_025][1], virus_1_1[state->unk_025][2],
                      virus_1_1[state->unk_025][0], virus_anime_table[virus_1_1[state->unk_025][0]][state->unk_027]);

            state->unk_025++;
            if (state->unk_025 >= 4U) {
                st->mode = WATCHMANUALMODE_10;
            }
            break;

        case WATCHMANUALMODE_10:
            tutolWnd_fadeIn(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_1);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_20;
            break;

        case WATCHMANUALMODE_20:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_2);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_30;
            break;

        case WATCHMANUALMODE_30:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_3);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_40;

            break;

        case WATCHMANUALMODE_40:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_4);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_41;
            break;

        case WATCHMANUALMODE_41:
            st->mode_stop_flg = 1;
            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            aifMake2(state, 3, 0xC, 0, 0);
            st->mode++; // WATCHMANUALMODE_42
            break;

        case WATCHMANUALMODE_42:
            state->unk_030 = 1;

            switch (cap->pos_y[0]) {
                case 0x4:
                    if (cap->pos_y[0] == cap->pos_y[1]) {
                        rotate_capsel(mapCells, cap, -1);
                        st->key_flash_count[3] = 8;
                    }
                    break;

                case 0x6:
                    if (cap->pos_y[0] != cap->pos_y[1]) {
                        rotate_capsel(mapCells, cap, -1);
                        st->key_flash_count[3] = 8;
                    }
                    break;

                case 0x8:
                    if (cap->pos_y[0] == cap->pos_y[1]) {
                        rotate_capsel(mapCells, cap, 1);
                        st->key_flash_count[2] = 8;
                    }
                    break;

                case 0xA:
                    if (cap->pos_y[0] != cap->pos_y[1]) {
                        rotate_capsel(mapCells, cap, 1);
                        st->key_flash_count[2] = 8;
                    }
                    break;

                case 0xC:
                    aifMakeFlagSet(state);
                    aifMake2(state, 4, 0xE, 0, 0);
                    st->mode++; // WATCHMANUALMODE_43
                    break;
            }
            break;

        case WATCHMANUALMODE_43:
            if (state->unk_23D == 0) {
                st->mode = WATCHMANUALMODE_50;
            }
            break;

        case WATCHMANUALMODE_50:
            st->mode_stop_flg = 0;
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_5);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_51;
            break;

        case WATCHMANUALMODE_51:
            st->mode_stop_flg = 1;
            aifMake2(state, 2, 0xC, 1, 0);
            st->mode++; // WATCHMANUALMODE_52
            break;

        case WATCHMANUALMODE_52:
            if (state->unk_23D == 0) {
                aifMake2(state, 5, 0xD, 1, 0);
                st->mode++; // WATCHMANUALMODE_53
            }
            break;

        case WATCHMANUALMODE_53:
            if (state->unk_23D == 0) {
                st->mode = WATCHMANUALMODE_60;
            }
            break;

        case WATCHMANUALMODE_60:
            st->mode_stop_flg = 0;
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_6);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_61;
            break;

        case WATCHMANUALMODE_61:
            st->mode_stop_flg = 1;
            aifMake2(state, 2, 0x10, 0, 0);
            st->mode++; // WATCHMANUALMODE_62
            break;

        case WATCHMANUALMODE_62:
            if (ret == dm_ret_clear) {
                dm_seq_play(SEQ_INDEX_14);
                st->bgm_timer = 0;
                st->bgm_timeout = 120;
                st->mode++; // WATCHMANUALMODE_63
            }
            break;

        case WATCHMANUALMODE_63:
            if (ret == dm_ret_next_stage) {
                clear_map_all(mapCells);
                st->mode++; // WATCHMANUALMODE_64

                state->unk_026 = 0xF;
                _dm_virus_init(0, state, virus_map_data[0], virus_map_disp_order[0], 1);

                for (i = 0; i < 3; i++) {
                    animeState_set(get_virus_anime_state(i), ANIMENO_0);
                    animeSmog_stop(get_virus_smog_state(i));
                }

                for (i = 0; i < ARRAY_COUNTU(RO_800B2474); i++) {
                    CapsMagazine[i + 1] = RO_800B2474[i];
                }

                state->unk_032 = 1;
                dm_set_capsel(state);

                state->unk_00C = GAMESTATEDATA_UNK_00C_1;
                state->unk_014 = GAMESTATEDATA_UNK_014_2;
                state->unk_025 = 0;
            }
            break;

        case WATCHMANUALMODE_64:
            i = virus_map_disp_order[0][state->unk_025];

            set_virus(mapCells, virus_map_data[0][i].x_pos, virus_map_data[0][i].y_pos, virus_map_data[0][i].virus_type,
                      virus_anime_table[virus_map_data[0][i].virus_type][state->unk_027]);

            state->unk_025++;

            if (state->unk_025 >= dm_get_first_virus_count(evs_gamemode, state)) {
                st->mode = WATCHMANUALMODE_70;
            }
            break;

        case WATCHMANUALMODE_70:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_7);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_71;
            break;

        case WATCHMANUALMODE_71:
            st->mode_stop_flg = 1;
            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            aifMakeFlagSet(state);
            st->mode++; // WATCHMANUALMODE_72
            break;

        case WATCHMANUALMODE_72:
            i = state->unk_032 - 2;
            if (i < 4U) {
                aifMake2(state, position_1_1[i][0], position_1_1[i][1], position_1_1[i][2], position_1_1[i][3]);
            } else {
                st->mode++; // WATCHMANUALMODE_73
            }
            break;

        case WATCHMANUALMODE_73:
            if (ret == dm_ret_game_over) {
                dm_seq_play(SEQ_INDEX_17);
                st->mode++; // WATCHMANUALMODE_74
            }
            break;

        case WATCHMANUALMODE_74:
            if (ret == dm_ret_end) {
                st->mode = WATCHMANUALMODE_80;
            }
            break;

        case WATCHMANUALMODE_80:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_1_8);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = MODE_EXIT;
            break;

        case MODE_WAIT_MESSAGE:
            if (tutolWnd_isEnd(&st->msgWnd)) {
                st->mode = st->next_mode;
            }
            break;

        case MODE_EXIT:
            res = false;
            break;

        default:
            break;
    }

    return res;
}

/**
 * Original name: dm_manual_2_main
 */
bool dm_manual_2_main(void) {
    struct_watchManual *st = watchManual;
    struct_game_state_data *state = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    bool res = true;
    s32 i;

    if (st->mode_stop_flg != 0) {
        dm_manual_main_cnt(state, game_map_data[0], 0, 1);
        dm_manual_main_cnt(&state[1], game_map_data[1], 1, 1);
        dm_manual_make_key(state, game_map_data[0]);
    }

    dm_manual_effect_cnt(state, game_map_data[0], 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 2; i++) {
        dm_virus_anime(&state[i], game_map_data[i]);
    }

    dm_warning_h_line_se();

    switch (st->mode) {
        case WATCHMANUALMODE_0:
            tutolWnd_setPos(&st->msgWnd, RO_800B2410[0], RO_800B2410[1]);
            st->pino_dir = 1;
            st->pino_pos_x = RO_800B2430[0];
            st->pino_pos_y = RO_800B2430[1];
            tutolWnd_fadeOut(&st->msgWnd);
            st->mode = WATCHMANUALMODE_1;

            for (i = 0; i < ARRAY_COUNTU(capsel_2_1); i++) {
                CapsMagazine[i + 1] = capsel_2_1[i];
            }
            state->unk_032 = 1;
            dm_set_capsel(state);
            break;

        case WATCHMANUALMODE_1:
            set_virus(mapCells, virus_2_1[state->unk_025][1], virus_2_1[state->unk_025][2],
                      virus_2_1[state->unk_025][0], virus_anime_table[virus_2_1[state->unk_025][0]][state->unk_027]);

            state->unk_025++;
            if (state->unk_025 >= 0x14U) {
                st->mode = WATCHMANUALMODE_10;
            }
            break;

        case WATCHMANUALMODE_10:
            tutolWnd_fadeIn(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_1);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_20;
            break;

        case WATCHMANUALMODE_20:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_2);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_30;
            break;

        case WATCHMANUALMODE_30:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_3);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_40;
            break;

        case WATCHMANUALMODE_40:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_4);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_50;
            break;

        case WATCHMANUALMODE_50:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_5);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_60;
            break;

        case WATCHMANUALMODE_60:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_6);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_61;
            break;

        case WATCHMANUALMODE_61:
            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_70;
            break;

        case WATCHMANUALMODE_70:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_7);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_71;
            break;

        case WATCHMANUALMODE_71:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_80;
            break;

        case WATCHMANUALMODE_80:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_81;
            break;

        case WATCHMANUALMODE_81:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_8);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_90;
            break;

        case WATCHMANUALMODE_90:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_2_9);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = MODE_EXIT;
            break;

        case MODE_CAPSEL_PROC:
            st->mode_stop_flg = 1;
            i = state->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_2_1)) {
                aifMake2(state, position_2_1[i][0], position_2_1[i][1], position_2_1[i][2], position_2_1[i][3]);
            }

            switch (st->capsel_flow) {
                case 0:
                    if (i == 2) {
                        dm_manual_set_attack_capsel(st->attack_cap[1], 2, 2);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][1], 6, 0);
                        st->attack_cap_count[1] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow++;
                    }
                    break;

                case 1:
                    if (i == 5) {
                        dm_manual_set_attack_capsel(st->attack_cap[1], 2, 2);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][1], 4, 0);

                        dm_manual_set_attack_capsel(&st->attack_cap[1][2], 6, 1);
                        st->attack_cap_count[1] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow++;
                    }
                    break;

                case 2:
                    if (i == 0xA) {
                        dm_manual_set_attack_capsel(st->attack_cap[1], 1, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][1], 3, 1);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][2], 5, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][3], 7, 2);
                        st->attack_cap_count[1] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow++;
                    }
                    break;
            }
            break;

        case MODE_WAIT_MESSAGE:
            st->mode_stop_flg = 0;
            if (tutolWnd_isEnd(&st->msgWnd)) {
                st->mode = st->next_mode;
            }
            break;

        case MODE_WAIT_CAPSEL_FALL:
            st->mode_stop_flg = 0;
            if (st->attack_cap[1][1].capsel_a_flg[0] == 0) {
                st->mode = st->next_mode;
            }
            break;

        case MODE_EXIT:
            res = false;
            break;

        default:
            break;
    }

    return res;
}

/**
 * Original name: dm_manual_3_main
 */
bool dm_manual_3_main(void) {
    struct_game_state_data *state = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    struct_watchManual *st = watchManual;
    bool res = true;
    s32 i;

    if (st->mode_stop_flg != 0) {
        dm_manual_main_cnt(state, mapCells, 0, 2);

        for (i = 1; i < 3; i++) {
            dm_manual_main_cnt(&state[i], game_map_data[i], i, 2);
        }

        dm_manual_make_key(state, mapCells);
    }

    dm_manual_effect_cnt(state, mapCells, 0);
    dm_manual_attack_capsel_down();

    for (i = 0; i < 4; i++) {
        dm_virus_anime(&game_state_data[i], game_map_data[i]);
    }

    dm_warning_h_line_se();

    switch (st->mode) {
        case WATCHMANUALMODE_0:
            tutolWnd_setPos(&st->msgWnd, RO_800B2420[0], RO_800B2420[1]);
            st->pino_dir = 1;
            st->pino_pos_x = RO_800B2440[0];
            st->pino_pos_y = RO_800B2440[1];
            tutolWnd_fadeOut(&st->msgWnd);
            st->mode = WATCHMANUALMODE_1;

            for (i = 0; i < ARRAY_COUNTU(capsel_3_1); i++) {
                CapsMagazine[i + 1] = capsel_3_1[i];
            }

            state->unk_032 = 1;
            dm_set_capsel(state);
            break;

        case WATCHMANUALMODE_1:
            set_virus(mapCells, virus_3_1[state->unk_025][1], virus_3_1[state->unk_025][2],
                      virus_3_1[state->unk_025][0], virus_anime_table[virus_3_1[state->unk_025][0]][state->unk_027]);

            state->unk_025++;
            if (state->unk_025 >= 0x14U) {
                st->mode = WATCHMANUALMODE_10;
            }
            break;

        case WATCHMANUALMODE_10:
            tutolWnd_fadeIn(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_1);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_20;
            break;

        case WATCHMANUALMODE_20:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_2);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_30;
            break;

        case WATCHMANUALMODE_30:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_3);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_40;
            break;

        case WATCHMANUALMODE_40:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_4);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_50;
            break;

        case WATCHMANUALMODE_50:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_5);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_60;
            break;

        case WATCHMANUALMODE_60:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_6);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_61;
            break;

        case WATCHMANUALMODE_61:
            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_70;
            break;

        case WATCHMANUALMODE_70:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_7);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_71;
            break;

        case WATCHMANUALMODE_71:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_80;
            break;

        case WATCHMANUALMODE_80:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_8);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_81;
            break;

        case WATCHMANUALMODE_81:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_90;
            break;

        case WATCHMANUALMODE_90:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_9);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_91;
            break;

        case WATCHMANUALMODE_91:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_100;
            break;

        case WATCHMANUALMODE_100:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_10);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_110;
            break;

        case WATCHMANUALMODE_110:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_11);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_120;
            break;

        case WATCHMANUALMODE_120:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_12);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_130;
            break;

        case WATCHMANUALMODE_130:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_13);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_140;
            break;

        case WATCHMANUALMODE_140:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_14);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_150;
            break;

        case WATCHMANUALMODE_150:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_3_15);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = MODE_EXIT;
            break;

        case MODE_CAPSEL_PROC:
            st->mode_stop_flg = 1;
            i = state->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_3_1)) {
                aifMake2(state, position_3_1[i][0], position_3_1[i][1], position_3_1[i][2], position_3_1[i][3]);
            }

            switch (st->capsel_flow) {
                case 0x0:
                    if (i == 2) {
                        dm_manual_set_attack_capsel(st->attack_cap[1], 2, 2);
                        dm_manual_set_attack_capsel(&st->attack_cap[1][1], 6, 1);
                        st->attack_cap_count[1] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow += 1;
                    }
                    break;

                case 0x1:
                    if (i == 5) {
                        dm_manual_set_attack_capsel(st->attack_cap[2], 2, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[2][1], 6, 1);
                        st->attack_cap_count[2] = 0;

                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow += 1;
                        st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                    }
                    break;

                case 0x2:
                    if (i == 8) {
                        dm_manual_set_attack_capsel(st->attack_cap[3], 2, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[3][1], 6, 2);
                        st->attack_cap_count[3] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow += 1;
                        st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                    }
                    break;

                case 0x3:
                    if (i == 0xA) {
                        dm_manual_set_attack_capsel(st->attack_cap[2], 2, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[2][1], 6, 1);
                        st->attack_cap_count[2] = 0;
                        dm_manual_set_attack_capsel(st->attack_cap[3], 2, 0);
                        dm_manual_set_attack_capsel(&st->attack_cap[3][1], 6, 1);
                        st->attack_cap_count[3] = 0;
                        st->mode = MODE_WAIT_CAPSEL_FALL;
                        st->capsel_flow += 1;
                        st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                    }
                    break;

                default:
                    break;
            }
            break;

        case MODE_WAIT_MESSAGE:
            st->mode_stop_flg = 0;
            if (tutolWnd_isEnd(&st->msgWnd)) {
                st->mode = st->next_mode;
            }
            break;

        case MODE_WAIT_CAPSEL_FALL:
            st->mode_stop_flg = 0;
            if ((st->attack_cap[1][1].capsel_a_flg[0] == 0) && (st->attack_cap[2][1].capsel_a_flg[0] == 0) &&
                (st->attack_cap[3][1].capsel_a_flg[0] == 0)) {
                if (st->pino_dir < 0) {
                    if (st->msgWnd.alphaStep > 0.0f) {
                        st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                    } else if (st->msgWnd.alpha == 0.0f) {
                        tutolWnd_setPos(&st->msgWnd, RO_800B2420[0], RO_800B2420[1]);
                        st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                        st->pino_dir = -st->pino_dir;
                        st->pino_pos_x = RO_800B2440[0];
                        st->pino_pos_y = RO_800B2440[1];
                    }
                } else {
                    st->mode = st->next_mode;
                }
            } else {
                if ((st->msgWnd.alphaStep < 0.0f) && (st->msgWnd.alpha == 0.0f)) {
                    tutolWnd_setPos(&st->msgWnd, RO_800B2418[0], RO_800B2418[1]);
                    st->msgWnd.alphaStep = -st->msgWnd.alphaStep;
                    st->pino_dir = -st->pino_dir;
                    st->pino_pos_x = RO_800B2438[0];
                    st->pino_pos_y = RO_800B2438[1];
                }
            }
            break;

        case MODE_EXIT:
            res = false;
            break;

        default:
            break;
    }

    return res;
}

/**
 * Original name: dm_manual_4_main
 */
bool dm_manual_4_main(void) {
    struct_watchManual *st = watchManual;
    bool res = true;
    struct_game_state_data *state = game_state_data;
    GameMapCell *mapCells = game_map_data[0];
    bool j;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(st->key_flash_count); i++) {
        if (st->key_flash_count[i] != -0x14) {
            st->key_flash_count[i]--;
        }
    }

    if (st->mode_stop_flg != 0) {
        dm_manual_main_cnt(state, mapCells, 0, 0);
        dm_manual_make_key(state, mapCells);
    }
    dm_manual_effect_cnt(state, mapCells, 0);
    dm_virus_anime(state, mapCells);
    dm_manual_update_virus_anime(state);
    dm_warning_h_line_se();

    switch (st->mode) {
        case WATCHMANUALMODE_0:
            tutolWnd_setPos(&st->msgWnd, RO_800B2408[0], RO_800B2408[1]);
            st->pino_dir = 1;
            st->pino_pos_x = RO_800B2428[0];
            st->pino_pos_y = RO_800B2428[1];
            tutolWnd_fadeOut(&st->msgWnd);
            st->mode = WATCHMANUALMODE_1;

            for (i = 0; i < ARRAY_COUNTU(capsel_4_1); i++) {
                CapsMagazine[i + 1] = capsel_4_1[i];
            }

            state->unk_032 = 1;
            dm_set_capsel(state);
            break;

        case WATCHMANUALMODE_1:
            set_virus(mapCells, virus_4_1[state->unk_025][1], virus_4_1[state->unk_025][2],
                      virus_4_1[state->unk_025][0], virus_anime_table[virus_4_1[state->unk_025][0]][state->unk_027]);
            state->unk_025++;
            if (state->unk_025 >= 0x10U) {
                st->mode = WATCHMANUALMODE_10;
            }
            break;

        case WATCHMANUALMODE_10:
            tutolWnd_fadeIn(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_1);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_20;
            break;

        case WATCHMANUALMODE_20:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_2);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_21;
            break;

        case WATCHMANUALMODE_21:
            state->unk_00C = GAMESTATEDATA_UNK_00C_4;
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_30;
            break;

        case WATCHMANUALMODE_30:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_3);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_40;
            break;

        case WATCHMANUALMODE_40:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_4);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_41;
            break;

        case WATCHMANUALMODE_41:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_50;
            break;

        case WATCHMANUALMODE_50:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_5);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_51;
            break;

        case WATCHMANUALMODE_51:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_60;
            break;

        case WATCHMANUALMODE_60:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_6);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_61;
            break;

        case WATCHMANUALMODE_61:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_70;
            break;

        case WATCHMANUALMODE_70:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_7);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_71;
            break;

        case WATCHMANUALMODE_71:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_80;
            break;

        case WATCHMANUALMODE_80:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_8);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_81;
            break;

        case WATCHMANUALMODE_81:
            st->mode = MODE_CAPSEL_PROC;
            st->next_mode = WATCHMANUALMODE_90;
            break;

        case WATCHMANUALMODE_90:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_9);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = WATCHMANUALMODE_100;
            break;

        case WATCHMANUALMODE_100:
            tutolWnd_clear(&st->msgWnd);
            tutolWnd_addStr(&st->msgWnd, mes_4_10);
            st->mode = MODE_WAIT_MESSAGE;
            st->next_mode = MODE_EXIT;
            break;

        case MODE_CAPSEL_PROC:
            st->mode_stop_flg = 1;
            i = state->unk_032 - 2;
            if (i < ARRAY_COUNTU(position_4_1)) {
                aifMake2(state, position_4_1[i][0], position_4_1[i][1], position_4_1[i][2], position_4_1[i][3]);
            }

            switch (st->capsel_flow) {
                case 0x0:
                    j = i == 3;
                    break;
                case 0x1:
                    j = i == 5;
                    break;
                case 0x2:
                    j = i == 0xA;
                    break;
                case 0x3:
                    j = i == 0xC;
                    break;
                case 0x4:
                    j = i == 0xF;
                    break;
                case 0x5:
                    j = i == 0x10;
                    break;
                default:
                    j = false;
                    break;
            }

            if (j) {
                st->mode = st->next_mode;
                st->capsel_flow++;
            }
            break;

        case MODE_WAIT_MESSAGE:
            st->mode_stop_flg = 0;
            if (tutolWnd_isEnd(&st->msgWnd)) {
                st->mode = st->next_mode;
            }
            break;

        case MODE_EXIT:
            res = false;
            break;

        default:
            break;
    }

    return res;
}

/**
 * Original name: _tex_884
 */
const s32 _tex_884[][2] = {
    { 0, 2 },
    { 1, 3 },
};

/**
 * Original name: _pos_885
 */
const s32 _pos_885[][2] = {
    { 0, 0 },
    { 0, 0xC },
};

/**
 * Original name: draw_AB_guide
 */
void draw_AB_guide(s32 x_pos, s32 y_pos) {
    s32 i;

    gSPDisplayList(gGfxHead++, alpha_texture_init_dl);
    gDPSetCombineLERP(gGfxHead++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gGfxHead++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 2U; i++) {
        TiTexData *texC = &_texAll[_tex_884[i][0]];
        TiTexData *texA = &_texAll[_tex_884[i][1]];
        s32 width;

        width = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);

        StretchAlphaTexTile(&gGfxHead, width, texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX],
                            texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH], 0, 0,
                            width, texC->info[TI_INFO_IDX_HEIGHT], x_pos + _pos_885[i][0], y_pos + _pos_885[i][1],
                            width, texC->info[TI_INFO_IDX_HEIGHT]);
    }
}

const s32 RO_800B3150[] = {
    0, 1, 2, 3, 2, 1,
};

// unused
void func_80074B08(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct_watchManual *temp_s0 = watchManual;
    Gfx *gfx = *gfxP;
    Mtx *mtx = *mtxP;
    Vtx *vtx = *vtxP;
    f32 sp48[4][4];
    TiTexData *temp_s4;
    TiTexData *temp_s1;
    s32 var_s1;
    s32 var_s0;
    s32 var_s3;
    f32 temp;

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 10.0f, 1.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    mtx++;

    guTranslate(mtx, 0.0f, 0.0f, -5.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    mtx++;

    temp = WrapF(0.0f, 1.0f, temp_s0->animeCount * DOUBLE_LITERAL(1.0 / 128)) * DOUBLE_LITERAL(M_PI) * 2;
    guRotateRPYF(sp48, 0.0f, (1 - arg5) * 0x5A, sinf(temp) * 4.0f * arg5);

    var_s1 = WrapI(0, ARRAY_COUNT(RO_800B3150), ((temp_s0->animeCount & 0x7F) * 3) >> 2);
    if (tutolWnd_isSpeaking(&temp_s0->msgWnd) == false) {
        var_s1 = 0;
    }

    temp_s4 = &_texKaSa[RO_800B3150[var_s1] + 1];
    temp_s1 = &_texKaSa[0];

    var_s0 = MIN(temp_s4->info[TI_INFO_IDX_WIDTH], temp_s1->info[TI_INFO_IDX_WIDTH]);
    var_s3 = MIN(temp_s4->info[TI_INFO_IDX_HEIGHT], temp_s1->info[TI_INFO_IDX_HEIGHT]);

    gSPDisplayList(gfx++, alpha_texture_init_dl);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, arg6);

    if (arg5 <= 0) {
        sp48[3][0] = arg3 + var_s0;
    } else {
        sp48[3][0] = arg3;
    }
    sp48[3][1] = arg4;

    guMtxF2L(sp48, mtx);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    mtx++;

    RectAlphaTexTile(&gfx, &vtx, var_s0, var_s3, temp_s4->texs[TI_TEX_TEX], temp_s4->info[TI_INFO_IDX_WIDTH],
                     temp_s1->texs[TI_TEX_TEX], temp_s1->info[TI_INFO_IDX_WIDTH], 0, 0, var_s0, var_s3, 0.0f, 0.0f,
                     var_s0, var_s3);

    *vtxP = vtx;
    *mtxP = mtx;
    *gfxP = gfx;
}

/**
 * Original name: _posContPanel
 */
const s32 _posContPanel[] = { 0x0000000A, 0x0000000E };

/**
 * Original name: dm_manual_at_cap_draw
 */
void dm_manual_at_cap_draw(struct_game_state_data *state, AttackCapsel *cap, s32 size_flg) {
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 j;

        load_TexPal(dm_game_get_capsel_pal(size_flg, i)->texs[TI_TEX_TLUT]);

        for (j = 0; j < 4; j++) {
            if ((cap[j].capsel_a_flg[0] != 0) && (cap[j].capsel_a_p == i)) {
                draw_Tex(state->unk_006 + (cap[j].pos_a_x * state->unk_00A),
                         state->unk_008 + (cap[j].pos_a_y * state->unk_00A), state->unk_00A, state->unk_00A, 0,
                         state->unk_00A * 4);
            }
        }
    }
}

/**
 * Original name: _posCircle_924
 */
const s32 _posCircle_924[][2] = {
#if VERSION_US || VERSION_GW
    { 0xD, 0x14 },
    { 0x1C, 0x15 },
    { 0x46, 0x20 },
    { 0x3E, 0x1A },
#elif VERSION_CN
    { 0x16, 0x2E },
    { 0x1F, 0x2A },
    { 0x34, 0x1B },
    { 0x2B, 0x19 },
#endif
};
static_assert(ARRAY_COUNT(_posCircle_924) == STRUCT_WATCHGAME_MANUAL_UNK_LEN2, "");

/**
 * Original name: _posFinger_925
 */
const s32 _posFinger_925[][2] = {
#if VERSION_US || VERSION_GW
    { 0xD, 6 },
    { 0x1C, 7 },
    { 0x46, 0x12 },
    { 0x3E, 0xC },
#elif VERSION_CN
    { 0x16, 0x20 },
    { 0x1F, 0x1C },
    { 0x34, 0xD },
    { 0x2B, 0xB },
#endif
};
static_assert(ARRAY_COUNT(_posFinger_925) == STRUCT_WATCHGAME_MANUAL_UNK_LEN2, "");

/**
 * Original name: disp_cont
 */
void disp_cont(void) {
    struct_watchManual *st = watchManual;
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(st->key_flash_count); i++) {
        TiTexData *texC;
        TiTexData *texA;
        const s32 *pos;
        s32 var_t0;

        if (st->key_flash_count[i] == -0x14) {
            continue;
        }

        gSPDisplayList(gGfxHead++, normal_texture_init_dl);

        gDPSetCombineLERP(gGfxHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                          PRIMITIVE, 0);
        gDPSetRenderMode(gGfxHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(gGfxHead++, 0, 0, 255, 0, 0, 255);
        gDPSetTextureLUT(gGfxHead++, G_TT_NONE);

        pos = _posCircle_924[i];
        texC = &_texAll[6];
        StretchTexBlock4i(&gGfxHead, texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT],
                          texC->texs[TI_TEX_TEX], _posContPanel[0] + pos[0], _posContPanel[1] + pos[1],
                          texC->info[TI_INFO_IDX_WIDTH], texC->info[TI_INFO_IDX_HEIGHT]);

        gSPDisplayList(gGfxHead++, alpha_texture_init_dl);

        texC = &_texAll[4];
        texA = &_texAll[5];

        pos = _posFinger_925[i];
        var_t0 = MIN(texC->info[TI_INFO_IDX_WIDTH], texA->info[TI_INFO_IDX_WIDTH]);

        StretchAlphaTexBlock(&gGfxHead, var_t0, texC->info[TI_INFO_IDX_HEIGHT], texC->texs[TI_TEX_TEX],
                             texC->info[TI_INFO_IDX_WIDTH], texA->texs[TI_TEX_TEX], texA->info[TI_INFO_IDX_WIDTH],
                             _posContPanel[0] + pos[0], _posContPanel[1] + pos[1] - MIN(4, ABS(st->key_flash_count[i])),
                             var_t0, texC->info[TI_INFO_IDX_HEIGHT]);
    }
}

/**
 * Original name: dm_manual_draw_fg
 */
void dm_manual_draw_fg(Mtx **mtxP, Vtx **vtxP) {
    struct_watchManual *st = watchManual;
    s32 i;
    TiTexData *texC;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            gSPDisplayList(gGfxHead++, normal_texture_init_dl);

            texC = &_texAll[7];
            tiStretchTexBlock(&gGfxHead, texC, false, _posContPanel[0], _posContPanel[1], texC->info[TI_INFO_IDX_WIDTH],
                              texC->info[TI_INFO_IDX_HEIGHT]);
            dm_draw_big_virus(&gGfxHead);
            break;

        default:
            break;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_1:
            dm_calc_bottle_2p();
            dm_draw_bottle_2p(&gGfxHead);

            for (i = 0; i < 2; i++) {
                dm_game_graphic_p(&game_state_data[i], i, game_map_data[i]);
                dm_manual_at_cap_draw(&game_state_data[i], st->attack_cap[i], 0);
            }
            break;

        case EVS_MANUAL_NO_2:
            for (i = 0; i < 4; i++) {
                dm_game_graphic_p(&game_state_data[i], i, game_map_data[i]);
                dm_manual_at_cap_draw(&game_state_data[i], st->attack_cap[i], 1);
            }
            break;

        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            dm_game_graphic_p(game_state_data, 0, game_map_data[0]);
            disp_cont();
            break;
    }

    dm_draw_KaSaMaRu(&gGfxHead, mtxP, vtxP, tutolWnd_isSpeaking(&st->msgWnd), st->pino_pos_x, st->pino_pos_y,
                     st->pino_dir, (s32)(st->msgWnd.alpha * 255));
    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            if (main_old == MAIN_TITLE) {
                push_any_key_draw(0xDC, 0xD2);
            } else {
                draw_AB_guide(0xC8, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_1:
            if (main_old == MAIN_TITLE) {
                push_any_key_draw(0x80, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;

        case EVS_MANUAL_NO_2:
            if (main_old == MAIN_TITLE) {
                push_any_key_draw(0xE6, 0xD2);
            } else {
                draw_AB_guide(0x6E, 0xCA);
            }
            break;
    }

    tutolWnd_draw(&st->msgWnd, &gGfxHead);
}

/**
 * Original name: map_x_table_1036
 */
const u16 map_x_table_1036[][4] = {
    { 0x76, 0x76, 0x76, 0x76 },
    { 0x1C, 0xD4, 0x1C, 0xD4 },
    { 0x14, 0x5C, 0xA4, 0xEC },
};

/**
 * Original name: _seqTbl_1037
 */
const u8 _seqTbl_1037[] = { 2, 3 };

/**
 * Original name: map_y_table_1038
 */
const u8 map_y_table_1038[] = { 0x2E, 0x2E };

/**
 * Original name: size_table_1039
 */
const u8 size_table_1039[] = { 0xA, 8 };

/**
 * Original name: dm_manual_all_init
 */
void dm_manual_all_init(void) {
    struct_watchManual *st;
    RomOffsetPair *tbl;
    void **heap;
    s32 i;
    s32 j;
    s32 k;

    evs_seqnumb = _seqTbl_1037[evs_manual_no % ARRAY_COUNTU(_seqTbl_1037)];
    evs_seqence = 1;

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            evs_gamesel = ENUM_EVS_GAMESEL_0;
            evs_playcnt = 1;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            evs_gamesel = ENUM_EVS_GAMESEL_1;
            evs_playcnt = 2;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            evs_gamesel = ENUM_EVS_GAMESEL_2;
            evs_playcnt = 4;
            break;
    }

    evs_gamemode = GMD_NORMAL;
    story_proc_no = BGROMDATA_INDEX1;

    dm_game_init_heap();
    heap = dm_game_heap_top();
    watchManual = ALIGN_PTR(*heap);
    st = watchManual;
    bzero(st, sizeof(struct_watchManual));
    *heap = watchManual + 1;

    tbl = _romDataTbl;
    _texAll = tiLoadTexData(heap, tbl[ROMDATATBL_TUTORIAL_KASA].start, tbl[ROMDATATBL_TUTORIAL_KASA].end);
    _texKaSa = tiLoadTexData(heap, tbl[ROMDATATBL_MENU_KASA].start, tbl[ROMDATATBL_MENU_KASA].end);

    tutolWnd_init(&st->msgWnd, heap);
    tutolWnd_fadeIn(&st->msgWnd);

    dm_game_init_static();
    dm_game_init_snap_bg();
    dm_game_init(false);

    st->fade_count = 255;
    st->fade_step = -8;
    st->last3_flg = false;

    for (i = 0; i < ARRAY_COUNTU(st->key_flash_count); i++) {
        st->key_flash_count[i] = -0x14;
    }

    st->logo_timer = 0;
    st->bgm_timer = 0;
    st->bgm_timeout = 0;
    st->animeCount = 0;

    j = 0;
    for (i = 0; i < STRUCT_WATCHGAME_MANUAL_UNK_LEN; i++) {
        st->big_virus_flg[i].unk_0 = false;
        st->big_virus_flg[i].unk_4 = false;

        // This is pretty useless, since nothing actually uses these values.
        st->big_virus_pos[i].unk_8 = j;
        st->big_virus_pos[i].unk_0 = sinf(st->big_virus_pos[i].unk_8 * DOUBLE_LITERAL(PI_D) / 180) * 20.0f + 45.0f;
        st->big_virus_pos[i].unk_4 = cosf(st->big_virus_pos[i].unk_8 * DOUBLE_LITERAL(PI_D) / 180) * -20.0f + 155.0f;

        j += 0x78;
    }

    switch (evs_manual_no) {
        case EVS_MANUAL_NO_0:
        case EVS_MANUAL_NO_3:
            k = 0;
            j = 0;
            break;

        case EVS_MANUAL_NO_1:
        case EVS_MANUAL_NO_4:
            k = 0;
            j = 1;
            break;

        case EVS_MANUAL_NO_2:
        case EVS_MANUAL_NO_5:
            k = 1;
            j = 2;
            break;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        struct_game_state_data *state = &game_state_data[i];

        state->unk_006 = map_x_table_1036[j][i];
        state->unk_008 = map_y_table_1038[k];
        state->unk_00A = size_table_1039[k];
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        struct_game_state_data *state = &game_state_data[i];

        state->unk_02C = 1;
        state->unk_02D = GameSpeed[state->unk_02C];
        state->unk_04D = 0;
        state->unk_04E = 2;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_2:
            case EVS_MANUAL_NO_5:
                state->unk_02B = 0xC;
                state->unk_02A = 0;
                break;

            default:
                state->unk_02B = 8;
                state->unk_02A = 2;
                break;
        }

        st->attack_cap_count[i] = 0;

        for (j = 0; j < ARRAY_COUNTU(st->attack_cap[i]); j++) {
            AttackCapsel *acap = &st->attack_cap[i][j];

            acap->pos_a_x = 0;
            acap->pos_a_y = 0;
            acap->capsel_a_p = 0;

            for (k = 0; k < ARRAY_COUNTU(acap->capsel_a_flg); k++) {
                acap->capsel_a_flg[k] = 0;
            }
        }
    }

    st->mode = WATCHMANUALMODE_0;
    st->next_mode = WATCHMANUALMODE_0;
    st->mode_stop_flg = 0;
    st->capsel_flow = 0;
}

/**
 * Original name: dm_manual_main
 */
enum_main_no dm_manual_main(NNSched *sc) {
    OSMesgQueue scMQ;
    OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    NNScClient scClient;
    s32 handover_demono;
    s32 key;
    s32 i;
    bool loop_flg = true;
    bool fade_out = false;
    struct_watchManual *st;

    osCreateMesgQueue(&scMQ, scMsgBuf, ARRAY_COUNT(scMsgBuf));
    nnScAddClient(sc, &scClient, &scMQ);

    dm_manual_all_init();

    st = watchManual;

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        aifMakeFlagSet(&game_state_data[i]);
    }

    while (!fade_out) {
        joyProcCore();
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);

#ifdef NN_SC_PERF
        if (D_80092F10_cn) {
            graphic_no = GRAPHIC_NO_0;
            dm_audio_update();
            continue;
        }
#endif
        tutolWnd_update(&st->msgWnd);
        dm_effect_make();

        fade_out = false;
        st->animeCount++;

        if (st->fade_step > 0) {
            fade_out = st->fade_count == 255;
        }

        handover_demono = st->fade_count + st->fade_step;
        handover_demono = CLAMP(handover_demono, 0, 255);
        st->fade_count = handover_demono;

        switch (evs_manual_no) {
            case EVS_MANUAL_NO_0:
                loop_flg = dm_manual_1_main();
                break;

            case EVS_MANUAL_NO_1:
                loop_flg = dm_manual_2_main();
                break;

            case EVS_MANUAL_NO_2:
                loop_flg = dm_manual_3_main();
                break;

            case EVS_MANUAL_NO_3:
                loop_flg = dm_manual_4_main();
                break;
        }

        dm_seq_set_volume(0x60);
        dm_audio_update();

        if (st->bgm_timeout != 0) {
            st->bgm_timer++;
            if (st->bgm_timer >= st->bgm_timeout) {
                st->bgm_timer = 0;
                st->bgm_timeout = 0;
                dm_seq_play_in_game(evs_seqnumb * 2);
            }
        }
        if (st->fade_count == 0) {
            key = B_BUTTON;
            if (main_old == MAIN_TITLE) {
                key = ANY_BUTTON;
            }
            if (gControllerPressedButtons[main_joy[0]] & key) {
                loop_flg = false;
            }
        }

        if (!loop_flg) {
            if (st->fade_step < 0) {
                st->fade_step = -st->fade_step;
            }
        }

        graphic_no = GRAPHIC_NO_3;
    }

    dm_audio_stop();
    graphic_no = GRAPHIC_NO_0;

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&scMQ, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    nnScRemoveClient(sc, &scClient);

    if (main_old == MAIN_TITLE) {
        return MAIN_TITLE;
    } else if (main_old == MAIN_MENU) {
        return MAIN_MENU;
    }

#ifdef PRESERVE_UB
    return MAIN_TITLE;
#endif
}

/**
 * Original name: dm_manual_graphic
 */
void dm_manual_graphic(void) {
    struct_watchManual *st = watchManual;
    Mtx *mtx;
    Vtx *vtx;
    OSScTask *ptr;
    s32 color;
    s32 alpha;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    ptr = &B_800FAE80[gfx_gtask_no];

    mtx = dm_get_mtx_buf();
    vtx = dm_get_vtx_buf();

    gSPSegment(gGfxHead++, 0x00, NULL);
    F3RCPinitRtn();
    F3ClearFZRtn(false);

    gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    dm_game_draw_snap_bg(&gGfxHead, &mtx, &vtx, 0);
    dm_manual_draw_fg(&mtx, &vtx);

    color = 255;
    alpha = CLAMP((st->fade_count - 127) * 1.2 + 127, 0, 255);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    gfxTaskStart(ptr, gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
}
