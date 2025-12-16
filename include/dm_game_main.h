#ifndef DM_GAME_MAIN_H
#define DM_GAME_MAIN_H

#include "libc/assert.h"
#include "libultra.h"
#include "ai.h"
#include "char_anime.h"
#include "color.h"
#include "defines.h"
#include "game_etc.h"
#include "gamemap.h"
#include "msgwnd.h"
#include "recwritingmsg.h"
#include "main.h"
#include "unk.h"

struct struct_virus_map_data;
struct NNSched;

struct struct_gameGeom;
#define ANIMES_COUNT 3
struct struct_watchGame;
struct GameStateBackup;

typedef enum enum_evs_gamemode {
    /* 0 */ GMD_NORMAL,
    /* 1 */ GMD_FLASH,
    /* 2 */ GMD_TaiQ,
    /* 3 */ GMD_TIME_ATTACK
} enum_evs_gamemode;

typedef enum TeamNumber {
    /* 0x0 */ TEAMNUMBER_0,
    /* 0x1 */ TEAMNUMBER_1,
    /* 0x2 */ TEAMNUMBER_2,
    /* 0x3 */ TEAMNUMBER_3,
    /* 0x4 */ TEAMNUMBER_MAX,
} TeamNumber;
static_assert(TEAMNUMBER_MAX == MAX_PLAYERS, "");

#define STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN 2

typedef struct struct_game_state_data_now_cap {
    /* 0x0 */ s8 pos_x[STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN]; /* Original name: pos_x */
    /* 0x2 */ s8 pos_y[STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN]; /* Original name: pos_y */
    /* 0x4 */ s8 casel_g[STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN]; /* Original name: casel_g */
    /* 0x6 */ s8 capsel_p[STRUCT_GAME_STATE_DATA_UNK_178_UNK_LEN]; /* Original name: capsel_p */
    /* 0x8 */ s8 capsel_flg_0; /* Original name: capsel_flg[4] */
    /* 0x9 */ s8 capsel_flg_1; /* Original name: capsel_flg[4] */
    /* 0xA */ s8 capsel_flg_2; /* Original name: capsel_flg[4] */
    /* 0xB */ s8 capsel_flg_3; // unused
} struct_game_state_data_now_cap; // size = 0xC

typedef struct struct_game_state_data_cap_attack_work {
    /* 0x0 */ u16 unk_0;
    /* 0x2 */ u16 unk_2;
} struct_game_state_data_cap_attack_work; // size = 0x4

