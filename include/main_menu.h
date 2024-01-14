#ifndef MAINMENU_H
#define MAINMENU_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "color.h"
#include "msgwnd.h"
#include "char_anime.h"
#include "audio/sound.h"
#include "nnsched.h"
#include "main.h"
#include "recwritingmsg.h"
#include "unk.h"

struct MenuItem;
struct struct_watchMenu;

typedef enum MainMenuMode {
    /*  0 */ MAINMENUMODE_MENUMAIN_0,
    /*  1 */ MAINMENUMODE_1,
    /*  2 */ MAINMENUMODE_2,
    /*  3 */ MAINMENUMODE_MENUNMENT_3,
    /*  4 */ MAINMENUMODE_MENUSTORY_4,
    /*  5 */ MAINMENUMODE_5,
    /*  6 */ MAINMENUMODE_MENUNMENT_6,
    /*  7 */ MAINMENUMODE_MENULVSEL_7, // Classic
    /*  8 */ MAINMENUMODE_8,
    /*  9 */ MAINMENUMODE_MENUNMENT_9,
    /* 10 */ MAINMENUMODE_MENULVSEL_10, // Marathon
    /* 11 */ MAINMENUMODE_11,
    /* 12 */ MAINMENUMODE_MENUNMENT_12,
    /* 13 */ MAINMENUMODE_MENULVSEL_13, // Score Attack
    /* 14 */ MAINMENUMODE_14,
    /* 15 */ MAINMENUMODE_MENUNMENT_15,
    /* 16 */ MAINMENUMODE_MENUCHSEL_16,
    /* 17 */ MAINMENUMODE_MENUPLAY2_17,
    /* 18 */ MAINMENUMODE_18,
    /* 19 */ MAINMENUMODE_MENUNMENT_19,
    /* 20 */ MAINMENUMODE_MENUCHSEL_20,
    /* 21 */ MAINMENUMODE_MENUPLAY2_21,
    /* 22 */ MAINMENUMODE_22,
    /* 23 */ MAINMENUMODE_23,
    /* 24 */ MAINMENUMODE_MENUNMENT_24,
    /* 25 */ MAINMENUMODE_MENUCHSEL_25,
    /* 26 */ MAINMENUMODE_MENUPLAY2_26,
    /* 27 */ MAINMENUMODE_27,
    /* 28 */ MAINMENUMODE_MENUNMENT_28,
    /* 29 */ MAINMENUMODE_MENUCHSEL_29,
    /* 30 */ MAINMENUMODE_MENUPLAY2_30,
    /* 31 */ MAINMENUMODE_31,
    /* 32 */ MAINMENUMODE_MENUNMENT_32,
    /* 33 */ MAINMENUMODE_MENUCHSEL_33,
    /* 34 */ MAINMENUMODE_MENUPLAY2_34,
    /* 35 */ MAINMENUMODE_35,
    /* 36 */ MAINMENUMODE_36,
    /* 37 */ MAINMENUMODE_37,
    /* 38 */ MAINMENUMODE_38,
    /* 39 */ MAINMENUMODE_39,
    /* 40 */ MAINMENUMODE_MENUCHSEL_40,
    /* 41 */ MAINMENUMODE_MENUPLAY2_41,
    /* 42 */ MAINMENUMODE_MENUCHSEL_42,
    /* 43 */ MAINMENUMODE_MENUPLAY2_43,
    /* 44 */ MAINMENUMODE_MENUCHSEL_44,
    /* 45 */ MAINMENUMODE_MENUPLAY2_45,
    /* 46 */ MAINMENUMODE_46,
    /* 47 */ MAINMENUMODE_47,
    /* 48 */ MAINMENUMODE_48,
    /* 49 */ MAINMENUMODE_MENURANK_49, // Records / One Player / Story
    /* 50 */ MAINMENUMODE_MENURANK_50, // Records / One Player / Classic
    /* 51 */ MAINMENUMODE_MENURANK_51, // Records / One Player / Marathon
    /* 52 */ MAINMENUMODE_MENURANK_52, // Records / One Player / Score Attack
    /* 53 */ MAINMENUMODE_MENURANK_53, // Records / One Player / Vs.Computer
    /* 54 */ MAINMENUMODE_MENURANK_54, // Records / One Player / Flash
    /* 55 */ MAINMENUMODE_MENURANK_55,
    /* 56 */ MAINMENUMODE_MENURANK_56, // Records / Two Player / 2-Player Vs.
    /* 57 */ MAINMENUMODE_MENURANK_57, // Records / Two Player / Flash
    /* 58 */ MAINMENUMODE_MENURANK_58, // Records / Two Player / Score Attack
    /* 59 */ MAINMENUMODE_59,
    /* 60 */ MAINMENUMODE_60,
    /* 61 */ MAINMENUMODE_61,
    /* 62 */ MAINMENUMODE_62,
    /* 63 */ MAINMENUMODE_MENUNMENT_63,
    /* 64 */ MAINMENUMODE_MENUNMENT_64,
    /* 65 */ MAINMENUMODE_65,
    /* 66 */ MAINMENUMODE_66,
    /* 67 */ MAINMENUMODE_67,
    /* 68 */ MAINMENUMODE_68,
    /* 69 */ MAINMENUMODE_69,
    /* 70 */ MAINMENUMODE_70,
    /* 71 */ MAINMENUMODE_71,
    /* 72 */ MAINMENUMODE_72,
    /* 73 */ MAINMENUMODE_73,
} MainMenuMode;


typedef void (*MenuItem_TransCallback)(struct MenuItem *);
typedef void (*MenuItem_ScaleCallback)(struct MenuItem *);
typedef void (*MenuItem_ColorCallback)(struct MenuItem *);

#define MENUITEM_UNK_LEN 2U
#define MENUITEM_UNK_LEN2 2U

