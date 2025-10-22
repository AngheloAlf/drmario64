#ifndef RECORD_H
#define RECORD_H

#include "libultra.h"
#include "unk.h"
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

typedef void (EepRom_WriteDif_arg3)(void*);

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
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09[2];
    /* 0x0B */ u8 unk_0B[2];
    /* 0x0D */ u8 unk_0D[2];
    /* 0x0F */ u8 unk_0F[2];
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
} struct_evs_mem_data_config; // size = 0x1A

#if 0
typedef struct /* struct_dm_game_main_c_13768 */ {
    // total size: 0x1A
    unsigned char st_lv; // offset 0x0, size 0x1
    unsigned char st_sh; // offset 0x1, size 0x1
    unsigned char st_st; // offset 0x2, size 0x1
    unsigned char st_no; // offset 0x3, size 0x1
    unsigned char p1_lv; // offset 0x4, size 0x1
    unsigned char p1_sp; // offset 0x5, size 0x1
    unsigned char p1_m; // offset 0x6, size 0x1
    unsigned char p1_ta_lv; // offset 0x7, size 0x1
    unsigned char p1_tq_lv; // offset 0x8, size 0x1
    unsigned char vc_fl_lv[2]; // offset 0x9, size 0x2
    unsigned char vc_lv[2]; // offset 0xB, size 0x2
    unsigned char vc_sp[2]; // offset 0xD, size 0x2
    unsigned char vc_no[2]; // offset 0xF, size 0x2
    unsigned char vc_st; // offset 0x11, size 0x1
    unsigned char vc_m; // offset 0x12, size 0x1
    unsigned char vm_fl_lv; // offset 0x13, size 0x1
    unsigned char vm_ta_lv; // offset 0x14, size 0x1
    unsigned char vm_lv; // offset 0x15, size 0x1
    unsigned char vm_sp; // offset 0x16, size 0x1
    unsigned char vm_no; // offset 0x17, size 0x1
    unsigned char vm_st; // offset 0x18, size 0x1
    unsigned char vm_m; // offset 0x19, size 0x1
} struct_dm_game_main_c_13768;
#endif



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

#define VSRESULT_LEN 2

typedef struct struct_evs_mem_data {
    /* 0x00 */ u8 mem_use_flg; /* Original name: mem_use_flg */
    /* 0x01 */ u8 mem_name[4]; /* Original name: mem_name */
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
EepRomErr EepRom_InitFirst(EepRom_WriteDif_arg3 proc, void *args);
void EepRom_InitVars(void);
u8 *eepRom_longRead(bool forceRead);
EepRomErr EepRom_WriteDif(const void *oldBuf, void *newBuf, size_t size, EepRom_WriteDif_arg3 proc, void *args);
EepRomErr EepRom_ReadAll(void);
EepRomErr EepRom_WriteAll(EepRom_WriteDif_arg3 proc, void *args);
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
