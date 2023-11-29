#ifndef MAINMENU_H
#define MAINMENU_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "color.h"
#include "unk.h"
#include "msgwnd.h"
#include "char_anime.h"


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
    /* 0x004 */ s32 unk_004; // enum?
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



typedef struct MenuNumber_unk_14 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x8];
} MenuNumber_unk_14; // size = 0x8

typedef struct MenuNumber {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ MenuNumber_unk_14 unk_14;
    /* 0x1C */ MenuItem unk_1C;
} MenuNumber; // size = 0xAC

typedef struct MenuLvGauge {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
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


typedef struct MenuRank_unk_001C {
    /* 0x0 */ UNK_TYPE unk_0;
} MenuRank_unk_001C; // size >= 0x4

typedef struct MenuRankLabel {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ MenuItem unk_0C;
} MenuRankLabel; // size = 0x9C

typedef struct MenuRankHeader {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ MenuItem unk_08;
    /* 0x98 */ MenuRankLabel unk_98[UNK_SIZE];
} MenuRankHeader; // size >= 0x134

typedef struct MenuRankFig {
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
} MenuRankFig; // size = 0xC8

typedef struct MenuRankBase {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ MenuItem unk_04;
} MenuRankBase; // size = 0x94

typedef struct MenuRankNum {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ MenuItem unk_08;
} MenuRankNum; // size = 0x98

typedef struct MenuRankName {
    /* 0x00 */ UNK_TYPE1 unk_00[0x8];
    /* 0x08 */ MenuItem unk_08;
} MenuRankName; // size = 0x98

typedef struct MenuRankPanel {
    /* 0x000 */ UNK_TYPE1 unk_000[0x4];
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
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
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
    /* 0x0034 */ s32 unk_0034;
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


typedef struct MenuStory {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004[4][2];
    /* 0x0024 */ s32 unk_0024;
    /* 0x0028 */ s32 unk_0028[3];
    /* 0x0034 */ bool unk_0034;
    /* 0x0038 */ void *unk_0038[2];
    /* 0x0040 */ MenuItem unk_0040;
    /* 0x00D0 */ MenuItem unk_00D0;
    /* 0x0160 */ MenuItem unk_0160[2];
    /* 0x0280 */ AnimeState unk_0280[2];
    /* 0x0300 */ MenuCursor unk_0300[2];
    /* 0x07C0 */ MenuSpeedAsk unk_07C0;
    /* 0x085C */ MenuSpeedItem unk_085C;
    /* 0x0EC0 */ MenuNumber unk_0EC0;
    /* 0x0F6C */ MenuItem unk_0F6C;
    /* 0x0FFC */ MenuItem unk_0FFC[2];
    /* 0x111C */ MenuItem unk_111C[2];
    /* 0x123C */ MenuItem unk_123C[2];
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
    /* 0x0004 */ s32 unk_0004;
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
    /* 0x0194 */ MenuItem unk_0194[15];
    /* 0x0A04 */ MenuItem unk_0A04[15];
    /* 0x1274 */ MenuComLvPanel unk_1274[15];
    /* 0x23CC */ MenuCursor unk_23CC[4];
} MenuChSel; // size >= 0x2D4C <= 0x75A4

typedef struct MenuNmEnt {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C[2];
    /* 0x0014 */ s32 unk_0014[2];
    /* 0x001C */ s32 unk_001C[2][2];
    /* 0x002C */ s8 unk_002C[2][4];
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
    /* 0x0020 */ UNK_TYPE1 unk_0020[0x15C];
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


#endif
