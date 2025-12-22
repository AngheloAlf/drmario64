#ifndef MAINMENU_H
#define MAINMENU_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "color.h"
#include "msgwnd.h"
#include "char_anime.h"
#include "audio/snd_seq.h"
#include "nnsched.h"
#include "main.h"
#include "record.h"
#include "recwritingmsg.h"
#include "unk.h"

struct SMenuItem;
struct struct_watchMenu;

typedef enum MainMenuMode {
    /*  0 */ MODE_MAIN, /* Original name: MODE_MAIN */
    /*  1 */ MODE_PLAY1, /* Original name: MODE_PLAY1 */
    /*  2 */ MODE_STORY_NS, /* Original name: MODE_STORY_NS */
    /*  3 */ MODE_STORY_NE, /* Original name: MODE_STORY_NE */
    /*  4 */ MODE_STORY, /* Original name: MODE_STORY */
    /*  5 */ MODE_LVSEL_NS, /* Original name: MODE_LVSEL_NS */
    /*  6 */ MODE_LVSEL_NE, /* Original name: MODE_LVSEL_NE */
    /*  7 */ MODE_LVSEL, /* Original name: MODE_LVSEL */ // Classic
    /*  8 */ MODE_LVSEL_TQ_NS, /* Original name: MODE_LVSEL_TQ_NS */
    /*  9 */ MODE_LVSEL_TQ_NE, /* Original name: MODE_LVSEL_TQ_NE */
    /* 10 */ MODE_LVSEL_TQ, /* Original name: MODE_LVSEL_TQ */ // Marathon
    /* 11 */ MODE_LVSEL_TA_NS, /* Original name: MODE_LVSEL_TA_NS */
    /* 12 */ MODE_LVSEL_TA_NE, /* Original name: MODE_LVSEL_TA_NE */
    /* 13 */ MODE_LVSEL_TA, /* Original name: MODE_LVSEL_TA */ // Score Attack
    /* 14 */ MODE_VSCOM_NS, /* Original name: MODE_VSCOM_NS */
    /* 15 */ MODE_VSCOM_NE, /* Original name: MODE_VSCOM_NE */
    /* 16 */ MODE_VSCOM_CH, /* Original name: MODE_VSCOM_CH */
    /* 17 */ MODE_VSCOM, /* Original name: MODE_VSCOM */
    /* 18 */ MODE_VSCOM_FL_NS, /* Original name: MODE_VSCOM_FL_NS */
    /* 19 */ MODE_VSCOM_FL_NE, /* Original name: MODE_VSCOM_FL_NE */
    /* 20 */ MODE_VSCOM_FL_CH, /* Original name: MODE_VSCOM_FL_CH */
    /* 21 */ MODE_VSCOM_FL, /* Original name: MODE_VSCOM_FL */
    /* 22 */ MODE_PLAY2, /* Original name: MODE_PLAY2 */
    /* 23 */ MODE_VSMAN_NS, /* Original name: MODE_VSMAN_NS */
    /* 24 */ MODE_VSMAN_NE, /* Original name: MODE_VSMAN_NE */
    /* 25 */ MODE_VSMAN_CH, /* Original name: MODE_VSMAN_CH */
    /* 26 */ MODE_VSMAN, /* Original name: MODE_VSMAN */
    /* 27 */ MODE_VSMAN_FL_NS, /* Original name: MODE_VSMAN_FL_NS */
    /* 28 */ MODE_VSMAN_FL_NE, /* Original name: MODE_VSMAN_FL_NE */
    /* 29 */ MODE_VSMAN_FL_CH, /* Original name: MODE_VSMAN_FL_CH */
    /* 30 */ MODE_VSMAN_FL, /* Original name: MODE_VSMAN_FL */
    /* 31 */ MODE_VSMAN_TA_NS, /* Original name: MODE_VSMAN_TA_NS */
    /* 32 */ MODE_VSMAN_TA_NE, /* Original name: MODE_VSMAN_TA_NE */
    /* 33 */ MODE_VSMAN_TA_CH, /* Original name: MODE_VSMAN_TA_CH */
    /* 34 */ MODE_VSMAN_TA, /* Original name: MODE_VSMAN_TA */
    /* 35 */ MODE_PLAY4, /* Original name: MODE_PLAY4 */
    /* 36 */ MODE_PLAY4_TYPE1, /* Original name: MODE_PLAY4_TYPE1 */
    /* 37 */ MODE_PLAY4_TYPE2, /* Original name: MODE_PLAY4_TYPE2 */
    /* 38 */ MODE_PLAY4_TYPE3, /* Original name: MODE_PLAY4_TYPE3 */
    /* 39 */ MODE_PLAY4_TYPE4, /* Original name: MODE_PLAY4_TYPE4 */
    /* 40 */ MODE_PLAY4_CH, /* Original name: MODE_PLAY4_CH */
    /* 41 */ MODE_PLAY4_LV, /* Original name: MODE_PLAY4_LV */
    /* 42 */ MODE_PLAY4_TB_CH, /* Original name: MODE_PLAY4_TB_CH */
    /* 43 */ MODE_PLAY4_TB_LV, /* Original name: MODE_PLAY4_TB_LV */
    /* 44 */ MODE_PLAY4_FL_CH, /* Original name: MODE_PLAY4_FL_CH */
    /* 45 */ MODE_PLAY4_FL_LV, /* Original name: MODE_PLAY4_FL_LV */
    /* 46 */ MODE_OPTION, /* Original name: MODE_OPTION */
    /* 47 */ MODE_RECORD_MS, /* Original name: MODE_RECORD_MS */
    /* 48 */ MODE_RECORD_PLAY1, /* Original name: MODE_RECORD_PLAY1 */
    /* 49 */ MODE_RECORD_ST, /* Original name: MODE_RECORD_ST */ // Records / One Player / Story
    /* 50 */ MODE_RECORD_LS, /* Original name: MODE_RECORD_LS */ // Records / One Player / Classic
    /* 51 */ MODE_RECORD_LS_TQ, /* Original name: MODE_RECORD_LS_TQ */ // Records / One Player / Marathon
    /* 52 */ MODE_RECORD_LS_TA, /* Original name: MODE_RECORD_LS_TA */ // Records / One Player / Score Attack
    /* 53 */ MODE_RECORD_VC, /* Original name: MODE_RECORD_VC */ // Records / One Player / Vs.Computer
    /* 54 */ MODE_RECORD_VC_FL, /* Original name: MODE_RECORD_VC_FL */ // Records / One Player / Flash
    /* 55 */ MODE_RECORD_PLAY2, /* Original name: MODE_RECORD_PLAY2 */
    /* 56 */ MODE_RECORD_VM, /* Original name: MODE_RECORD_VM */ // Records / Two Player / 2-Player Vs.
    /* 57 */ MODE_RECORD_VM_FL, /* Original name: MODE_RECORD_VM_FL */ // Records / Two Player / Flash
    /* 58 */ MODE_RECORD_VM_TA, /* Original name: MODE_RECORD_VM_TA */ // Records / Two Player / Score Attack
    /* 59 */ MODE_TUTORIAL, /* Original name: MODE_TUTORIAL */
    /* 60 */ MODE_CONT, /* Original name: MODE_CONT */
    /* 61 */ MODE_NAME_NS, /* Original name: MODE_NAME_NS */
    /* 62 */ MODE_NAME, /* Original name: MODE_NAME */
    /* 63 */ MODE_NAME_NE, /* Original name: MODE_NAME_NE */
    /* 64 */ MODE_NAME_NE2, /* Original name: MODE_NAME_NE2 */
    /* 65 */ MODE_NAME_DEL_YN, /* Original name: MODE_NAME_DEL_YN */
    /* 66 */ MODE_NAME_DEL_MES, /* Original name: MODE_NAME_DEL_MES */
    /* 67 */ MODE_BACKUP, /* Original name: MODE_BACKUP */
    /* 68 */ MODE_BACKUP_YN, /* Original name: MODE_BACKUP_YN */
    /* 69 */ MODE_BACKUP_MES, /* Original name: MODE_BACKUP_MES */
    /* 70 */ MODE_MISC, /* Original name: MODE_MISC */
    /* 71 */ MODE_SOUND, /* Original name: MODE_SOUND */
    /* 72 */ MODE_COUNT, /* Original name: MODE_COUNT */
    /* 73 */ MODE_SCORE, /* Original name: MODE_SCORE */
} MainMenuMode;


