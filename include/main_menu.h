#ifndef MAINMENU_H
#define MAINMENU_H

#include "libultra.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

#include "macros_defines.h"
#include "defines.h"

#include "audio/snd_seq.h"
#include "char_anime.h"
#include "main.h"
#include "msgwnd.h"
#include "nnsched.h"
#include "record.h"
#include "recwritingmsg.h"
#include "unk.h"

struct SMenuItem;
struct SMenuAll;

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
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
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
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
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
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 level; /* Original name: level */
    /* 0x008 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x098 */ SMenuItem miVirus; /* Original name: miVirus */
} MenuBottle; // size = 0x128

/** Original name: SMenuLvGauge */
typedef struct SMenuLvGauge {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 size; /* Original name: size */ // TODO: enum?
    /* 0x008 */ int levelMax; /* Original name: levelMax */
    /* 0x00C */ int level; /* Original name: level */
    /* 0x010 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A0 */ MenuCursor cursor; /* Original name: cursor */
} SMenuLvGauge; // size = 0x300

typedef struct MenuYN {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 select; /* Original name: select */
    /* 0x008 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x098 */ SMenuItem miYN[2]; /* Original name: miYN */
    /* 0x1B8 */ MenuCursor cursor; /* Original name: cursor */
    /* 0x418 */ MenuCursor window; /* Original name: window */
} MenuYN; // size = 0x678

typedef struct MenuMes {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x094 */ MessageWnd msgWnd; /* Original name: msgWnd */
    /* 0x114 */ MenuCursor window; /* Original name: window */
} MenuMes; // size = 0x374

typedef struct MenuSpeedAsk {
    /* 0x0 */ struct SMenuAll *global; /* Original name: global */
    /* 0x4 */ s32 size; /* Original name: size */
    /* 0x8 */ s32 select; /* Original name: select */
    /* 0xC */ SMenuItem miBase; /* Original name: miBase */
} MenuSpeedAsk; // size = 0x9C

#define MENUSPEEDITEM_UNK_LEN 3U

typedef struct MenuSpeedItem {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 size; /* Original name: size */
    /* 0x008 */ s32 select; /* Original name: select */
    /* 0x00C */ struct {
                    // Likely intended to be bitfields
                    bool blink; /* Original name: blink */
                    bool special; /* Original name: special */
                } flags; /* Original name: flags */
    /* 0x014 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A4 */ SMenuItem miLabel[3]; /* Original name: miLabel */
    /* 0x254 */ SMenuItem miMask[MENUSPEEDITEM_UNK_LEN]; /* Original name: miMask */
    /* 0x404 */ MenuCursor cursor; /* Original name: cursor */
} MenuSpeedItem; // size = 0x664

#define MENUMUSICITEM_COUNT 5U

typedef struct MenuMusicItem {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 select; /* Original name: select */
    /* 0x008 */ s32 playNo; /* Original name: playNo */
    /* 0x00C */ struct {
                    bool blink : 1; /* Original name: blink */
                } flags; /* Original name: flags */
    /* 0x010 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A0 */ SMenuItem miLabel[MENUMUSICITEM_COUNT]; /* Original name: miLabel */
    /* 0x370 */ SMenuItem miMask[MENUMUSICITEM_COUNT]; /* Original name: miMask */
    /* 0x640 */ MenuCursor cursor; /* Original name: cursor */
} MenuMusicItem; // size = 0x8A0

typedef struct MenuNumber {
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
    /* 0x04 */ s32 size; /* Original name: size */
    /* 0x08 */ s32 column; /* Original name: column */
    /* 0x0C */ s32 number; /* Original name: number */
    /* 0x10 */ struct {
                    bool zero : 1; /* Original name: blink */
                } flags; /* Original name: flags */
    /* 0x14 */ char columns[8]; /* Original name: columns */
    /* 0x1C */ SMenuItem miBase; /* Original name: miBase */
} MenuNumber; // size = 0xAC

typedef struct MenuComLvPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 level; /* Original name: level */
    /* 0x008 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x098 */ SMenuItem miStar; /* Original name: miStar */
} MenuComLvPanel; // size = 0x128

#define MENUCONT_UNK_094_LEN 5
#define MENUCONT_UNK_364_LEN 1

typedef struct MenuCont {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x094 */ SMenuItem miDesc[MENUCONT_UNK_094_LEN]; /* Original name: miDesc */
    /* 0x364 */ SMenuItem miLine[MENUCONT_UNK_364_LEN]; /* Original name: miLine */
    /* 0x3F4 */ SMenuItem miLabel[1]; /* Original name: miLabel */
    /* 0x484 */ SMenuItem miPushAnyKey[1]; /* Original name: miPushAnyKey */
} MenuCont; // size >= 0x514

#define MENUMAINPANEL_UNK_LEN (6)

typedef struct MenuMainPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ UNUSED_MEMBER(s32 size); /* Original name: size */
    /* 0x008 */ s32 count; /* Original name: count */
    /* 0x00C */ s32 select; /* Original name: select */
    /* 0x010 */ s32 indexes[MENUMAINPANEL_UNK_LEN]; /* Original name: indexes */
    /* 0x028 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0B8 */ SMenuItem miPanel[MENUMAINPANEL_UNK_LEN]; /* Original name: miPanel */
    /* 0x418 */ MenuCursor cursor; /* Original name: cursor */
} MenuMainPanel; // size = 0x678

typedef struct MenuNameSelPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 playerCount; /* Original name: playerCount */
    /* 0x008 */ s32 flow; /* Original name: flow */
    /* 0x00C */ s32 depth[2]; /* Original name: depth */
    /* 0x014 */ s32 select[2]; /* Original name: select */
    /* 0x01C */ s32 column[2]; /* Original name: column */
    /* 0x024 */ struct {
                    bool guest : 1; /* Original name: guest */
                } flags; /* Original name: flags */
    /* 0x028 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0B8 */ SMenuItem miLabel[9]; /* Original name: miLabel */
    /* 0x5C8 */ MenuCursor cursor[2]; /* Original name: cursor */
} MenuNameSelPanel; // size = 0xA88

#define MENUNAMEOPPANEL_NAME_LEN 4U

typedef enum MenuNameOpPanelType {
    /* 0 */ MENUNAMEOPPANELTYPE_0,
    /* 1 */ MENUNAMEOPPANELTYPE_1, // unused
    /* 2 */ MENUNAMEOPPANELTYPE_MAX,
} MenuNameOpPanelType;

typedef struct MenuNameOpPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ MenuNameOpPanelType type; /* Original name: type */
    /* 0x008 */ s32 select; /* Original name: select */
    /* 0x00C */ u8 name[MENUNAMEOPPANEL_NAME_LEN]; /* Original name: name */
    /* 0x010 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A0 */ SMenuItem miName; /* Original name: miName */
    /* 0x130 */ SMenuItem miPanel[2]; /* Original name: miPanel */
    /* 0x250 */ MenuCursor cursor; /* Original name: cursor */
} MenuNameOpPanel; // size >= 0x4B0