typedef enum EnumGameStateDataMode {
    /* 0x00 */ dm_mode_null, /* Original name: dm_mode_null */
    /* 0x01 */ dm_mode_init, /* Original name: dm_mode_init */
    /* 0x02 */ dm_mode_wait, /* Original name: dm_mode_wait */
    /* 0x03 */ dm_mode_throw, /* Original name: dm_mode_throw */
    /* 0x04 */ dm_mode_down, /* Original name: dm_mode_down */
    /* 0x05 */ dm_mode_down_wait, /* Original name: dm_mode_down_wait */
    /* 0x06 */ dm_mode_erase_chack, /* Original name: dm_mode_erase_chack */
    /* 0x07 */ dm_mode_erase_anime, /* Original name: dm_mode_erase_anime */
    /* 0x08 */ dm_mode_ball_down, /* Original name: dm_mode_ball_down */
    /* 0x09 */ dm_mode_cap_set, /* Original name: dm_mode_cap_set */
    /* 0x0A */ dm_mode_stage_clear, /* Original name: dm_mode_stage_clear */
    /* 0x0B */ dm_mode_game_over, /* Original name: dm_mode_game_over */
    /* 0x0C */ dm_mode_bottom_up, /* Original name: dm_mode_bottom_up */
    /* 0x0D */ dm_mode_win, /* Original name: dm_mode_win */
    /* 0x0E */ dm_mode_win_retry, /* Original name: dm_mode_win_retry */
    /* 0x0F */ dm_mode_lose, /* Original name: dm_mode_lose */
    /* 0x10 */ dm_mode_lose_retry, /* Original name: dm_mode_lose_retry */
    /* 0x11 */ dm_mode_draw, /* Original name: dm_mode_draw */
    /* 0x12 */ dm_mode_draw_retry, /* Original name: dm_mode_draw_retry */
    /* 0x13 */ dm_mode_tr_chaeck, /* Original name: dm_mode_tr_chaeck */
    /* 0x14 */ dm_mode_training, /* Original name: dm_mode_training */
    /* 0x15 */ dm_mode_tr_erase_chack, /* Original name: dm_mode_tr_erase_chack */
    /* 0x16 */ dm_mode_tr_cap_set, /* Original name: dm_mode_tr_cap_set */
    /* 0x17 */ dm_mode_pause, /* Original name: dm_mode_pause */
    /* 0x18 */ dm_mode_pause_retry, /* Original name: dm_mode_pause_retry */
    /* 0x19 */ dm_mode_no_action, /* Original name: dm_mode_no_action */
    /* 0x1A */ dm_mode_clear_wait, /* Original name: dm_mode_clear_wait */
    /* 0x1B */ dm_mode_clear_result, /* Original name: dm_mode_clear_result */
    /* 0x1C */ dm_mode_gover_wait, /* Original name: dm_mode_gover_wait */
    /* 0x1D */ dm_mode_gover_result, /* Original name: dm_mode_gover_result */
    /* 0x1E */ dm_mode_retire_wait, /* Original name: dm_mode_retire_wait */
    /* 0x1F */ dm_mode_retire_result, /* Original name: dm_mode_retire_result */
    /* 0x20 */ dm_mode_debug_config, /* Original name: dm_mode_debug_config */ /* Open the character edit debug menu */
    /* 0x21 */ dm_mode_debug, /* Original name: dm_mode_debug */ /* Open the debug settins */
} EnumGameStateDataMode;

typedef enum EnumGameStateDataCnd {
    /* 0x00 */ dm_cnd_null, /* Original name: dm_cnd_null */
    /* 0x01 */ dm_cnd_wait, /* Original name: dm_cnd_wait */
    /* 0x02 */ dm_cnd_init, /* Original name: dm_cnd_init */
    /* 0x03 */ dm_cnd_stage_clear, /* Original name: dm_cnd_stage_clear */
    /* 0x04 */ dm_cnd_game_over, /* Original name: dm_cnd_game_over */
    /* 0x05 */ dm_cnd_win, /* Original name: dm_cnd_win */
    /* 0x06 */ dm_cnd_win_retry, /* Original name: dm_cnd_win_retry */
    /* 0x07 */ dm_cnd_win_retry_sc, /* Original name: dm_cnd_win_retry_sc */
    /* 0x08 */ dm_cnd_lose, /* Original name: dm_cnd_lose */
    /* 0x09 */ dm_cnd_lose_retry, /* Original name: dm_cnd_lose_retry */
    /* 0x0A */ dm_cnd_lose_retry_sc, /* Original name: dm_cnd_lose_retry_sc */
    /* 0x0B */ dm_cnd_draw, /* Original name: dm_cnd_draw */
    /* 0x0C */ dm_cnd_draw_retry, /* Original name: dm_cnd_draw_retry */
    /* 0x0D */ dm_cnd_pause, /* Original name: dm_cnd_pause */
    /* 0x0E */ dm_cnd_pause_re, /* Original name: dm_cnd_pause_re */
    /* 0x0F */ dm_cnd_pause_re_sc, /* Original name: dm_cnd_pause_re_sc */
    /* 0x10 */ dm_cnd_retire, /* Original name: dm_cnd_retire */
    /* 0x11 */ dm_cnd_tr_chack, /* Original name: dm_cnd_tr_chack */
    /* 0x12 */ dm_cnd_training, /* Original name: dm_cnd_training */
    /* 0x13 */ dm_cnd_clear_wait, /* Original name: dm_cnd_clear_wait */
    /* 0x14 */ dm_cnd_clear_result, /* Original name: dm_cnd_clear_result */
    /* 0x15 */ dm_cnd_gover_wait, /* Original name: dm_cnd_gover_wait */
    /* 0x16 */ dm_cnd_gover_result, /* Original name: dm_cnd_gover_result */
    /* 0x17 */ dm_cnd_retire_wait, /* Original name: dm_cnd_retire_wait */
    /* 0x18 */ dm_cnd_retire_result, /* Original name: dm_cnd_retire_result */
    /* 0x19 */ dm_cnd_debug_config, /* Original name: dm_cnd_debug_config */
    /* 0x1A */ dm_cnd_debug, /* Original name: dm_cnd_debug */
} EnumGameStateDataCnd;

