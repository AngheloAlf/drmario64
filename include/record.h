#ifndef RECORD_H
#define RECORD_H

#include "libultra.h"
#include "libc/stdbool.h"

struct SRankSortInfo;
struct struct_evs_cfg_4p;

/**
 * Original name: BitField
 */
typedef struct BitField {
    /* 0x00 */ u8 *buffer; /* Original name: buf */
    /* 0x04 */ size_t size; /* Original name: bufSiz */
    /* 0x08 */ s32 bufIdx; /* Original name: bufIdx */
    /* 0x0C */ s32 bitIdx; /* Original name: bitIdx */
    /* 0x10 */ u32 sum; /* Original name: sum */
} BitField; // size = 0x14


// TODO: merge together?
#define SRANKSORTINFO_SORT_LEN 8
#define SRANKSORTINFO_RANK_LEN 8

// TODO: merge with SRANKSORTINFO_SORT_LEN and SRANKSORTINFO_RANK_LEN?
#define SRANKSORTINFO_VSRESULT_LEN 8

#define SRANKSORTINFO_LEVEL_NUM 3

/**
 * Original name: SRankSortInfo
 */
typedef struct SRankSortInfo {
    /* 0x000 */ u8 story_sort[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_SORT_LEN];
    /* 0x018 */ u8 story_rank[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_RANK_LEN];
    /* 0x030 */ u8 level_sort[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_SORT_LEN];
    /* 0x048 */ u8 level_rank[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_RANK_LEN];
    /* 0x060 */ u8 taiQ_sort[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_SORT_LEN];
    /* 0x078 */ u8 taiQ_rank[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_RANK_LEN];
    /* 0x090 */ u8 timeAt_sort[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_SORT_LEN];
    /* 0x0A8 */ u8 timeAt_rank[SRANKSORTINFO_LEVEL_NUM][SRANKSORTINFO_RANK_LEN];
    /* 0x0C0 */ u8 vscom_sort[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x0C8 */ u8 vscom_rank[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x0D0 */ u16 vscom_ave[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x0E0 */ u8 vc_fl_sort[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x0E8 */ u8 vc_fl_rank[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x0F0 */ u16 vc_fl_ave[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x100 */ u8 vsman_sort[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x108 */ u8 vsman_rank[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x110 */ u16 vsman_ave[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x120 */ u8 vm_fl_sort[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x128 */ u8 vm_fl_rank[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x130 */ u16 vm_fl_ave[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x140 */ u8 vm_ta_sort[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x148 */ u8 vm_ta_rank[SRANKSORTINFO_VSRESULT_LEN];
    /* 0x150 */ u16 vm_ta_ave[SRANKSORTINFO_VSRESULT_LEN];
} SRankSortInfo; // size = 0x160


typedef void (EepRom_Proc)(void*);

/**
 * Original name: EepRomErr
 */
typedef enum EepRomErr {
    /* 0 */ EepRomErr_NoError, /* Original name: EepRomErr_NoError */
    /* 1 */ EepRomErr_NotFound, /* Original name: EepRomErr_NotFound */
    /* 2 */ EepRomErr_NotInit, /* Original name: EepRomErr_NotInit */
    /* 3 */ EepRomErr_ReadError, /* Original name: EepRomErr_ReadError */
    /* 4 */ EepRomErr_WriteError, /* Original name: EepRomErr_WriteError */
    /* 5 */ EepRomErr_BadSum, /* Original name: EepRomErr_BadSum */
} EepRomErr;

typedef struct struct_evs_mem_data_config {
    /* 0x00 */ u8 st_lv;
    /* 0x01 */ u8 st_sh;
    /* 0x02 */ u8 st_st;
    /* 0x03 */ u8 st_no;
    /* 0x04 */ u8 p1_lv;
    /* 0x05 */ u8 p1_sp;
    /* 0x06 */ u8 p1_m;
    /* 0x07 */ u8 p1_ta_lv;
    /* 0x08 */ u8 p1_tq_lv;
    /* 0x09 */ u8 vc_fl_lv[2];
    /* 0x0B */ u8 vc_lv[2];
    /* 0x0D */ u8 vc_sp[2];
    /* 0x0F */ u8 vc_no[2];
    /* 0x11 */ u8 vc_st;
    /* 0x12 */ u8 vc_m;
    /* 0x13 */ u8 vm_fl_lv;
    /* 0x14 */ u8 vm_ta_lv;
    /* 0x15 */ u8 vm_lv;
    /* 0x16 */ u8 vm_sp;
    /* 0x17 */ u8 vm_no;
    /* 0x18 */ u8 vm_st;
    /* 0x19 */ u8 vm_m;
} struct_evs_mem_data_config; // size = 0x1A

typedef struct struct_evs_mem_data_story_data {
    /* 0x0 */ u32 score; /* Original name: score */
    /* 0x4 */ u32 time; /* Original name: time */
    /* 0x8 */ u8 c_stage; /* Original name: c_stage */
} struct_evs_mem_data_story_data; // size = 0xC

typedef struct struct_evs_mem_data_level_data {
    /* 0x0 */ u32 score; /* Original name: score */
    /* 0x4 */ u8 c_level; /* Original name: c_level */
} struct_evs_mem_data_level_data; // size = 0x8

typedef struct struct_evs_mem_data_taiQ_data {
    /* 0x0 */ u32 score; /* Original name: score*/
    /* 0x4 */ u32 time; /* Original name: time*/
} struct_evs_mem_data_taiQ_data; // size = 0x8

typedef struct struct_evs_mem_data_timeAt_data {
    /* 0x0 */ u32 score; /* Original name: score */
    /* 0x4 */ u32 time; /* Original name: time */
    /* 0x4 */ u8 erase; /* Original name: erase */
} struct_evs_mem_data_timeAt_data; // size = 0xC

#define MEM_USE_FLG_1 (1 << 0)
#define MEM_USE_FLG_2 (1 << 1)

#define MEM_NAME_LEN 4

#define VSRESULT_LEN 2

typedef struct struct_evs_mem_data {
    /* 0x00 */ u8 mem_use_flg; /* Original name: mem_use_flg */
    /* 0x01 */ u8 mem_name[MEM_NAME_LEN]; /* Original name: mem_name */
    /* 0x08 */ s32 clear_stage[4][2]; /* Original name: clear_stage */
    /* 0x28 */ struct_evs_mem_data_story_data story_data[3]; /* Original name: story_data */
    /* 0x4C */ struct_evs_mem_data_level_data level_data[3]; /* Original name: level_data */
    /* 0x64 */ struct_evs_mem_data_taiQ_data taiQ_data[3]; /* Original name: taiQ_data */
    /* 0x7C */ struct_evs_mem_data_timeAt_data timeAt_data[3]; /* Original name: timeAt_data */
    /* 0xA0 */ u16 vscom_data[VSRESULT_LEN]; /* Original name: vscom_data */
    /* 0xA4 */ u16 vc_fl_data[VSRESULT_LEN]; /* Original name: vc_fl_data */
    /* 0xA8 */ u16 vsman_data[VSRESULT_LEN]; /* Original name: vsman_data */
    /* 0xAC */ u16 vm_fl_data[VSRESULT_LEN]; /* Original name: vm_fl_data */
    /* 0xB0 */ u16 vm_ta_data[VSRESULT_LEN]; /* Original name: vm_ta_data */
    /* 0xB4 */ struct_evs_mem_data_config config; /* Original name: config */
} struct_evs_mem_data; // size = 0xD0



typedef struct struct_mess_panel_tex_size {
    /* 0x0 */ u16 width;
    /* 0x2 */ u16 height;
    /* 0x4 */ u16 unk_4;
    /* 0x6 */ u16 unk_6;
} struct_mess_panel_tex_size; // size = 0x8

void BitField_Attach(BitField *st, u8 *buffer, size_t size);
void BitField_Init(BitField *st, u8 *buffer, size_t size);
void BitField_PutBit(BitField *st, s32 count, u32 bits);
u32 BitField_GetBit(BitField *st, s32 count);

void dm_init_config_save(struct_evs_mem_data_config *config);
void dm_init_config_4p_save(struct struct_evs_cfg_4p *config);
void dm_init_story_save(struct_evs_mem_data_story_data *st);
void dm_init_level_save(struct_evs_mem_data_level_data *st);
void dm_init_taiQ_save(struct_evs_mem_data_taiQ_data *st);
void dm_init_timeAt_save(struct_evs_mem_data_timeAt_data *st);
void dm_init_save_mem(struct_evs_mem_data *mem);
void dm_init_system_mem(void);
void dm_story_sort_set(s32 player_no, s32 char_no, s32 g_level, s32 score, s32 time, s32 c_stage, bool ignoreFlag);
void dm_level_sort_set(s32 player_no, s32 g_speed, s32 score, s32 c_level);
void dm_taiQ_sort_set(s32 player_no, s32 dif, s32 score, s32 time);
void dm_timeAt_sort_set(s32 player_no, s32 dif, s32 score, s32 time, s32 erase);
void dm_vscom_set(s32 player_no, s32 win, s32 lose);
void dm_vc_fl_set(s32 player_no, s32 win, s32 lose);
void dm_vsman_set(s32 player_no, s32 win, s32 lose);
void dm_vm_fl_set(s32 player_no, s32 win, s32 lose);
void dm_vm_ta_set(s32 player_no, s32 win, s32 lose);

void dm_data_mode_story_sort(struct SRankSortInfo *st);
void dm_data_mode_level_sort(struct SRankSortInfo *st);
void dm_data_mode_taiQ_sort(struct SRankSortInfo *st);
void dm_data_mode_timeAt_sort(struct SRankSortInfo *st);

void dm_data_vscom_sort(struct SRankSortInfo *st);
void dm_data_vc_fl_sort(struct SRankSortInfo *st);
void dm_data_vsman_sort(struct SRankSortInfo *st);
void dm_data_vm_fl_sort(struct SRankSortInfo *st);
void dm_data_vm_ta_sort(struct SRankSortInfo *st);

EepRomErr EepRom_Init(void);
EepRomErr EepRom_InitFirst(EepRom_Proc *proc, void *args);
void EepRom_InitVars(void);
u8 *eepRom_longRead(bool forceRead);
EepRomErr EepRom_WriteDif(const void *oldBuf, void *newBuf, size_t size, EepRom_Proc *proc, void *args);
EepRomErr EepRom_ReadAll(void);
EepRomErr EepRom_WriteAll(EepRom_Proc *proc, void *args);
void EepRom_DumpErrMes(EepRomErr status);
void EepRom_DumpDataSize(void);
void setSleepTimer(s32 milliseconds);

// .data

extern struct_mess_panel_tex_size mess_panel_tex_size;
extern u16 mess_panel_lut[];
extern u8 mess_panel_tex[];
extern bool _cached_1332;


extern struct_evs_mem_data evs_mem_data[9];

#endif