typedef struct MenuItem {
    /* 0x00 */ f32 unk_00[2];
    /* 0x08 */ MenuItem_TransCallback transCallback;
    /* 0x0C */ f32 unk_0C[MENUITEM_UNK_LEN2];
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C[MENUITEM_UNK_LEN2];
    /* 0x24 */ f32 unk_24[MENUITEM_UNK_LEN2];
    /* 0x2C */ MenuItem_ScaleCallback scaleCallback;
    /* 0x30 */ f32 unk_30[MENUITEM_UNK_LEN];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40[MENUITEM_UNK_LEN];
    /* 0x48 */ f32 unk_48[MENUITEM_UNK_LEN];
    /* 0x50 */ MenuItem_ColorCallback colorCallback;
    /* 0x54 */ Color_RGBAf32 color;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C[2][4];
    /* 0x8C */ union {
                    u32 w;
                    struct {
                        bool unk_31:1; // update colors?
                        bool unk_30:1; // update alpha?
                    } b;
                } unk_8C;
} MenuItem; // size = 0x90


typedef struct MenuCursor {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004; // enum? // if enum then remmeber to update menuCursor_draw1
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ union {
                    u32 w;
                    struct {
                        bool unk_31:1;
                        bool unk_30:1;
                        bool unk_29:1;
                        bool unk_28:1;
                    } b;
                } unk_01C;
    /* 0x020 */ MenuItem unk_020;
    /* 0x0B0 */ MenuItem unk_0B0;
    /* 0x140 */ MenuItem unk_140;
    /* 0x1D0 */ MenuItem unk_1D0;
} MenuCursor; // size = 0x260



typedef struct MenuNumber {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10; // bitfield?
    /* 0x14 */ char unk_14[8];
    /* 0x1C */ MenuItem unk_1C;
} MenuNumber; // size = 0xAC

typedef struct MenuLvGauge {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ int unk_008;
    /* 0x00C */ int unk_00C;
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuCursor unk_0A0;
} MenuLvGauge; // size = 0x300

typedef struct MenuSpeedAsk {
    /* 0x0 */ struct struct_watchMenu *watchMenuRef;
    /* 0x4 */ UNK_TYPE unk_4;
    /* 0x8 */ UNK_TYPE unk_8;
    /* 0xC */ MenuItem unk_C;
} MenuSpeedAsk; // size = 0x9C

typedef struct MenuSpeedItem {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ bool unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ MenuItem unk_014;
    /* 0x0A4 */ MenuItem unk_0A4[3];
    /* 0x254 */ MenuItem unk_254[3];
    /* 0x404 */ MenuCursor unk_404;
} MenuSpeedItem; // size = 0x664

typedef struct MenuMusicItem {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ union {
                    u32 w;
                    struct {
                        bool unk_31 : 1;
                    } b;
                } unk_00C;
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuItem unk_0A0[5];
    /* 0x370 */ MenuItem unk_370[5];
    /* 0x640 */ MenuCursor unk_640;
} MenuMusicItem; // size = 0x8A0

typedef struct MenuBottle {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuItem unk_08;
    /* 0x098 */ MenuItem unk_98;
} MenuBottle; // size = 0x128


// Maybe move to record.h?
typedef struct MenuRank_unk_001C {
    /* 0x000 */ u8 unk_000[UNK_SIZE][8];
    /* 0x008 */ UNK_TYPE1 unk_008[0x10];
    /* 0x018 */ u8 unk_018[UNK_SIZE][8];
    /* 0x020 */ UNK_TYPE1 unk_020[0x10];
    /* 0x030 */ u8 unk_030[UNK_SIZE][8];
    /* 0x038 */ UNK_TYPE1 unk_038[0x10];
    /* 0x048 */ u8 unk_048[UNK_SIZE][8];
    /* 0x050 */ UNK_TYPE1 unk_050[0x10];
    /* 0x060 */ u8 unk_060[UNK_SIZE][8];
    /* 0x068 */ UNK_TYPE1 unk_068[0x10];
    /* 0x078 */ u8 unk_078[UNK_SIZE][8];
    /* 0x080 */ UNK_TYPE1 unk_080[0x10];
    /* 0x090 */ u8 unk_090[UNK_SIZE][8];
    /* 0x098 */ UNK_TYPE1 unk_098[0x10];
    /* 0x0A8 */ u8 unk_0A8[UNK_SIZE][8];
    /* 0x0B0 */ UNK_TYPE1 unk_0B0[0x10];
    /* 0x0C0 */ u8 unk_0C0[UNK_SIZE];
    /* 0x0C1 */ UNK_TYPE1 unk_0C1[0x7];
    /* 0x0C8 */ u8 unk_0C8[UNK_SIZE];
    /* 0x0C9 */ UNK_TYPE1 unk_0C9[0x7];
    /* 0x0D0 */ u16 unk_0D0[UNK_SIZE];
    /* 0x0D2 */ UNK_TYPE1 unk_0D2[0xE];
    /* 0x0E0 */ u8 unk_0E0[UNK_SIZE];
    /* 0x0C1 */ UNK_TYPE1 unk_0E1[0x7];
    /* 0x0E8 */ u8 unk_0E8[UNK_SIZE];
    /* 0x0E9 */ UNK_TYPE1 unk_0E9[0x7];
    /* 0x0F0 */ u16 unk_0F0[UNK_SIZE];
    /* 0x0F2 */ UNK_TYPE1 unk_0F2[0xE];
    /* 0x100 */ u8 unk_100[UNK_SIZE];
    /* 0x101 */ UNK_TYPE1 unk_101[0x7];
    /* 0x108 */ u8 unk_108[UNK_SIZE];
    /* 0x109 */ UNK_TYPE1 unk_109[0x7];
    /* 0x110 */ u16 unk_110[UNK_SIZE];
    /* 0x112 */ UNK_TYPE1 unk_112[0xE];
    /* 0x120 */ u8 unk_120[UNK_SIZE];
    /* 0x121 */ UNK_TYPE1 unk_121[0x7];
    /* 0x128 */ u8 unk_128[UNK_SIZE];
    /* 0x129 */ UNK_TYPE1 unk_129[0x7];
    /* 0x130 */ u16 unk_130[UNK_SIZE];
    /* 0x132 */ UNK_TYPE1 unk_132[0xE];
    /* 0x140 */ u8 unk_140[UNK_SIZE];
    /* 0x141 */ UNK_TYPE1 unk_141[0x7];
    /* 0x148 */ u8 unk_148[UNK_SIZE];
    /* 0x149 */ UNK_TYPE1 unk_149[0x7];
    /* 0x150 */ u16 unk_150[UNK_SIZE];
    /* 0x152 */ UNK_TYPE1 unk_152[0x2];
} MenuRank_unk_001C; // size >= 0x154, <= 0x160