typedef enum PlayerType {
    /* 0x0 */ PLAYERTYPE_0, // Human?
    /* 0x1 */ PLAYERTYPE_1,
} PlayerType;

typedef enum ThinkLevel {
    /* 0x0 */ THINKLEVEL_0,
    /* 0x1 */ THINKLEVEL_1,
    /* 0x2 */ THINKLEVEL_2,
    /* 0x3 */ THINKLEVEL_MAX,
} ThinkLevel;

#define FLASH_VIRUS_LEN 9

typedef struct struct_game_state_data_flash_virus_pos {
    /* 0x0 */ s32 column;
    /* 0x4 */ s32 row;
    /* 0x8 */ s32 color;
} struct_game_state_data_flash_virus_pos; // size = 0xC

#define AI_EFFECT_LEN 16

typedef struct struct_game_state_data_ai {
    /* 0x000 */ struct_aiFlag aiFlagDecide; /* Original name: aiFlagDecide */
    /* 0x040 */ struct_aiRoot aiRootDecide[AIROOT_LEN]; /* Original name: aiRootDecide */ // Indexed by aiKeyCount
    /* 0x0A4 */ u8 aiKeyCount; /* Original name: aiKeyCount */
    /* 0x0A5 */ u8 aiSpeedCnt; /* Original name: aiSpeedCnt */
    /* 0x0A6 */ u8 aiKRFlag; /* Original name: aiKRFlag */
    /* 0x0A7 */ u8 aiRollCnt; /* Original name: aiRollCnt */
    /* 0x0A8 */ u8 aiRollFinal; /* Original name: aiRollFinal */
    /* 0x0A9 */ u8 aiRollHabit; /* Original name: aiRollHabit */ // TODO: bitflags
    /* 0x0AA */ u8 aiSpUpFlag; /* Original name: aiSpUpFlag */
    /* 0x0AB */ u8 aiSpUpStart; /* Original name: aiSpUpStart */
    /* 0x0AC */ u8 aivl; /* Original name: aivl */ /* ThinkLevel */
    /* 0x0AD */ u8 aiok; /* Original name: aiok */
    /* 0x0AE */ u8 aiRandFlag; /* Original name: aiRandFlag */
    /* 0x0AF */ u8 aiEX; /* Original name: aiEX */
    /* 0x0B0 */ u8 aiEY; /* Original name: aiEY */
    /* 0x0B1 */ u8 aiOldRollCnt; /* Original name: aiOldRollCnt */
    /* 0x0B2 */ u8 aiEffectNo[AI_EFFECT_LEN]; /* Original name: aiEffectNo */ /* TODO: enum? Same value as struct_ai_char_data::effect */
    /* 0x0C2 */ s16 aiEffectParam[AI_EFFECT_LEN]; /* Original name: aiEffectParam */
    /* 0x0E2 */ s16 aiEffectCount[AI_EFFECT_LEN]; /* Original name: aiEffectCount */
    /* 0x102 */ u8 aiState; /* Original name: aiState */ // TODO: bitflags
    /* 0x103 */ u8 aiSelSpeed; /* Original name: aiSelSpeed */
    /* 0x104 */ u8 aiRootP; /* Original name: aiRootP */
    /* 0x106 */ u16 aiPriOfs; /* Original name: aiPriOfs */
} struct_game_state_data_ai; // size = 0x108

// See `Unk_AIFEntry`
typedef struct struct_game_state_data_blk {
    /* 0x0 */ u8 st; /* Original name: st */ // TODO: row? column?
    /* 0x1 */ u8 co; /* Original name: co */
} struct_game_state_data_blk; // size = 0x2

