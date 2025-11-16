/**
 * Original filename: record.c
 */

#include "record.h"

#include "macros_defines.h"

#include "recwritingmsg.h"
#include "main_menu.h"
#include "main1x.h"
#include "joy.h"
#include "tex_func.h"
#include "libc/assert.h"
#include "font.h"

#if VERSION_US || CC_CHECK
#include "audio/sound.h"
#endif

struct_evs_mem_data evs_mem_data[9];

#define CACHE_SIZE 0x200
/**
 * Original name: _cache_1333
 *
 * Its size must be a multiple of 8
 */
static u8 _cache_1333[CACHE_SIZE];

#define MESS_PANEL_TEX_WIDTH 200
#define MESS_PANEL_TEX_HEIGHT 69

struct_mess_panel_tex_size mess_panel_tex_size = { MESS_PANEL_TEX_WIDTH, MESS_PANEL_TEX_HEIGHT, 8, 1 };

u16 mess_panel_lut[] ALIGNED(8) = {
#include "main_segment/record/mess_panel_tex.palette.inc"
};

u8 mess_panel_tex[] ALIGNED(8) = {
#include "main_segment/record/mess_panel_tex.ci8.inc"
};

static_assert(sizeof(mess_panel_tex) == MESS_PANEL_TEX_WIDTH * MESS_PANEL_TEX_HEIGHT * sizeof(u8),
              "Texture does not have the expected resolution");

bool _cached_1332 = false;

#define EEPROM_HEADER_LEN 4U

/**
 * Original name: eeprom_header
 */
const CHAR_SIGNED char eeprom_header[] = {
    'D',
    'M',
    '6',
    '4',
};

/**
 * Original name: eeprom_header_bits
 */
const CHAR_SIGNED char eeprom_header_bits[] = {
    7, // ceil(log2('D'))
    7, // ceil(log2('M'))
    6, // ceil(log2('6'))
    6, // ceil(log2('4'))
};

static_assert(ARRAY_COUNTU(eeprom_header) == EEPROM_HEADER_LEN, "");
static_assert(ARRAY_COUNTU(eeprom_header_bits) == EEPROM_HEADER_LEN, "");

#if CC_CHECK
#define DEFNAME_LEN
#else
#define DEFNAME_LEN 4 * 2
#endif

/**
 * Original name: static _defName
 */
const char _defName[DEFNAME_LEN] =
#if VERSION_US || VERSION_GW
    "ＮＥＷ　"
#elif VERSION_CN
    "　　　　"
#endif
    ;

/**
 * Original name: static BitField_Attach
 */
void BitField_Attach(BitField *st, u8 *buffer, size_t size) {
    st->buffer = buffer;
    st->size = size;
    st->bufIdx = 0;
    st->bitIdx = 0;
    st->sum = 0;
}

/**
 * Original name: static BitField_Init
 */
void BitField_Init(BitField *st, u8 *buffer, size_t size) {
    bzero(buffer, size);
    BitField_Attach(st, buffer, size);
}

/**
 * Original name: BitField_PutBit
 */
void BitField_PutBit(BitField *st, s32 count, u32 bits) {
    s32 i;

    st->sum += bits & ((1 << count) - 1);
    for (i = count - 1; i >= 0; i--) {
        st->buffer[st->bufIdx] |= (((bits >> i) & 1) << st->bitIdx);

        st->bitIdx++;
        st->bufIdx += st->bitIdx >> 3;
        st->bitIdx &= 7;
    }
}

/**
 * Original name: BitField_GetBit
 */
u32 BitField_GetBit(BitField *st, s32 count) {
    u32 bits = 0;
    s32 i;

    for (i = count - 1; i >= 0; i--) {
        bits |= ((st->buffer[st->bufIdx] >> st->bitIdx) & 1) << i;
        st->bitIdx++;
        st->bufIdx += st->bitIdx >> 3;
        st->bitIdx &= 7;
    }

    st->sum += bits;
    return bits;
}

/**
 * Original name: dm_init_config_save
 */
void dm_init_config_save(struct_evs_mem_data_config *config) {
    config->unk_00 = 1;
    config->unk_01 = 0;
    config->unk_02 = 0;
    config->unk_03 = 0;
    config->unk_04 = 0xA;
    config->unk_05 = 1;
    config->unk_06 = 0;
    config->unk_07 = 1;
    config->unk_08 = 1;
    config->unk_09[0] = 1;
    config->unk_09[1] = 1;
    config->unk_0B[0] = 0xA;
    config->unk_0B[1] = 0xA;
    config->unk_0D[0] = 1;
    config->unk_0D[1] = 1;
    config->unk_0F[0] = 0;
    config->unk_0F[1] = 1;
    config->unk_11 = 0;
    config->unk_12 = 0;
    config->unk_13 = 1;
    config->unk_14 = 1;
    config->unk_15 = 0xA;
    config->unk_16 = 1;
    config->unk_17 = 0;
    config->unk_18 = 0;
    config->unk_19 = 0;
}

/**
 * Original name: dm_init_config_save
 */
void dm_init_config_4p_save(struct_evs_cfg_4p *config) {
    s32 i;

    for (i = 0; i < STRUCT_EVS_CFG_4P_COUNT; i++) {
        config->p4_team[i] = i % 2;
        config->p4_lv[i] = 10;
        config->p4_fl_lv[i] = 1;
        config->p4_no[i] = i;
        config->p4_sp[i] = 1;
    }

    config->unk_14 = 0;
    config->unk_15 = 0;
}