typedef struct MenuRankLabel {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ MenuItem unk_0C;
} MenuRankLabel; // size = 0x9C

typedef struct MenuRankHeader {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04; // count of unk_98
    /* 0x08 */ MenuItem unk_08;
    /* 0x98 */ MenuRankLabel unk_98[UNK_SIZE]; // Maybe 5?
} MenuRankHeader; // size >= 0x134

typedef struct MenuRankFig {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04; // enum?
    /* 0x08 */ s32 unk_08; // enum?
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
} MenuRankFig; // size = 0xC8

typedef struct MenuRankBase {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ MenuItem unk_04;
} MenuRankBase; // size = 0x94

typedef struct MenuRankNum {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ MenuItem unk_08;
} MenuRankNum; // size = 0x98

typedef struct MenuRankName {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ u8 unk_04[4];
    /* 0x08 */ MenuItem unk_08;
} MenuRankName; // size = 0x98

typedef struct MenuRankPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuRankBase unk_008;
    /* 0x09C */ MenuRankNum unk_09C;
    /* 0x134 */ MenuRankName unk_134;
    /* 0x1CC */ MenuRankFig unk_1CC;
    /* 0x294 */ MenuRankFig unk_294;
    /* 0x35C */ MenuRankFig unk_35C;
} MenuRankPanel; // size = 0x424

typedef struct MenuRank_unk_590 {
    /* 0x0000 */ s32 unk_0000;
    /* 0x0004 */ MenuRankHeader unk_0004;
    /* 0x0138 */ UNK_TYPE1 unk_0138[0x270];
    /* 0x03A8 */ MenuRankPanel unk_3A8[8];
} MenuRank_unk_590; // size = 0x24C8

#define MENUMAINPANEL_UNK_LEN (6)

typedef struct MenuMainPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ UNK_TYPE1 unk_004[0x4];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010[MENUMAINPANEL_UNK_LEN];
    /* 0x028 */ MenuItem unk_028;
    /* 0x0B8 */ MenuItem unk_0B8[MENUMAINPANEL_UNK_LEN];
    /* 0x418 */ MenuCursor unk_418;
} MenuMainPanel; // size = 0x678


typedef struct MenuNameSelPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C[2];
    /* 0x014 */ s32 unk_014[2];
    /* 0x01C */ s32 unk_01C[2];
    /* 0x024 */ union {
                    u32 w;
                    struct {
                        u32 unk_31 : 1;
                    } b;
                } unk_024;
    /* 0x028 */ MenuItem unk_028;
    /* 0x0B8 */ MenuItem unk_0B8[9];
    /* 0x5C8 */ MenuCursor unk_5C8[2];
} MenuNameSelPanel; // size = 0xA88

typedef struct MenuNameOpPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004*/ s32 unk_004;
    /* 0x008*/ s32 unk_008;
    /* 0x00C */ u8 unk_00C[4];
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuItem unk_0A0;
    /* 0x130 */ MenuItem unk_130[2];
    /* 0x250 */ MenuCursor unk_250;
} MenuNameOpPanel; // size >= 0x4B0

typedef struct MenuSndSelPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ SeqIndex unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ SndIndex unk_010;
    /* 0x014 */ MenuItem unk_014;
    /* 0x0A4 */ MenuItem unk_0A4[4];
    /* 0x2E4 */ MenuNumber unk_2E4[2];
    /* 0x43C */ MenuCursor unk_43C;
} MenuSndSelPanel; // size >= 0x69C

typedef struct MenuCont {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ MenuItem unk_004;
    /* 0x094 */ MenuItem unk_094[5];
    /* 0x364 */ MenuItem unk_364[1];
    /* 0x3F4 */ MenuItem unk_3F4[1];
    /* 0x484 */ MenuItem unk_484[1];
} MenuCont; // size >= 0x514

typedef struct MenuYN {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuItem unk_008;
    /* 0x098 */ MenuItem unk_098[2];
    /* 0x1B8 */ MenuCursor unk_1B8;
    /* 0x418 */ MenuCursor unk_418;
} MenuYN; // size = 0x678

typedef struct MenuMes {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ MenuItem unk_004;
    /* 0x094 */ MessageWnd unk_094;
    /* 0x174 */ MenuCursor unk_174;
} MenuMes; // size >= 0x3D4

typedef struct MenuPlay2Panel {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C;
    /* 0x0010 */ s32 unk_0010;
    /* 0x0014 */ s32 unk_0014;
    /* 0x0018 */ s32 unk_0018;
    /* 0x001C */ s32 unk_001C;
    /* 0x0020 */ CharAnimeMode unk_0020;
    /* 0x0024 */ s32 unk_0024;
    /* 0x0028 */ s32 unk_0028;
    /* 0x002C */ void *unk_002C;
    /* 0x0030 */ union {
                    u32 w;
                    struct {
                        bool bit_31 : 1;
                        bool bit_30 : 1;
                    } b;
                } unk_0030;
    /* 0x0034 */ MenuItem unk_0034;
    /* 0x00C4 */ MenuItem unk_00C4;
    /* 0x0154 */ MenuItem unk_0154;
    /* 0x01E4 */ MenuNumber unk_01E4;
    /* 0x0290 */ MenuLvGauge unk_0290;
    /* 0x0590 */ MenuSpeedAsk unk_0590;
    /* 0x062C */ MenuSpeedItem unk_062C;
    /* 0x0C90 */ AnimeState unk_0C90;
    /* 0x0CD0 */ MenuItem unk_0CD0;
    /* 0x0D60 */ MenuCursor unk_0D60[2];
    /* 0x1220 */ MenuSpeedAsk unk_1220;
    /* 0x12BC */ MenuSpeedItem unk_12BC;
} MenuPlay2Panel; // size = 0x1920

typedef struct MenuPlay2PanelSub {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ MenuItem unk_010;
    /* 0x0A0 */ MenuMusicItem unk_0A0;
    /* 0x940 */ MenuNumber unk_940;
    /* 0x9EC */ MenuItem unk_9EC;
    /* 0xA7C */ MenuItem unk_A7C[2];
    /* 0xB9C */ MenuCursor unk_B9C[2];
} MenuPlay2PanelSub; // size = 0x105C


