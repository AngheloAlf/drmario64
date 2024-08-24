#ifndef RECORD_H
#define RECORD_H

#include "libultra.h"
#include "unk.h"
#include "libc/stdbool.h"

struct MenuRank_unk_001C;
struct struct_evs_cfg_4p;

typedef struct struct_800365B0_arg0 {
    /* 0x00 */ u8 *buffer;
    /* 0x04 */ size_t size;
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ UNK_TYPE4 unk_0C;
    /* 0x10 */ UNK_TYPE4 unk_10;
    /* 0x14 */ UNK_TYPE1 unk_14[0x4];
} struct_800365B0_arg0; // size <= 0x18?

typedef void (*EepRom_WriteDif_arg3)(void*);

typedef enum EepRomStatus {
    /* 0 */ EEPROM_STATUS_0,
    /* 1 */ EEPROM_STATUS_1,
    /* 2 */ EEPROM_STATUS_2,
    /* 3 */ EEPROM_STATUS_3,
    /* 4 */ EEPROM_STATUS_4,
    /* 5 */ EEPROM_STATUS_5
} EepRomStatus;



typedef struct struct_evs_mem_data_unk_B4 {
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
} struct_evs_mem_data_unk_B4; // size >= 0x1A

typedef struct struct_evs_mem_data_unk_28 {
    /* 0x0 */ u32 unk_0; // score?
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ u8 unk_8;
} struct_evs_mem_data_unk_28; // size = 0xC

typedef struct struct_evs_mem_data_unk_4C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ u8 unk_4;
} struct_evs_mem_data_unk_4C; // size = 0x8

typedef struct struct_evs_mem_data_unk_64 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
} struct_evs_mem_data_unk_64; // size = 0x8

typedef struct struct_evs_mem_data_unk_7C {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x4 */ u8 unk_8;
} struct_evs_mem_data_unk_7C; // size = 0xC

typedef struct struct_evs_mem_data {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01[4];
    /* 0x05 */ UNK_TYPE1 unk_05[0x3];
    /* 0x08 */ s32 unk_08[4][2];
    /* 0x28 */ struct_evs_mem_data_unk_28 unk_28[3];
    /* 0x4C */ struct_evs_mem_data_unk_4C unk_4C[3];
    /* 0x64 */ struct_evs_mem_data_unk_64 unk_64[3];
    /* 0x7C */ struct_evs_mem_data_unk_7C unk_7C[3];
    /* 0xA0 */ u16 unk_A0[2];
    /* 0xA4 */ u16 unk_A4[2];
    /* 0xA8 */ u16 unk_A8[2];
    /* 0xAC */ u16 unk_AC[2];
    /* 0xB0 */ u16 unk_B0[2];
    /* 0xB4 */ struct_evs_mem_data_unk_B4 unk_B4;
    /* 0xCE */ UNK_TYPE1 unk_CE[0x2]; // pad?
} struct_evs_mem_data; // size = 0xD0


typedef struct struct_mess_panel_tex_size {
    /* 0x0 */ u16 width;
    /* 0x2 */ u16 height;
    /* 0x4 */ u16 unk_4;
    /* 0x6 */ u16 unk_6;
} struct_mess_panel_tex_size; // size = 0x8



void func_800365B0(struct_800365B0_arg0 *arg0, u8 *buffer, size_t size);
void func_800365C8(struct_800365B0_arg0 *arg0, u8 *buffer, size_t size);
void BitField_PutBit(struct_800365B0_arg0 *arg0, s32 arg1, u32 arg2);
s32 BitField_GetBit(struct_800365B0_arg0 *arg0, s32 arg1);
void dm_init_config_save(struct_evs_mem_data_unk_B4 *arg0);
void func_8003678C(struct struct_evs_cfg_4p *arg0);
void func_800367E0(struct_evs_mem_data_unk_28 *arg0);
void func_800367F0(struct_evs_mem_data_unk_4C *arg0);
void func_800367FC(struct_evs_mem_data_unk_64 *arg0);
void func_80036808(struct_evs_mem_data_unk_7C *arg0);
void dm_init_save_mem(struct_evs_mem_data *arg0);
void dm_init_system_mem(void);
void dm_story_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void dm_level_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void dm_taiQ_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void dm_timeAt_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void dm_vscom_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vc_fl_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vsman_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vm_fl_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vm_ta_set(s32 arg0, s32 arg1, s32 arg2);
// void func_80036EC8();
// void func_80036F1C();
// void _get1PLess();
// void _sort1PMode();
void dm_data_mode_story_sort(struct MenuRank_unk_001C *arg0);
void dm_data_mode_level_sort(struct MenuRank_unk_001C *arg0);
void dm_data_mode_taiQ_sort(struct MenuRank_unk_001C *arg0);
void dm_data_mode_timeAt_sort(struct MenuRank_unk_001C *arg0);
// void func_80037378();
// void func_800373C8();
// void func_80037418();
// void func_80037468();
// void _sortVsMode();
void dm_data_vscom_sort(struct MenuRank_unk_001C *arg0);
void dm_data_vc_fl_sort(struct MenuRank_unk_001C *arg0);
void dm_data_vsman_sort(struct MenuRank_unk_001C *arg0);
void dm_data_vm_fl_sort(struct MenuRank_unk_001C *arg0);
void dm_data_vm_ta_sort(struct MenuRank_unk_001C *arg0);
// void func_8003779C();
void func_80037808(struct_800365B0_arg0 *arg0);
void func_800378B0(struct_800365B0_arg0 *arg0);
void func_80037950(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800379D4(struct_800365B0_arg0 *arg0, s32 arg1);
void RecStory_Compress(struct_800365B0_arg0 *arg0, s32 arg1);
void RecStory_Extract(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80037C7C(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80037D40(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80037DF0(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80037EB4(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80037F64(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80038038(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800380F0(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80038168(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800381DC(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80038254(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800382C8(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80038340(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800383B4(struct_800365B0_arg0 *arg0, s32 arg1);
void func_8003842C(struct_800365B0_arg0 *arg0, s32 arg1);
void func_800384A0(struct_800365B0_arg0 *arg0, s32 arg1);
void func_80038518(struct_800365B0_arg0 *arg0, s32 arg1);
void RecAll_Compress(struct_800365B0_arg0 *arg0);
s32 RecAll_Extract(struct_800365B0_arg0 *arg0, char arg1[4]);
EepRomStatus EepRom_Init(void);
EepRomStatus EepRom_InitFirst(EepRom_WriteDif_arg3 arg0, void *arg1);
void EepRom_InitVars(void);
u8 *func_80038938(bool arg0);
EepRomStatus EepRom_WriteDif(u8 *arg0, u8 *arg1, size_t size, EepRom_WriteDif_arg3 arg3, void *arg4);
EepRomStatus EepRom_ReadAll(void);
EepRomStatus EepRom_WriteAll(EepRom_WriteDif_arg3 arg0, void *arg1);
void EepRom_DumpErrMes(EepRomStatus status);
void EepRom_DumpDataSize(void);
void setSleepTimer(s32 milliseconds);

// .data

extern struct_mess_panel_tex_size mess_panel_tex_size;
extern u16 mess_panel_lut[];
extern u8 mess_panel_tex[];
extern bool _cached_1332;



extern struct_evs_mem_data evs_mem_data[9];


#endif