/**
 * Original name: dm_init_story_save
 */
void dm_init_story_save(struct_evs_mem_data_story_data *st) {
    st->score = 0;
    st->time = 0;
    st->c_stage = 0;
}

/**
 * Original name: dm_init_level_save
 */
void dm_init_level_save(struct_evs_mem_data_level_data *st) {
    st->score = 0;
    st->c_level = 0;
}

/**
 * Original name: dm_init_taiQ_save
 */
void dm_init_taiQ_save(struct_evs_mem_data_taiQ_data *st) {
    st->score = 0;
    st->time = 0;
}

/**
 * Original name: dm_init_timeAt_save
 */
void dm_init_timeAt_save(struct_evs_mem_data_timeAt_data *st) {
    st->score = 0;
    st->time = 0;
    st->erase = 0;
}

/**
 * Original name: dm_init_save_mem
 */
void dm_init_save_mem(struct_evs_mem_data *mem) {
    s32 i;
    s32 j;

    mem->mem_use_flg = 0;

    for (i = 0; i < ARRAY_COUNTU(mem->clear_stage); i++) {
        for (j = 0; j < ARRAY_COUNTU(mem->clear_stage[i]); j++) {
            mem->clear_stage[i][j] = 0;
        }
    }

    for (i = 0; i < ARRAY_COUNT(mem->mem_name); i++) {
        mem->mem_name[i] = evs_default_name[i];
    }

    for (i = 0; i < ARRAY_COUNTU(mem->story_data); i++) {
        dm_init_story_save(&mem->story_data[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(mem->level_data); i++) {
        dm_init_level_save(&mem->level_data[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(mem->taiQ_data); i++) {
        dm_init_taiQ_save(&mem->taiQ_data[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(mem->timeAt_data); i++) {
        dm_init_timeAt_save(&mem->timeAt_data[i]);
    }

    for (i = 0; i < ARRAY_COUNTU(mem->vscom_data); i++) {
        mem->vscom_data[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(mem->vc_fl_data); i++) {
        mem->vc_fl_data[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(mem->vsman_data); i++) {
        mem->vsman_data[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(mem->vm_fl_data); i++) {
        mem->vm_fl_data[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNTU(mem->vm_ta_data); i++) {
        mem->vm_ta_data[i] = 0;
    }

    dm_init_config_save(&mem->config);
}

/**
 * Original name: dm_init_system_mem
 */
void dm_init_system_mem(void) {
    s32 i;
    s32 temp;

    for (i = 0; i < 4; i++) {
        evs_default_name[i] = font2index(&_defName[i * 2]);
    }

    evs_stereo = true;
    temp = 1;
    dm_audio_set_stereo(evs_stereo);
    evs_gamesel = ENUM_EVS_GAMESEL_0;
    evs_secret_flg[temp] = 0;
    evs_secret_flg[0] = 0;
    evs_level_21 = 0;
    evs_vs_count = 3;
    evs_score_flag = 1;
}

/**
 * Original name: dm_story_sort_set
 */
void dm_story_sort_set(s32 player_no, s32 char_no, s32 g_level, s32 score, s32 time, s32 c_stage, bool ignoreFlag) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    time = time / 60;
    time = MIN(5999, time);

    c_stage = MAX(0, c_stage - 1);

    if (!ignoreFlag && (g_level < 3)) {
        struct_evs_mem_data_story_data *ms = &mc->story_data[g_level];
        s32 var_v0_2 = ms->c_stage;
        s32 var_t0 = c_stage;

#if 0
        int hi; // r1+0x0
        int lo; // r9
#endif

        if (var_v0_2 == c_stage) {
            var_v0_2 = ms->score;
            var_t0 = score;
            if (var_v0_2 == score) {
                var_v0_2 = time;
                var_t0 = ms->time;
            }
        }

        if (var_v0_2 < var_t0) {
            ms->score = score;
            ms->time = time;
            ms->c_stage = c_stage;
        }
    }

    mc->clear_stage[g_level][char_no] = MAX(mc->clear_stage[g_level][char_no], c_stage);
    mc->clear_stage[g_level][char_no] = MIN(mc->clear_stage[g_level][char_no], 7);
}

/**
 * Original name: dm_level_sort_set
 */
void dm_level_sort_set(s32 player_no, s32 g_speed, s32 score, s32 c_level) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];
    struct_evs_mem_data_level_data *ml = &mc->level_data[g_speed];
    s32 var_v0 = ml->c_level;
    s32 var_v1 = c_level;

#if 0
    int hi; // r1+0x0
    int lo; // r4
#endif

    //! FAKE: ?
    do {
        if (ml->c_level == c_level) {
            var_v0 = ml->score;
            var_v1 = score;
        }
    } while (0);

    if (var_v0 < var_v1) {
        ml->score = score;
        ml->c_level = c_level;
    }
}

/**
 * Original name: dm_taiQ_sort_set
 */
void dm_taiQ_sort_set(s32 player_no, s32 dif, s32 score, s32 time) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];
    struct_evs_mem_data_taiQ_data *tq = &mc->taiQ_data[dif];
    s32 var_a0;
    s32 var_v0;

    time = time / 60;
    time = MIN(5999, time);

    var_v0 = tq->score;
    var_a0 = score;

    if (var_v0 == var_a0) {
        var_v0 = tq->time;
        var_a0 = time;
    }

    if (var_v0 < var_a0) {
        tq->score = score;
        tq->time = time;
    }
}

/**
 * Original name: dm_timeAt_sort_set
 */
void dm_timeAt_sort_set(s32 player_no, s32 dif, s32 score, s32 time, s32 erase) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];
    struct_evs_mem_data_timeAt_data *ta = &mc->timeAt_data[dif];
    s32 var_a1;
    s32 var_v0;

    time = time / 6;
    time = MIN(1800, time);

    var_v0 = ta->score;
    var_a1 = score;

    if (var_v0 == var_a1) {
        var_a1 = ta->time;
        var_v0 = time;
        if (var_v0 == var_a1) {
            var_v0 = ta->erase;
            var_a1 = erase;
        }
    }

    if (var_v0 < var_a1) {
        ta->score = score;
        ta->time = time;
        ta->erase = erase;
    }
}

/**
 * Original name: dm_vscom_set
 */
void dm_vscom_set(s32 player_no, s32 win, s32 lose) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    mc->vscom_data[0] = MIN(99, mc->vscom_data[0] + win);
    mc->vscom_data[1] = MIN(99, mc->vscom_data[1] + lose);
}

/**
 * Original name: dm_vc_fl_set
 */
void dm_vc_fl_set(s32 player_no, s32 win, s32 lose) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    mc->vc_fl_data[0] = MIN(99, mc->vc_fl_data[0] + win);
    mc->vc_fl_data[1] = MIN(99, mc->vc_fl_data[1] + lose);
}

/**
 * Original name: dm_vsman_set
 */
void dm_vsman_set(s32 player_no, s32 win, s32 lose) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    mc->vsman_data[0] = MIN(99, mc->vsman_data[0] + win);
    mc->vsman_data[1] = MIN(99, mc->vsman_data[1] + lose);
}