typedef void (MenuItem_TransFunc)(struct SMenuItem *);
typedef void (MenuItem_ScaleFunc)(struct SMenuItem *);
typedef void (MenuItem_ColorFunc)(struct SMenuItem *);

#define MENUITEM_DIM 2U
#define MENUITEM_UNK_LEN3 2U
#define MENUITEM_COLOR_COUNT 4U

/** Original name: SMenuItem */
typedef struct SMenuItem {
    /* 0x00 */ f32 center[MENUITEM_DIM]; /* Original name: center */
    /* 0x08 */ MenuItem_TransFunc *transFunc; /* Original name: transFunc */
    /* 0x0C */ f32 trans[MENUITEM_DIM]; /* Original name: trans */ /* Position */
    /* 0x14 */ f32 transTime; /* Original name: transTime */
    /* 0x18 */ f32 transStep; /* Original name: transStep */
    /* 0x1C */ f32 transRange[2][MENUITEM_DIM]; /* Original name: transRange */
    /* 0x2C */ MenuItem_ScaleFunc *scaleFunc; /* Original name: scaleFunc */
    /* 0x30 */ f32 scale[MENUITEM_DIM]; /* Original name: scale */
    /* 0x38 */ f32 scaleTime; /* Original name: scaleTime */
    /* 0x3C */ f32 scaleStep; /* Original name: scaleStep */
    /* 0x40 */ f32 scaleRange[2][MENUITEM_DIM]; /* Original name: scaleRange */
    /* 0x50 */ MenuItem_ColorFunc *colorFunc; /* Original name: colorFunc */
    /* 0x54 */ f32 color[MENUITEM_COLOR_COUNT]; /* Original name: color */
    /* 0x64 */ f32 colorTime; /* Original name: colorTime */
    /* 0x68 */ f32 colorStep; /* Original name: colorStep */
    /* 0x6C */ f32 colorRange[MENUITEM_UNK_LEN3][MENUITEM_COLOR_COUNT]; /* Original name: colorRange */
    /* 0x8C */ struct {
                    bool localColor:1; /* Original name: localColor */
                    bool localAlpha:1; /* Original name: localAlpha */
                } flags; /* Original name: flags */
} SMenuItem; // size = 0x90


#define MENUTITLE_TLT_COUNT 2U

typedef struct MenuTitle {
    /* 0x00 */ struct struct_watchMenu *global; /* Original name: global */
    /* 0x04 */ s32 current; /* Original name: current */
    /* 0x08 */ s32 titleNo[MENUTITLE_TLT_COUNT]; /* Original name: titleNo */ // TODO: make enum?
    /* 0x10 */ SMenuItem miBase[MENUTITLE_TLT_COUNT]; /* Original name: miBase */
} MenuTitle; // size = 0x130


typedef enum CursorType {
    /* 0 */ CURSOR_ITEM,
    /* 1 */ CURSOR_PANEL,
    /* 2 */ CURSOR_WINDOW,
    /* 3 */ CURSOR_THICK,
    /* 4 */ CURSOR_NEW_4P,
    /* 5 */ CURSOR_NEW_MUSIC,
    /* 6 */ CURSOR_NEW_SPEED,
    /* 7 */ CURSOR_NEW_VIRUS_LV_L,
    /* 8 */ CURSOR_NEW_VIRUS_LV_S,
    /* 9 */ CURSOR_TYPE_SUM,
} CursorType;