typedef struct struct_game_state_data_cap {
    /* 0x0 */ u8 mx; /* Original name: mx */
    /* 0x1 */ u8 my; /* Original name: my */
    /* 0x2 */ u8 ca; /* Original name: ca */
    /* 0x3 */ u8 cb; /* Original name: cb */
    /* 0x4 */ u8 sp; /* Original name: sp */
    /* 0x5 */ u8 cn; /* Original name: cn */
} struct_game_state_data_cap; // size = 0x6

// TODO: struct_dm_game_main_c_171
typedef struct struct_game_state_data {
    /* 0x000 */ u32 game_score; /* Original name: game_score */
    /* 0x004 */ u16 game_retry; /* Original name: game_retry */
    /* 0x006 */ s16 map_x; /* Original name: map_x */
    /* 0x008 */ s16 map_y; /* Original name: map_y */
    /* 0x008 */ s8 map_item_size; /* Original name: map_item_size */
    /* 0x00C */ EnumGameStateDataMode mode_now; /* Original name: mode_now */
    /* 0x010 */ EnumGameStateDataMode mode_old; /* Original name: mode_old */
    /* 0x014 */ EnumGameStateDataCnd cnd_now; /* Original name: cnd_now */
    /* 0x018 */ EnumGameStateDataCnd cnd_old; /* Original name: cnd_old */
    /* 0x01C */ EnumGameStateDataCnd cnd_training; /* Original name: cnd_training */
    /* 0x020 */ EnumGameStateDataCnd cnd_static; /* Original name: cnd_static */
    /* 0x024 */ u8 virus_order_number; /* Original name: virus_order_number */
    /* 0x025 */ u8 virus_number; /* Original name: virus_number */
    /* 0x026 */ u8 virus_level; /* Original name: virus_level */ /* TODO: enum? */
    /* 0x027 */ u8 virus_anime; /* Original name: virus_anime */
    /* 0x028 */ s8 virus_anime_vec; /* Original name: virus_anime_vec */
    /* 0x029 */ u8 virus_anime_count; /* Original name: virus_anime_count */
    /* 0x02A */ u8 virus_anime_max; /* Original name: virus_anime_max */
    /* 0x02B */ u8 virus_anime_spead; /* Original name: virus_anime_spead */
    /* 0x02C */ u8 cap_def_speed; /* Original name: cap_def_speed */
    /* 0x02D */ u8 cap_speed; /* Original name: cap_speed */
    /* 0x02E */ u8 cap_count; /* Original name: cap_count */
    /* 0x02F */ u8 cap_speed_count; /* Original name: cap_speed_count */
    /* 0x030 */ u8 cap_speed_vec; /* Original name: cap_speed_vec */
    /* 0x031 */ u8 cap_speed_max; /* Original name: cap_speed_max */
    /* 0x032 */ u8 cap_magazine_cnt; /* Original name: cap_magazine_cnt */
    /* 0x033 */ u8 cap_magazine_save; /* Original name: cap_magazine_save */
    /* 0x034 */ s8 cap_move_se_flg; /* Original name: cap_move_se_flg */
    /* 0x035 */ u8 erase_anime; /* Original name: erase_anime */
    /* 0x036 */ u8 erase_anime_count; /* Original name: erase_anime_count */
    /* 0x037 */ u8 erase_virus_count; /* Original name: erase_virus_count */
    /* 0x038 */ u8 erase_virus_count_old; /* Original name: erase_virus_count_old */
    /* 0x039 */ u8 chain_count; /* Original name: chain_count */
    /* 0x03A */ u8 chain_line; /* Original name: chain_line */
    /* 0x03B */ u8 chain_line_max; /* Original name: chain_line_max */
    /* 0x03C */ u8 chain_color[4]; /* Original name: chain_color */
    /* 0x040 */ u8 black_up_count; /* Original name: black_up_count */
    /* 0x040 */ bool warning_se_flag; /* Original name: warning_se_flag */
    /* 0x048 */ u8 flg_retire; /* Original name: flg_retire */
    /* 0x048 */ u8 flg_game_over; /* Original name: flg_game_over */
    /* 0x048 */ u8 flg_training; /* Original name: flg_training */
    /* 0x04B */ u8 player_no; /* Original name: player_no */
    /* 0x04C */ u8 player_type; /* Original name: player_type */ /* PlayerType */
    /* 0x04D */ u8 think_type; /* Original name: think_type */ /* ThinkType */
    /* 0x04E */ u8 think_level; /* Original name: think_level */ /* ThinkLevel */
    /* 0x04F */ u8 team_no; /* Original name: team_no */ /* TeamNumber */
    /* 0x050 */ struct_game_state_data_cap_attack_work cap_attack_work[0x10]; /* Original name: cap_attack_work */
    /* 0x090 */ CharAnimeMode charNo; /* Original name: charNo */
    /* 0x094 */ SAnimeState anime; /* Original name: anime */
    /* 0x0D4 */ struct_game_state_data_flash_virus_pos flash_virus_pos[FLASH_VIRUS_LEN]; /* Original name: flash_virus_pos */
    /* 0x140 */ s32 flash_virus_bak[FLASH_VIRUS_LEN]; /* Original name: flash_virus_bak */
    /* 0x164 */ s32 flash_virus_count; /* Original name: flash_virus_count */
    /* 0x168 */ s32 bottom_up_scroll; /* Original name: bottom_up_scroll */
    /* 0x16C */ s32 game_level; /* Original name: game_level */
    /* 0x170 */ s32 total_erase_count; /* Original name: total_erase_count */
    /* 0x174 */ s32 total_chain_count; /* Original name: total_chain_count */
    /* 0x178 */ struct_game_state_data_now_cap now_cap; /* Original name: now_cap */
    /* 0x184 */ struct_game_state_data_now_cap next_cap; /* Original name: next_cap */
    /* 0x190 */ struct_game_state_data_ai ai; /* Original name: ai */
    /* 0x298 */ u8 pn; /* Original name: pn */
    /* 0x299 */ u8 gs; /* Original name: gs */
    /* 0x29A */ u8 lv; /* Original name: lv */
    /* 0x29B */ u8 vs; /* Original name: vs */
    /* 0x29C */ struct_game_state_data_blk blk[GAME_MAP_ROWS+1][GAME_MAP_COLUMNS]; /* Original name: blk */
    /* 0x3BC */ struct_game_state_data_cap cap; /* Original name: cap */
} struct_game_state_data; // size = 0x3C4