#define MENUSNDSELPANEL_UNK_0A4_LEN 4
#define MENUSNDSELPANEL_UNK_2E4_LEN 2

typedef struct MenuSndSelPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 select; /* Original name: select */
    /* 0x008 */ SeqIndex bgmNo; /* Original name: bgmNo */
    /* 0x00C */ s32 sndId; /* Original name: sndId */
    /* 0x010 */ SndIndex sndNo; /* Original name: sndNo */
    /* 0x014 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A4 */ SMenuItem miPanel[MENUSNDSELPANEL_UNK_0A4_LEN]; /* Original name: miPanel */
    /* 0x2E4 */ MenuNumber number[MENUSNDSELPANEL_UNK_2E4_LEN]; /* Original name: number */
    /* 0x43C */ MenuCursor cursor; /* Original name: cursor */
} MenuSndSelPanel; // size = 0x69C

typedef struct MenuPlay2Panel {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ bool flash; /* Original name: flash */
    /* 0x0008 */ bool timeAt; /* Original name: timeAt */
    /* 0x000C */ bool FL_TA; /* Original name: FL_TA */
    /* 0x0010 */ s32 size; /* Original name: size */
    /* 0x0014 */ s32 playerCount; /* Original name: playerCount */
    /* 0x0018 */ s32 cpuCount; /* Original name: cpuCount */
    /* 0x001C */ s32 playerNo; /* Original name: playerNo */
    /* 0x0020 */ CharAnimeMode charNo; /* Original name: charNo */
    /* 0x0024 */ s32 depth; /* Original name: depth */
    /* 0x0028 */ s32 flow; /* Original name: flow */
    /* 0x002C */ void *animeAddr; /* Original name: animeAddr */
    /* 0x0030 */ struct {
                    bool cpu : 1; /* Original name: cpu */
                    bool loaded : 1; /* Original name: loaded */
                } flags; /* Original name: flags */
    /* 0x0034 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x00C4 */ SMenuItem miPlayer; /* Original name: miPlayer */
    /* 0x0154 */ SMenuItem miPlayerNo; /* Original name: miPlayerNo */
    /* 0x01E4 */ MenuNumber lvNum; /* Original name: lvNum */
    /* 0x0290 */ SMenuLvGauge lvGauge; /* Original name: lvGauge */
    /* 0x0590 */ MenuSpeedAsk speedAsk; /* Original name: speedAsk */
    /* 0x062C */ MenuSpeedItem speedItem; /* Original name: speedItem */
    /* 0x0C90 */ SAnimeState animeState; /* Original name: animeState */
    /* 0x0CD0 */ SMenuItem miOk; /* Original name: miOk */
    /* 0x0D60 */ MenuCursor cursor[2]; /* Original name: cursor */
    /* 0x1220 */ MenuSpeedAsk glvAsk; /* Original name: glvAsk */
    /* 0x12BC */ MenuSpeedItem glvItem; /* Original name: glvItem */
} MenuPlay2Panel; // size = 0x1920

#define MENUPLAY2PANELSUB_UNK_17C 2
#define MENUPLAY2PANELSUB_UNK_B9C 2

typedef struct MenuPlay2PanelSub {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ s32 depth; /* Original name: depth */
    /* 0x008 */ s32 flow; /* Original name: flow */
    /* 0x00C */ s32 topBgGap; /* Original name: topBgGap */
    /* 0x010 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0A0 */ MenuMusicItem musicItem; /* Original name: musicItem */
    /* 0x940 */ MenuNumber stageNum; /* Original name: stageNum */
    /* 0x9EC */ SMenuItem miStageBg; /* Original name: miStageBg */
    /* 0xA7C */ SMenuItem miBgCursor[MENUPLAY2PANELSUB_UNK_17C]; /* Original name: miBgCursor */
    /* 0xB9C */ MenuCursor cursor[MENUPLAY2PANELSUB_UNK_B9C]; /* Original name: cursor */
} MenuPlay2PanelSub; // size = 0x105C

typedef struct MenuMain {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ MainMenuMode mode; /* Original name: mode */
    /* 0x0008 */ s32 depth; /* Original name: depth */
    /* 0x000C */ s32 select[8]; /* Original name: select */
    /* 0x002C */ s32 screenNo; /* Original name: screenNo */
    /* 0x0030 */ s32 screenDir; /* Original name: screenDir */
    /* 0x0034 */ SeqIndex playSeqNo; /* Original name: playSeqNo */
    /* 0x0038 */ f32 kasaCount; /* Original name: kasaCount */
    /* 0x003C */ MenuMainPanel panel[2]; /* Original name: panel */
    /* 0x0D2C */ MenuNameSelPanel nameSel; /* Original name: nameSel */
    /* 0x17B4 */ MenuNameOpPanel nameOp; /* Original name: nameOp */
    /* 0x1C64 */ MenuSndSelPanel sndSel; /* Original name: sndSel */
    /* 0x2300 */ s32 current; /* Original name: current */
    /* 0x2304 */ const char *msgStr; /* Original name: char */
    /* 0x2308 */ MessageWnd msgWnd; /* Original name: msgWnd */
    /* 0x2388 */ SMenuItem miMsgWnd; /* Original name: miMsgWnd */
    /* 0x2418 */ SMenuItem miKaSaMaRu; /* Original name: miKaSaMaRu */
    /* 0x24A8 */ SMenuItem miSmoke; /* Original name: miSmoke */
    /* 0x2538 */ SMenuItem miScrWnd; /* Original name: miScrWnd */
    /* 0x25C8 */ SMenuItem miScreen; /* Original name: miScreen */
    /* 0x2658 */ MenuCont cont; /* Original name: cont */
    /* 0x2B6C */ MenuYN yesNo; /* Original name: yesNo */
    /* 0x31E4 */ MenuMes message; /* Original name: message */
} MenuMain; // size = 0x3558

#define MENUSTORY_UNK_LEN 2U
#define MENUSTORY_UNK_LEN_2 2U
#define MENUSTORY_UNK_LEN_3 3U
#define MENUSTORY_UNK_LEN_4 2U