typedef struct MenuCursor {
    /* 0x000 */ struct struct_watchMenu *global; /* Original name: global */
    /* 0x004 */ CursorType type; /* Original name: type */
    /* 0x008 */ s32 playerCount; /* Original name: playerCount */
    /* 0x00C */ s32 cpuCount; /* Original name: cpuCount */
    /* 0x010 */ s32 playerNo; /* Original name: playerNo */
    /* 0x014 */ s32 size[2]; /* Original name: size */
    /* 0x01C */ struct {
                    bool cursor:1; /* Original name: cursor */
                    bool finger:1; /* Original name: finger */
                    bool player:1; /* Original name: player */
                    bool blink:1; /* Original name: blink */
                } flags; /* Original name: flags */
    /* 0x020 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0B0 */ SMenuItem miCursor; /* Original name: miCursor */
    /* 0x140 */ SMenuItem miFinger; /* Original name: miFinger */
    /* 0x1D0 */ SMenuItem miPlayer; /* Original name: miPlayer */
} MenuCursor; // size = 0x260


typedef struct MenuBottle {
    /* 0x000 */ struct struct_watchMenu *global; /* Original name: global */
    /* 0x004 */ s32 level; /* Original name: level */
    /* 0x008 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x098 */ SMenuItem miVirus; /* Original name: miVirus */
} MenuBottle; // size = 0x128


typedef struct MenuLvGauge {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ int unk_008;
    /* 0x00C */ int unk_00C;
    /* 0x010 */ SMenuItem unk_010;
    /* 0x0A0 */ MenuCursor unk_0A0;
} MenuLvGauge; // size = 0x300

typedef struct MenuYN {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ SMenuItem unk_008;
    /* 0x098 */ SMenuItem unk_098[2];
    /* 0x1B8 */ MenuCursor unk_1B8;
    /* 0x418 */ MenuCursor unk_418;
} MenuYN; // size = 0x678

typedef struct MenuMes {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ SMenuItem unk_004;
    /* 0x094 */ MessageWnd unk_094;
    /* 0x174 */ MenuCursor unk_174;
} MenuMes; // size >= 0x3D4

typedef struct MenuSpeedAsk {
    /* 0x0 */ struct struct_watchMenu *watchMenuRef;
    /* 0x4 */ UNK_TYPE unk_4;
    /* 0x8 */ UNK_TYPE unk_8;
    /* 0xC */ SMenuItem unk_C;
} MenuSpeedAsk; // size = 0x9C

#define MENUSPEEDITEM_UNK_LEN 3U

typedef struct MenuSpeedItem {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ bool unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ SMenuItem unk_014;
    /* 0x0A4 */ SMenuItem unk_0A4[3];
    /* 0x254 */ SMenuItem unk_254[MENUSPEEDITEM_UNK_LEN];
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
    /* 0x010 */ SMenuItem unk_010;
    /* 0x0A0 */ SMenuItem unk_0A0[5];
    /* 0x370 */ SMenuItem unk_370[5];
    /* 0x640 */ MenuCursor unk_640;
} MenuMusicItem; // size = 0x8A0

typedef struct MenuNumber {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10; // bitfield?
    /* 0x14 */ char unk_14[8];
    /* 0x1C */ SMenuItem unk_1C;
} MenuNumber; // size = 0xAC

typedef struct MenuComLvPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ SMenuItem unk_008;
    /* 0x098 */ SMenuItem unk_098;
} MenuComLvPanel; // size = 0x128

#define MENUCONT_UNK_094_LEN 5
#define MENUCONT_UNK_364_LEN 1

typedef struct MenuCont {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ SMenuItem unk_004;
    /* 0x094 */ SMenuItem unk_094[MENUCONT_UNK_094_LEN];
    /* 0x364 */ SMenuItem unk_364[MENUCONT_UNK_364_LEN];
    /* 0x3F4 */ SMenuItem unk_3F4[1];
    /* 0x484 */ SMenuItem unk_484[1];
} MenuCont; // size >= 0x514

#define MENUMAINPANEL_UNK_LEN (6)

typedef struct MenuMainPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ UNK_TYPE1 unk_004[0x4];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010[MENUMAINPANEL_UNK_LEN];
    /* 0x028 */ SMenuItem unk_028;
    /* 0x0B8 */ SMenuItem unk_0B8[MENUMAINPANEL_UNK_LEN];
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
    /* 0x028 */ SMenuItem unk_028;
    /* 0x0B8 */ SMenuItem unk_0B8[9];
    /* 0x5C8 */ MenuCursor unk_5C8[2];
} MenuNameSelPanel; // size = 0xA88

#define MENUNAMEOPPANEL_UNK_LEN 4U

typedef struct MenuNameOpPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ u8 unk_00C[MENUNAMEOPPANEL_UNK_LEN];
    /* 0x010 */ SMenuItem unk_010;
    /* 0x0A0 */ SMenuItem unk_0A0;
    /* 0x130 */ SMenuItem unk_130[2];
    /* 0x250 */ MenuCursor unk_250;
} MenuNameOpPanel; // size >= 0x4B0

#define MENUSNDSELPANEL_UNK_0A4_LEN 4
#define MENUSNDSELPANEL_UNK_2E4_LEN 2