typedef struct MenuComLvPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ MenuItem unk_008;
    /* 0x098 */ MenuItem unk_098;
} MenuComLvPanel; // size = 0x128



typedef struct MenuMain {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ MainMenuMode mode;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C[8];
    /* 0x002C */ s32 unk_002C;
    /* 0x0030 */ s32 unk_0030;
    /* 0x0034 */ SeqIndex unk_0034;
    /* 0x0038 */ f32 unk_0038;
    /* 0x003C */ MenuMainPanel unk_003C[2];
    /* 0x0D2C */ MenuNameSelPanel unk_0D2C;
    /* 0x17B4 */ MenuNameOpPanel unk_17B4;
    /* 0x1C64 */ MenuSndSelPanel unk_1C64;
    /* 0x2300 */ s32 unk_2300;
    /* 0x2304 */ const char *unk_2304;
    /* 0x2308 */ MessageWnd unk_2308;
    /* 0x2388 */ MenuItem unk_2388;
    /* 0x2418 */ MenuItem unk_2418;
    /* 0x24A8 */ MenuItem unk_24A8;
    /* 0x2538 */ MenuItem unk_2538;
    /* 0x25C8 */ MenuItem unk_25C8;
    /* 0x2658 */ MenuCont unk_2658;
    /* 0x2B6C */ MenuYN unk_2B6C;
    /* 0x31E4 */ MenuMes unk_31E4;
} MenuMain; // size >= 0x35B8

#define MENU_STORY_UNK_LEN 2U
#define MENU_STORY_UNK_LEN_2 2U

typedef struct MenuStory {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004[4][2];
    /* 0x0024 */ s32 unk_0024;
    /* 0x0028 */ s32 unk_0028[3];
    /* 0x0034 */ bool unk_0034;
    /* 0x0038 */ void *unk_0038[2];
    /* 0x0040 */ MenuItem unk_0040;
    /* 0x00D0 */ MenuItem unk_00D0;
    /* 0x0160 */ MenuItem unk_0160[MENU_STORY_UNK_LEN];
    /* 0x0280 */ AnimeState unk_0280[MENU_STORY_UNK_LEN];
    /* 0x0300 */ MenuCursor unk_0300[2];
    /* 0x07C0 */ MenuSpeedAsk unk_07C0;
    /* 0x085C */ MenuSpeedItem unk_085C;
    /* 0x0EC0 */ MenuNumber unk_0EC0;
    /* 0x0F6C */ MenuItem unk_0F6C;
    /* 0x0FFC */ MenuItem unk_0FFC[MENU_STORY_UNK_LEN_2];
    /* 0x111C */ MenuItem unk_111C[2];
    /* 0x123C */ MenuItem unk_123C[MENU_STORY_UNK_LEN_2];
    /* 0x135C */ MenuCursor unk_135C[3];
} MenuStory; // size = 0x2D3C

typedef struct MenuLvSel {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ MainMenuMode unk_0004;
    /* 0x0008 */ MenuItem unk_0008; // root?
    /* 0x0098 */ MenuItem unk_0098[2]; // panels?
    /* 0x01B8 */ MenuNumber virusLvlNumber;
    /* 0x0264 */ MenuLvGauge virusLvlGauge;
    /* 0x0564 */ MenuSpeedAsk speedIcon;
    /* 0x0600 */ MenuSpeedItem speedSelector;
    /* 0x0C64 */ MenuMusicItem musicSelector;
    /* 0x1504 */ MenuBottle bottle;
    /* 0x162C */ MenuCursor unk_162C[3];
    /* 0x1D4C */ MenuItem capsuleSpeedIcon;
    /* 0x1DDC */ MenuItem musicIcon;
    /* 0x1E6C */ MenuSpeedAsk gameLvlIcon;
    /* 0x1F08 */ MenuSpeedItem gameLvlSelector;
    /* 0x256C */ s32 unk_256C;
    /* 0x2570 */ s32 unk_2570;
} MenuLvSel; // size <= 0x75A4

typedef struct MenuPlay2 {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004; // enum?
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C;
    /* 0x0010 */ s32 unk_0010[4];
    /* 0x0020 */ s32 unk_0020;
    /* 0x0024 */ s32 unk_0024[4];
    /* 0x0034 */ MenuItem unk_0034;
    /* 0x00C4 */ s32 unk_00C4;
    /* 0x00C8 */ MenuPlay2Panel unk_00C8[4];
    /* 0x6548 */ MenuPlay2PanelSub unk_6548;
} MenuPlay2; // size = 0x75A4

#define MENU_CH_SEL_UNK_LEN 15U

typedef struct MenuChSel {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008[4];
    /* 0x0018 */ s32 unk_0018[4];
    /* 0x0028 */ s32 unk_0028;
    /* 0x002C */ s32 unk_002C; // bool?
    /* 0x0030 */ s32 unk_0030;
    /* 0x0034 */ s32 unk_0034;
    /* 0x0038 */ s32 unk_0038;
    /* 0x003C */ s32 unk_003C;
    /* 0x0040 */ s32 unk_0040[4];
    /* 0x0050 */ s32 unk_0050[4];
    /* 0x0060 */ s32 unk_0060;
    /* 0x0064 */ s32 unk_0064[4];
    /* 0x0074 */ MenuItem unk_0074;
    /* 0x0104 */ MenuItem unk_0104;
    /* 0x0194 */ MenuItem unk_0194[MENU_CH_SEL_UNK_LEN];
    /* 0x0A04 */ MenuItem unk_0A04[MENU_CH_SEL_UNK_LEN];
    /* 0x1274 */ MenuComLvPanel unk_1274[MENU_CH_SEL_UNK_LEN];
    /* 0x23CC */ MenuCursor unk_23CC[4];
} MenuChSel; // size >= 0x2D4C <= 0x75A4