typedef struct MenuStory {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ s32 stageMax[4][2]; /* Original name: stageMax */
    /* 0x0024 */ s32 depth; /* Original name: depth */
    /* 0x0028 */ s32 select[3]; /* Original name: select */
    /* 0x0034 */ bool loaded; /* Original name: loaded */
    /* 0x0038 */ void *animeAddr[2]; /* Original name: animeAddr */
    /* 0x0040 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x00D0 */ SMenuItem miCharName; /* Original name: miCharName */
    /* 0x0160 */ SMenuItem miChar[MENUSTORY_UNK_LEN]; /* Original name: miChar */
    /* 0x0280 */ SAnimeState animeState[MENUSTORY_UNK_LEN]; /* Original name: animeState */
    /* 0x0300 */ MenuCursor charCursor[MENUSTORY_UNK_LEN]; /* Original name: charCursor */
    /* 0x07C0 */ MenuSpeedAsk speedAsk; /* Original name: speedAsk */
    /* 0x085C */ MenuSpeedItem speedItem; /* Original name: speedItem */
    /* 0x0EC0 */ MenuNumber stageNum; /* Original name: stageNum */
    /* 0x0F6C */ SMenuItem miStageBase; /* Original name: miStageBase */
    /* 0x0FFC */ SMenuItem miStageBg[MENUSTORY_UNK_LEN_2]; /* Original name: miStageBg */
    /* 0x111C */ SMenuItem miBgCursor[MENUSTORY_UNK_LEN_4]; /* Original name: miBgCursor */
    /* 0x123C */ SMenuItem miWalk[MENUSTORY_UNK_LEN_2]; /* Original name: miWalk */
    /* 0x135C */ MenuCursor cursor[MENUSTORY_UNK_LEN_3]; /* Original name: cursor */
} MenuStory; // size = 0x1A7C


#define MENULVSEL_UNK_162C_LEN 3

typedef struct MenuLvSel {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ MainMenuMode mode; /* Original name: mode */
    /* 0x0008 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0098 */ SMenuItem miPanel[2]; /* Original name: miPanel */
    /* 0x01B8 */ MenuNumber lvNum; /* Original name: lvNum */ // virus level number
    /* 0x0264 */ SMenuLvGauge lvGauge; /* Original name: lvGauge */ // virus level gauge
    /* 0x0564 */ MenuSpeedAsk speedAsk; /* Original name: speedAsk */
    /* 0x0600 */ MenuSpeedItem speedItem; /* Original name: speedItem */ // speed selector
    /* 0x0C64 */ MenuMusicItem musicItem; /* Original name: musicItem */ // music selector
    /* 0x1504 */ MenuBottle bottle; /* Original name: bottle */
    /* 0x162C */ MenuCursor cursor[MENULVSEL_UNK_162C_LEN]; /* Original name: cursor */
    /* 0x1D4C */ SMenuItem miCapsule; /* Original name: miCapsule */ // capsule speed icon
    /* 0x1DDC */ SMenuItem miMusic; /* Original name: miMusic */ // music icon
    /* 0x1E6C */ MenuSpeedAsk glvAsk; /* Original name: glvAsk */ // game level icon
    /* 0x1F08 */ MenuSpeedItem glvItem; /* Original name: glvItem */ // game level selector
    /* 0x256C */ s32 depth; /* Original name: depth */
    /* 0x2570 */ s32 levelMax; /* Original name: levelMax */
} MenuLvSel; // size = 0x75A4

#define MENUCH_SEL_UNK_LEN 15U

typedef struct MenuChSel {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ s32 allCount; /* Original name: allCount */
    /* 0x0008 */ s32 select[4]; /* Original name: select */
    /* 0x0018 */ s32 depth[4]; /* Original name: depth */
    /* 0x0028 */ s32 subDepth; /* Original name: subDepth */
    /* 0x002C */ bool hardFlag; /* Original name: hardFlag */
    /* 0x0030 */ s32 hardMode; /* Original name: hardMode */ /* ThinkLevel? */
    /* 0x0034 */ s32 comLvId; /* Original name: comLvId */
    /* 0x0038 */ s32 comLvPn; /* Original name: comLvPn */
    /* 0x003C */ s32 playerCount; /* Original name: playerCount */
    /* 0x0040 */ s32 playerTable[4]; /* Original name: playerTable */
    /* 0x0050 */ s32 cpuFlag[4]; /* Original name: cpuFlag */
    /* 0x0060 */ s32 cpuCount; /* Original name: cpuCount */
    /* 0x0064 */ s32 cpuTable[4]; /* Original name: cpuTable */
    /* 0x0074 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x0104 */ SMenuItem miHard; /* Original name: miHard */
    /* 0x0194 */ SMenuItem miChar[MENUCH_SEL_UNK_LEN]; /* Original name: miChar */
    /* 0x0A04 */ SMenuItem miCharFilt[MENUCH_SEL_UNK_LEN]; /* Original name: miCharFilt */
    /* 0x1274 */ MenuComLvPanel comLv[MENUCH_SEL_UNK_LEN]; /* Original name: comLv */
    /* 0x23CC */ MenuCursor cursor[4]; /* Original name: cursor */
} MenuChSel; // size = 0x2D4C

// TODO: make enums for all the depths

typedef struct MenuPlay2 {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ s32 depth; /* Original name: depth */
    /* 0x0008 */ s32 master; /* Original name: master */
    /* 0x000C */ s32 playerCount; /* Original name: playerCount */
    /* 0x0010 */ s32 playerTable[4]; /* Original name: playerTable */
    /* 0x0020 */ s32 cpuCount; /* Original name: cpuCount */
    /* 0x0024 */ s32 cpuTable[4]; /* Original name: cpuTable */
    /* 0x0034 */ SMenuItem miONaJi; /* Original name: miONaJi */
    /* 0x00C4 */ s32 panelCount; /* Original name: panelCount */
    /* 0x00C8 */ MenuPlay2Panel panel[4]; /* Original name: panel */
    /* 0x6548 */ MenuPlay2PanelSub panelSub; /* Original name: panelSub */
} MenuPlay2; // size = 0x75A4

typedef struct MenuNmEnt {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ s32 playerNo; /* Original name: playerNo */
    /* 0x0008 */ s32 playerCount; /* Original name: playerCount */
    /* 0x000C */ s32 flow[EVS_SELECT_NAME_NO_COUNT]; /* Original name: flow */
    /* 0x0014 */ s32 pageNo[EVS_SELECT_NAME_NO_COUNT]; /* Original name: pageNo */
    /* 0x001C */ s32 curPos[EVS_SELECT_NAME_NO_COUNT][2]; /* Original name: curPos */
    /* 0x002C */ s8 name[EVS_SELECT_NAME_NO_COUNT][4]; /* Original name: name */
    /* 0x0034 */ s32 namePos[EVS_SELECT_NAME_NO_COUNT]; /* Original name: namePos */
    /* 0x003C */ SMenuItem miBase; /* Original name: miBase */
    /* 0x00CC */ SMenuItem miPanel; /* Original name: miPanel */
    /* 0x015C */ SMenuItem miPlayerNo; /* Original name: miPlayerNo */
    /* 0x01EC */ SMenuItem miTable; /* Original name: miTable */
    /* 0x027C */ SMenuItem miCursor; /* Original name: miCursor */
    /* 0x030C */ MenuCursor cursor; /* Original name: cursor */
    /* 0x056C */ SMenuItem miName; /* Original name: miName */
    /* 0x05FC */ SMenuItem miNamePos; /* Original name: miNamePos */
} MenuNmEnt; // size >= 0x68C <= 0x75A4