u32 dm_make_score(struct_game_state_data *state);
void dm_attack_se(struct_game_state_data *state, s32 player_no);
void dm_warning_h_line(struct_game_state_data *state, GameMapCell *map);

void go_down(struct_game_state_data *state, GameMapCell *map, s32 cout);
void erase_anime(GameMapCell *map);

void translate_capsel(GameMapCell *map, struct_game_state_data *state, s32 move_vec, s32 joy_no);
void rotate_capsel(GameMapCell *map, struct_game_state_data_now_cap *cap, s32 move_vec);

void dm_set_capsel(struct_game_state_data *state);
void dm_capsel_speed_up(struct_game_state_data *state);
bool dm_check_game_over(struct_game_state_data *state, GameMapCell *mapCells);

void dm_virus_anime(struct_game_state_data *state, GameMapCell *map);
void dm_capsel_erase_anime(struct_game_state_data *state, GameMapCell *map);

bool dm_h_erase_chack(GameMapCell *map);
void dm_h_erase_chack_set(struct_game_state_data *state, GameMapCell *map);

bool dm_w_erase_chack(GameMapCell *map);
void dm_w_erase_chack_set(struct_game_state_data *state, GameMapCell *map);
void dm_h_ball_chack(GameMapCell *map);
void dm_w_ball_chack(GameMapCell *map);
bool dm_black_up(struct_game_state_data *state, GameMapCell *map);
bool dm_broken_set(struct_game_state_data *state, GameMapCell *map);

void **dm_game_heap_top(void);
SAnimeState *get_virus_anime_state(s32 index);
SAnimeSmog *get_virus_smog_state(s32 index);
Mtx *dm_get_mtx_buf(void);
Vtx *dm_get_vtx_buf(void);

void backup_game_state(s32 bufNo);
void resume_game_state(s32 bufNo);
void set_replay_state(void);
void reset_replay_state(void);
void start_replay_proc(void);
void dm_warning_h_line_se(void);