typedef struct MenuSndSelPanel {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ SeqIndex unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ SndIndex unk_010;
    /* 0x014 */ SMenuItem unk_014;
    /* 0x0A4 */ SMenuItem unk_0A4[MENUSNDSELPANEL_UNK_0A4_LEN];
    /* 0x2E4 */ MenuNumber unk_2E4[MENUSNDSELPANEL_UNK_2E4_LEN];
    /* 0x43C */ MenuCursor unk_43C;
} MenuSndSelPanel; // size >= 0x69C

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
    /* 0x0034 */ SMenuItem unk_0034;
    /* 0x00C4 */ SMenuItem unk_00C4;
    /* 0x0154 */ SMenuItem unk_0154;
    /* 0x01E4 */ MenuNumber unk_01E4;
    /* 0x0290 */ MenuLvGauge unk_0290;
    /* 0x0590 */ MenuSpeedAsk unk_0590;
    /* 0x062C */ MenuSpeedItem unk_062C;
    /* 0x0C90 */ SAnimeState unk_0C90;
    /* 0x0CD0 */ SMenuItem unk_0CD0;
    /* 0x0D60 */ MenuCursor unk_0D60[2];
    /* 0x1220 */ MenuSpeedAsk unk_1220;
    /* 0x12BC */ MenuSpeedItem unk_12BC;
} MenuPlay2Panel; // size = 0x1920

#define MENUPLAY2PANELSUB_UNK_17C 2
#define MENUPLAY2PANELSUB_UNK_B9C 2

typedef struct MenuPlay2PanelSub {
    /* 0x000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ SMenuItem unk_010;
    /* 0x0A0 */ MenuMusicItem unk_0A0;
    /* 0x940 */ MenuNumber unk_940;
    /* 0x9EC */ SMenuItem unk_9EC;
    /* 0xA7C */ SMenuItem unk_A7C[MENUPLAY2PANELSUB_UNK_17C];
    /* 0xB9C */ MenuCursor unk_B9C[MENUPLAY2PANELSUB_UNK_B9C];
} MenuPlay2PanelSub; // size = 0x105C

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
    /* 0x2308 */ MessageWnd msgWnd;
    /* 0x2388 */ SMenuItem unk_2388;
    /* 0x2418 */ SMenuItem unk_2418;
    /* 0x24A8 */ SMenuItem unk_24A8;
    /* 0x2538 */ SMenuItem unk_2538;
    /* 0x25C8 */ SMenuItem unk_25C8;
    /* 0x2658 */ MenuCont unk_2658;
    /* 0x2B6C */ MenuYN unk_2B6C;
    /* 0x31E4 */ MenuMes unk_31E4;
} MenuMain; // size >= 0x35B8

#define MENUSTORY_UNK_LEN 2U
#define MENUSTORY_UNK_LEN_2 2U
#define MENUSTORY_UNK_LEN_3 3U
#define MENUSTORY_UNK_LEN_4 2U

typedef struct MenuStory {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004[4][2];
    /* 0x0024 */ s32 unk_0024;
    /* 0x0028 */ s32 unk_0028[3];
    /* 0x0034 */ bool unk_0034;
    /* 0x0038 */ void *unk_0038[2];
    /* 0x0040 */ SMenuItem unk_0040;
    /* 0x00D0 */ SMenuItem unk_00D0;
    /* 0x0160 */ SMenuItem unk_0160[MENUSTORY_UNK_LEN];
    /* 0x0280 */ SAnimeState unk_0280[MENUSTORY_UNK_LEN];
    /* 0x0300 */ MenuCursor unk_0300[MENUSTORY_UNK_LEN];
    /* 0x07C0 */ MenuSpeedAsk unk_07C0;
    /* 0x085C */ MenuSpeedItem unk_085C;
    /* 0x0EC0 */ MenuNumber unk_0EC0;
    /* 0x0F6C */ SMenuItem unk_0F6C;
    /* 0x0FFC */ SMenuItem unk_0FFC[MENUSTORY_UNK_LEN_2];
    /* 0x111C */ SMenuItem unk_111C[MENUSTORY_UNK_LEN_4];
    /* 0x123C */ SMenuItem unk_123C[MENUSTORY_UNK_LEN_2];
    /* 0x135C */ MenuCursor unk_135C[MENUSTORY_UNK_LEN_3];
} MenuStory; // size = 0x2D3C


#define MENULVSEL_UNK_162C_LEN 3

typedef struct MenuLvSel {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ MainMenuMode unk_0004;
    /* 0x0008 */ SMenuItem unk_0008; // root?
    /* 0x0098 */ SMenuItem unk_0098[2]; // panels?
    /* 0x01B8 */ MenuNumber virusLvlNumber;
    /* 0x0264 */ MenuLvGauge virusLvlGauge;
    /* 0x0564 */ MenuSpeedAsk speedIcon;
    /* 0x0600 */ MenuSpeedItem speedSelector;
    /* 0x0C64 */ MenuMusicItem musicSelector;
    /* 0x1504 */ MenuBottle bottle;
    /* 0x162C */ MenuCursor unk_162C[MENULVSEL_UNK_162C_LEN];
    /* 0x1D4C */ SMenuItem capsuleSpeedIcon;
    /* 0x1DDC */ SMenuItem musicIcon;
    /* 0x1E6C */ MenuSpeedAsk gameLvlIcon;
    /* 0x1F08 */ MenuSpeedItem gameLvlSelector;
    /* 0x256C */ s32 unk_256C;
    /* 0x2570 */ s32 unk_2570;
} MenuLvSel; // size <= 0x75A4

#define MENUCH_SEL_UNK_LEN 15U

typedef struct MenuChSel {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008[4];
    /* 0x0018 */ s32 unk_0018[4];
    /* 0x0028 */ s32 unk_0028;
    /* 0x002C */ s32 unk_002C; // bool?
    /* 0x0030 */ s32 unk_0030; /* ThinkLevel? */
    /* 0x0034 */ s32 unk_0034;
    /* 0x0038 */ s32 unk_0038;
    /* 0x003C */ s32 unk_003C;
    /* 0x0040 */ s32 unk_0040[4];
    /* 0x0050 */ s32 unk_0050[4];
    /* 0x0060 */ s32 unk_0060;
    /* 0x0064 */ s32 unk_0064[4];
    /* 0x0074 */ SMenuItem unk_0074;
    /* 0x0104 */ SMenuItem unk_0104;
    /* 0x0194 */ SMenuItem unk_0194[MENUCH_SEL_UNK_LEN];
    /* 0x0A04 */ SMenuItem unk_0A04[MENUCH_SEL_UNK_LEN];
    /* 0x1274 */ MenuComLvPanel unk_1274[MENUCH_SEL_UNK_LEN];
    /* 0x23CC */ MenuCursor unk_23CC[4];
} MenuChSel; // size >= 0x2D4C <= 0x75A4