typedef struct MenuRankBase {
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
    /* 0x04 */ SMenuItem miBase; /* Original name: miBase */
} MenuRankBase; // size = 0x94

typedef struct MenuRankNum {
    /* 0x00 */ struct SMenuAll *global;
    /* 0x04 */ s32 number;
    /* 0x08 */ SMenuItem miBase;
} MenuRankNum; // size = 0x98


typedef enum menuRankFig_init {
    /*  7 */ RANK_FIG_NUMBER = 7, /* Original name: RANK_FIG_NUMBER */
    /*  8 */ RANK_FIG_TIME, /* Original name: RANK_FIG_TIME */
    /*  9 */ RANK_FIG_RATIO, /* Original name: RANK_FIG_RATIO */
    /* 10 */ RANK_FIG_LEVEL , /* Original name: RANK_FIG_LEVEL */
    /* 11 */ RANK_FIG_TIME2 , /* Original name: RANK_FIG_TIME2 */
    /* 12 */ RANK_FIG_CLEAR , /* Original name: RANK_FIG_CLEAR */
    /* 13 */ RANK_FIG_ALL , /* Original name: RANK_FIG_ALL */
    /* 14 */ RANK_FIG_SUM , /* Original name: RANK_FIG_SUM */
} MenuRankFigType;

#define MENURANKFIG_COLUMNS_MAX 10

#define RANK_FIG_NUMBER_MAX_COL 7
#define RANK_FIG_TIME_MAX_COL 5
#define RANK_FIG_RATIO_MAX_COL 6
#define RANK_FIG_LEVEL_MAX_COL 7
#define RANK_FIG_TIME2_MAX_COL 6
#define RANK_FIG_CLEAR_MAX_COL 5
#define RANK_FIG_ALL_MAX_COL 3

#if RANK_FIG_NUMBER_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_TIME_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_RATIO_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_LEVEL_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_TIME2_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_CLEAR_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif
#if RANK_FIG_ALL_MAX_COL > MENURANKFIG_COLUMNS_MAX
#error ""
#endif

typedef enum MenuRankFigVal {
    /*  0 */ MENURANKFIGVALUE_0,
    /*  1 */ MENURANKFIGVALUE_1,
    /*  2 */ MENURANKFIGVALUE_2,
    /*  3 */ MENURANKFIGVALUE_3,
    /*  4 */ MENURANKFIGVALUE_4,
    /*  5 */ MENURANKFIGVALUE_5,
    /*  6 */ MENURANKFIGVALUE_6,
    /*  7 */ MENURANKFIGVALUE_7,
    /*  8 */ MENURANKFIGVALUE_8,
    /*  9 */ MENURANKFIGVALUE_9,
    /* 10 */ MENURANKFIGVALUE_C,
    /* 11 */ MENURANKFIGVALUE_L,
    /* 12 */ MENURANKFIGVALUE_E,
    /* 13 */ MENURANKFIGVALUE_A,
    /* 14 */ MENURANKFIGVALUE_R,
    /* 15 */ MENURANKFIGVALUE_COLON,
    /* 16 */ MENURANKFIGVALUE_PERCENTAGE,
    /* 17 */ MENURANKFIGVALUE_DOT,
    /* 18 */ MENURANKFIGVALUE_V,
    /* 19 */ MENURANKFIGVALUE_MAX,
} MenuRankFigVal;

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
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
    /* 0x04 */ MenuRankFigType type; /* Original name: type */
    /* 0x08 */ s32 column; /* Original name: column */
    /* 0x0C */ MenuRankFigVal columns[MENURANKFIG_COLUMNS_MAX]; /* Original name: columns */
    /* 0x34 */ s32 number; /* Original name: number */
    /* 0x38 */ SMenuItem miBase; /* Original name: miBase */
} MenuRankFig; // size = 0xC8

typedef struct MenuRankName {
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
    /* 0x04 */ u8 name[4]; /* Original name: name */
    /* 0x08 */ SMenuItem miBase; /* Original name: miBase */
} MenuRankName; // size = 0x98

typedef struct MenuRankLabel {
    /* 0x00 */ struct SMenuAll *global;
    /* 0x04 */ s32 type;
    /* 0x08 */ s32 index;
    /* 0x0C */ SMenuItem miBase;
} MenuRankLabel; // size = 0x9C

#define MENURANKHEADER_UNK_98 5

typedef struct MenuRankHeader {
    /* 0x00 */ struct SMenuAll *global; /* Original name: global */
    /* 0x04 */ s32 labelCount; /* Original name: labelCount */ /* count of label */
    /* 0x08 */ SMenuItem miBase; /* Original name: miBase */
    /* 0x98 */ MenuRankLabel label[MENURANKHEADER_UNK_98]; /* Original name: label */
} MenuRankHeader; // size = 0x3A4


typedef enum MenuRankPanelType {
    /* 0 */ MENURANKPANELTYPE_OHA,
    /* 1 */ MENURANKPANELTYPE_END,
    /* 2 */ MENURANKPANELTYPE_TAIQ,
    /* 3 */ MENURANKPANELTYPE_TIMEAT,
    /* 4 */ MENURANKPANELTYPE_VS1,
} MenuRankPanelType;

typedef struct MenuRankPanel {
    /* 0x000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x004 */ MenuRankPanelType type; /* Original name: type */
    /* 0x008 */ MenuRankBase base; /* Original name: base */
    /* 0x09C */ MenuRankNum rank; /* Original name: rank */
    /* 0x134 */ MenuRankName name; /* Original name: name */
    /* 0x1CC */ union {
        struct {
            /* 0x1CC */ MenuRankFig score;
            /* 0x294 */ MenuRankFig time;
            /* 0x35C */ MenuRankFig stage;
        } oha;
        struct {
            /* 0x1CC */ MenuRankFig level;
            /* 0x294 */ MenuRankFig score;
        } end;
        struct {
            /* 0x1CC */ MenuRankFig time;
            /* 0x294 */ MenuRankFig score;
        } taiQ;
        struct {
            /* 0x1CC */ MenuRankFig score;
            /* 0x294 */ MenuRankFig time;
            /* 0x35C */ MenuRankFig erase;
        } timeAt;
        struct {
            /* 0x1CC */ MenuRankFig ratio;
            /* 0x294 */ MenuRankFig win;
            /* 0x35C */ MenuRankFig lose;
        } vs1;
    } misc;
} MenuRankPanel; // size = 0x424

typedef struct MenuRankCt {
    /* 0x0000 */ s32 panelCount;
    /* 0x0004 */ MenuRankHeader header;
    /* 0x03A8 */ MenuRankPanel panel[8];
} MenuRankCt; // size = 0x24C8

#define MENURANK_MILR 2U

