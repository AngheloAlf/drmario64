#ifndef MAINMENU_H
#define MAINMENU_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"


struct MenuItem;
struct struct_watchMenu;


typedef enum enum_struct_watchMenu_unk_111CC {
    /*  0 */ STRUCT_WATCHMENU_UNK_111CC_MENUMAIN_0,
    /*  1 */ STRUCT_WATCHMENU_UNK_111CC_1,
    /*  2 */ STRUCT_WATCHMENU_UNK_111CC_2,
    /*  3 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_3,
    /*  4 */ STRUCT_WATCHMENU_UNK_111CC_MENUSTORY_4,
    /*  5 */ STRUCT_WATCHMENU_UNK_111CC_5,
    /*  6 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_6,
    /*  7 */ STRUCT_WATCHMENU_UNK_111CC_MENULVSEL_7,
    /*  8 */ STRUCT_WATCHMENU_UNK_111CC_8,
    /*  9 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_9,
    /* 10 */ STRUCT_WATCHMENU_UNK_111CC_MENULVSEL_10,
    /* 11 */ STRUCT_WATCHMENU_UNK_111CC_11,
    /* 12 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_12,
    /* 13 */ STRUCT_WATCHMENU_UNK_111CC_MENULVSEL_13,
    /* 14 */ STRUCT_WATCHMENU_UNK_111CC_14,
    /* 15 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_15,
    /* 16 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_16,
    /* 17 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_17,
    /* 18 */ STRUCT_WATCHMENU_UNK_111CC_18,
    /* 19 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_19,
    /* 20 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_20,
    /* 21 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_21,
    /* 22 */ STRUCT_WATCHMENU_UNK_111CC_22,
    /* 23 */ STRUCT_WATCHMENU_UNK_111CC_23,
    /* 24 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_24,
    /* 25 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_25,
    /* 26 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_26,
    /* 27 */ STRUCT_WATCHMENU_UNK_111CC_27,
    /* 28 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_28,
    /* 29 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_29,
    /* 30 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_30,
    /* 31 */ STRUCT_WATCHMENU_UNK_111CC_31,
    /* 32 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_32,
    /* 33 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_33,
    /* 34 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_34,
    /* 35 */ STRUCT_WATCHMENU_UNK_111CC_35,
    /* 36 */ STRUCT_WATCHMENU_UNK_111CC_36,
    /* 37 */ STRUCT_WATCHMENU_UNK_111CC_37,
    /* 38 */ STRUCT_WATCHMENU_UNK_111CC_38,
    /* 39 */ STRUCT_WATCHMENU_UNK_111CC_39,
    /* 40 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_40,
    /* 41 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_41,
    /* 42 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_42,
    /* 43 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_43,
    /* 44 */ STRUCT_WATCHMENU_UNK_111CC_MENUCHSEL_44,
    /* 45 */ STRUCT_WATCHMENU_UNK_111CC_MENUPLAY2_45,
    /* 46 */ STRUCT_WATCHMENU_UNK_111CC_46,
    /* 47 */ STRUCT_WATCHMENU_UNK_111CC_47,
    /* 48 */ STRUCT_WATCHMENU_UNK_111CC_48,
    /* 49 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_49,
    /* 50 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_50,
    /* 51 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_51,
    /* 52 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_52,
    /* 53 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_53,
    /* 54 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_54,
    /* 55 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_55,
    /* 56 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_56,
    /* 57 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_57,
    /* 58 */ STRUCT_WATCHMENU_UNK_111CC_MENURANK_58,
    /* 59 */ STRUCT_WATCHMENU_UNK_111CC_59,
    /* 60 */ STRUCT_WATCHMENU_UNK_111CC_60,
    /* 61 */ STRUCT_WATCHMENU_UNK_111CC_61,
    /* 62 */ STRUCT_WATCHMENU_UNK_111CC_62,
    /* 63 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_63,
    /* 64 */ STRUCT_WATCHMENU_UNK_111CC_MENUNMENT_64,
} enum_struct_watchMenu_unk_111CC;


typedef void (*MenuItem_TransCallback)(struct MenuItem *);
typedef void (*MenuItem_ScaleCallback)(struct MenuItem *);
typedef void (*MenuItem_ColorCallback)(struct MenuItem *);