/**
 * Original name: dm_vm_fl_set
 */
void dm_vm_fl_set(s32 player_no, s32 win, s32 lose) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    mc->vm_fl_data[0] = MIN(99, mc->vm_fl_data[0] + win);
    mc->vm_fl_data[1] = MIN(99, mc->vm_fl_data[1] + lose);
}

/**
 * Original name: dm_vm_ta_set
 */
void dm_vm_ta_set(s32 player_no, s32 win, s32 lose) {
    struct_evs_mem_data *mc = &evs_mem_data[player_no];

    mc->vm_ta_data[0] = MIN(99, mc->vm_ta_data[0] + win);
    mc->vm_ta_data[1] = MIN(99, mc->vm_ta_data[1] + lose);
}

typedef enum DataModeSort {
    /* 0 */ _1P_STORY,  /* Original name: _1P_STORY */
    /* 1 */ _1P_LEVEL,  /* Original name: _1P_LEVEL */
    /* 2 */ _1P_TaiQ,   /* Original name: _1P_TaiQ */
    /* 3 */ _1P_TimeAt, /* Original name: _1P_TimeAt */
} DataModeSort;

/**
 * Original name: _get1PSort
 */
u8 *_get1PSort(SRankSortInfo *st, DataModeSort mode, s32 level) {
    u8 *ptr;

    switch (mode) {
        case _1P_STORY:
            ptr = st->unk_000[level];
            break;

        case _1P_LEVEL:
            ptr = st->unk_030[level];
            break;

        case _1P_TaiQ:
            ptr = st->unk_060[level];
            break;

        case _1P_TimeAt:
            ptr = st->unk_090[level];
            break;
    }

    return ptr;
}

/**
 * Original name: _get1PRank
 */
u8 *_get1PRank(SRankSortInfo *st, DataModeSort mode, s32 level) {
    u8 *ptr;

    switch (mode) {
        case _1P_STORY:
            ptr = st->unk_018[level];
            break;

        case _1P_LEVEL:
            ptr = st->unk_048[level];
            break;

        case _1P_TaiQ:
            ptr = st->unk_078[level];
            break;

        case _1P_TimeAt:
            ptr = st->unk_0A8[level];
            break;
    }

    return ptr;
}

/**
 * Original name: _get1PLess
 */
bool _get1PLess(struct_evs_mem_data *mc1, struct_evs_mem_data *mc2, DataModeSort mode, s32 level) {
    s32 hi;
    s32 lo;

    switch (mode) {
        case _1P_STORY: {
            struct_evs_mem_data_story_data *story1 = &mc1->story_data[level];
            struct_evs_mem_data_story_data *story2 = &mc2->story_data[level];

            lo = story1->c_stage;
            hi = story2->c_stage;
            if (lo == hi) {
                lo = story1->score;
                hi = story2->score;
                if (lo == hi) {
                    lo = story2->time;
                    hi = story1->time;
                }
            }
        } break;

        case _1P_LEVEL: {
            struct_evs_mem_data_level_data *level1 = &mc1->level_data[level];
            struct_evs_mem_data_level_data *level2 = &mc2->level_data[level];

            lo = level1->c_level;
            hi = level2->c_level;
            if (lo == hi) {
                lo = level1->score;
                hi = level2->score;
            }
        } break;

        case _1P_TaiQ: {
            struct_evs_mem_data_taiQ_data *taiQ1 = &mc1->taiQ_data[level];
            struct_evs_mem_data_taiQ_data *taiQ2 = &mc2->taiQ_data[level];

            lo = taiQ1->time;
            hi = taiQ2->time;
            if (lo == hi) {
                lo = taiQ1->score;
                hi = taiQ2->score;
            }
        } break;

        case _1P_TimeAt: {
            struct_evs_mem_data_timeAt_data *timeAt1 = &mc1->timeAt_data[level];
            struct_evs_mem_data_timeAt_data *timeAt2 = &mc2->timeAt_data[level];

            lo = timeAt1->score;
            hi = timeAt2->score;
            if (lo == hi) {
                lo = timeAt2->time;
                hi = timeAt1->time;
                if (lo == hi) {
                    lo = timeAt1->erase;
                    hi = timeAt2->erase;
                }
            }
        } break;
    }

    return lo < hi;
}