typedef struct MenuRank {
    /* 0x0000 */ struct SMenuAll *global; /* Original name: global */
    /* 0x0004 */ MainMenuMode mode; /* Original name: mode */
    /* 0x0008 */ bool vsFlag; /* Original name: vsFlag */
    /* 0x000C */ s32 level; /* Original name: level */
    /* 0x0010 */ s32 levelOld; /* Original name: levelOld */
    /* 0x0014 */ s32 curBuf; /* Original name: curBuf */
    /* 0x0018 */ s32 oldBuf; /* Original name: oldBuf */
    /* 0x001C */ SRankSortInfo sortInfo; /* Original name: sortInfo */
    /* 0x017C */ SMenuItem miBase; /* Original name: miBase */
    /* 0x020C */ SMenuItem miLR[MENURANK_MILR]; /* Original name: miLR */
    /* 0x032C */ SMenuItem miNameBase; /* Original name: miNameBase */
    /* 0x03BC */ MenuRankLabel title; /* Original name: title */
    /* 0x0458 */ MenuRankLabel nameLabel[2]; /* Original name: nameLabel */
    /* 0x0590 */ MenuRankCt ct[2]; /* Original name: ct */
} MenuRank; // size = 0x4F20



typedef union MenusUnion {
    MenuMain main;
    MenuStory story;
    MenuLvSel lvSel;
    MenuPlay2 play2;
    MenuChSel chSel;
    MenuNmEnt nmEnt;
    MenuRank rank;
} MenusUnion; // size = 0x75A4


// Left column: us
// Right column: cn
/** Original name: SMenuAll */
typedef struct SMenuAll {
    /* 0x00000 */ NNSched *sched;
    /* 0x00004 */ NNScClient scClient;
    /* 0x0000C */ OSMesgQueue scMQ;
    /* 0x00024 */ OSMesg scMsgBuf[NN_SC_MAX_MESGS];
    /* 0x00044 */ UNK_TYPE1 unk_00044[4]; // unused/pad?
    /* 0x00048 */ Mtx mtxBuf[3][0x10]; /* Original name: mtxBuf */
    /* 0x00C48 */ Vtx vtxBuf[3][0x80]; /* Original name: vtxBuf */
    /* 0x02448 */ Mtx *mtxPtr[3]; /* Original name: mtxPtr */
    /* 0x02454 */ Vtx *vtxPtr[3]; /* Original name: vtxPtr */
    /* 0x02460 */ void *heapAll; /* Original name: heapAll */
    /* 0x02464 */ size_t heapSize; /* Original name: heapSize */
    /* 0x02468 */ void *heapTop[2]; /* Original name: heapTop */
    /* 0x02470 */ void *heapEnd[2]; /* Original name: heapEnd */
    /* 0x02478 */ struct TiTexData *texChar; /* Original name: texChar */ // TODO: enums to access those. Should the enum be shared or different for each?
    /* 0x0247C */ struct TiTexData *texCommon; /* Original name: texCommon */
    /* 0x02480 */ struct TiTexData *texCredit; /* Original name: texCredit */ /* unused and unset */
    /* 0x02484 */ struct TiTexData *texLevel; /* Original name: texLevel */
    /* 0x02488 */ struct TiTexData *texMain; /* Original name: texMain */
    /* 0x0248C */ struct TiTexData *texName; /* Original name: texName */
    /* 0x02490 */ struct TiTexData *texP2; /* Original name: texP2 */
    /* 0x02494 */ struct TiTexData *texP4; /* Original name: texP4 */
    /* 0x02498 */ struct TiTexData *texRank; /* Original name: texRank */
    /* 0x0249C */ struct TiTexData *texSetup; /* Original name: texSetup */
    /* 0x024A0 */ struct TiTexData *texStory; /* Original name: texStory */
    /* 0x024A4 */ struct TiTexData *texGameAl; /* Original name: texGameAl */
    /* 0x024A8 */ struct TiTexData *texGameP1; /* Original name: texGameP1 */
    /* 0x024AC */ struct TiTexData *texCont; /* Original name: texCont */
    /* 0x024B0 */ struct TiTexData *texTutol; /* Original name: texTutol */
    /* 0x024B4 */ struct TiTexData *texKasa; /* Original name: texKasa */
    /* 0x024B8 */ SMenuItem miRoot[1]; /* Original name: miRoot */
    /* 0x02548 */ MenuTitle title; /* Original name: title */
    /* 0x02678 */ MenusUnion context[2]; /* Original name: context */
    /* 0x111C0 */ s32 nowContext; /* Original name: nowContext */
    /* 0x111C4 */ s32 oldContext; /* Original name: oldContext */
    /* 0x111C8 */ MainMenuMode oldMode; /* Original name: oldMode */
    /* 0x111CC */ MainMenuMode nowMode; /* Original name: nowMode */
    /* 0x111D0 */ MainMenuMode newMode; /* Original name: newMode */
    /* 0x111D4 */ enum_main_no nextMain; /* Original name: nextMain */
    #ifdef NN_SC_PERF
    /*         0x111D8 */ bool unk_cn_pad;
    #endif
    /* 0x111D8 0x111DC */ s32 eepRom; /* Original name: eepRom */
    /* 0x111DC 0x111E0 */ f32 fadeRatio; /* Original name: fadeRatio */
    /* 0x111E0 0x111E4 */ f32 fadeStep; /* Original name: fadeStep */
    /* 0x111E4 0x111E8 */ bool mainFirst; /* Original name: mainFirst */ /* unused */
    /* 0x111E8 0x111EC */ bool grapFirst; /* Original name: grapFirst */ /* unused */
    /* 0x111EC 0x111F0 */ UNK_TYPE mainCount; /* Original name: mainCount */
    /* 0x111F0 0x111F4 */ UNK_TYPE grapCount; /* Original name: grapCount */
    /* 0x111F4 0x111F8 */ UNK_TYPE graphicThreadPri; /* Original name: graphicThreadPri */
    /* 0x111F8 0x111FC */ RecordWritingMessage writingMsg; /* Original name: writingMsg */
} SMenuAll; // size_us = 0x11280; size_cn = 0x11288



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
void menuTitle_init(MenuTitle *title, SMenuAll *global, UNK_TYPE x, UNK_TYPE y);
void menuTitle_update(MenuTitle *title, SMenuItem *parent);
void menuTitle_draw(MenuTitle *title, Gfx **gfxP);
void menuCursor_setFingerPos(MenuCursor *cursor, s32 x, s32 y);
void menuCursor_setPlayerPos(MenuCursor *cursor, s32 x, s32 y);
void menuCursor_init2(MenuCursor *cursor, SMenuAll *global, CursorType type, s32 playerCount, s32 cpuCount,
                      s32 playerNo, s32 x, s32 y, s32 w, s32 h);
void menuCursor_init(MenuCursor *cursor, SMenuAll *global, CursorType type, s32 playerNo, s32 x, s32 y, s32 w,
                     s32 h);