typedef struct MenuItem {
    /* 0x00 */ f32 unk_00[2];
    /* 0x08 */ MenuItem_TransCallback transCallback;
    /* 0x0C */ f32 unk_0C[2];
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C[2];
    /* 0x24 */ f32 unk_24[2];
    /* 0x2C */ MenuItem_ScaleCallback scaleCallback;
    /* 0x30 */ f32 unk_30[2];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40[2];
    /* 0x48 */ f32 unk_48[2];
    /* 0x50 */ MenuItem_ColorCallback colorCallback;
    /* 0x54 */ f32 unk_54[4];
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C[2][4];
    /* 0x8C */ u32 unk_8C;
} MenuItem; // size = 0x90


typedef struct MenuLvSel_unk_162C {
    /* 0x000 */ UNK_TYPE1 unk_000[0x1C];
    /* 0x01C */ u32 unk_01C;
    /* 0x020 */ MenuItem unk_020;
    /* 0x0B0 */ MenuItem unk_0B0;
    /* 0x140 */ MenuItem unk_140;
    /* 0x1D0 */ MenuItem unk_1D0;
} MenuLvSel_unk_162C; // size = 0x260



typedef struct MenuLvSel_unk_01B8_unk_14 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x8];
} MenuLvSel_unk_01B8_unk_14; // size = 0x8

typedef struct MenuLvSel_unk_01B8 {
    /* 0x00 */ struct struct_watchMenu *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ MenuLvSel_unk_01B8_unk_14 unk_14;
    /* 0x1C */ MenuItem unk_1C;
} MenuLvSel_unk_01B8; // size >= 0xAC

typedef struct MenuLvSel_unk_0264 {
    /* 0x000 */ struct struct_watchMenu *unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuLvSel_unk_162C unk_0A0;
} MenuLvSel_unk_0264; // size >= 0x300

typedef struct MenuLvSel_unk_0564 {
    /* 0x0 */ struct struct_watchMenu *unk_0;
    /* 0x4 */ UNK_TYPE unk_4;
    /* 0x8 */ UNK_TYPE unk_8;
    /* 0xC */ MenuItem unk_C;
} MenuLvSel_unk_0564; // size >= 0x9C

typedef struct MenuLvSel_unk_0600 {
    /* 0x000 */ struct struct_watchMenu *unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ MenuItem unk_014;
    /* 0x0A4 */ MenuItem unk_0A4[3];
    /* 0x254 */ MenuItem unk_254[3];
    /* 0x404 */ MenuLvSel_unk_162C unk_404;
} MenuLvSel_unk_0600; // size >= 0x664

typedef struct MenuLvSel_unk_0C64 {
    /* 0x000 */ struct struct_watchMenu *unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ u32 unk_00C;
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuItem unk_0A0[5];
    /* 0x370 */ MenuItem unk_370[5];
    /* 0x640 */ MenuLvSel_unk_162C unk_640; // size 0x260
} MenuLvSel_unk_0C64; // size >= 0x8A0

typedef struct MenuLvSel_unk_1504 {
    /* 0x000 */ struct struct_watchMenu *unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuItem unk_08;
    /* 0x098 */ MenuItem unk_98;
} MenuLvSel_unk_1504; // size >= 0x128

typedef struct MenuRank_unk_001C {
    /* 0x0 */ UNK_TYPE unk_0;
} MenuRank_unk_001C; // size >= 0x4

typedef struct MenuRank_unk_03BC {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ MenuItem unk_0C;
} MenuRank_unk_03BC; // size = 0x9C

typedef struct MenuRank_unk_590_unk_0004 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ MenuItem unk_08;
    /* 0x98 */ MenuRank_unk_03BC unk_98[UNK_SIZE];
} MenuRank_unk_590_unk_0004; // size >= 0x134

typedef struct menuRankFig_update_arg0 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C[UNK_SIZE];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ UNK_TYPE1 unk_28[0xC];
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ MenuItem unk_38;
} menuRankFig_update_arg0; // size = 0xC8

typedef struct MenuRank_unk_590_unk_3A8_unk_008 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ MenuItem unk_04;
} MenuRank_unk_590_unk_3A8_unk_008; // size = 0x94

typedef struct MenuRank_unk_590_unk_3A8_unk_09C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ MenuItem unk_08;
} MenuRank_unk_590_unk_3A8_unk_09C; // size = 0x98

typedef struct MenuRank_unk_590_unk_3A8_unk_134 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ MenuItem unk_08;
} MenuRank_unk_590_unk_3A8_unk_134; // size = 0x98