typedef struct MenuNmEnt {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C[2];
    /* 0x0014 */ s32 unk_0014[2];
    /* 0x001C */ s32 unk_001C[2][2];
    /* 0x002C */ s8 unk_002C[2][4]; // char instead of s8?
    /* 0x0034 */ s32 unk_0034[2];
    /* 0x003C */ MenuItem unk_003C;
    /* 0x00CC */ MenuItem unk_00CC;
    /* 0x015C */ MenuItem unk_015C;
    /* 0x01EC */ MenuItem unk_01EC;
    /* 0x027C */ MenuItem unk_027C;
    /* 0x030C */ MenuCursor unk_030C;
    /* 0x056C */ MenuItem unk_056C;
    /* 0x05FC */ MenuItem unk_05FC;
} MenuNmEnt; // size >= 0x68C <= 0x75A4

typedef struct MenuRank {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ MainMenuMode unk_0004;
    /* 0x0008 */ UNK_TYPE unk_0008;
    /* 0x000C */ UNK_TYPE unk_000C;
    /* 0x0010 */ UNK_TYPE unk_0010;
    /* 0x0014 */ UNK_TYPE unk_0014;
    /* 0x0018 */ UNK_TYPE unk_0018;
    /* 0x001C */ MenuRank_unk_001C unk_001C;
    /* 0x0170 */ UNK_TYPE1 unk_0170[0xC];
    /* 0x017C */ MenuItem unk_017C;
    /* 0x020C */ MenuItem unk_020C[2];
    /* 0x032C */ MenuItem unk_032C;
    /* 0x03BC */ MenuRankLabel unk_03BC;
    /* 0x0458 */ MenuRankLabel unk_0458;
    /* 0x04F4 */ MenuRankLabel unk_04F4;
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


struct struct_watchMenu;

typedef struct struct_watchMenu_unk_02470 {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x60000];
} struct_watchMenu_unk_02470; // size = 0x60000

// menuTitle?
typedef struct struct_watchMenu_unk_02548 {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08[2]; // TODO: make enum?
    /* 0x10 */ MenuItem unk_10[2];
} struct_watchMenu_unk_02548; // size >= 0x130

// Left column: us
// Right column: cn
typedef struct struct_watchMenu {
    /* 0x00000 */ NNSched *sched;
    /* 0x00004 */ NNScClient scClient;
    /* 0x0000C */ OSMesgQueue scMQ;
    /* 0x00024 */ OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    /* 0x00044 */ UNK_TYPE1 unk_00044[4]; // unused/pad?
    /* 0x00048 */ Mtx unk_00048[3][0x10];
    /* 0x00C48 */ Vtx unk_00C48[3][0x80];
    /* 0x02448 */ Mtx *unk_02448[3];
    /* 0x02454 */ Vtx *unk_02454[3];
    /* 0x02460 */ UNK_PTR unk_02460;
    /* 0x02464 */ UNK_TYPE unk_02464;
    /* 0x02468 */ struct_watchMenu_unk_02470 *unk_02468[2];
    /* 0x02470 */ struct_watchMenu_unk_02470 *unk_02470[2];
    /* 0x02478 */ struct TiTexData *unk_02478;
    /* 0x0247C */ struct TiTexData *unk_0247C;
    /* 0x02480 */ struct TiTexData *unk_02480; // unused
    /* 0x02484 */ struct TiTexData *unk_02484;
    /* 0x02488 */ struct TiTexData *unk_02488;
    /* 0x0248C */ struct TiTexData *unk_0248C;
    /* 0x02490 */ struct TiTexData *unk_02490;
    /* 0x02494 */ struct TiTexData *unk_02494;
    /* 0x02498 */ struct TiTexData *unk_02498;
    /* 0x0249C */ struct TiTexData *unk_0249C;
    /* 0x024A0 */ struct TiTexData *unk_024A0;
    /* 0x024A4 */ struct TiTexData *unk_024A4;
    /* 0x024A8 */ struct TiTexData *unk_024A8;
    /* 0x024AC */ struct TiTexData *unk_024AC;
    /* 0x024B0 */ struct TiTexData *unk_024B0;
    /* 0x024B4 */ struct TiTexData *unk_024B4;
    /* 0x024B8 */ MenuItem unk_024B8[1];
    /* 0x02548 */ struct_watchMenu_unk_02548 unk_02548;
    /* 0x02678 */ MenusUnion unk_02678[2];
    /* 0x111C0 */ UNK_TYPE unk_111C0;
    /* 0x111C4 */ UNK_TYPE unk_111C4;
    /* 0x111C8 */ MainMenuMode unk_111C8;
    /* 0x111CC */ MainMenuMode unk_111CC;
    /* 0x111D0 */ MainMenuMode unk_111D0;
    /* 0x111D4 */ enum_main_no unk_111D4;
    #ifdef VERSION_CN
    /*         0x111D8 */ UNK_TYPE4 unk_cn_pad;
    #endif
    /* 0x111D8 0x111DC */ UNK_TYPE unk_111D8;
    /* 0x111DC 0x111E0 */ f32 unk_111DC;
    /* 0x111E0 0x111E4 */ f32 unk_111E0;
    /* 0x111E4 0x111E8 */ UNK_TYPE unk_111E4;
    /* 0x111E8 0x111EC */ UNK_TYPE unk_111E8;
    /* 0x111EC 0x111F0 */ UNK_TYPE unk_111EC;
    /* 0x111F0 0x111F4 */ UNK_TYPE unk_111F0;
    /* 0x111F4 0x111F8 */ UNK_TYPE unk_111F4; // thread priority?
    /* 0x111F8 0x111FC */ RecordWritingMessage recMessage;
} struct_watchMenu; // size_us = 0x11280; size_cn = 0x11288



f32 func_80045DD0(f32 arg0, f32 arg1);
f32 func_80045E18(f32 arg0, f32 arg1);
f32 func_80045E48(f32 arg0);
void func_80045E94(MenuItem *item);
void transFunc_curve(MenuItem *item);
void transFunc_finger(MenuItem *item);
void func_80046008(MenuItem *item);
void scaleFunc_curve(MenuItem *item);
void func_800460DC(MenuItem *item);
void colorFunc_curve(MenuItem *item);
void colorFunc_cursor(MenuItem * item);
void menuItem_init(MenuItem *item, UNK_TYPE xPos, UNK_TYPE yPos);
void menuItem_updateTransScale(MenuItem *item, MenuItem *parent);
void menuItem_updateColor(MenuItem *item, MenuItem *parent);
void func_800464BC(MenuItem *item, MenuItem *parent);
void func_800464F8(MenuItem items[], s32 count, MenuItem *parent);
void func_8004655C(MenuItem *item, s32 arg1);
void func_800465B8(MenuItem *item, s32 arg1);
void func_80046614(MenuItem *item, s32 arg1);