void menuCursor_update(MenuCursor *cursor, SMenuItem *parent);
void menuCursor_draw1(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void menuCursor_draw2(MenuCursor *cursorArr[], s32 count, Gfx **gxfP);
void menuCursor_draw(MenuCursor *cursorArr[], s32 /*count*/, Gfx **gxfP);
void menuBottle_init(MenuBottle *bottle, SMenuAll *global, s32 x, s32 y);
void menuBottle_update(MenuBottle *bottle, SMenuItem *parent);
void menuBottle_draw(MenuBottle *bottle, Gfx **gxfP);
void menuLvGauge_init(SMenuLvGauge *lvGauge, SMenuAll *global, s32 size, s32 playerNo, s32 level, s32 x, s32 y);
void menuLvGauge_input(SMenuLvGauge *lvGauge, s32 playerNo);
void menuLvGauge_update(SMenuLvGauge *lvGauge, SMenuItem *parent);
void menuLvGauge_draw1(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gxfP);
void menuLvGauge_draw2(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gxfP);
void menuLvGauge_draw(SMenuLvGauge *lvGaugeArr[], s32 count, Gfx **gfxP);
void menuYN_setFade(MenuYN *yn, s32 dir, f32 time);
void menuYN_setFadeDir(MenuYN *yn, s32 dir);
void menuYN_init(MenuYN *yn, SMenuAll *global, s32 x, s32 y);
bool menuYN_input(MenuYN *yn, s32 playerNo);
void menuYN_update(MenuYN *yn, SMenuItem *parent);
void menuYN_draw(MenuYN *yn, Gfx **gfxP);
void menuMes_setFade(MenuMes *mes, s32 dir, f32 time);
void menuMes_setFadeDir(MenuMes *mes, s32 dir);
void menuMes_init(MenuMes *mes, SMenuAll *global, void **heapP, s32 col, s32 row, s32 x, s32 y);
void menuMes_setStr(MenuMes *mes, const char *str);
void menuMes_update(MenuMes *mes, SMenuItem *parent);
void menuMes_draw(MenuMes *mes, Gfx **gfxP);
void menuSpeedAsk_init(MenuSpeedAsk *speedAsk, SMenuAll *global, s32 size, s32 speed, s32 x, s32 y);
void menuSpeedAsk_update(MenuSpeedAsk *speedAsk, SMenuItem *parent);
void menuSpeedAsk_draw(MenuSpeedAsk *speedAskArr[], s32 count, Gfx **gxfP);
void menuSpeedItem_init(MenuSpeedItem *speedItem, SMenuAll *global, s32 size, s32 playerNo, s32 speed, s32 x,
                        s32 y, s32 step);
void menuSpeedItem_input(MenuSpeedItem *speedItem, s32 playerNo);
void menuSpeedItem_update(MenuSpeedItem *speedItem, SMenuItem *parent);
void menuSpeedItem_draw1(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP);
void menuSpeedItem_draw2(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gxfP);
void menuSpeedItem_draw(MenuSpeedItem *speedItemArr[], s32 count, Gfx **gfxP);
void menuMusicItem_init(MenuMusicItem *musicItem, SMenuAll *global, s32 musicNo, s32 x, s32 y);
void menuMusicItem_input(MenuMusicItem *musicItem, s32 playerNo);
void menuMusicItem_update(MenuMusicItem *musicItem, SMenuItem *parent);
void menuMusicItem_draw1(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void menuMusicItem_draw2(MenuMusicItem *musicItemArr[], s32 count, Gfx **gxfP);
void menuMusicItem_draw(MenuMusicItem *musicItemArr[], s32 count, Gfx **gfxP);
void menuNumber_init(MenuNumber *number, SMenuAll *global, s32 size, s32 column, s32 n, s32 x, s32 y);
void menuNumber_update(MenuNumber *number, SMenuItem *parent);
void menuNumber_draw(MenuNumber *numberArr[], s32 count, Gfx **gxfP);
void menuComLvPanel_setFade(MenuComLvPanel *comLvPanel, s32 dir, f32 time);
void menuComLvPanel_setFadeDir(MenuComLvPanel *comLvPanel, s32 dir);
void menuComLvPanel_setPos(MenuComLvPanel *comLvPanel, s32 x, s32 y);
void menuComLvPanel_init(MenuComLvPanel *comLvPanel, SMenuAll *global, s32 level, s32 x, s32 y);
void menuComLvPanel_update(MenuComLvPanel *comLvPanel, SMenuItem *parent);
void menuComLvPanel_draw(MenuComLvPanel *comLvPanelArr[], s32 count, Gfx **gfxP);
void menuCont_setFade(MenuCont *cont, s32 dir, f32 time);
void menuCont_setFrame(MenuCont *cont, s32 dir, s32 time);
void menuCont_init(MenuCont *cont, SMenuAll *global, s32 x, s32 y);
bool menuCont_input(MenuCont *cont, s32 playerNo);
void menuCont_update(MenuCont *cont, SMenuItem *parent);
void menuCont_draw(MenuCont *cont, Gfx **gfxP);
void menuMainPanel_setFrame(MenuMainPanel *mainPanel, s32 dir, f32 time);
void menuMainPanel_init(MenuMainPanel *mainPanel, SMenuAll *global, s32 count, s32 select, const s32 *indexes,
                        s32 x, s32 y);
bool menuMainPanel_input(MenuMainPanel *mainPanel, s32 playerNo);
void menuMainPanel_update(MenuMainPanel *mainPanel, SMenuItem *parent);
void menuMainPanel_draw(MenuMainPanel *mainPanel, Gfx **gfxP);
void menuNameSelPanel_setFrame(MenuNameSelPanel *nameSelPanel, s32 dir, f32 time);
void menuNameSelPanel_clear(MenuNameSelPanel *nameSelPanel, bool guestFlag, s32 playerCount);
void menuNameSelPanel_init(MenuNameSelPanel *nameSelPanel, SMenuAll *global, bool guestFlag, s32 playerCount,
                           s32 x, s32 y);
bool menuNameSelPanel_checkSelected(MenuNameSelPanel *nameSelPanel, s32 playerNo, s32 nameNo);
void menuNameSelPanel_input1(MenuNameSelPanel *nameSelPanel, s32 playerNo);
bool menuNameSelPanel_input(MenuNameSelPanel *nameSelPanel);
void menuNameSelPanel_update(MenuNameSelPanel *nameSelPanel, SMenuItem *parent);
void menuNameSelPanel_draw(MenuNameSelPanel *nameSelPanel, Gfx **gfxP);
void menuNameOpPanel_setFrame(MenuNameOpPanel *nameOpPanel, s32 dir, f32 time);
void menuNameOpPanel_init(MenuNameOpPanel *nameOpPanel, SMenuAll *global, MenuNameOpPanelType type, s32 select,
                          const u8 *name, s32 x, s32 y);
bool menuNameOpPanel_input(MenuNameOpPanel *nameOpPanel, s32 playerNo);
void menuNameOpPanel_update(MenuNameOpPanel *nameOpPanel, SMenuItem *parent);
void menuNameOpPanel_draw(MenuNameOpPanel *nameOpPanel, Gfx **gfxP);
void menuSndSelPanel_setFrame(MenuSndSelPanel *sndSelPanel, s32 dir, f32 time);
void menuSndSelPanel_init(MenuSndSelPanel *sndSelPanel, SMenuAll *global, s32 select, s32 x, s32 y);
bool menuSndSelPanel_input(MenuSndSelPanel *sndSelPanel, s32 playerNo);
void menuSndSelPanel_update(MenuSndSelPanel *sndSelPanel, SMenuItem *parentItem);
void menuSndSelPanel_draw(MenuSndSelPanel *sndSelPanel, Gfx **gfxP);
void _menuPlay2Panel_loadAnime(void *arg);
void menuPlay2Panel_init(MenuPlay2Panel *play2Panel, SMenuAll *global, void **heapP, s32 size, s32 playerCount,
                         s32 cpuCount, s32 playerNo, bool cpuFlag, CharAnimeMode charNo, s32 virusLevel, s32 gameSpeed,
                         s32 x, s32 y);
void menuPlay2Panel_copyConfig(MenuPlay2Panel *play2Panel, MenuPlay2Panel *from);
void menuPlay2Panel_copyCursor(MenuPlay2Panel *play2Panel, MenuPlay2Panel *from);
void menuPlay2Panel_input(MenuPlay2Panel *play2Panel, s32 playerNo, bool topFlag, bool bottomFlag);
void menuPlay2Panel_update(MenuPlay2Panel *play2Panel, SMenuItem *parent);
void menuPlay2Panel_draw(MenuPlay2Panel *play2PanelArr[], s32 count, Gfx **gfxP);
void menuPlay2PanelSub_setFrame(MenuPlay2PanelSub *play2PanelSub, s32 dir, f32 time);
void menuPlay2PanelSub_setStageBgFrame(MenuPlay2PanelSub *play2PanelSub, s32 dir, f32 time, f32 vec);
void menuPlay2PanelSub_init(MenuPlay2PanelSub *play2PanelSub, SMenuAll *global, void **heapP, s32 stageNo,
                            s32 musicNo, s32 x, s32 y);
bool menuPlay2PanelSub_input(MenuPlay2PanelSub *play2PanelSub, s32 playerNo);
void menuPlay2PanelSub_update(MenuPlay2PanelSub *play2PanelSub, SMenuItem *parent);
void menuPlay2PanelSub_draw(MenuPlay2PanelSub *play2PanelSub, Gfx **gfxP);
bool menuMain_setMsgStr(MenuMain *mMain, MainMenuMode mode, s32 select);
void menuMain_initPanel(MenuMain *mMain, MainMenuMode mode, s32 panelSw, s32 select);
void menuMain_init(MenuMain *mMain, SMenuAll *global, void **heapP);
void menuMain_waitCancel(MenuMain *mMain);
void _menuMain_updateCallback(void *arg);
void menuMain_input(MenuMain *mMain);
void menuMain_update(MenuMain *mMain);
void menuMain_drawKaSaMaRu(MenuMain *mMain, Gfx **gfxP);
void menuMain_draw(MenuMain *mMain, Gfx **gfxP);
void menuStory_getCharPos(s32 charNo, s32 stageNo, s32 plane, s32 *x, s32 *y);
void menuStory_setFrame(MenuStory *story, s32 dir, f32 time);
void _menuStory_loadAnime(void *arg);
void menuStory_init(MenuStory *story, SMenuAll *global, void **heapP);
void menuStory_waitCancel(MenuStory *story);
s32 menuStory_getLevel(MenuStory *story);
s32 func_800519EC(MenuStory *menuStory);
void menuStory_input(MenuStory *story);
void menuStory_update(MenuStory *story);
void menuStory_draw(MenuStory *story, Gfx **gfxP);
void menuLvSel_setFrame(MenuLvSel *lvSel, s32 dir, f32 time);
void menuLvSel_init(MenuLvSel *lvSel, SMenuAll *global, void **heapP);
void menuLvSel_waitCancel(MenuLvSel *lvSel);
void menuLvSel_input(MenuLvSel *lvSel);
void menuLvSel_update(MenuLvSel *lvSel);
void menuLvSel_draw(MenuLvSel *lvSel, Gfx **gfxP);
void menuChSel_setFrame(MenuChSel *chSel, s32 dir, f32 time);
void menuChSel_init(MenuChSel *chSel, SMenuAll *global, void **heapP);
bool menuChSel_checkSelected(MenuChSel *chSel, s32 playerNo, s32 charNo, s32 depth);
bool menuChSel_checkMoveable(MenuChSel *chSel, s32 playerNo, s32 charNo);
void menuChSel_input1(MenuChSel *chSel, s32 playerNo, s32 contNo);
void menuChSel_inputMan(MenuChSel *chSel);
void menuChSel_inputCom(MenuChSel *chSel);
void menuChSel_input(MenuChSel *chSel);
void menuChSel_update(MenuChSel *chSel);
void menuChSel_draw(MenuChSel *chSel, Gfx **gfxP);
void menuPlay2_setFrame(MenuPlay2 *play2, s32 dir, f32 time);
void menuPlay2_init(MenuPlay2 *play2, SMenuAll *global, void **heapP);
void menuPlay2_waitCancel(MenuPlay2 *play2);
bool menuPlay2_checkInputMaster(MenuPlay2 *play2, s32 playerNo, s32 contNo);
void menuPlay2_applyMasterConfig(MenuPlay2 *play2, s32 playerNo);
void menuPlay2_applyMasterCursor(MenuPlay2 *menuPlay2, s32 arg1);
void menuPlay2_inputMan(MenuPlay2 *play2);
void menuPlay2_inputCpu(MenuPlay2 *play2);
void menuPlay2_input(MenuPlay2 *play2);
void menuPlay2_update(MenuPlay2 *play2);
void menuPlay2_draw(MenuPlay2 *play2, Gfx **gfxP);
void menuNmEnt_setFrame(MenuNmEnt *nmEnt, s32 dir, f32 time);
void menuNmEnt_init(MenuNmEnt *nmEnt, SMenuAll *global, void **heapP);
void _menuNmEnt_updateCallback(void *arg);
void menuNmEnt_input(MenuNmEnt *nmEnt);
void menuNmEnt_update(MenuNmEnt *nmEnt);
void menuNmEnt_draw(MenuNmEnt *nmEnt, Gfx **gfxP);
void menuRankBase_init(MenuRankBase *rankBase, SMenuAll *global, s32 x, s32 y);
void menuRankBase_update(MenuRankBase *rankBase, SMenuItem *parent);
void menuRankBase_draw(MenuRankBase *rankBaseArr[], s32 count, Gfx **gfxP);
void menuRankNum_init(MenuRankNum *rankNum, SMenuAll *global, s32 number, s32 x, s32 y);
void menuRankNum_update(MenuRankNum *rankNum, SMenuItem *parent);
void menuRankNum_draw(MenuRankNum *rankNumArr[], s32 count, Gfx **gfxP);
void menuRankFig_init(MenuRankFig *rankFig, SMenuAll *global, MenuRankFigType column, s32 number,
                      MenuRankFigColor color, s32 x, s32 y);
void menuRankFig_update(MenuRankFig *rankFig, SMenuItem *parent);
void menuRankFig_draw(MenuRankFig *rankFigArr[], s32 count, Gfx **gfxP);
void menuRankName_init(MenuRankName *rankName, SMenuAll *global, const u8 name[4], s32 x, s32 y);
void menuRankName_update(MenuRankName *rankName, SMenuItem *parent);
void menuRankName_draw(MenuRankName *rankNameArr[], s32 count, Gfx **gfxP);
void menuRankLabel_init(MenuRankLabel *rankLabel, SMenuAll *global, s32 type, s32 index, s32 x, s32 y);
void menuRankLabel_update(MenuRankLabel *rankLabel, SMenuItem *parent);
void menuRankLabel_draw(MenuRankLabel *rankLabelArr[], s32 count, Gfx **gfxP);
void menuRankHeader_init(MenuRankHeader *rankHeader, SMenuAll *global, const s32 *labelType,
                         const s32 *labelIndex, const s32 *labelX, const s32 *labelY, s32 labelCount, s32 x, s32 y);
void menuRankHeader_update(MenuRankHeader *rankHeader, SMenuItem *parent);
void menuRankHeader_draw(MenuRankHeader *rankHeaderArr[], s32 count, Gfx **gfxP);
void menuRankPanel_initSt(MenuRankPanel *rankPanel, SMenuAll *global, s32 rank, const u8 name[4], s32 score,
                          s32 time, s32 stage, s32 x, s32 y);
void menuRankPanel_initLs(MenuRankPanel *rankPanel, SMenuAll *global, s32 rank, const u8 name[4], s32 level,
                          s32 score, s32 x, s32 y);
void menuRankPanel_initLsTq(MenuRankPanel *rankPanel, SMenuAll *global, s32 rank, const u8 name[4], s32 time,
                            s32 score, s32 x, s32 y);
void menuRankPanel_initLsTa(MenuRankPanel *rankPanel, SMenuAll *global, s32 rank, const u8 name[4], s32 score,
                            s32 time, s32 erase, s32 level, s32 x, s32 y);
void menuRankPanel_initVs1(MenuRankPanel *rankPanel, SMenuAll *global, s32 rank, const u8 name[4], s32 ratio,
                           s32 win, s32 lose, s32 x, s32 y);
void menuRankPanel_update(MenuRankPanel *rankPanel, SMenuItem *parent);
void menuRankPanel_draw(MenuRankPanel **rankPanelArr, s32 count, Gfx **gfxP);
void menuRank_setNameBaseScale(MenuRank *rank, UNK_TYPE dir, f32 time);
void menuRank_setSlide(MenuRank *rank, UNK_TYPE buf, UNK_TYPE dir, f32 time, f32 vec);
void menuRank_setFrame(MenuRank *rank, UNK_TYPE buf, UNK_TYPE dir, f32 time);
void menuRank_initCommon(MenuRank *rank, s32 buf);
void menuRank_setPanel(MenuRank *rank, s32 buf, MainMenuMode mode, UNK_TYPE level);
void menuRank_init(MenuRank *rank, SMenuAll *global, void **heapP);
void menuRank_input(MenuRank *rank);
void menuRank_update(MenuRank *rank);
void menuRank_draw(MenuRank *rank, Gfx **gfxP);

void _eep_writingCallback(void *arg);
void _eep_writePlayer(void *arg);
void _eep_eraseData(void *arg);
void _eep_retrace(SMenuAll *global);
void _eepWritePlayer(SMenuAll *global);
void _eepErasePlayer(SMenuAll *global);
void _eepEraseData(SMenuAll *global);

void _waitRetrace(SMenuAll *global);

Mtx **_getMtxPtr(SMenuAll *global);
Vtx **_getVtxPtr(SMenuAll *global);

struct TiTexData *_getTexChar(SMenuAll *global, s32 index);
struct TiTexData *_getTexCommon(SMenuAll *global, s32 index);
struct TiTexData *_getTexCredit(SMenuAll *global, s32 index);
struct TiTexData *_getTexLevel(SMenuAll *global, s32 index);
struct TiTexData *_getTexMain(SMenuAll *global, s32 index);
struct TiTexData *_getTexName(SMenuAll *global, s32 index);
struct TiTexData *_getTexP2(SMenuAll *global, s32 index);
struct TiTexData *_getTexP4(SMenuAll *global, s32 index);
struct TiTexData *_getTexRank(SMenuAll *global, s32 index);
struct TiTexData *_getTexSetup(SMenuAll *global, s32 index);
struct TiTexData *_getTexStory(SMenuAll *global, s32 index);
struct TiTexData *_getTexGameAl(SMenuAll *global, s32 index);
struct TiTexData *_getTexGameP1(SMenuAll *global, s32 index);
struct TiTexData *_getTexCont(SMenuAll *global, s32 index);
struct TiTexData *_getTexTutol(SMenuAll *global, s32 index);
struct TiTexData *_getTexKasa(SMenuAll *global, s32 index);

SMenuItem *_getRootItem(SMenuAll *global);

u32 _getKeyLvl(SMenuAll *global, s32 contNo);
u32 _getKeyTrg(SMenuAll *global, s32 contNo);
u32 _getKeyRep(SMenuAll *global, s32 contNo);

MainMenuMode _getMode(SMenuAll *global);
MainMenuMode _getModeOld(SMenuAll *global);
void _setMode(SMenuAll *global, MainMenuMode mode);

void _setNextMain(SMenuAll *global, enum_main_no nextMain);
void _setTitle(SMenuAll *global, MainMenuMode mode);
void _setFadeDir(SMenuAll *global, s32 dir);
void menuAll_init(SMenuAll *all, UNK_PTR *heapP, NNSched *sc);
void menuAll_exit(SMenuAll *all);
void menuAll_waitCancel(SMenuAll *all);
void menuAll_changeMenu(SMenuAll *all);

void menuAll_input(SMenuAll *all);
void menuAll_update(SMenuAll *all);
void menuAll_drawBg(SMenuAll *all, Gfx **gfxP);
void menuAll_draw(SMenuAll *all, Gfx **gfxP);
enum_main_no main_menu(NNSched *sc);
void graphic_menu(void);

// COMMON

extern SMenuAll *watchMenu;
extern s32 _menuMain_lastDepth;
extern s32 _menuMain_lastSelect[8]; // probably an enum

#endif