typedef struct MenuRank_unk_590_unk_3A8 {
    /* 0x000 */ UNK_TYPE1 unk_000[0x4];
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuRank_unk_590_unk_3A8_unk_008 unk_008;
    /* 0x09C */ MenuRank_unk_590_unk_3A8_unk_09C unk_09C;
    /* 0x134 */ MenuRank_unk_590_unk_3A8_unk_134 unk_134;
    /* 0x1CC */ menuRankFig_update_arg0 unk_1CC;
    /* 0x294 */ menuRankFig_update_arg0 unk_294;
    /* 0x35C */ menuRankFig_update_arg0 unk_35C;
} MenuRank_unk_590_unk_3A8; // size = 0x424

typedef struct MenuRank_unk_590 {
    /* 0x0000 */ s32 unk_0000;
    /* 0x0004 */ MenuRank_unk_590_unk_0004 unk_0004;
    /* 0x0138 */ UNK_TYPE1 unk_0138[0x270];
    /* 0x03A8 */ MenuRank_unk_590_unk_3A8 unk_3A8[UNK_SIZE];
    /* 0x07CC */ UNK_TYPE1 unk_07CC[0x1CFC];
} MenuRank_unk_590; // size = 0x24C8


typedef struct MenuMain {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x75A4];
} MenuMain; // size <= 0x75A4

typedef struct MenuStory {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x75A4];
} MenuStory; // size <= 0x75A4

typedef struct MenuLvSel {
    /* 0x0000 */ struct struct_watchMenu *unk_0000;
    /* 0x0004 */ enum_struct_watchMenu_unk_111CC unk_0004;
    /* 0x0008 */ MenuItem unk_0008;
    /* 0x0098 */ MenuItem unk_0098;
    /* 0x0128 */ MenuItem unk_0128;
    /* 0x01B8 */ MenuLvSel_unk_01B8 unk_01B8;
    /* 0x0264 */ MenuLvSel_unk_0264 unk_0264;
    /* 0x0564 */ MenuLvSel_unk_0564 unk_0564;
    /* 0x0600 */ MenuLvSel_unk_0600 unk_0600;
    /* 0x0C64 */ MenuLvSel_unk_0C64 unk_0C64;
    /* 0x1504 */ MenuLvSel_unk_1504 unk_1504;
    /* 0x162C */ MenuLvSel_unk_162C unk_162C[3];
    /* 0x1D4C */ MenuItem unk_1D4C;
    /* 0x1DDC */ MenuItem unk_1DDC;
    /* 0x1E6C */ MenuLvSel_unk_0564 unk_1E6C;
    /* 0x1F08 */ MenuLvSel_unk_0600 unk_1F08;
    /* 0x256C */ s32 unk_256C;
    /* 0x2570 */ s32 unk_2570;
    /* 0x2574 */ UNK_TYPE1 unk_2574[0x5030];
} MenuLvSel; // size <= 0x75A4

typedef struct MenuPlay2 {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x75A4];
} MenuPlay2; // size <= 0x75A4

typedef struct MenuChSel {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x75A4];
} MenuChSel; // size <= 0x75A4

typedef struct MenuNmEnt {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x75A4];
} MenuNmEnt; // size <= 0x75A4

typedef struct MenuRank {
    /* 0x0000 */ struct struct_watchMenu *unk_0000;
    /* 0x0004 */ enum_struct_watchMenu_unk_111CC unk_0004;
    /* 0x0008 */ UNK_TYPE unk_0008;
    /* 0x000C */ UNK_TYPE unk_000C;
    /* 0x0010 */ UNK_TYPE unk_0010;
    /* 0x0014 */ UNK_TYPE unk_0014;
    /* 0x0018 */ UNK_TYPE unk_0018;
    /* 0x001C */ MenuRank_unk_001C unk_001C;
    /* 0x0020 */ UNK_TYPE1 unk_0020[0x15C];
    /* 0x017C */ MenuItem unk_017C;
    /* 0x020C */ MenuItem unk_020C[2];
    /* 0x032C */ MenuItem unk_032C;
    /* 0x03BC */ MenuRank_unk_03BC unk_03BC;
    /* 0x0458 */ MenuRank_unk_03BC unk_0458;
    /* 0x04F4 */ MenuRank_unk_03BC unk_04F4;
    /* 0x0590 */ MenuRank_unk_590 unk_590[2];
    /* 0x4F20 */ UNK_TYPE1 unk_4F20[0x2684];
} MenuRank; // size <= 0x75A4


typedef union MenusUnion {
    MenuMain menuMain;
    MenuStory menuStory;
    MenuLvSel menuLvSel;
    MenuPlay2 menuPlay2;
    MenuChSel menuChSel;
    MenuNmEnt menuNmEnt;
    MenuRank menuRank;
    UNK_TYPE1 forceSize[0x75A4];
} MenusUnion; // size = 0x75A4


#endif