/**
 * Original name: _sort1PMode
 */
void _sort1PMode(SRankSortInfo *st, DataModeSort mode, s32 level) {
    struct_evs_mem_data *mc = evs_mem_data;
    u8 *sort = _get1PSort(st, mode, level);
    u8 *rank = _get1PRank(st, mode, level);
    s32 i;
    s32 rankNo;

    for (i = 0; i < SRANKSORTINFO_SORT_LEN; i++) {
        sort[i] = i;
    }

    i = 0;
    while (i < SRANKSORTINFO_SORT_LEN - 1) {
        s32 j;

        for (j = i + 1; j < SRANKSORTINFO_SORT_LEN; j++) {
            s32 lo = mc[sort[i]].mem_use_flg & 1;
            s32 hi = mc[sort[j]].mem_use_flg & 1;

            if (_get1PLess(&mc[sort[i]], &mc[sort[j]], mode, level) || (lo < hi)) {
                u8 temp = sort[i];

                sort[i] = sort[j];
                sort[j] = temp;
            }
        }

        i++;
    }

    rank[0] = rankNo = 1;
    for (i = 1; i < SRANKSORTINFO_RANK_LEN; i++) {
        if (_get1PLess(&mc[sort[i]], &mc[sort[i - 1]], mode, level)) {
            rankNo++;
        }
        rank[i] = rankNo;
    }
}

/**
 * Original name: dm_data_mode_story_sort
 */
void dm_data_mode_story_sort(SRankSortInfo *st) {
    s32 i;

    for (i = 0; i < SRANKSORTINFO_LEVEL_NUM; i++) {
        _sort1PMode(st, _1P_STORY, i);
    }
}

/**
 * Original name: dm_data_mode_level_sort
 */
void dm_data_mode_level_sort(SRankSortInfo *st) {
    s32 i;

    for (i = 0; i < SRANKSORTINFO_LEVEL_NUM; i++) {
        _sort1PMode(st, _1P_LEVEL, i);
    }
}

/**
 * Original name: dm_data_mode_taiQ_sort
 */
void dm_data_mode_taiQ_sort(SRankSortInfo *st) {
    s32 i;

    for (i = 0; i < SRANKSORTINFO_LEVEL_NUM; i++) {
        _sort1PMode(st, _1P_TaiQ, i);
    }
}

/**
 * Original name: dm_data_mode_timeAt_sort
 */
void dm_data_mode_timeAt_sort(SRankSortInfo *st) {
    s32 i;

    for (i = 0; i < SRANKSORTINFO_LEVEL_NUM; i++) {
        _sort1PMode(st, _1P_TimeAt, i);
    }
}

typedef enum VsModeSort {
    /* 0 */ _VS_COM,         /* Original name: _VS_COM */
    /* 1 */ _VS_COM_FLASH,   /* Original name: _VS_COM_FLASH */
    /* 2 */ _VS_MAN,         /* Original name: _VS_MAN */
    /* 3 */ _VS_MAN_FLASH,   /* Original name: _VS_MAN_FLASH */
    /* 4 */ _VS_MAN_TIME_AT, /* Original name: _VS_MAN_TIME_AT */
} VsModeSort;

u16 *_getVsResult(struct_evs_mem_data *mc, VsModeSort mode) {
    u16 *ptr;

    switch (mode) {
        case _VS_COM:
            ptr = mc->vscom_data;
            break;

        case _VS_COM_FLASH:
            ptr = mc->vc_fl_data;
            break;

        case _VS_MAN:
            ptr = mc->vsman_data;
            break;

        case _VS_MAN_FLASH:
            ptr = mc->vm_fl_data;
            break;

        case _VS_MAN_TIME_AT:
            ptr = mc->vm_ta_data;
            break;
    }

    return ptr;
}

/**
 * Original name: _getVsRank
 */
u8 *_getVsSort(SRankSortInfo *st, VsModeSort mode) {
    u8 *ptr;

    switch (mode) {
        case _VS_COM:
            ptr = st->unk_0C0;
            break;

        case _VS_COM_FLASH:
            ptr = st->unk_0E0;
            break;

        case _VS_MAN:
            ptr = st->unk_100;
            break;

        case _VS_MAN_FLASH:
            ptr = st->unk_120;
            break;

        case _VS_MAN_TIME_AT:
            ptr = st->unk_140;
            break;
    }

    return ptr;
}

/**
 * Original name: _getVsRank
 */