typedef struct MenuPlay2 {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004; // enum?
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C;
    /* 0x0010 */ s32 unk_0010[4];
    /* 0x0020 */ s32 unk_0020;
    /* 0x0024 */ s32 unk_0024[4];
    /* 0x0034 */ SMenuItem unk_0034;
    /* 0x00C4 */ s32 unk_00C4;
    /* 0x00C8 */ MenuPlay2Panel unk_00C8[4];
    /* 0x6548 */ MenuPlay2PanelSub unk_6548;
} MenuPlay2; // size = 0x75A4

typedef struct MenuNmEnt {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C[2];
    /* 0x0014 */ s32 unk_0014[2];
    /* 0x001C */ s32 unk_001C[2][2];
    /* 0x002C */ s8 unk_002C[2][4]; // char instead of s8?
    /* 0x0034 */ s32 unk_0034[2];
    /* 0x003C */ SMenuItem unk_003C;
    /* 0x00CC */ SMenuItem unk_00CC;
    /* 0x015C */ SMenuItem unk_015C;
    /* 0x01EC */ SMenuItem unk_01EC;
    /* 0x027C */ SMenuItem unk_027C;
    /* 0x030C */ MenuCursor unk_030C;
    /* 0x056C */ SMenuItem unk_056C;
    /* 0x05FC */ SMenuItem unk_05FC;
} MenuNmEnt; // size >= 0x68C <= 0x75A4

typedef struct MenuRankBase {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ SMenuItem unk_04;
} MenuRankBase; // size = 0x94

typedef struct MenuRankNum {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ SMenuItem unk_08;
} MenuRankNum; // size = 0x98


typedef enum MenuRankFigColor {
    /* 0 */ MENURANKFIG_COLOR_WHITE,
    /* 1 */ MENURANKFIG_COLOR_RED,
    /* 2 */ MENURANKFIG_COLOR_BLUE,
    /* 3 */ MENURANKFIG_COLOR_YELLOW,
    /* 4 */ MENURANKFIG_COLOR_GREEN,
    /* 5 */ MENURANKFIG_COLOR_ORANGE,
    /* 6 */ MENURANKFIG_COLOR_PINK,
    /* 7 */ MENURANKFIG_COLOR_CYAN,
    /* 8 */ MENURANKFIG_COLOR_MAX
} MenuRankFigColor;

typedef struct MenuRankFig {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04; // enum?
    /* 0x08 */ s32 unk_08; // enum?
    /* 0x0C */ s32 unk_0C[7];
    /* 0x28 */ UNK_TYPE1 unk_28[0xC];
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ SMenuItem unk_38;
} MenuRankFig; // size = 0xC8

typedef struct MenuRankName {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ u8 unk_04[4];
    /* 0x08 */ SMenuItem unk_08;
} MenuRankName; // size = 0x98

typedef struct MenuRankLabel {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 type;
    /* 0x08 */ s32 id;
    /* 0x0C */ SMenuItem unk_0C;
} MenuRankLabel; // size = 0x9C

#define MENURANKHEADER_UNK_98 5

typedef struct MenuRankHeader {
    /* 0x00 */ struct struct_watchMenu *watchMenuRef;
    /* 0x04 */ s32 unk_04; // count of unk_98
    /* 0x08 */ SMenuItem unk_08;
    /* 0x98 */ MenuRankLabel unk_98[MENURANKHEADER_UNK_98];
} MenuRankHeader; // size = 0x3A4

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
    /* 0x03A8 */ MenuRankPanel unk_3A8[8];
} MenuRank_unk_590; // size = 0x24C8

typedef struct MenuRank {
    /* 0x0000 */ struct struct_watchMenu *watchMenuRef;
    /* 0x0004 */ MainMenuMode unk_0004;
    /* 0x0008 */ UNK_TYPE unk_0008;
    /* 0x000C */ UNK_TYPE unk_000C;
    /* 0x0010 */ UNK_TYPE unk_0010;
    /* 0x0014 */ UNK_TYPE unk_0014;
    /* 0x0018 */ UNK_TYPE unk_0018;
    /* 0x001C */ SRankSortInfo unk_001C;
    /* 0x017C */ SMenuItem unk_017C;
    /* 0x020C */ SMenuItem unk_020C[2];
    /* 0x032C */ SMenuItem unk_032C;
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
} MenusUnion; // size = 0x75A4


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
    /* 0x02464 */ size_t unk_02464;
    /* 0x02468 */ void *unk_02468[2];
    /* 0x02470 */ void *unk_02470[2];
    /* 0x02478 */ struct TiTexData *unk_02478; // TODO: enums to access those. Should the enum be shared or different for each?
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
    /* 0x024B8 */ SMenuItem unk_024B8[1];
    /* 0x02548 */ MenuTitle unk_02548;
    /* 0x02678 */ MenusUnion unk_02678[2];
    /* 0x111C0 */ UNK_TYPE unk_111C0;
    /* 0x111C4 */ UNK_TYPE unk_111C4;
    /* 0x111C8 */ MainMenuMode unk_111C8;
    /* 0x111CC */ MainMenuMode unk_111CC;
    /* 0x111D0 */ MainMenuMode unk_111D0;
    /* 0x111D4 */ enum_main_no unk_111D4;
    #ifdef NN_SC_PERF
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