void func_80046670(MenuItem *item, f32 arg1, f32 arg2);
void func_8004667C(MenuItem *item, f32 arg1, f32 arg2);
void func_80046688(MenuItem *item, f32 arg1, f32 arg2);
void func_80046694(MenuItem *item, f32 arg1, f32 arg2);
void func_800466A0(MenuItem *item, f32 arg1, f32 arg2);
void func_800466B8(MenuItem *item, f32 arg0, f32 arg1);
void func_800466D0(MenuItem *item);
void func_80046734(MenuItem *item, f32 arg0, f32 arg1, f32 arg2);
void func_800467E0(MenuItem *item);
void func_80046844(MenuItem *item, Gfx **gfxP);
bool menuItem_outOfScreen(MenuItem *item, s32 arg1, s32 arg2);
bool menuItem_drawTex(MenuItem *item, Gfx **gfxP, struct TiTexData *arg2, s32 arg3);
bool func_80046C74(MenuItem *item, Gfx **gfxP, struct TiTexData *arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 menuItem_drawAlphaTex(MenuItem *item, Gfx **gfxP, struct TiTexData * arg2, struct TiTexData * arg3, s32 arg4);
s32 func_80046F58(MenuItem *item, Gfx **gfxP, struct TiTexData * arg2, s32 arg3, s32 arg4, s32 arg5);
void func_80047074(MenuItem *item, Gfx **gfxP, struct TiTexData *arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
bool func_8004714C(MenuItem *item, Gfx **gfxP, struct TiTexData *arg2, struct TiTexData *arg3, s32 arg4, s32 arg5, s32 arg6);
// void func_800472D0();
void menuTitle_setTitle(struct_watchMenu_unk_02548 *arg0, MainMenuMode arg1);
void func_800474EC(struct_watchMenu_unk_02548 *arg0, struct_watchMenu *watchMenuRef, UNK_TYPE arg2, UNK_TYPE arg3);
void func_80047584(struct_watchMenu_unk_02548 *arg0, MenuItem *item);
void menuTitle_draw(struct_watchMenu_unk_02548 *arg0, Gfx **gfxP);
void func_80047720(MenuCursor *cursor, s32 arg1, s32 arg2);
void func_800477BC(MenuCursor *cursor, s32 arg1, s32 arg2);
void menuCursor_init2(MenuCursor *cursor, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_800479A8(MenuCursor *cursor, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void menuCursor_update(MenuCursor *cursor, MenuItem *arg1);
void menuCursor_draw1(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void menuCursor_draw2(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void func_80048634(MenuCursor *cursorArr[], s32 /*count*/, Gfx **gxfP);
void func_80048680(MenuBottle *bottle, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
void func_800486C8(MenuBottle *bottle, MenuItem *arg1);
void menuBottle_draw(MenuBottle *bottle, Gfx **gxfP);
void func_80048B8C(MenuLvGauge *lvGauge, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_80048C48(MenuLvGauge *lvGauge, s32 arg1);
void func_80048CC8(MenuLvGauge *arg0, MenuItem *arg1);
void menuLvGauge_draw1(MenuLvGauge *lvGaugeP[], s32 count, Gfx **gxfP);
void func_80048FA0(MenuLvGauge *lvGaugeP[], s32 count, Gfx **gxfP);
void func_80049034(MenuLvGauge *lvGaugeArr[], s32 count, Gfx **gfxP);
void func_80049080(MenuYN *yn, s32 arg1, f32 arg2);
void func_800490B8(MenuYN *yn, s32 arg1);
void menuYN_init(MenuYN *yn, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
bool menuYN_input(MenuYN *yn, s32 arg1);
void func_800492D8(MenuYN *yn, MenuItem *parentItem);
void menuYN_draw(MenuYN *yn, Gfx **gfxP);
void func_80049540(MenuMes *mes, s32 arg1, f32 arg2);
void func_80049578(MenuMes *mes, s32 arg1);
void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 ** arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8004970C(MenuMes *mes, const char *arg1);
void func_80049754(MenuMes *mes, MenuItem *parentItem);
void func_800497D0(MenuMes *mes, Gfx **gfxP);
void func_80049894(MenuSpeedAsk *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_800498C4(MenuSpeedAsk *arg0, MenuItem *arg1);
void menuSpeedAsk_draw(MenuSpeedAsk *speedAskArr[], s32 count, Gfx **gxfP);
void menuSpeedItem_init(MenuSpeedItem *speedItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80049C54(MenuSpeedItem *speedItem, s32 arg1);
void menuSpeedItem_update(MenuSpeedItem *arg0, MenuItem *arg1);
void menuSpeedItem_draw1(MenuSpeedItem **speedItemP, s32 count, Gfx **gfxP);
void func_8004A160(MenuSpeedItem *speedItemP[], s32 count, Gfx **gxfP);
void func_8004A1F4(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP);
void menuMusicItem_init(MenuMusicItem *musicItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void menuMusicItem_input(MenuMusicItem *menuMusicItem, s32 arg1);
void menuMusicItem_update(MenuMusicItem *menuMusicItem, MenuItem *arg1);
void menuMusicItem_draw1(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void menuMusicItem_draw2(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void func_8004A814(MenuMusicItem *musicItemArr[], s32 arg1, Gfx **gfxP);
void func_8004A860(MenuNumber *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void menuNumber_update(MenuNumber *menuNumber, MenuItem *item);
void menuNumber_draw(MenuNumber *numberP[], s32 arg1, Gfx **gxfP);
void func_8004AC98(MenuComLvPanel *comLvPanel, s32 arg1, f32 arg2);
void func_8004ACF4(MenuComLvPanel *comLvPanel, s32 arg1);
void func_8004AD10(MenuComLvPanel *comLvPanel, s32 arg1, s32 arg2);
void func_8004AD3C(MenuComLvPanel *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void func_8004AD84(MenuComLvPanel *comLvPanel, MenuItem *parent);
void menuComLvPanel_draw(MenuComLvPanel *comLvPanelP[], s32 count, Gfx **gfxP);
void menuCont_setFade(MenuCont *cont, s32 arg1, f32 arg2);
void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2);
void menuCont_init(MenuCont *cont, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
bool func_8004B43C(MenuCont *cont, s32 arg1);
void func_8004B488(MenuCont *cont, MenuItem *parentItem);
void menuCont_draw(MenuCont *cont, Gfx **gfxP);
void func_8004B774(MenuMainPanel *mainPanel, s32 arg1, f32 arg2);
void menuMainPanel_init(MenuMainPanel *mainPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const s32 *arg4, s32 arg5, s32 arg6);
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 arg1);
void func_8004B98C(MenuMainPanel *arg0, MenuItem *parentItem);
void menuMainPanel_draw(MenuMainPanel *arg0, Gfx **gfxP);
void func_8004BB14(MenuNameSelPanel *nameSelPanel, s32 arg1, f32 arg2);
void menuNameSelPanel_clear(MenuNameSelPanel *nameSelPanel, bool arg1, s32 arg2);
void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, struct_watchMenu *watchMenuRef, bool arg2, s32 arg3, s32 arg4, s32 arg5);
bool func_8004BEB4(MenuNameSelPanel *nameSelPanel, s32 arg1, s32 arg2);
void menuNameSelPanel_input1(MenuNameSelPanel *nameSelPanel, s32 arg1);
bool menuNameSelPanel_input(MenuNameSelPanel *nameSelPanel);
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, MenuItem *parentItem);
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP);
void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2);
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const u8 *arg4, s32 xPos, s32 yPos);
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 arg1);
void func_8004CA30(MenuNameOpPanel *nameOpPanel, MenuItem *parentItem);
void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP);
void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2);
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
bool menuSndSelPanel_input(MenuSndSelPanel *sndSelPanel, s32 arg1);
void func_8004CFB8(MenuSndSelPanel *sndSelPanel, MenuItem *parentItem);
void menuSndSelPanel_draw(MenuSndSelPanel *sndSelPanel, Gfx **gfxP);
void func_8004D258(void *arg);
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, bool arg7, CharAnimeMode arg8, s32 arg9, s32 argA, s32 argB, s32 argC);
void menuPlay2Panel_copyConfig(MenuPlay2Panel *play2Panel, MenuPlay2Panel *arg1);
void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *other);
void menuPlay2Panel_input(MenuPlay2Panel *play2Panel, s32 arg1, s32 arg2, s32 arg3);
void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, MenuItem *parentItem);
void menuPlay2Panel_draw(MenuPlay2Panel *play2PanelArr[], s32 count, Gfx **gfxP);
void func_8004E270(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2);
void func_8004E2B4(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2, f32 arg3);
void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 ** arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 arg1);
void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, MenuItem *parentItem);
void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP);
bool menuMain_setMsgStr(MenuMain *menuMain, MainMenuMode mode, s32 arg2);
void menuMain_initPanel(MenuMain *menuMain, MainMenuMode mode, s32 arg2, s32 arg3);
void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void func_8004F2D8(MenuMain *menuMain);
void func_8004F33C(MenuMain *menuMain);
void menuMain_input(MenuMain *menuMain);
void menuMain_update(MenuMain *menuMain);
void menuMain_drawKaSaMaRu(MenuMain *menuMain, Gfx **gfxP);
void menuMain_draw(MenuMain *menuMain, Gfx **gfxP);
void func_800513F0(s32 arg0, s32 arg1, s32 arg2, s32 *xP, s32 *yP);
void func_80051480(MenuStory *menuStory, s32 arg1, f32 arg2);
void func_800514C4(void *arg);
void menuStory_init(MenuStory *menuStory, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void func_80051974(MenuStory *menuStory);
s32 func_800519CC(MenuStory *menuStory);
s32 func_800519EC(MenuStory *menuStory);
void menuStory_input(MenuStory *menuStory);
void menuStory_update(MenuStory *menuStory);
void menuStory_draw(MenuStory *menuStory, Gfx **gfxP);
void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2);
void menuLvSel_init(MenuLvSel *menuLvSel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void func_80052DF0(MenuLvSel *menuLvSel);
void menuLvSel_input(MenuLvSel *menuLvSel);
void menuLvSel_update(MenuLvSel *menuLvSel);
void menuLvSel_draw(MenuLvSel *menuLvSel, Gfx **gfxP);
void func_8005380C(MenuChSel *menuChSel, s32 arg1, f32 arg2);
void menuChSel_init(MenuChSel *menuChSel, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
bool menuChSel_checkSelected(MenuChSel *menuChSel, s32 arg1, s32 arg2, s32 arg3);
bool func_80053C84(MenuChSel *menuChSel, s32 arg1, s32 arg2);
void menuChSel_input1(MenuChSel *menuChSel, s32 arg1, s32 arg2);
void menuChSel_inputMan(MenuChSel *menuChSel);
void menuChSel_inputCom(MenuChSel *menuChSel);
void menuChSel_input(MenuChSel *menuChSel);
void menuChSel_update(MenuChSel *menuChSel);
void menuChSel_draw(MenuChSel *menuChSel, Gfx **gfxP);
void func_80054A94(MenuPlay2 *menuPlay2, s32 arg1, f32 arg2);
void menuPlay2_init(MenuPlay2 *menuPlay2, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void func_800550F4(MenuPlay2 *menuPlay2);
bool func_80055154(MenuPlay2 *play2, s32 arg1, s32 arg2);
void func_800551BC(MenuPlay2 *menuPlay2, s32 index);
void func_80055254(MenuPlay2 *menuPlay2, s32 arg1);
void menuPlay2_inputMan(MenuPlay2 *play2);
void menuPlay2_inputCpu(MenuPlay2 *play2);
void menuPlay2_input(MenuPlay2 *menuPlay2);
void menuPlay2_update(MenuPlay2 *menuPlay2);
void menuPlay2_draw(MenuPlay2 *menuPlay2, Gfx **gfxP);
void func_80055DFC(MenuNmEnt *menuNmEnt, s32 arg1, f32 arg2);
void menuNmEnt_init(MenuNmEnt *menuNmEnt, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void func_800560D4(MenuNmEnt *nmEnt);
void menuNmEnt_input(MenuNmEnt *menuNmEnt);
void menuNmEnt_update(MenuNmEnt *menuNmEnt);
void menuNmEnt_draw(MenuNmEnt *menuNmEnt, Gfx **gfxP);
void func_80056C84(MenuRankBase *menuRankBase, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
void func_80056CAC(MenuRankBase *arg0, MenuItem *arg1);
void menuRankBase_draw(MenuRankBase *rankBaseArr[], s32 count, Gfx **gfxP);
void func_80056DF0(MenuRankNum *menuRankNum, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void func_80056E1C(MenuRankNum *arg0, MenuItem *arg1);
void menuRankNum_draw(MenuRankNum *rankNumArr[], s32 count, Gfx **gfxP);
void menuRankFig_init(MenuRankFig *menuRankFig, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void menuRankFig_update(MenuRankFig *rankFig, MenuItem *arg1);
void menuRankFig_draw(MenuRankFig *rankFigArr[], s32 count, Gfx **gfxP);
void menuRankName_init(MenuRankName *menuRankName, struct_watchMenu *watchMenuRef, u8 arg2[4], s32 arg3, s32 arg4);
void func_80057724(MenuRankName *arg0, MenuItem *arg1);
void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP);
void func_80057898(MenuRankLabel *menuRankLabel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_800578C8(MenuRankLabel *arg0, MenuItem *arg1);
void menuRankLabel_draw(MenuRankLabel *rankLabelArr[], s32 count, Gfx **gfxP);
void func_80057AFC(MenuRankHeader *menuRankHeader, struct_watchMenu *watchMenuRef, const s32 *arg2, const s32 *arg3, const s32 *arg4, const s32 *arg5, s32 arg6, s32 arg7, s32 arg8);
void func_80057BE8(MenuRankHeader *rankHeader, MenuItem *arg1);
void menuRankHeader_draw(MenuRankHeader *rankHeaderArr[], s32 count, Gfx **gfxP);
void func_80057D24(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, u32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_80057E68(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80057F6C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8005806C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_800581C8(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void menuRankPanel_update(MenuRankPanel *arg0, MenuItem *arg1);
void menuRankPanel_draw(MenuRankPanel **arg0, s32 count, Gfx **gfxP);
void menuRank_setNameBaseScale(MenuRank *menuRank, UNK_TYPE arg1, f32 arg2);
void menuRank_setSlide(MenuRank *menuRank, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3, f32 arg4);
void menuRank_setFrame(MenuRank *menuRank, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3);
void func_80058A24(MenuRank *menuRank, s32 arg1);
void menuRank_setPanel(MenuRank *menuRank, s32 arg1, MainMenuMode arg2, UNK_TYPE arg3);
void menuRank_init(MenuRank *menuRank, struct_watchMenu *watchMenuRef, struct_watchMenu_unk_02470 **arg2);
void menuRank_input(MenuRank *menuRank);
void menuRank_update(MenuRank *menuRank);
void menuRank_draw(MenuRank *menuRank, Gfx **gfxP);

void _eep_writingCallback(void *arg);
void func_80059A58(void *arg);
void func_80059AA4(void *arg);
void func_80059AF0(struct_watchMenu *arg0);
void _eepWritePlayer(struct_watchMenu *arg0);
void _eepErasePlayer(struct_watchMenu *arg0);
void _eepEraseData(struct_watchMenu *arg0);

void _waitRetrace(struct_watchMenu *watchMenuRef);

Mtx **_getMtxPtr(struct_watchMenu *watchMenuRef);
Vtx **_getVtxPtr(struct_watchMenu *watchMenuRef);

struct TiTexData *_getTexChar(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexCommon(struct_watchMenu *watchMenuRef, s32 arg1);
struct TiTexData *func_80059D14(struct_watchMenu *watchMenuRef, s32 arg1);
struct TiTexData *_getTexLevel(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexMain(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexName(struct_watchMenu *arg0, s32 arg1);
struct TiTexData *_getTexP2(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexP4(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexRank(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexSetup(struct_watchMenu *watchMenuRef, s32 index);
struct TiTexData *_getTexStory(struct_watchMenu *arg0, s32 arg1);
struct TiTexData *_getTexGameAl(struct_watchMenu *arg0, s32 arg1);
struct TiTexData *_getTexGameP1(struct_watchMenu *arg0, s32 arg1);
struct TiTexData *_getTexCont(struct_watchMenu *watchMenuRef, s32 arg1);
struct TiTexData *_getTexTutol(struct_watchMenu *watchMenuRef, s32 arg1);
struct TiTexData *_getTexKasa(struct_watchMenu *watchMenuRef, s32 index);

MenuItem *_getRootItem(struct_watchMenu *watchMenuRef);

u32 _getKeyLvl(struct_watchMenu *watchMenuRef, s32 arg1);
u32 _getKeyTrg(struct_watchMenu *watchMenuRef, s32 arg1);
u32 _getKeyRep(struct_watchMenu *watchMenuRef, s32 arg1);

MainMenuMode _getMode(struct_watchMenu *watchMenuRef);
MainMenuMode _getModeOld(struct_watchMenu *watchMenuRef);
void _setMode(struct_watchMenu *watchMenuRef, MainMenuMode arg1);

void _setNextMain(struct_watchMenu *watchMenuRef, enum_main_no arg1);
void _setTitle(struct_watchMenu *watchMenuRef, MainMenuMode arg1);
void _setFadeDir(struct_watchMenu *watchMenuRef, s32 arg1);
void menuAll_init(struct_watchMenu *arg0, UNK_PTR *arg1, NNSched *sc);
void func_8005A2AC(struct_watchMenu *arg0);
void func_8005A2EC(struct_watchMenu *arg0);
void menuAll_changeMenu(struct_watchMenu *arg0);

void menuAll_input(struct_watchMenu *arg0);
void menuAll_update(struct_watchMenu *arg0);
void menuAll_drawBg(struct_watchMenu *arg0, Gfx **gfxP);
void menuAll_draw(struct_watchMenu *arg0, Gfx **gfxP);
enum_main_no main_menu(NNSched *sc);
void graphic_menu(void);


#endif