u8 *_getVsRank(SRankSortInfo *st, VsModeSort mode) {
    u8 *ptr;

    switch (mode) {
        case _VS_COM:
            ptr = st->unk_0C8;
            break;

        case _VS_COM_FLASH:
            ptr = st->unk_0E8;
            break;

        case _VS_MAN:
            ptr = st->unk_108;
            break;

        case _VS_MAN_FLASH:
            ptr = st->unk_128;
            break;

        case _VS_MAN_TIME_AT:
            ptr = st->unk_148;
            break;
    }

    return ptr;
}

/**
 * Original name: _getVsAve
 */
u16 *_getVsAve(SRankSortInfo *st, VsModeSort mode) {
    u16 *ptr;

    switch (mode) {
        case _VS_COM:
            ptr = st->unk_0D0;
            break;

        case _VS_COM_FLASH:
            ptr = st->unk_0F0;
            break;

        case _VS_MAN:
            ptr = st->unk_110;
            break;

        case _VS_MAN_FLASH:
            ptr = st->unk_130;
            break;

        case _VS_MAN_TIME_AT:
            ptr = st->unk_150;
            break;
    }

    return ptr;
}

/**
 * Original name: _sortVsMode
 */
void _sortVsMode(SRankSortInfo *st, VsModeSort mode) {
    struct_evs_mem_data *mc = evs_mem_data;
    u8 *sort = _getVsSort(st, mode);
    u8 *rank = _getVsRank(st, mode);
    u16 *ave = _getVsAve(st, mode);
    s32 i;
    s32 rankNo;
    s32 aveVal;

    for (i = 0; i < 8; i++) {
        u16 *result = _getVsResult(&mc[i], mode);

        sort[i] = i;
        if ((result[0] != 0) || (result[1] != 0)) {
            ave[i] = (result[0] * 1000) / (result[0] + result[1]);
        } else {
            ave[i] = 0;
        }
    }

    for (i = 0; i < 7; i++) {
        s32 j;

        for (j = i + 1; j < 8; j++) {
            u8 temp_t1 = sort[i];
            u8 temp_t0 = sort[j];
            s32 lo;
            s32 hi;

            lo = ave[temp_t1];
            hi = ave[temp_t0];
            if (lo == hi) {
                lo = mc[temp_t1].mem_use_flg & 1;
                hi = mc[temp_t0].mem_use_flg & 1;
            }

            if (lo < hi) {
                sort[i] = temp_t0;
                sort[j] = temp_t1;
            }
        }
    }

    aveVal = ave[sort[0]];

    rank[0] = rankNo = 1;
    for (i = 1; i < 8; i++) {
        if (ave[sort[i]] != aveVal) {
            aveVal = ave[sort[i]];
            rankNo++;
        }

        rank[i] = rankNo;
    }
}

/**
 * Original name: dm_data_vscom_sort
 */
void dm_data_vscom_sort(SRankSortInfo *st) {
    _sortVsMode(st, _VS_COM);
}

/**
 * Original name: dm_data_vc_fl_sort
 */
void dm_data_vc_fl_sort(SRankSortInfo *st) {
    _sortVsMode(st, _VS_COM_FLASH);
}

/**
 * Original name: dm_data_vsman_sort
 */
void dm_data_vsman_sort(SRankSortInfo *st) {
    _sortVsMode(st, _VS_MAN);
}

/**
 * Original name: dm_data_vm_fl_sort
 */
void dm_data_vm_fl_sort(SRankSortInfo *st) {
    _sortVsMode(st, _VS_MAN_FLASH);
}

/**
 * Original name: dm_data_vm_ta_sort
 */
void dm_data_vm_ta_sort(SRankSortInfo *st) {
    _sortVsMode(st, _VS_MAN_TIME_AT);
}

#define FONTNAME_LEN 4

/**
 * Original name: fontName_getRange
 */
void fontName_getRange(const u8 name[FONTNAME_LEN], s32 *offset, s32 *size) {
    s32 end = 0;
    s32 start = 0;
    s32 i;

    for (i = 0; i < FONTNAME_LEN; i++) {
        if (name[i] != 0) {
            start = i;
            break;
        }
    }

    for (; i < FONTNAME_LEN; i++) {
        if (name[i] != 0) {
            end = i + 1;
        }
    }

    *offset = start;
    *size = end - start;
}

/**
 * Original name: BitField
 */
void RecSystem_Compress(BitField *bf) {
    BitField_PutBit(bf, 1, evs_stereo != 0);
    BitField_PutBit(bf, 1, evs_secret_flg[0] != 0);
    BitField_PutBit(bf, 1, evs_secret_flg[1] != 0);
    BitField_PutBit(bf, 1, evs_level_21 != 0);
    BitField_PutBit(bf, 2, evs_vs_count);
    BitField_PutBit(bf, 1, evs_score_flag != 0);
}

/**
 * Original name: RecSystem_Extract
 */
void RecSystem_Extract(BitField *bf) {
    evs_stereo = BitField_GetBit(bf, 1);
    evs_secret_flg[0] = BitField_GetBit(bf, 1);
    evs_secret_flg[1] = BitField_GetBit(bf, 1);
    evs_level_21 = BitField_GetBit(bf, 1);
    evs_vs_count = BitField_GetBit(bf, 2);
    evs_score_flag = BitField_GetBit(bf, 1);
    dm_audio_set_stereo(evs_stereo);
}

/**
 * Original name: RecPlayer_Compress
 */
void RecPlayer_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    BitField_PutBit(bf, 2, player->mem_use_flg);

    for (i = 0; i < ARRAY_COUNTU(player->mem_name); i++) {
        BitField_PutBit(bf, 8, player->mem_name[i]);
    }
}