void transFunc_linear(SMenuItem *item);
void transFunc_curve(SMenuItem *item);
void transFunc_finger(SMenuItem *item);
void scaleFunc_linear(SMenuItem *item);
void scaleFunc_curve(SMenuItem *item);
void colorFunc_linear(SMenuItem *item);
void colorFunc_curve(SMenuItem *item);
void colorFunc_cursor(SMenuItem * item);
void menuItem_init(SMenuItem *item, s32 x, s32 y);
void menuItem_updateTransScale(SMenuItem *item, SMenuItem *parent);
void menuItem_updateColor(SMenuItem *item, SMenuItem *parent);
void menuItem_update(SMenuItem *item, SMenuItem *parent);
void menuItem_updateN(SMenuItem items[], s32 count, SMenuItem *parent);
void menuItem_setTransDir(SMenuItem *item, s32 dir);
void menuItem_setScaleDir(SMenuItem *item, s32 dir);
void menuItem_setColorDir(SMenuItem *item, s32 dir);

void menuItem_setTransLow(SMenuItem *item, f32 x, f32 y);
void menuItem_setTransHi(SMenuItem *item, f32 x, f32 y);
void menuItem_setScaleLow(SMenuItem *item, f32 x, f32 y);
void menuItem_setScaleHi(SMenuItem *item, f32 x, f32 y);
void menuItem_setColorLow(SMenuItem *item, f32 bright, f32 alpha);
void menuItem_setColorHi(SMenuItem *item, f32 bright, f32 alpha);
void menuItem_setColor_cursor(SMenuItem *item);
void menuItem_setColor_cursor2(SMenuItem *item, f32 red, f32 green, f32 blue);
void menuItem_setColor_fade(SMenuItem *item);
void menuItem_setPrim(SMenuItem *item, Gfx **gfxP);
bool menuItem_outOfScreen(SMenuItem *item, s32 width, s32 height);
bool menuItem_drawTex(SMenuItem *item, Gfx **gfxP, struct TiTexData *tex, bool cached);
bool menuItem_drawTex2(SMenuItem *item, Gfx **gfxP, struct TiTexData *tex, bool cached, f32 x, f32 y, f32 sx, f32 sy);
bool menuItem_drawAlphaTex(SMenuItem *item, Gfx **gfxP, struct TiTexData *texC, struct TiTexData *texA, bool cached);
bool menuItem_drawItem(SMenuItem *item, Gfx **gfxP, struct TiTexData *tex, bool cached, s32 itemCount, s32 itemIndex);
bool menuItem_drawItem2(SMenuItem *item, Gfx **gfxP, struct TiTexData *tex, bool cached, s32 itemCount, s32 itemIndex,
                        f32 x, f32 y, f32 sx, f32 sy);
bool menuItem_drawAlphaItem(SMenuItem *item, Gfx **gfxP, struct TiTexData *texC, struct TiTexData *texA, bool cached,
                            s32 itemCount, s32 itemIndex);
// void menuItem_drawAlphaItem2();
void menuTitle_setTitle(MenuTitle *title, MainMenuMode mode);
void menuTitle_init(MenuTitle *title, struct_watchMenu *global, UNK_TYPE x, UNK_TYPE y);
void menuTitle_update(MenuTitle *title, SMenuItem *parent);
void menuTitle_draw(MenuTitle *title, Gfx **gfxP);
void menuCursor_setFingerPos(MenuCursor *cursor, s32 x, s32 y);
void menuCursor_setPlayerPos(MenuCursor *cursor, s32 x, s32 y);
void menuCursor_init2(MenuCursor *cursor, struct_watchMenu *global, CursorType type, s32 playerCount, s32 cpuCount,
                      s32 playerNo, s32 x, s32 y, s32 w, s32 h);
void menuCursor_init(MenuCursor *cursor, struct_watchMenu *global, CursorType type, s32 playerNo, s32 x, s32 y, s32 w,
                     s32 h);