void dm_capsel_down(struct_game_state_data *state, GameMapCell *map);

void dm_calc_big_virus_pos(struct_game_state_data *state);

struct TiTexData *dm_game_get_capsel_tex(s32 sizeIndex);
struct TiTexData *dm_game_get_capsel_pal(s32 sizeIndex, s32 colorIndex);

void draw_star_base(Gfx **gfxP, s32 x, s32 y, bool cached);

void dm_map_draw(GameMapCell *mapCells, u8 col_no, s16 x_p, s16 y_p, s8 size);
void dm_find_fall_point(GameMapCell *map, struct_game_state_data_now_cap *cap, s32 fallPosY[2]);
void draw_virus_number(Gfx **gfxP, u32 number, s32 x, s32 y, f32 sx, f32 arg5);
void draw_count_number(Gfx **gfxP, s32 color, s32 column, u32 number, s32 x, s32 y);
void draw_time(Gfx **gfxP, u32 time, s32 x, s32 y);
void draw_time2(Gfx **gfxP, u32 time, s32 x, s32 y);
void push_any_key_draw(s32 x_pos, s32 y_pos);

void draw_vsmode_board(Gfx **gfxP, s32 x, s32 y, bool visBoard, bool visScore);
void _draw_bottle_10(Gfx **gfxP, const s32 *xx, const s32 *yy, s32 count);
void dm_calc_bottle_2p(void);
void dm_draw_bottle_2p(Gfx **gfxP);
void dm_draw_big_virus(Gfx **gfxP);
void dm_draw_KaSaMaRu(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, bool speaking, s32 x, s32 y, s32 dir, u32 alpha);
void dm_game_graphic_common(struct_game_state_data *state, s32 player_no, GameMapCell *map);
void dm_game_graphic_p(struct_game_state_data *state, s32 player_no, GameMapCell *map);

void dm_game_graphic_effect(struct_game_state_data *state, s32 player_no, s32 arg2);
void key_cntrol_init(void);
void dm_make_key(void);
void key_control_main(struct_game_state_data *state, GameMapCell *map, s32 player_no, s32 joy_no);
void make_ai_main();
void dm_effect_make(void);
void dm_game_init_heap(void);
void dm_game_init(bool arg0);
void dm_game_init_static(void);
void dm_game_init_snap_bg(void);
void dm_game_draw_snap_bg(Gfx **gfxP, Mtx **mtxP, Vtx **vtxP, UNK_TYPE arg3);
void func_8006F628(Gfx **gfxP);
enum_main_no dm_game_main(struct NNSched *sc);
s32 dm_game_main2(void);
enum_main_no dm_game_main3(UNK_TYPE arg0);
void dm_game_graphic(void);
void dm_game_graphic2(void);
void dm_game_graphic_onDoneSawp(void);
void func_80071A44(void);
enum_main_no main_techmes(struct NNSched *sc);
void graphic_techmes(void);

// data

extern u8 virus_anime_table[3][4];
extern s8 dm_chaine_se_table_vs_178[4];
extern s8 dm_chaine_se_table_4p_179[4][3];
extern s32 rotate_table_474[];
extern s32 rotate_mtx_475[];
extern bool dm_think_flg;
extern bool visible_fall_point[];
extern char _mesPassword[];
extern char _mesEasyCont[];
extern char _mesEasyNoCont[];
extern char _mesNormalCont[];
extern char _mesNormalNoCont[];
extern char _mesHardCont[];
extern char _mesHardNoCont[];
extern char _mesSHardCont[];
extern char _mesSHardNoCont[];
extern s32 _n_1199[];
extern u8 D_800A7360[];
extern u8 tbl_4589[];
extern Color_RGBA8 col_4590[];

// COMMON

extern struct struct_gameGeom *gameGeom;
extern struct_game_state_data game_state_data[MAX_PLAYERS];
extern struct struct_watchGame *watchGame;
extern enum_evs_gamemode evs_gamemode;
extern u8 CapsMagazine[0x100];
extern struct GameStateBackup *gameBackup[2];

#endif