/**
 * Original name: RecPlayer_Extract
 */
void RecPlayer_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    player->mem_use_flg = BitField_GetBit(bf, 2);

    for (i = 0; i < ARRAY_COUNTU(player->mem_name); i++) {
        player->mem_name[i] = BitField_GetBit(bf, 8);
    }
}

/**
 * Original name: RecStory_Compress
 */
void RecStory_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->clear_stage); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(player->clear_stage[i]); j++) {
            BitField_PutBit(bf, 3, player->clear_stage[i][j]);
        }
    }

    for (i = 0; i < ARRAY_COUNTU(player->story_data); i++) {
        struct_evs_mem_data_story_data *story = &player->story_data[i];

        BitField_PutBit(bf, 17, story->score / 100);
        BitField_PutBit(bf, 13, story->time);
        BitField_PutBit(bf, 4, story->c_stage);
    }
}

/**
 * Original name: RecStory_Extract
 */
void RecStory_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->clear_stage); i++) {
        s32 j;

        for (j = 0; j < ARRAY_COUNTU(player->clear_stage[i]); j++) {
            player->clear_stage[i][j] = BitField_GetBit(bf, 3);
        }
    }

    for (i = 0; i < ARRAY_COUNTU(player->story_data); i++) {
        struct_evs_mem_data_story_data *story = &player->story_data[i];

        story->score = BitField_GetBit(bf, 17) * 100;
        story->time = BitField_GetBit(bf, 13);
        story->c_stage = BitField_GetBit(bf, 4);
    }
}

/**
 * Original name: RecLevel_Compress
 */
void RecLevel_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->level_data); i++) {
        struct_evs_mem_data_level_data *level = &player->level_data[i];

        BitField_PutBit(bf, 17, level->score / 100);
        BitField_PutBit(bf, 7, level->c_level);
    }
}

/**
 * Original name: RecLevel_Extract
 */
void RecLevel_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->level_data); i++) {
        struct_evs_mem_data_level_data *level = &player->level_data[i];

        level->score = BitField_GetBit(bf, 17) * 100;
        level->c_level = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecLevelTaiQ_Compress
 */
void RecLevelTaiQ_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->taiQ_data); i++) {
        struct_evs_mem_data_taiQ_data *taiQ = &player->taiQ_data[i];

        BitField_PutBit(bf, 17, taiQ->score / 100);
        BitField_PutBit(bf, 13, taiQ->time);
    }
}

/**
 * Original name: RecLevelTaiQ_Extract
 */
void RecLevelTaiQ_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->taiQ_data); i++) {
        struct_evs_mem_data_taiQ_data *taiQ = &player->taiQ_data[i];

        taiQ->score = BitField_GetBit(bf, 17) * 100;
        taiQ->time = BitField_GetBit(bf, 13);
    }
}

/**
 * Original name: RecLevelTimeAT_Compress
 */
void RecLevelTimeAT_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->timeAt_data); i++) {
        struct_evs_mem_data_timeAt_data *timeAt = &player->timeAt_data[i];

        BitField_PutBit(bf, 16, timeAt->score / 10);
        BitField_PutBit(bf, 11, timeAt->time);
        BitField_PutBit(bf, 6, timeAt->erase);
    }
}

/**
 * Original name: RecLevelTimeAT_Extract
 */
void RecLevelTimeAT_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->timeAt_data); i++) {
        struct_evs_mem_data_timeAt_data *timeAt = &player->timeAt_data[i];

        timeAt->score = BitField_GetBit(bf, 16) * 10;
        timeAt->time = BitField_GetBit(bf, 11);
        timeAt->erase = BitField_GetBit(bf, 6);
    }
}

/**
 * Original name: RecVsCom_Compress
 */
void RecVsCom_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vscom_data); i++) {
        BitField_PutBit(bf, 7, player->vscom_data[i]);
    }
}

/**
 * Original name: RecVsCom_Extract
 */
void RecVsCom_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vscom_data); i++) {
        player->vscom_data[i] = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecVsComFlash_Compress
 */
void RecVsComFlash_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vc_fl_data); i++) {
        BitField_PutBit(bf, 7, player->vc_fl_data[i]);
    }
}

/**
 * Original name: RecVsComFlash_Extract
 */
void RecVsComFlash_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vc_fl_data); i++) {
        player->vc_fl_data[i] = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecVsMan_Compress
 */
void RecVsMan_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vsman_data); i++) {
        BitField_PutBit(bf, 7, player->vsman_data[i]);
    }
}

/**
 * Original name: RecVsMan_Extract
 */
void RecVsMan_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vsman_data); i++) {
        player->vsman_data[i] = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecVsManFlash_Compress
 */
void RecVsManFlash_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vm_fl_data); i++) {
        BitField_PutBit(bf, 7, player->vm_fl_data[i]);
    }
}

/**
 * Original name: RecVsManFlash_Extract
 */
void RecVsManFlash_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vm_fl_data); i++) {
        player->vm_fl_data[i] = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecVsManTimeAT_Compress
 */
void RecVsManTimeAT_Compress(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vm_ta_data); i++) {
        BitField_PutBit(bf, 7, player->vm_ta_data[i]);
    }
}

/**
 * Original name: RecVsManTimeAT_Extract
 */