void menuCursor_update(MenuCursor *cursor, SMenuItem *parent);
void menuCursor_draw1(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void menuCursor_draw2(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void menuCursor_draw(MenuCursor *cursorArr[], s32 /*count*/, Gfx **gxfP);
void menuBottle_init(MenuBottle *bottle, struct_watchMenu *global, s32 x, s32 y);
void menuBottle_update(MenuBottle *bottle, SMenuItem *parent);
void menuBottle_draw(MenuBottle *bottle, Gfx **gxfP);
void func_80048B8C(MenuLvGauge *lvGauge, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_80048C48(MenuLvGauge *lvGauge, s32 arg1);
void func_80048CC8(MenuLvGauge *arg0, SMenuItem *arg1);
void menuLvGauge_draw1(MenuLvGauge *lvGaugeP[], s32 count, Gfx **gxfP);
void func_80048FA0(MenuLvGauge *lvGaugeP[], s32 count, Gfx **gxfP);
void func_80049034(MenuLvGauge *lvGaugeArr[], s32 count, Gfx **gfxP);
void func_80049080(MenuYN *yn, s32 arg1, f32 arg2);
void func_800490B8(MenuYN *yn, s32 arg1);
void menuYN_init(MenuYN *yn, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
bool menuYN_input(MenuYN *yn, s32 arg1);
void func_800492D8(MenuYN *yn, SMenuItem *parentItem);
void menuYN_draw(MenuYN *yn, Gfx **gfxP);
void func_80049540(MenuMes *mes, s32 arg1, f32 arg2);
void func_80049578(MenuMes *mes, s32 arg1);
void menuMes_init(MenuMes *mes, struct_watchMenu *watchMenuRef, void **heapP, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8004970C(MenuMes *mes, const char *arg1);
void func_80049754(MenuMes *mes, SMenuItem *parentItem);
void func_800497D0(MenuMes *mes, Gfx **gfxP);
void func_80049894(MenuSpeedAsk *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_800498C4(MenuSpeedAsk *arg0, SMenuItem *arg1);
void menuSpeedAsk_draw(MenuSpeedAsk *speedAskArr[], s32 count, Gfx **gxfP);
void menuSpeedItem_init(MenuSpeedItem *speedItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80049C54(MenuSpeedItem *speedItem, s32 arg1);
void menuSpeedItem_update(MenuSpeedItem *arg0, SMenuItem *arg1);
void menuSpeedItem_draw1(MenuSpeedItem **speedItemP, s32 count, Gfx **gfxP);
void func_8004A160(MenuSpeedItem *speedItemP[], s32 count, Gfx **gxfP);
void func_8004A1F4(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP);
void menuMusicItem_init(MenuMusicItem *musicItem, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void menuMusicItem_input(MenuMusicItem *menuMusicItem, s32 arg1);
void menuMusicItem_update(MenuMusicItem *menuMusicItem, SMenuItem *arg1);
void menuMusicItem_draw1(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void menuMusicItem_draw2(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void func_8004A814(MenuMusicItem *musicItemArr[], s32 arg1, Gfx **gfxP);
void func_8004A860(MenuNumber *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void menuNumber_update(MenuNumber *menuNumber, SMenuItem *item);
void menuNumber_draw(MenuNumber *numberP[], s32 arg1, Gfx **gxfP);
void func_8004AC98(MenuComLvPanel *comLvPanel, s32 arg1, f32 arg2);
void func_8004ACF4(MenuComLvPanel *comLvPanel, s32 arg1);
void func_8004AD10(MenuComLvPanel *comLvPanel, s32 arg1, s32 arg2);
void func_8004AD3C(MenuComLvPanel *arg0, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void func_8004AD84(MenuComLvPanel *comLvPanel, SMenuItem *parent);
void menuComLvPanel_draw(MenuComLvPanel *comLvPanelP[], s32 count, Gfx **gfxP);
void menuCont_setFade(MenuCont *cont, s32 arg1, f32 arg2);
void func_8004B2C8(MenuCont *cont, s32 arg1, s32 arg2);
void menuCont_init(MenuCont *cont, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
bool func_8004B43C(MenuCont *cont, s32 arg1);
void func_8004B488(MenuCont *cont, SMenuItem *parentItem);
void menuCont_draw(MenuCont *cont, Gfx **gfxP);
void func_8004B774(MenuMainPanel *mainPanel, s32 arg1, f32 arg2);
void menuMainPanel_init(MenuMainPanel *mainPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const s32 *arg4, s32 arg5, s32 arg6);
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 arg1);
void func_8004B98C(MenuMainPanel *arg0, SMenuItem *parentItem);
void menuMainPanel_draw(MenuMainPanel *arg0, Gfx **gfxP);
void func_8004BB14(MenuNameSelPanel *nameSelPanel, s32 arg1, f32 arg2);
void menuNameSelPanel_clear(MenuNameSelPanel *nameSelPanel, bool arg1, s32 arg2);
void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, struct_watchMenu *watchMenuRef, bool arg2, s32 arg3, s32 arg4, s32 arg5);
bool func_8004BEB4(MenuNameSelPanel *nameSelPanel, s32 arg1, s32 arg2);
void menuNameSelPanel_input1(MenuNameSelPanel *nameSelPanel, s32 arg1);
bool menuNameSelPanel_input(MenuNameSelPanel *nameSelPanel);
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, SMenuItem *parentItem);
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP);
void func_8004C820(MenuNameOpPanel *nameOpPanel, s32 arg1, f32 arg2);
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, const u8 *arg4, s32 xPos, s32 yPos);
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 arg1);
void func_8004CA30(MenuNameOpPanel *nameOpPanel, SMenuItem *parentItem);
void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP);
void func_8004CCD0(MenuSndSelPanel *sndSelPanel, s32 arg1, f32 arg2);
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
bool menuSndSelPanel_input(MenuSndSelPanel *sndSelPanel, s32 arg1);
void func_8004CFB8(MenuSndSelPanel *sndSelPanel, SMenuItem *parentItem);
void menuSndSelPanel_draw(MenuSndSelPanel *sndSelPanel, Gfx **gfxP);
void func_8004D258(void *arg);
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, struct_watchMenu *watchMenuRef, void **heapP, s32 arg3, s32 arg4,
                         s32 arg5, s32 arg6, bool arg7, CharAnimeMode arg8, s32 arg9, s32 argA, s32 argB, s32 argC);
void menuPlay2Panel_copyConfig(MenuPlay2Panel *play2Panel, MenuPlay2Panel *arg1);
void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *other);
void menuPlay2Panel_input(MenuPlay2Panel *play2Panel, s32 arg1, s32 arg2, s32 arg3);
void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, SMenuItem *parentItem);
void menuPlay2Panel_draw(MenuPlay2Panel *play2PanelArr[], s32 count, Gfx **gfxP);
void func_8004E270(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2);
void func_8004E2B4(MenuPlay2PanelSub *play2PanelSub, s32 arg1, f32 arg2, f32 arg3);
void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, struct_watchMenu *watchMenuRef, void **heapP, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 arg1);
void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, SMenuItem *parentItem);
void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP);
bool menuMain_setMsgStr(MenuMain *menuMain, MainMenuMode mode, s32 arg2);
void menuMain_initPanel(MenuMain *menuMain, MainMenuMode mode, s32 arg2, s32 arg3);
void menuMain_init(MenuMain *menuMain, struct_watchMenu *watchMenuRef, void **heapP);
void func_8004F2D8(MenuMain *menuMain);
void func_8004F33C(MenuMain *menuMain);
void menuMain_input(MenuMain *menuMain);
void menuMain_update(MenuMain *menuMain);
void menuMain_drawKaSaMaRu(MenuMain *menuMain, Gfx **gfxP);
void menuMain_draw(MenuMain *menuMain, Gfx **gfxP);
void func_800513F0(s32 arg0, s32 arg1, s32 arg2, s32 *xP, s32 *yP);
void func_80051480(MenuStory *menuStory, s32 arg1, f32 arg2);
void func_800514C4(void *arg);
void menuStory_init(MenuStory *menuStory, struct_watchMenu *watchMenuRef, void **heapP);
void func_80051974(MenuStory *menuStory);
s32 func_800519CC(MenuStory *menuStory);
s32 func_800519EC(MenuStory *menuStory);
void menuStory_input(MenuStory *menuStory);
void menuStory_update(MenuStory *menuStory);
void menuStory_draw(MenuStory *menuStory, Gfx **gfxP);
void func_800529FC(MenuLvSel *menuLvSel, s32 arg1, f32 arg2);
void menuLvSel_init(MenuLvSel *menuLvSel, struct_watchMenu *watchMenuRef, void **heapP);
void func_80052DF0(MenuLvSel *menuLvSel);
void menuLvSel_input(MenuLvSel *menuLvSel);
void menuLvSel_update(MenuLvSel *menuLvSel);
void menuLvSel_draw(MenuLvSel *menuLvSel, Gfx **gfxP);
void func_8005380C(MenuChSel *menuChSel, s32 arg1, f32 arg2);
void menuChSel_init(MenuChSel *menuChSel, struct_watchMenu *watchMenuRef, void **heapP);
bool menuChSel_checkSelected(MenuChSel *menuChSel, s32 arg1, s32 arg2, s32 arg3);
bool func_80053C84(MenuChSel *menuChSel, s32 arg1, s32 arg2);
void menuChSel_input1(MenuChSel *menuChSel, s32 arg1, s32 arg2);
void menuChSel_inputMan(MenuChSel *menuChSel);
void menuChSel_inputCom(MenuChSel *menuChSel);
void menuChSel_input(MenuChSel *menuChSel);
void menuChSel_update(MenuChSel *menuChSel);
void menuChSel_draw(MenuChSel *menuChSel, Gfx **gfxP);
void func_80054A94(MenuPlay2 *menuPlay2, s32 arg1, f32 arg2);
void menuPlay2_init(MenuPlay2 *menuPlay2, struct_watchMenu *watchMenuRef, void **heapP);
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
void menuNmEnt_init(MenuNmEnt *menuNmEnt, struct_watchMenu *watchMenuRef, void **heapP);
void func_800560D4(MenuNmEnt *nmEnt);
void menuNmEnt_input(MenuNmEnt *menuNmEnt);
void menuNmEnt_update(MenuNmEnt *menuNmEnt);
void menuNmEnt_draw(MenuNmEnt *menuNmEnt, Gfx **gfxP);
void func_80056C84(MenuRankBase *menuRankBase, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3);
void func_80056CAC(MenuRankBase *arg0, SMenuItem *arg1);
void menuRankBase_draw(MenuRankBase *rankBaseArr[], s32 count, Gfx **gfxP);
void func_80056DF0(MenuRankNum *menuRankNum, struct_watchMenu *watchMenuRef, s32 arg2, s32 arg3, s32 arg4);
void func_80056E1C(MenuRankNum *arg0, SMenuItem *arg1);
void menuRankNum_draw(MenuRankNum *rankNumArr[], s32 count, Gfx **gfxP);
void menuRankFig_init(MenuRankFig *menuRankFig, struct_watchMenu *watchMenuRef, u32 arg2, s32 arg3, MenuRankFigColor color, s32 arg5, s32 arg6);
void menuRankFig_update(MenuRankFig *rankFig, SMenuItem *arg1);
void menuRankFig_draw(MenuRankFig *rankFigArr[], s32 count, Gfx **gfxP);
void menuRankName_init(MenuRankName *menuRankName, struct_watchMenu *watchMenuRef, u8 arg2[4], s32 arg3, s32 arg4);
void func_80057724(MenuRankName *arg0, SMenuItem *arg1);
void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP);
void func_80057898(MenuRankLabel *menuRankLabel, struct_watchMenu *watchMenuRef, s32 type, s32 id, s32 x, s32 y);
void func_800578C8(MenuRankLabel *arg0, SMenuItem *arg1);
void menuRankLabel_draw(MenuRankLabel *rankLabelArr[], s32 count, Gfx **gfxP);
void func_80057AFC(MenuRankHeader *menuRankHeader, struct_watchMenu *watchMenuRef, const s32 *typeP, const s32 *idP, const s32 *xP, const s32 *yP, s32 count, s32 arg7, s32 arg8);
void func_80057BE8(MenuRankHeader *rankHeader, SMenuItem *arg1);
void menuRankHeader_draw(MenuRankHeader *rankHeaderArr[], s32 count, Gfx **gfxP);
void func_80057D24(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, u32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_80057E68(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80057F6C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8005806C(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_800581C8(MenuRankPanel *menuRankPanel, struct_watchMenu *watchMenuRef, s32 arg2, u8 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void menuRankPanel_update(MenuRankPanel *arg0, SMenuItem *arg1);
void menuRankPanel_draw(MenuRankPanel **arg0, s32 count, Gfx **gfxP);
void menuRank_setNameBaseScale(MenuRank *menuRank, UNK_TYPE arg1, f32 arg2);
void menuRank_setSlide(MenuRank *menuRank, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3, f32 arg4);
void menuRank_setFrame(MenuRank *menuRank, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3);
void func_80058A24(MenuRank *menuRank, s32 arg1);
void menuRank_setPanel(MenuRank *menuRank, s32 arg1, MainMenuMode arg2, UNK_TYPE arg3);
void menuRank_init(MenuRank *menuRank, struct_watchMenu *watchMenuRef, void **heapP);
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

SMenuItem *_getRootItem(struct_watchMenu *watchMenuRef);

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

// COMMON

extern struct_watchMenu *watchMenu;
extern s32 _menuMain_lastDepth;
extern s32 _menuMain_lastSelect[8]; // probably an enum

#endif