void RecVsManTimeAT_Extract(BitField *bf, s32 num) {
    struct_evs_mem_data *player = &evs_mem_data[num];
    s32 i;

    for (i = 0; i < ARRAY_COUNTU(player->vm_ta_data); i++) {
        player->vm_ta_data[i] = BitField_GetBit(bf, 7);
    }
}

/**
 * Original name: RecAll_Compress
 */
void RecAll_Compress(BitField *bf) {
    s32 i;

    bf->sum = 0;
    RecSystem_Compress(bf);
    BitField_PutBit(bf, 4, bf->sum);

    for (i = 0; i < ARRAY_COUNT(evs_mem_data) - 1; i++) {
        bf->sum = 0;

        RecPlayer_Compress(bf, i);
        RecStory_Compress(bf, i);
        RecLevel_Compress(bf, i);
        RecLevelTaiQ_Compress(bf, i);
        RecLevelTimeAT_Compress(bf, i);
        RecVsCom_Compress(bf, i);
        RecVsComFlash_Compress(bf, i);
        RecVsMan_Compress(bf, i);
        RecVsManFlash_Compress(bf, i);
        RecVsManTimeAT_Compress(bf, i);

        BitField_PutBit(bf, 8, bf->sum);
    }

    bf->bufIdx = 0x1F8;
    bf->bitIdx = 0;

    for (i = 0; i < EEPROM_HEADER_LEN; i++) {
        BitField_PutBit(bf, eeprom_header_bits[i], eeprom_header[i]);
    }
}

/**
 * Original name: RecAll_Extract
 */
s32 RecAll_Extract(BitField *bf, char header[EEPROM_HEADER_LEN]) {
    s32 bad = 0;
    s32 i;
    s32 sum;

    bf->sum = 0;
    RecSystem_Extract(bf);

    sum = bf->sum & 0xF;
    if (sum != BitField_GetBit(bf, 4)) {
        dm_init_system_mem();
        bad++;
    }

    for (i = 0; i < ARRAY_COUNT(evs_mem_data) - 1; i++) {
        bf->sum = 0;

        RecPlayer_Extract(bf, i);
        RecStory_Extract(bf, i);
        RecLevel_Extract(bf, i);
        RecLevelTaiQ_Extract(bf, i);
        RecLevelTimeAT_Extract(bf, i);
        RecVsCom_Extract(bf, i);
        RecVsComFlash_Extract(bf, i);
        RecVsMan_Extract(bf, i);
        RecVsManFlash_Extract(bf, i);
        RecVsManTimeAT_Extract(bf, i);

        sum = bf->sum & 0xFF;
        if (sum != BitField_GetBit(bf, 8)) {
            dm_init_save_mem(&evs_mem_data[i]);
            bad++;
        }
    }

    bf->bufIdx = 0x1F8;
    bf->bitIdx = 0;

    for (i = 0; i < EEPROM_HEADER_LEN; i++) {
        header[i] = BitField_GetBit(bf, eeprom_header_bits[i]);
    }

    return bad;
}

/**
 * Original name: EepRom_Init
 */
EepRomErr EepRom_Init(void) {
    s32 temp;

    EepRom_InitVars();
    temp = osEepromProbe(&B_800F3E38);
    if ((temp != EEPROM_TYPE_4K) && (temp != EEPROM_TYPE_16K)) {
        EepRom_DumpErrMes(EepRomErr_NotFound);
        return EepRomErr_NotFound;
    }

    return EepRom_ReadAll();
}

/**
 * Original name: EepRom_InitFirst
 */
EepRomErr EepRom_InitFirst(EepRom_WriteDif_arg3 *proc, void *args) {
    s32 temp;

    EepRom_InitVars();
    temp = osEepromProbe(&B_800F3E38);
    if ((temp != EEPROM_TYPE_4K) && (temp != EEPROM_TYPE_16K)) {
        EepRom_DumpErrMes(EepRomErr_NotFound);
        return EepRomErr_NotFound;
    }

    return EepRom_WriteAll(proc, args);
}

/**
 * Original name: EepRom_InitVars
 */
void EepRom_InitVars(void) {
    s32 i;

    dm_init_system_mem();
    dm_init_config_4p_save(&evs_cfg_4p);

    for (i = 0; i < ARRAY_COUNT(evs_mem_data); i++) {
        dm_init_save_mem(&evs_mem_data[i]);
    }
}

/**
 * Original name: eepRom_longRead
 */
u8 *eepRom_longRead(bool forceRead) {
    if (!_cached_1332 || forceRead) {
        _cached_1332 = !osEepromLongRead(&B_800F3E38, 0, _cache_1333, sizeof(_cache_1333));
    }

    return _cached_1332 ? _cache_1333 : NULL;
}

/**
 * Original name: EepRom_WriteDif
 */
EepRomErr EepRom_WriteDif(const void *oldBuf, void *newBuf, size_t size, EepRom_WriteDif_arg3 *proc, void *args) {
    const u8 *oldPtr = oldBuf;
    u8 *newPtr = newBuf;
    s32 i;

// Must be a multiple of 8
#define NBYTES 8

    for (i = 0; i < (s32)size; i += NBYTES) {
        if (bcmp(oldPtr, newPtr, NBYTES) != 0) {
            if (proc != NULL) {
                proc(args);
                proc = NULL;
            }

            if (osEepromLongWrite(&B_800F3E38, i / NBYTES, newPtr, NBYTES) != 0) {
                EepRom_DumpErrMes(EepRomErr_WriteError);
                return EepRomErr_WriteError;
            }
        }
        oldPtr += NBYTES;
        newPtr += NBYTES;
    }

#undef NBYTES

    return EepRomErr_NoError;
}

/**
 * Original name: EepRom_ReadAll
 */
EepRomErr EepRom_ReadAll(void) {
    BitField bf;
    char header[4];
    s32 bad;
    u8 *cache = eepRom_longRead(true);

    if (cache == NULL) {
        EepRom_DumpErrMes(EepRomErr_ReadError);
        return EepRomErr_ReadError;
    }

    BitField_Attach(&bf, cache, CACHE_SIZE);
    bad = RecAll_Extract(&bf, header);

    if (bcmp(header, eeprom_header, sizeof(eeprom_header)) != 0) {
        return EepRomErr_NotInit;
    }
    if (bad == 0) {
        return EepRomErr_NoError;
    }
    return EepRomErr_BadSum;
}

/**
 * Original name: EepRom_WriteAll
 */
EepRomErr EepRom_WriteAll(EepRom_WriteDif_arg3 *proc, void *args) {
    BitField bf;
    u8 out[CACHE_SIZE];
    u8 *in = eepRom_longRead(true);

    if (in == NULL) {
        EepRom_DumpErrMes(EepRomErr_ReadError);
        return EepRomErr_ReadError;
    }

    BitField_Init(&bf, out, sizeof(out));
    RecAll_Compress(&bf);
    if (EepRom_WriteDif(in, out, sizeof(out), proc, args) != EepRomErr_NoError) {
        EepRom_DumpErrMes(EepRomErr_WriteError);
        return EepRomErr_WriteError;
    }

    bcopy(out, in, sizeof(out));
    return EepRomErr_NoError;
}

/**
 * Original name: EepRom_DumpErrMes
 */
void EepRom_DumpErrMes(EepRomErr status UNUSED) {
}

/**
 * Original name: EepRom_DumpDataSize
 */
void EepRom_DumpDataSize(void) {
}

/**
 * Original name: RecWritingMsg_init
 */
void RecWritingMsg_init(RecordWritingMessage *recMessage, void **heap) {
    msgWnd_init(&recMessage->messageWnd, heap, 0x18, 2, 0, 0);
    recMessage->messageWnd.centering = true;
    RecWritingMsg_setPos(recMessage, 0, 0);
    recMessage->unk_84 = 0x78;
    recMessage->unk_80 = 0x78;
}

/**
 * Original name: RecWritingMsg_setStr
 */
void RecWritingMsg_setStr(RecordWritingMessage *recMessage, const char *str) {
    msgWnd_clear(&recMessage->messageWnd);
    msgWnd_addStr(&recMessage->messageWnd, str);
    msgWnd_skip(&recMessage->messageWnd);
}

/**
 * Original name: RecWritingMsg_calc
 */
void RecWritingMsg_calc(RecordWritingMessage *recMessage) {
    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    msgWnd_update(&recMessage->messageWnd);
    recMessage->unk_84++;
}

/**
 * Original name: RecWritingMsg_draw
 */
void RecWritingMsg_draw(RecordWritingMessage *recMessage, Gfx **gfxP) {
    Gfx *gfx;
    s32 width;
    s32 height;

    if (RecWritingMsg_isEnd(recMessage)) {
        return;
    }

    gfx = *gfxP;

    width = msgWnd_getWidth(&recMessage->messageWnd);
    height = msgWnd_getHeight(&recMessage->messageWnd);
    gSPDisplayList(gfx++, normal_texture_init_dl);

    StretchTexTile8(&gfx, mess_panel_tex_size.width, mess_panel_tex_size.height, mess_panel_lut, mess_panel_tex, 0, 0,
                    mess_panel_tex_size.width, mess_panel_tex_size.height,
                    recMessage->messageWnd.posX - ((mess_panel_tex_size.width - width) / 2),
                    recMessage->messageWnd.posY - ((mess_panel_tex_size.height - height) / 2),
                    mess_panel_tex_size.width, mess_panel_tex_size.height);
    msgWnd_draw(&recMessage->messageWnd, &gfx);

    *gfxP = gfx;
}

/**
 * Original name: RecWritingMsg_start
 */
void RecWritingMsg_start(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = 0;
}

/**
 * Original name: RecWritingMsg_end
 */
void RecWritingMsg_end(RecordWritingMessage *recMessage) {
    recMessage->unk_84 = recMessage->unk_80;
}

/**
 * Original name: RecWritingMsg_isEnd
 */
bool RecWritingMsg_isEnd(const RecordWritingMessage *recMessage) {
    return recMessage->unk_84 >= recMessage->unk_80;
}

/**
 * Original name: RecWritingMsg_setPos
 */
void RecWritingMsg_setPos(RecordWritingMessage *recMessage, s32 x, s32 y) {
    recMessage->messageWnd.posX = x;
    recMessage->messageWnd.posY = y;
}

/**
 * Original name: setSleepTimer
 */
void setSleepTimer(s32 milliseconds) {
    OSMesgQueue mq;
    OSTimer timer;
    OSMesg msg[1];

    osCreateMesgQueue(&mq, msg, ARRAY_COUNT(msg));
    osSetTimer(&timer, OS_USEC_TO_CYCLES(milliseconds * 1000), 0, &mq, NULL);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}
