/**
 * Debug menu
 *
 * Name is made up
 */

#include "debug_menu.h"

#include "libc/assert.h"

#include "util.h"
#include "macros_defines.h"

#include "aiset.h"
#include "joy.h"
#include "main1x.h"
#include "screen_print/debug_print.h"

typedef enum SettingsPage {
    /* 0 */ SETTINGS_PAGE_LOGIC_MENU,
    /* 1 */ SETTINGS_PAGE_CHARACTER_MENU,
    /* 2 */ SETTINGS_PAGE_SPEED_MENU,

// This macro should expand to (the last entry + 1)
#define SETTINGS_PAGE_MAX (3)
} SettingsPage;

typedef enum CharacterEditColumn {
    /* 0 */ CHARACTER_EDIT_COLUMN_NAME,
    /* 1 */ CHARACTER_EDIT_COLUMN_PERFORMANCE,
    /* 2 */ CHARACTER_EDIT_COLUMN_SPEED,
    /* 3 */ CHARACTER_EDIT_COLUMN_SPECIAL,

// This macro should expand to (the last entry + 1)
#define CHARACTER_EDIT_COLUMN_MAX (4)
} CharacterEditColumn;

typedef enum CharacterEditChar {
    /*  0 */ CHARACTER_EDIT_CHAR_MARIO,
    /*  1 */ CHARACTER_EDIT_CHAR_KOOPATROOPA,
    /*  2 */ CHARACTER_EDIT_CHAR_BOBOMB,
    /*  3 */ CHARACTER_EDIT_CHAR_CHEEPCHEEP,
    /*  4 */ CHARACTER_EDIT_CHAR_MONTYMOLE,
    /*  5 */ CHARACTER_EDIT_CHAR_FLYGUY,
    /*  6 */ CHARACTER_EDIT_CHAR_WIGGLER,
    /*  7 */ CHARACTER_EDIT_CHAR_TERESA,
    /*  8 */ CHARACTER_EDIT_CHAR_PIRANHAPLANT,
    /*  9 */ CHARACTER_EDIT_CHAR_KAMEK,
    /* 10 */ CHARACTER_EDIT_CHAR_BOWSER,
    /* 11 */ CHARACTER_EDIT_CHAR_PRINCESSPEACH,

// This macro should expand to (the last entry + 1)
#define CHARACTER_EDIT_CHAR_MAX (12)
} CharacterEditChar;

typedef enum CharacterEditPerformance {
    /* 0 */ CHARACTER_EDIT_PERF_SPEED,
    /* 1 */ CHARACTER_EDIT_PERF_BALANCE,
    /* 2 */ CHARACTER_EDIT_PERF_ATTACK,
    /* 3 */ CHARACTER_EDIT_PERF_BIG_CHAIN,
    /* 4 */ CHARACTER_EDIT_PERF_YOKOZUKI,

// This macro should expand to (the last entry + 1)
#define CHARACTER_EDIT_PERF_MAX (5)
} CharacterEditPerformance;

typedef enum CharacterEditSpeed {
    /* 0 */ CHARACTER_EDIT_SPEED_VERY_SLOW,
    /* 1 */ CHARACTER_EDIT_SPEED_SLOW,
    /* 2 */ CHARACTER_EDIT_SPEED_NORMAL,
    /* 3 */ CHARACTER_EDIT_SPEED_QUICK,
    /* 4 */ CHARACTER_EDIT_SPEED_VERY_QUICK,
    /* 5 */ CHARACTER_EDIT_SPEED_MORE_QUICK,

// This macro should expand to (the last entry + 1)
#define CHARACTER_EDIT_SPEED_MAX (6)
} CharacterEditSpeed;

typedef enum CharacterEditSpecial {
    /*  0 */ CHARACTER_EDIT_SPECIAL_PREEMTIVE_ATTACK,
    /*  1 */ CHARACTER_EDIT_SPECIAL_COUNTER,
    /*  2 */ CHARACTER_EDIT_SPECIAL_LUCK,
    /*  3 */ CHARACTER_EDIT_SPECIAL_BEWILDERMENT,
    /*  4 */ CHARACTER_EDIT_SPECIAL_ROTATE,
    /*  5 */ CHARACTER_EDIT_SPECIAL_PROVOKE,
    /*  6 */ CHARACTER_EDIT_SPECIAL_DOUYOU,
    /*  7 */ CHARACTER_EDIT_SPECIAL_SPEED,
    /*  8 */ CHARACTER_EDIT_SPECIAL_OIAGERU,
    /*  9 */ CHARACTER_EDIT_SPECIAL_SHODDY,
    /* 10 */ CHARACTER_EDIT_SPECIAL_OIKOMI,
    /* 11 */ CHARACTER_EDIT_SPECIAL_DEFAULT,

// This macro should expand to (the last entry + 1)
#define CHARACTER_EDIT_SPECIAL_MAX (12)
} CharacterEditSpecial;

#if MODDING
#define SettingsPage_type SettingsPage
#else
#define SettingsPage_type s32
#endif

typedef struct CharacterStats {
    /* 0x0 */ s8 performance;
    /* 0x1 */ s8 speed;
    /* 0x2 */ u16 specials;
} CharacterStats; // size = 0x4

typedef struct CharacterStatsDefaults {
    /* 0x0 */ s8 performance;
    /* 0x1 */ s8 speed;
} CharacterStatsDefaults; // size = 0x2

static s32 B_800E58B0;
static s32 B_800E58B4;
static s32 B_800E58B8;
static bool B_800E58BC;
static s16 B_800E58C0[40];
static s32 sDebugMenu_CursorCounter;
static s32 B_800E5914;
static s32 B_800E5918;
static s32 B_800E591C;
static s32 B_800E5920;
static s32 B_800E5924;
static s32 B_800E5928;
static s32 B_800E592C;
static SettingsPage_type sDebugMenu_CurrentSettingsPage;
static s32 sDebugMenu_CharacterEdit_SelectedCharacter;
static CharacterStats sDebugMenu_CharacterEdit_CharacterStats[CHARACTER_EDIT_CHAR_MAX];
static CharacterStatsDefaults sDebugMenu_CharacterEdit_DefaultStats;
static s32 sDebugMenu_CharacterEdit_SelectedColumn;
static s32 sDebugMenu_CharacterEdit_SelectedRow[CHARACTER_EDIT_COLUMN_MAX];

s32 D_8008E370[] = {
    1,
    10,
    100,
    1000,
};

const char *D_8008E380[] = {
    "FastErase", "SmallRensa", "Rensa&Erase", "Rensa&Attack", "WidErase", "MajorityRensa",
};

const char *D_8008E398[] = {
    "Dead", "Narrow", "Last", "LastVsnh", "LastVsn", "Badline2", "Badline1", "Normal",
};

const char *D_8008E3B8[] = {
    "Off",
    "On",
};

const char *D_8008E3C0[] = {
    "Mario",        "NokoNoko", "Bomhei", "PukuPuku", "Chiropoo", "Heihoo", "Hanachan", "Telesa",
    "PakkunFlower", "Kamek",    "Koopa",  "Peach",    "Plain1",   "Plain2", "Plain3",   "Plain4",
};

const char *D_8008E400[] = {
    "SpSlow", "Slower", "Slow", "Fast", "Faster", "Fastest", "NoWait", "FasterNW",
};

const char *D_8008E420[] = {
    "--------------", "Unconditional", "Random", "Damage", "Many Vir", "Few Vir",    "Pile",
    "Easy",           "Normal",        "Hard",   "Last",   "Rensa",    "PreemPtive",
};

const char *D_8008E454[] = {
    "----------", "Rotate", "Waver",     "Not Move", "beFast", "beSlow",
    "beNoWait",   "Rapid",  "be Attack", "be Erase", "Lose",
};

typedef u8 (*D_8008E480_type)[3];

D_8008E480_type D_8008E480[] = {
    aiVirusLevel,
    aiDownSpeed,
    aiSlideSpeed,
    aiSlideFSpeed,
};

const char *D_8008E490[] = {
    "VirusLv",
    "DownS",
    "SlideS",
    "SlideFS",
};

void DebugMenu_8003E730(Gfx **gfxP, s32 posX, s32 posY, s32 character) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];

    if (character != B_800E5914) {
        return;
    }

    if (gfxP != NULL) {
        sDebugMenu_CursorCounter++;
        if (sDebugMenu_CursorCounter & 0x10) {
            DebugPrint_DrawCharacter(gfxP, posX + ((2 - B_800E58B0) * DBGPRT_FONT_CHAR_WIDTH),
                                     posY + DBGPRT_FONT_CHAR_HEIGHT, '^');
        }
    } else {
        s32 var_t0;
        u8 *temp_a3;

        var_t0 = 0;
        if (buttonPressed & L_JPAD) {
            var_t0++;
        }
        if (buttonPressed & R_JPAD) {
            var_t0--;
        }

        B_800E58B0 = CLAMP(B_800E58B0 + var_t0, 0, 2);

        var_t0 = 0;
        if (buttonCurrent & U_JPAD) {
            var_t0++;
        }
        if (buttonCurrent & D_JPAD) {
            var_t0--;
        }

        temp_a3 = &D_8008E480[character / 21][(character % 7) + 1][(character / 7) - (character / 21 * 3)];
        *temp_a3 = CLAMP(*temp_a3 + (var_t0 * D_8008E370[B_800E58B0]), 0, 30);
    }
}

const char *D_8008E4A0[] = {
    "Easy",
    "Normal",
    "Hard",
};

void DebugMenu_Page_SpeedMenu_Draw(Gfx **gxfP, s32 posX, s32 posY) {
    PrinterState_Callback callback = DebugMenu_8003E730;
    s32 i;
    s32 j;

    DebugPrint_Open(gxfP, callback, posX, posY + DBGPRT_FONT_CHAR_HEIGHT);
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "");
    for (i = 0; i < ARRAY_COUNT(D_8008E490); i++) {
        DebugPrint_Printf("%s\n\n\n\n\n\n", D_8008E490[i]);
    }
    DebugPrint_Close();

    DebugPrint_Open(gxfP, callback, posX + 7 * DBGPRT_FONT_CHAR_WIDTH, posY + DBGPRT_FONT_CHAR_HEIGHT);
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < ARRAY_COUNT(D_8008E4A0); j++) {
            DebugPrint_Printf("%6s\n\n", D_8008E4A0[j]);
        }
    }
    DebugPrint_Close();

    DebugPrint_Open(gxfP, callback, posX + 14 * DBGPRT_FONT_CHAR_WIDTH, posY);
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "S_er Slow Fast F_er Fest N_Wt F_NW");
    DebugPrint_Close();

    DebugPrint_Open(gxfP, callback, posX + 15 * DBGPRT_FONT_CHAR_WIDTH, posY + DBGPRT_FONT_CHAR_HEIGHT);
    for (i = 0; i < ARRAY_COUNT(D_8008E480); i++) {
        for (j = 0; j < ARRAY_COUNT(*D_8008E480[i]); j++) {
            s32 k;

            for (k = 1; k < 8; k++) {
                DebugPrint_Printf(DBGPRT_CALLBACK "%c%03d  ", 0x15 * i + 7 * j + k - 1, D_8008E480[i][k][j]);
            }

            DebugPrint_Printf("\n\n");
        }
    }
    DebugPrint_Close();

    DebugPrint_Open(gxfP, callback, posX, posY + 25 * DBGPRT_FONT_CHAR_HEIGHT);
    DebugPrint_Printf(DBGPRT_COLOR(CYAN) "<- CharacterMenu\t\t\t\t\tLogicMenu ->");
    DebugPrint_Close();
}

void DebugMenu_8003EB20(void) {
    struct_ai_param *temp_a1 = &ai_param[B_800E591C][B_800E5920];
    s16 *temp_v0 = B_800E58C0;

    *temp_v0++ = B_800E591C;
    *temp_v0++ = B_800E5920;
    *temp_v0++ = temp_a1->unk_00;
    *temp_v0++ = temp_a1->unk_02;
    *temp_v0++ = temp_a1->unk_04;
    *temp_v0++ = temp_a1->unk_08;
    *temp_v0++ = temp_a1->unk_0A;
    *temp_v0++ = temp_a1->unk_0C;
    *temp_v0++ = temp_a1->unk_0E;
    *temp_v0++ = temp_a1->unk_10;
    *temp_v0++ = temp_a1->unk_12;
    *temp_v0++ = temp_a1->unk_14;
    *temp_v0++ = temp_a1->unk_16;
    *temp_v0++ = temp_a1->unk_18;
    *temp_v0++ = temp_a1->unk_1A;
    *temp_v0++ = temp_a1->unk_1C;
    *temp_v0++ = temp_a1->unk_1E;
    *temp_v0++ = temp_a1->unk_20;
    *temp_v0++ = temp_a1->unk_22;
    *temp_v0++ = temp_a1->unk_24;
    *temp_v0++ = temp_a1->unk_26;
    *temp_v0++ = temp_a1->unk_2A;
    *temp_v0++ = temp_a1->unk_06;
    *temp_v0++ = temp_a1->unk_2C;
    *temp_v0++ = temp_a1->unk_2E;
    *temp_v0++ = temp_a1->unk_30;
    *temp_v0++ = temp_a1->unk_32;
    *temp_v0++ = temp_a1->unk_34;
    *temp_v0++ = temp_a1->unk_36;
    *temp_v0++ = evs_gamespeed;
    *temp_v0++ = aiDebugP1 + 1;
}

void DebugMenu_8003ECDC(void) {
    s16 *temp_v0 = B_800E58C0;
    struct_ai_param *temp_a0 = &ai_param[B_800E591C][B_800E5920];

    B_800E591C = *temp_v0++;
    B_800E5920 = *temp_v0++;
    temp_a0->unk_00 = *temp_v0++;
    temp_a0->unk_02 = *temp_v0++;
    temp_a0->unk_04 = *temp_v0++;
    temp_a0->unk_08 = *temp_v0++;
    temp_a0->unk_0A = *temp_v0++;
    temp_a0->unk_0C = *temp_v0++;
    temp_a0->unk_0E = *temp_v0++;
    temp_a0->unk_10 = *temp_v0++;
    temp_a0->unk_12 = *temp_v0++;
    temp_a0->unk_14 = *temp_v0++;
    temp_a0->unk_16 = *temp_v0++;
    temp_a0->unk_18 = *temp_v0++;
    temp_a0->unk_1A = *temp_v0++;
    temp_a0->unk_1C = *temp_v0++;
    temp_a0->unk_1E = *temp_v0++;
    temp_a0->unk_20 = *temp_v0++;
    temp_a0->unk_22 = *temp_v0++;
    temp_a0->unk_24 = *temp_v0++;
    temp_a0->unk_28 = temp_a0->unk_26 = *temp_v0++;
    temp_a0->unk_2A = *temp_v0++;
    temp_a0->unk_06 = *temp_v0++;
    temp_a0->unk_2C = *temp_v0++;
    temp_a0->unk_2E = *temp_v0++;
    temp_a0->unk_30 = *temp_v0++;
    temp_a0->unk_32 = *temp_v0++;
    temp_a0->unk_34 = *temp_v0++;
    temp_a0->unk_36 = *temp_v0++;
    evs_gamespeed = *temp_v0++;
    aiDebugP1 = *temp_v0++ - 1;
}

void DebugMenu_8003EEA4(Gfx **gfxP, s32 posX, s32 posY, s32 character) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s32 var_t0;
    s32 var_t2;
    s32 var_t1;

    if (character != B_800E5918) {
        return;
    }

    var_t2 = 0;
    var_t1 = 2;
    if (character == 0) {
        var_t0 = 5;
    } else if (character == 1) {
        var_t0 = 7;
    } else if (character == 0x15) {
        var_t0 = 1;
    } else if (character < 0x1D) {
        var_t2 = -0x270F;
        var_t0 = 0x270F;
        var_t1 = 5;
    } else if (character == 0x1D) {
        var_t0 = 0x14;
        var_t1 = 3;
    } else if (character == 0x1E) {
        var_t0 = 0x10;
        var_t1 = 3;
    }

    if (gfxP != NULL) {
        sDebugMenu_CursorCounter++;
        if (sDebugMenu_CursorCounter & 0x10) {
            DebugPrint_DrawCharacter(gfxP, posX + (((var_t1 - B_800E58B4) - 1) * DBGPRT_FONT_CHAR_WIDTH),
                                     posY + DBGPRT_FONT_CHAR_HEIGHT, '^');
        }
    } else {
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1--;
        }

        B_800E58B4 = CLAMP(B_800E58B4 + var_a1, 0, var_t1 - 1);

        var_a1 = 0;
        if (buttonCurrent & U_JPAD) {
            var_a1++;
        }
        if (buttonCurrent & D_JPAD) {
            var_a1--;
        }

        B_800E58C0[character] = CLAMP(B_800E58C0[character] + D_8008E370[B_800E58B4] * var_a1, var_t2, var_t0);
    }
}

void DebugMenu_Page_LogicMenu_Draw(Gfx **gxfP, s32 posX, s32 posY) {
    s16 *temp = B_800E58C0;
    s32 index = 0;
    s32 i;

    DebugPrint_Open(gxfP, DebugMenu_8003EEA4, posX, posY);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "Logic             State\n" DBGPRT_COLOR(
                          WHITE) " " DBGPRT_CALLBACK "%c%02d:%-14s " DBGPRT_CALLBACK "%c%02d:%-14s\n\n",
                      index, temp[index + 0], D_8008E380[temp[index + 0]], index + 1, temp[index + 1],
                      D_8008E398[temp[index + 1]]);
    index += 2;

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "OLVrs  ErVrs  ErL1   HeiEr   WidEr   HeightP\n" DBGPRT_COLOR(WHITE));

    for (i = 0; i < 6; i++) {
        DebugPrint_Printf(((i == 3) || (i == 4)) ? " " DBGPRT_CALLBACK "%c%05d%% " : " " DBGPRT_CALLBACK "%c%05d ",
                          index, temp[index]);
        index++;
    }

    DebugPrint_Printf("\n\n");
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "\tALNB   FC     FV     C      V\n" DBGPRT_COLOR(GREEN) "Hei" DBGPRT_COLOR(
        WHITE) "  -----");

    for (i = 1; i < 5; i++) {
        DebugPrint_Printf("  " DBGPRT_CALLBACK "%c%05d", index, temp[index]);
        index++;
    }

    DebugPrint_Printf("\n\n" DBGPRT_COLOR(GREEN) "Wid" DBGPRT_COLOR(WHITE));

    for (i = 0; i < 5; i++) {
        DebugPrint_Printf("  " DBGPRT_CALLBACK "%c%05d", index, temp[index]);
        index++;
    }

    DebugPrint_Printf("\n\n");

    DebugPrint_Printf(
        DBGPRT_COLOR(GREEN) "OnVrs  Rensa  MRensa HiEr    WallP   ErOL3\n" DBGPRT_COLOR(
            WHITE) " " DBGPRT_CALLBACK "%c%05d  " DBGPRT_CALLBACK "%c%05d  " DBGPRT_CALLBACK "%c%05d  " DBGPRT_CALLBACK
                   "%c%05d%%  " DBGPRT_CALLBACK "%c%02d:%-3s  " DBGPRT_CALLBACK "%c%05d\n\n",
        index, temp[index + 0], index + 1, temp[index + 1], index + 2, temp[index + 2], index + 3, temp[index + 3],
        index + 4, temp[index + 4], D_8008E3B8[temp[index + 4]], index + 5, temp[index + 5]);
    index += 6;

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "\tLine2  Line3  Line4~8\n" DBGPRT_COLOR(GREEN) "Hei" DBGPRT_COLOR(WHITE));

    for (i = 0; i < 3; i++) {
        DebugPrint_Printf("  " DBGPRT_CALLBACK "%c%05d", index, temp[index]);
        index++;
    }

    DebugPrint_Printf("\n\n" DBGPRT_COLOR(GREEN) "Wid" DBGPRT_COLOR(WHITE));

    for (i = 0; i < 3; i++) {
        DebugPrint_Printf("  " DBGPRT_CALLBACK "%c%05d", index, temp[index]);
        index++;
    }

    DebugPrint_Printf("\n\n" DBGPRT_COLOR(GREEN) "DebugSpeed PlayerCom\n" DBGPRT_COLOR(
                          WHITE) " " DBGPRT_CALLBACK "%c%03d        " DBGPRT_CALLBACK "%c%03d:%-14s\n\n\n\n\n",
                      index, temp[index], index + 1, temp[index + 1],
                      (temp[index + 1] != 0) ? D_8008E3C0[temp[index + 1] - 1] : "Man");
    index += 2;

    DebugPrint_Printf(DBGPRT_COLOR(CYAN) "<- SpeedMenu\t\t\t\t\tCharacterMenu ->");
    DebugPrint_Close();
}

void DebugMenu_8003F360(void) {
    struct_ai_char_data *temp_a1 = &ai_char_data[B_800E5928];
    s16 *var_a3 = B_800E58C0;
    s32 i;

    *var_a3++ = B_800E5928;
    *var_a3++ = temp_a1->unk_00;
    *var_a3++ = temp_a1->speed;
    *var_a3++ = temp_a1->unk_02;

    for (i = 0; i < ARRAY_COUNT(temp_a1->performance); i++) {
        *var_a3++ = temp_a1->performance[i];
    }

    for (i = B_800E592C; i < B_800E592C + 4; i++) {
        *var_a3++ = temp_a1->unk_0C[i];
        *var_a3++ = temp_a1->unk_1C[i];
        *var_a3++ = temp_a1->unk_3C[i];
        *var_a3++ = temp_a1->unk_4C[i];
    }
}

void DebugMenu_8003F474(void) {
    struct_ai_char_data *temp_t3 = &ai_char_data[B_800E5928];
    s16 *var_t1 = B_800E58C0;
    s32 i;

    B_800E5928 = *var_t1++;
    temp_t3->unk_00 = *var_t1++;
    temp_t3->speed = *var_t1++;
    temp_t3->unk_02 = *var_t1++;

    for (i = 0; i < ARRAY_COUNT(temp_t3->performance); i++) {
        temp_t3->performance[i] = *var_t1++;
    }

    for (i = B_800E592C; i < B_800E592C + 4; i++) {
        temp_t3->unk_0C[i] = *var_t1++;
        temp_t3->unk_1C[i] = *var_t1++;
        temp_t3->unk_3C[i] = *var_t1++;
        temp_t3->unk_4C[i] = *var_t1++;
    }
}

void DebugMenu_8003F568(Gfx **gfxP, s32 posX, s32 posY, s32 character) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s32 var_t1;
    s32 var_t4;
    s32 var_t0;
    s32 var_t5;
    s32 var_t6;

    if (character != B_800E5924) {
        return;
    }

    var_t5 = 0;
    var_t6 = 0;
    var_t4 = 0;
    var_t0 = 2;

    if (character == 0) {
        var_t1 = 0xF;
    } else if (character == 1) {
        var_t1 = 1;
    } else if (character == 2) {
        var_t4 = 1;
        var_t1 = 7;
    } else if (character == 3) {
        var_t4 = -0x64;
        var_t1 = 0x64;
        var_t0 = 3;
    } else if (character < 0xC) {
        var_t1 = 5;
    } else if (character < 0x1B) {
        switch ((character - 0xC) & 3) {
            case 0:
                var_t1 = 0xC;
                var_t0 = 3;
                break;

            case 1:
                var_t1 = 0x3E7;
                var_t5 = 1;
                var_t0 = 3;
                break;

            case 2:
                var_t1 = 0xA;
                var_t0 = 3;
                break;

            case 3:
                var_t1 = 0x3E7;
                var_t6 = 1;
                var_t0 = 3;
                break;

            default:
                var_t0 = 3;
                break;
        }
    }

    if (gfxP != NULL) {
        sDebugMenu_CursorCounter++;
        if (sDebugMenu_CursorCounter & 0x10) {
            DebugPrint_DrawCharacter(gfxP, posX + (((var_t0 - B_800E58B8) - 1) * DBGPRT_FONT_CHAR_WIDTH),
                                     posY + DBGPRT_FONT_CHAR_HEIGHT, '^');
        }
    } else {
        s32 var_a2 = 1;
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1--;
        }

        B_800E58B8 = CLAMP(B_800E58B8 + var_a1, 0, var_t0 - 1);

        if (var_t5 != 0) {
            switch (B_800E58C0[character - 1]) {
                case 0x0:
                case 0x1:
                case 0x3:
                case 0x6:
                case 0x7:
                case 0x8:
                case 0x9:
                case 0xB:
                    var_a2 = 0;
                    break;
            }
        } else if (var_t6 != 0) {
            switch (B_800E58C0[character - 1]) {
                case 0x0:
                case 0x1:
                case 0x2:
                    var_a2 = 0;
                    break;
            }
        }

        if (var_a2 != 0) {
            var_a1 = 0;
            if (buttonCurrent & U_JPAD) {
                var_a1++;
            }
            if (buttonCurrent & D_JPAD) {
                var_a1 -= 1;
            }

            B_800E58C0[character] = CLAMP(B_800E58C0[character] + D_8008E370[B_800E58B8] * var_a1, var_t4, var_t1);
        }
    }
}

void DebugMenu_Page_CharacterMenu_Draw(Gfx **gxfP, s32 posX, s32 posY) {
    s16 *new_var = B_800E58C0;
    s32 var_s0 = 0;
    s32 i;

    DebugPrint_Open(gxfP, DebugMenu_8003F568, posX, posY);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "Character         WaitAttack Speed       Luck\n" DBGPRT_COLOR(
                          WHITE) " " DBGPRT_CALLBACK "%c%02d:%-14s " DBGPRT_CALLBACK "%c%02d:%-3s     " DBGPRT_CALLBACK
                                 "%c%02d:%-8s " DBGPRT_CALLBACK "%c%03d%%\n\n",
                      var_s0, new_var[var_s0], D_8008E3C0[new_var[var_s0]], var_s0 + 1, new_var[var_s0 + 1],
                      D_8008E3B8[new_var[var_s0 + 1]], var_s0 + 2, new_var[var_s0 + 2], D_8008E400[new_var[var_s0 + 2]],
                      var_s0 + 3, new_var[var_s0 + 3]);
    var_s0 += 4;

    for (i = 0; i < 4; i++) {
        DebugPrint_Printf(
            DBGPRT_COLOR(GREEN) "%-18s %-18s\n" DBGPRT_COLOR(WHITE) " " DBGPRT_CALLBACK "%c%02d:%-14s  " DBGPRT_CALLBACK
                                                                    "%c%02d:%-14s\n\n",
            D_8008E398[2 * i], D_8008E398[2 * i + 1], var_s0, new_var[var_s0], D_8008E380[new_var[var_s0]], var_s0 + 1,
            new_var[var_s0 + 1], D_8008E380[new_var[var_s0 + 1]]);
        var_s0 += 2;
    }

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "  ExCondition        Sub   ExEffect       Sub\n");

    for (i = 0; i < 4; i++) {
        DebugPrint_Printf(DBGPRT_COLOR(GREEN) "%02d " DBGPRT_COLOR(WHITE) DBGPRT_CALLBACK "%c%03d:%-14s ",
                          B_800E592C + i + 1, var_s0, new_var[var_s0], D_8008E420[new_var[var_s0]]);

        var_s0++;
        switch (new_var[var_s0 - 1]) {
            case 0x0:
            case 0x1:
            case 0x3:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xB:
                DebugPrint_Printf(DBGPRT_CALLBACK "%c---   ", var_s0);
                break;

            default:
                DebugPrint_Printf(DBGPRT_CALLBACK "%c%03d%c  ", var_s0, new_var[var_s0],
                                  (new_var[var_s0 - 1] == 2) ? '%' : ' ');
                break;
        }

        var_s0++;

        DebugPrint_Printf(DBGPRT_CALLBACK "%c%03d:%-10s ", var_s0, new_var[var_s0], D_8008E454[new_var[var_s0]]);

        var_s0++;
        switch (new_var[var_s0 - 1]) {
            case 0:
            case 1:
            case 2:
                DebugPrint_Printf(DBGPRT_CALLBACK "%c---", var_s0);
                break;

            default:
                DebugPrint_Printf(DBGPRT_CALLBACK "%c%03d", var_s0, new_var[var_s0]);
                break;
        }

        var_s0++;

        DebugPrint_Printf("\n\n");
    }

    DebugPrint_Printf("\n");
    DebugPrint_Printf(DBGPRT_COLOR(CYAN) "<- LogicMenu\t\t\t\t\t\tSpeedMenu ->");
    DebugPrint_Close();
}

void DebugMenu_Settings_Update(void) {
    u16 button = joycur[0];
    s32 dir;

    dir = 0;
    if (gControllerPressedButtons[0] & L_CBUTTONS) {
        dir--;
    }
    if (gControllerPressedButtons[0] & R_CBUTTONS) {
        dir++;
    }

    sDebugMenu_CurrentSettingsPage = WrapI(0, SETTINGS_PAGE_MAX, sDebugMenu_CurrentSettingsPage + dir);

    dir = 0;
    if (button & L_TRIG) {
        dir--;
    }
    if (button & R_TRIG) {
        dir++;
    }

    switch (sDebugMenu_CurrentSettingsPage) {
        case SETTINGS_PAGE_LOGIC_MENU:
            B_800E5918 = WrapI(0, 0x1F, B_800E5918 + dir);
            DebugMenu_8003EB20();
            DebugMenu_Page_LogicMenu_Draw(NULL, 0x10, 0x10);
            DebugMenu_8003ECDC();
            break;

        case SETTINGS_PAGE_CHARACTER_MENU:
            B_800E5924 = WrapI(0, 0x1C, B_800E5924 + dir);
            if (dir > 0) {
                if (B_800E5924 == 0) {
                    B_800E592C = WrapI(0, 0x10, B_800E592C + 4);
                    if (B_800E592C != 0) {
                        B_800E5924 = 0xC;
                    }
                } else if (B_800E5924 == 0xC) {
                    B_800E592C = 0;
                }
            } else if (dir < 0) {
                if (B_800E5924 == 0xB) {
                    if (B_800E592C != 0) {
                        B_800E5924 = 0x1B;
                        B_800E592C = WrapI(0, 0x10, B_800E592C - 4);
                    }
                } else if (B_800E5924 == 0x1B) {
                    B_800E592C = 0xC;
                }
            }

            DebugMenu_8003F360();
            DebugMenu_Page_CharacterMenu_Draw(NULL, 0x10, 0x10);
            DebugMenu_8003F474();
            break;

        case SETTINGS_PAGE_SPEED_MENU:
            B_800E5914 = WrapI(0, 0x54, B_800E5914 + dir);
            DebugMenu_Page_SpeedMenu_Draw(NULL, 0x10, 0x10);
            break;
    }
}

void DebugMenu_Settings_Draw(Gfx **gxfP) {
    switch (sDebugMenu_CurrentSettingsPage) {
        case SETTINGS_PAGE_LOGIC_MENU:
            DebugMenu_Page_LogicMenu_Draw(gxfP, 0x10, 0x10);
            break;

        case SETTINGS_PAGE_CHARACTER_MENU:
            DebugMenu_Page_CharacterMenu_Draw(gxfP, 0x10, 0x10);
            break;

        case SETTINGS_PAGE_SPEED_MENU:
            DebugMenu_Page_SpeedMenu_Draw(gxfP, 0x10, 0x10);
            break;
    }
}

void DebugMenu_Page_CharacterEdit_Callback(Gfx **gfxP, s32 posX, s32 posY, s32 character) {
    u16 button = gControllerPressedButtons[0];
    CharacterStats *stats = &sDebugMenu_CharacterEdit_CharacterStats[sDebugMenu_CharacterEdit_SelectedCharacter];
    s32 column = character >> 5;
    s32 row = character & 0x1F;

    if (column != sDebugMenu_CharacterEdit_SelectedColumn) {
        return;
    }

    if (row != sDebugMenu_CharacterEdit_SelectedRow[column]) {
        return;
    }

    if (gfxP != NULL) {
        sDebugMenu_CursorCounter++;
        if (sDebugMenu_CursorCounter & 0x10) {
            DebugPrint_SetColor(gfxP, DBGPRT_COLOR_WHITE);
            DebugPrint_DrawCharacter(gfxP, posX - DBGPRT_FONT_CHAR_WIDTH, posY, '>');
        }
    } else if (button & A_BUTTON) {
        switch (column) {
            case CHARACTER_EDIT_COLUMN_NAME:
                sDebugMenu_CharacterEdit_SelectedCharacter = sDebugMenu_CharacterEdit_SelectedRow[column];
                return;

            case CHARACTER_EDIT_COLUMN_PERFORMANCE:
                stats->performance = sDebugMenu_CharacterEdit_SelectedRow[column];
                break;

            case CHARACTER_EDIT_COLUMN_SPEED:
                stats->speed = sDebugMenu_CharacterEdit_SelectedRow[column];
                break;

            case CHARACTER_EDIT_COLUMN_SPECIAL:
                stats->specials ^= 1 << sDebugMenu_CharacterEdit_SelectedRow[column];
                break;
        }
    }
}

const char *sDebugMenu_CharacterEdit_CharacterNames[] = {
    [CHARACTER_EDIT_CHAR_MARIO] = T("ﾏﾘｵ", "Mario"),
    [CHARACTER_EDIT_CHAR_KOOPATROOPA] = T("ﾉｺﾉｺ", "KoopaTroopa"),
    [CHARACTER_EDIT_CHAR_BOBOMB] = T("ﾎﾞﾑﾍｲ", "Bob-omb"),
    [CHARACTER_EDIT_CHAR_CHEEPCHEEP] = T("ﾌﾟｸﾌﾟｸ", "CheepCheep"),
    [CHARACTER_EDIT_CHAR_MONTYMOLE] = T("ﾁｮﾛﾌﾟｰ", "Monty Mole"),
    [CHARACTER_EDIT_CHAR_FLYGUY] = T("ﾌﾟﾛﾍﾟﾗﾍｲﾎｰ", "Fly Guy"),
    [CHARACTER_EDIT_CHAR_WIGGLER] = T("ﾊﾅﾁｬﾝ", "Wiggler"),
    [CHARACTER_EDIT_CHAR_TERESA] = T("ﾃﾚｻ", "Teresa"), // Boo?
    [CHARACTER_EDIT_CHAR_PIRANHAPLANT] = T("ﾊﾟｯｸﾝﾌﾗﾜｰ", "Piranha Plant"),
    [CHARACTER_EDIT_CHAR_KAMEK] = T("ｶﾒｯｸ", "Kamek"),
    [CHARACTER_EDIT_CHAR_BOWSER] = T("ｸｯﾊﾟ", "Bowser"),
    [CHARACTER_EDIT_CHAR_PRINCESSPEACH] = T("ﾌﾟﾘﾝｾｽﾋﾟｰﾁ", "Princess Peach"),
};
static_assert(ARRAY_COUNT(sDebugMenu_CharacterEdit_CharacterNames) == CHARACTER_EDIT_CHAR_MAX, "");

const char *D_8008E4DC[] = {
    [CHARACTER_EDIT_PERF_SPEED] = T("ｽﾋﾟｰﾄﾞ", "Speed"),
    [CHARACTER_EDIT_PERF_BALANCE] = T("ﾊﾞﾗﾝｽ", "Balance"),
    [CHARACTER_EDIT_PERF_ATTACK] = T("ｺｳｹﾞｷ", "Attack"),
    [CHARACTER_EDIT_PERF_BIG_CHAIN] = T("ﾀﾞｲﾚﾝｻﾈﾗｲ", "Big chain"),
    [CHARACTER_EDIT_PERF_YOKOZUKI] = T("ﾖｺｽﾞｷ", "Yokozuki"), // TODO
};
static_assert(ARRAY_COUNT(D_8008E4DC) == CHARACTER_EDIT_PERF_MAX, "");

const char *D_8008E4F0[] = {
    [CHARACTER_EDIT_SPEED_VERY_SLOW] = T("ﾋｼﾞｮｳﾆｵｿｲ", "Very slow"),
    [CHARACTER_EDIT_SPEED_SLOW] = T("ｵｿｲ", "Slow"),
    [CHARACTER_EDIT_SPEED_NORMAL] = T("ﾌﾂｳ", "Normal"),
    [CHARACTER_EDIT_SPEED_QUICK] = T("ﾊﾔｲ", "Quick"),
    [CHARACTER_EDIT_SPEED_VERY_QUICK] = T("ﾋｼﾞｮｳﾆﾊﾔｲ", "Very quick"),
    [CHARACTER_EDIT_SPEED_MORE_QUICK] = T("ﾓｯﾄﾓﾊﾔｲ", "More quick"),
};
static_assert(ARRAY_COUNT(D_8008E4F0) == CHARACTER_EDIT_SPEED_MAX, "");

const char *D_8008E508[] = {
    [CHARACTER_EDIT_SPECIAL_PREEMTIVE_ATTACK] = T("ｾﾝｾｲｺｳｹﾞｷ", "Preemptive attack"),
    [CHARACTER_EDIT_SPECIAL_COUNTER] = T("ｶｳﾝﾀｰ", "Counter"),
    [CHARACTER_EDIT_SPECIAL_LUCK] = T("ﾗｯｸ", "Luck"),
    [CHARACTER_EDIT_SPECIAL_BEWILDERMENT] = T("ﾏﾖｲ", "Bewilderment"),
    [CHARACTER_EDIT_SPECIAL_ROTATE] = T("ｸﾙｸﾙﾏﾜｽ", "Rotate"),
    [CHARACTER_EDIT_SPECIAL_PROVOKE] = T("ﾁｮｳﾊﾂ", "Provoke"),
    [CHARACTER_EDIT_SPECIAL_DOUYOU] = T("ﾄﾞｳﾖｳ", "Douyou"), // TODO
    [CHARACTER_EDIT_SPECIAL_SPEED] = T("ｽﾋﾟｰﾄﾞｱｯﾌﾟ", "Speed up"),
    [CHARACTER_EDIT_SPECIAL_OIAGERU] = T("ｵｲｱｹﾞﾙ", "Oiageru"), // TODO
    [CHARACTER_EDIT_SPECIAL_SHODDY] = T("ﾃﾇｷ", "Shoddy"),
    [CHARACTER_EDIT_SPECIAL_OIKOMI] = T("ｵｲｺﾐ", "Oikomi"), // TODO
    [CHARACTER_EDIT_SPECIAL_DEFAULT] = T("ﾃﾞﾌｫﾙﾄ", "Default"),
};
static_assert(ARRAY_COUNT(D_8008E508) == CHARACTER_EDIT_SPECIAL_MAX, "");

s8 D_8008E538[] = {
    [CHARACTER_EDIT_PERF_SPEED] = 0x00,     [CHARACTER_EDIT_PERF_BALANCE] = 0x02,  [CHARACTER_EDIT_PERF_ATTACK] = 0x03,
    [CHARACTER_EDIT_PERF_BIG_CHAIN] = 0x05, [CHARACTER_EDIT_PERF_YOKOZUKI] = 0x04,
};
static_assert(ARRAY_COUNT(D_8008E538) == CHARACTER_EDIT_PERF_MAX, "");

#if VERSION_CN
#define D_8008E540_ARR D_80099290_cn
#else
#define D_8008E540_ARR D_8008E540
#endif

s8 D_8008E540_ARR[] = {
    [CHARACTER_EDIT_SPEED_VERY_SLOW] = 1, [CHARACTER_EDIT_SPEED_SLOW] = 2,       [CHARACTER_EDIT_SPEED_NORMAL] = 3,
    [CHARACTER_EDIT_SPEED_QUICK] = 4,     [CHARACTER_EDIT_SPEED_VERY_QUICK] = 5, [CHARACTER_EDIT_SPEED_MORE_QUICK] = 6,
};
static_assert(ARRAY_COUNT(D_8008E540_ARR) == CHARACTER_EDIT_SPEED_MAX, "");

const char **D_8008E548[] = {
    [CHARACTER_EDIT_COLUMN_NAME] = sDebugMenu_CharacterEdit_CharacterNames,
    [CHARACTER_EDIT_COLUMN_PERFORMANCE] = D_8008E4DC,
    [CHARACTER_EDIT_COLUMN_SPEED] = D_8008E4F0,
    [CHARACTER_EDIT_COLUMN_SPECIAL] = D_8008E508,
};
static_assert(ARRAY_COUNTU(D_8008E548) == CHARACTER_EDIT_COLUMN_MAX, "");

s32 sDebugMenu_CharacterEdit_RowsPerColumn[] = {
    [CHARACTER_EDIT_COLUMN_NAME] = 12,
    [CHARACTER_EDIT_COLUMN_PERFORMANCE] = 5,
    [CHARACTER_EDIT_COLUMN_SPEED] = 6,
    [CHARACTER_EDIT_COLUMN_SPECIAL] = 12,
};
static_assert(ARRAY_COUNTU(sDebugMenu_CharacterEdit_RowsPerColumn) == CHARACTER_EDIT_COLUMN_MAX, "");

s8 D_8008E568[] = {
    [CHARACTER_EDIT_CHAR_MARIO] = 0,         [CHARACTER_EDIT_CHAR_KOOPATROOPA] = -14,
    [CHARACTER_EDIT_CHAR_BOBOMB] = 0,        [CHARACTER_EDIT_CHAR_CHEEPCHEEP] = 0,
    [CHARACTER_EDIT_CHAR_MONTYMOLE] = 2,     [CHARACTER_EDIT_CHAR_FLYGUY] = -2,
    [CHARACTER_EDIT_CHAR_WIGGLER] = 0,       [CHARACTER_EDIT_CHAR_TERESA] = 2,
    [CHARACTER_EDIT_CHAR_PIRANHAPLANT] = -2, [CHARACTER_EDIT_CHAR_KAMEK] = 4,
    [CHARACTER_EDIT_CHAR_BOWSER] = 2,        [CHARACTER_EDIT_CHAR_PRINCESSPEACH] = 0,
};
static_assert(ARRAY_COUNTU(D_8008E568) == CHARACTER_EDIT_CHAR_MAX, "");

s8 D_8008E574[] = {
    [CHARACTER_EDIT_PERF_SPEED] = 33,     [CHARACTER_EDIT_PERF_BALANCE] = 40,  [CHARACTER_EDIT_PERF_ATTACK] = 25,
    [CHARACTER_EDIT_PERF_BIG_CHAIN] = 10, [CHARACTER_EDIT_PERF_YOKOZUKI] = 34,
};
static_assert(ARRAY_COUNTU(D_8008E574) == CHARACTER_EDIT_PERF_MAX, "");

s8 D_8008E57C[] = {
    [CHARACTER_EDIT_SPEED_VERY_SLOW] = 0,   [CHARACTER_EDIT_SPEED_SLOW] = 8,
    [CHARACTER_EDIT_SPEED_NORMAL] = 16,     [CHARACTER_EDIT_SPEED_QUICK] = 24,
    [CHARACTER_EDIT_SPEED_VERY_QUICK] = 32, [CHARACTER_EDIT_SPEED_MORE_QUICK] = 40,
};
static_assert(ARRAY_COUNTU(D_8008E57C) == CHARACTER_EDIT_SPEED_MAX, "");

s8 D_8008E584[] = {
    [CHARACTER_EDIT_SPECIAL_PREEMTIVE_ATTACK] = 6,
    [CHARACTER_EDIT_SPECIAL_COUNTER] = 4,
    [CHARACTER_EDIT_SPECIAL_LUCK] = 10,
    [CHARACTER_EDIT_SPECIAL_BEWILDERMENT] = -2,
    [CHARACTER_EDIT_SPECIAL_ROTATE] = -2,
    [CHARACTER_EDIT_SPECIAL_PROVOKE] = -2,
    [CHARACTER_EDIT_SPECIAL_DOUYOU] = -10,
    [CHARACTER_EDIT_SPECIAL_SPEED] = 4,
    [CHARACTER_EDIT_SPECIAL_OIAGERU] = 2,
    [CHARACTER_EDIT_SPECIAL_SHODDY] = -6,
    [CHARACTER_EDIT_SPECIAL_OIKOMI] = 4,
    [CHARACTER_EDIT_SPECIAL_DEFAULT] = 0,
};
static_assert(ARRAY_COUNTU(D_8008E584) == CHARACTER_EDIT_SPECIAL_MAX, "");

s32 DebugMenu_GetCharacterStrength(void) {
    s32 strength = 0;
    CharacterStats stats = sDebugMenu_CharacterEdit_CharacterStats[sDebugMenu_CharacterEdit_SelectedCharacter];
    s32 i;

    for (i = 0; i < sDebugMenu_CharacterEdit_RowsPerColumn[CHARACTER_EDIT_COLUMN_SPECIAL]; i++) {
        bool turnOff;

#if PRESERVE_UB
        turnOff = false;
#endif

        switch (stats.specials & (1 << i)) {
            case 1 << CHARACTER_EDIT_SPECIAL_PREEMTIVE_ATTACK:
                turnOff = (stats.performance == CHARACTER_EDIT_PERF_ATTACK) &&
                          (stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK);
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_COUNTER:
                turnOff = stats.performance == CHARACTER_EDIT_PERF_ATTACK;
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_LUCK:
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_BEWILDERMENT:
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_ROTATE:
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_PROVOKE:
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_DOUYOU:
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_SPEED:
                turnOff = stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK;
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_OIAGERU:
                turnOff = stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK;
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_SHODDY:
                turnOff = stats.speed <= CHARACTER_EDIT_SPEED_SLOW;
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_OIKOMI:
                turnOff = stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK;
                break;

            case 1 << CHARACTER_EDIT_SPECIAL_DEFAULT:
                switch (sDebugMenu_CharacterEdit_SelectedCharacter) {
                    case CHARACTER_EDIT_CHAR_MARIO:
                        break;

                    case CHARACTER_EDIT_CHAR_KOOPATROOPA:
                        turnOff = stats.specials &
                                  ((1 << CHARACTER_EDIT_SPECIAL_BEWILDERMENT) | (1 << CHARACTER_EDIT_SPECIAL_ROTATE) |
                                   (1 << CHARACTER_EDIT_SPECIAL_DOUYOU));
                        break;

                    case CHARACTER_EDIT_CHAR_MONTYMOLE:
                        turnOff = stats.speed == CHARACTER_EDIT_SPEED_MORE_QUICK;
                        break;

                    case CHARACTER_EDIT_CHAR_FLYGUY:
                        turnOff = stats.specials & (1 << CHARACTER_EDIT_SPECIAL_ROTATE);
                        break;

                    case CHARACTER_EDIT_CHAR_TERESA:
                        turnOff = stats.specials & (1 << CHARACTER_EDIT_SPECIAL_SPEED);
                        break;

                    case CHARACTER_EDIT_CHAR_PIRANHAPLANT:
                        turnOff = stats.specials & (1 << CHARACTER_EDIT_SPECIAL_BEWILDERMENT);
                        break;

                    case CHARACTER_EDIT_CHAR_KAMEK:
                        turnOff = (stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK);
                        break;

                    case CHARACTER_EDIT_CHAR_BOWSER:
                        turnOff = false;
                        if ((stats.speed >= CHARACTER_EDIT_SPEED_VERY_QUICK) ||
                            (stats.specials &
                             ((1 << CHARACTER_EDIT_SPECIAL_COUNTER) | (1 << CHARACTER_EDIT_SPECIAL_OIKOMI)))) {
                            turnOff = true;
                        }
                        break;

                    case CHARACTER_EDIT_CHAR_PRINCESSPEACH:
                        break;
                }
                break;
        }

        //! @bug: using `var_a1` which may be unitialized
        if (turnOff) {
            stats.specials &= ~(1 << i);
        }
    }

    if (stats.specials & (1 << CHARACTER_EDIT_SPECIAL_DEFAULT)) {
        strength += D_8008E568[sDebugMenu_CharacterEdit_SelectedCharacter];
    }

    if (stats.performance >= 0) {
        strength += D_8008E574[stats.performance];
    }

    if (stats.speed >= 0) {
        strength += D_8008E57C[stats.speed];
    }

    for (i = 0; i < ARRAY_COUNTU(D_8008E584); i++) {
        if ((stats.specials >> i) & 1) {
            strength += D_8008E584[i];
        }
    }

    return strength;
}

s8 D_8008E590[] = {
    CHARACTER_EDIT_PERF_SPEED,  CHARACTER_EDIT_PERF_SPEED,    CHARACTER_EDIT_PERF_BALANCE,
    CHARACTER_EDIT_PERF_ATTACK, CHARACTER_EDIT_PERF_YOKOZUKI, CHARACTER_EDIT_PERF_BIG_CHAIN,
    CHARACTER_EDIT_PERF_SPEED,  CHARACTER_EDIT_PERF_SPEED,
};

s8 D_8008E598[] = {
    CHARACTER_EDIT_SPEED_VERY_SLOW,  CHARACTER_EDIT_SPEED_VERY_SLOW,  CHARACTER_EDIT_SPEED_SLOW,
    CHARACTER_EDIT_SPEED_NORMAL,     CHARACTER_EDIT_SPEED_QUICK,      CHARACTER_EDIT_SPEED_VERY_QUICK,
    CHARACTER_EDIT_SPEED_MORE_QUICK, CHARACTER_EDIT_SPEED_MORE_QUICK,
};

void DebugMenu_Page_CharacterEdit_RetrieveStats(void) {
    CharacterStatsDefaults *statsDefaults = &sDebugMenu_CharacterEdit_DefaultStats;
    s32 i;

    for (i = 0; i < sDebugMenu_CharacterEdit_RowsPerColumn[CHARACTER_EDIT_COLUMN_NAME]; i++) {
        struct_ai_char_data *temp2 = &ai_char_data_org[i];
        struct_ai_char_data *var_a1 = &ai_char_data[i];
        CharacterStats *stats = &sDebugMenu_CharacterEdit_CharacterStats[i];

        stats->performance = D_8008E590[var_a1->performance[7]];
        stats->speed = D_8008E598[var_a1->speed];

        if (!B_800E58BC) {
            stats->specials = (1 << CHARACTER_EDIT_SPECIAL_DEFAULT);
        }

        if (i == sDebugMenu_CharacterEdit_SelectedCharacter) {
            statsDefaults->performance = D_8008E590[temp2->performance[7]];
            statsDefaults->speed = D_8008E598[temp2->speed];
        }
    }

    B_800E58BC = true;
}

void DebugMenu_Page_CharacterEdit_ApplyStats(void) {
    s32 i;

    for (i = 0; i < sDebugMenu_CharacterEdit_RowsPerColumn[CHARACTER_EDIT_COLUMN_NAME]; i++) {
        struct_ai_char_data *temp_a2 = &ai_char_data_org[i];
        struct_ai_char_data *temp_t8 = &ai_char_data[i];
        CharacterStats *stats = &sDebugMenu_CharacterEdit_CharacterStats[i];
        s32 j;
        s32 index;

        for (j = 0; j < ARRAY_COUNT(temp_t8->performance); j++) {
            temp_t8->performance[j] = D_8008E538[stats->performance];
        }

        //! FAKE: renaming D_80099290_cn to D_8008E540 produces different codegen
        temp_t8->speed = D_8008E540_ARR[stats->speed];

        index = 0;

        if (stats->specials & (1 << CHARACTER_EDIT_SPECIAL_DEFAULT)) {
            for (j = 0; j < 4; j++) {
                temp_t8->unk_0C[index] = temp_a2->unk_0C[j];
                temp_t8->unk_1C[index] = temp_a2->unk_1C[j];
                temp_t8->unk_3C[index] = temp_a2->unk_3C[j];
                temp_t8->unk_4C[index] = temp_a2->unk_4C[j];
                index++;
            }
        }

        for (j = 0; j < sDebugMenu_CharacterEdit_RowsPerColumn[CHARACTER_EDIT_COLUMN_SPECIAL]; j++) {
            switch (stats->specials & (1 << j)) {
                case 1 << CHARACTER_EDIT_SPECIAL_PREEMTIVE_ATTACK:
                    temp_t8->unk_0C[index] = 0xC;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 4;
                    temp_t8->unk_4C[index] = 1;
                    index++;

                    temp_t8->unk_0C[index] = 0xC;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 8;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_COUNTER:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 8;
                    temp_t8->unk_4C[index] = 7;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_LUCK:
                    temp_t8->unk_02 = 0x32;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_BEWILDERMENT:
                    temp_t8->unk_0C[index] = 2;
                    temp_t8->unk_1C[index] = 0x21;
                    temp_t8->unk_3C[index] = 2;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_ROTATE:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_PROVOKE:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_DOUYOU:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 3;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_SPEED:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 7;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_OIAGERU:
                    temp_t8->unk_0C[index] = 4;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 6;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_SHODDY:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 5;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 1 << CHARACTER_EDIT_SPECIAL_OIKOMI:
                    temp_t8->unk_0C[index] = 0xA;
                    temp_t8->unk_1C[index] = 0xA;
                    temp_t8->unk_3C[index] = 4;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;
            }
        }

        for (j = index; j < STRUCT_AI_CHAR_DATA_LEN; j++) {
            temp_t8->unk_0C[j] = 0;
            temp_t8->unk_1C[j] = 0;
            temp_t8->unk_3C[j] = 0;
            temp_t8->unk_4C[j] = 0;
        }
    }
}

void DebugMenu_Page_CharacterEdit_UpdateController(void) {
    s32 vertical = 0;
    s32 horizontal = 0;

    if (gControllerPressedButtons[0] & L_JPAD) {
        horizontal--;
    }
    if (gControllerPressedButtons[0] & R_JPAD) {
        horizontal++;
    }

    if (gControllerPressedButtons[0] & U_JPAD) {
        vertical--;
    }
    if (gControllerPressedButtons[0] & D_JPAD) {
        vertical++;
    }

    sDebugMenu_CharacterEdit_SelectedColumn = WrapI(0, ARRAY_COUNT(sDebugMenu_CharacterEdit_SelectedRow),
                                                    sDebugMenu_CharacterEdit_SelectedColumn + horizontal);
    sDebugMenu_CharacterEdit_SelectedRow[sDebugMenu_CharacterEdit_SelectedColumn] =
        WrapI(0, sDebugMenu_CharacterEdit_RowsPerColumn[sDebugMenu_CharacterEdit_SelectedColumn],
              sDebugMenu_CharacterEdit_SelectedRow[sDebugMenu_CharacterEdit_SelectedColumn] + vertical);
}

const char *sDebugMenu_CharacterEdit_ColumnNames[] = {
    [CHARACTER_EDIT_COLUMN_NAME] = "<" T("ｷｬﾗｸﾀｰ", "Character") ">",
    [CHARACTER_EDIT_COLUMN_PERFORMANCE] = "<" T("ｾｲｶｸ", "Performance") ">",
    [CHARACTER_EDIT_COLUMN_SPEED] = "<" T("ｽﾋﾟｰﾄﾞ", "Speed") ">",
    [CHARACTER_EDIT_COLUMN_SPECIAL] = "<" T("ﾄｸｼｭ", "Special") ">",
};
static_assert(ARRAY_COUNTU(sDebugMenu_CharacterEdit_ColumnNames) == CHARACTER_EDIT_COLUMN_MAX, "");

s32 sDebugMenu_CharacterEdit_DefaultColor = '0' + DBGPRT_COLOR_MAGENTA;

s32 sDebugMenu_CharacterEdit_ColumnWidths[] = {
    [CHARACTER_EDIT_COLUMN_NAME] = 11,
    [CHARACTER_EDIT_COLUMN_PERFORMANCE] = 10,
    [CHARACTER_EDIT_COLUMN_SPEED] = 10,
    [CHARACTER_EDIT_COLUMN_SPECIAL] = 14,
};
static_assert(ARRAY_COUNTU(sDebugMenu_CharacterEdit_ColumnWidths) == CHARACTER_EDIT_COLUMN_MAX, "");

void DebugMenu_Page_CharacterEdit_Draw(Gfx **gfxP, s32 posX, s32 posY) {
    CharacterStats *stats = &sDebugMenu_CharacterEdit_CharacterStats[sDebugMenu_CharacterEdit_SelectedCharacter];
    s32 strength = CLAMP(DebugMenu_GetCharacterStrength() / 10, 0, 10);
    s32 column;

    DebugPrint_Open(gfxP, DebugMenu_Page_CharacterEdit_Callback, posX, posY);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "[" T("ｷｬﾗｸﾀｰｴﾃﾞｨｯﾄ", "Character edit") "]\n\n");
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) T("ﾂﾖｻ", "Strength") " ");

    for (column = 0; column < strength; column++) {
        // ★
        DebugPrint_Printf("%c", 0x83);
    }

    for (; column < 10; column++) {
        // ☆
        DebugPrint_Printf("%c", 0x82);
    }

    DebugPrint_Close();

    posX += DBGPRT_FONT_CHAR_WIDTH;
    posY += 4 * DBGPRT_FONT_CHAR_HEIGHT;

    for (column = 0; column < CHARACTER_EDIT_COLUMN_MAX; column++) {
        s32 row;
        s32 callbackArg;

        DebugPrint_Open(gfxP, DebugMenu_Page_CharacterEdit_Callback, posX, posY);

        DebugPrint_Printf(DBGPRT_COLOR(GREEN) "%s\n", sDebugMenu_CharacterEdit_ColumnNames[column]);

        callbackArg = column << 5;

        for (row = 0; row < sDebugMenu_CharacterEdit_RowsPerColumn[column]; row++) {
            s32 color = '0' + DBGPRT_COLOR_WHITE;
            s32 checkbox;

            switch (column) {
                case CHARACTER_EDIT_COLUMN_NAME:
                    if (row == sDebugMenu_CharacterEdit_SelectedCharacter) {
                        color = '0' + DBGPRT_COLOR_CYAN;
                    }
                    break;

                case CHARACTER_EDIT_COLUMN_PERFORMANCE:
                    if (row == stats->performance) {
                        color = '0' + DBGPRT_COLOR_CYAN;
                    } else if (row == sDebugMenu_CharacterEdit_DefaultStats.performance) {
                        color = sDebugMenu_CharacterEdit_DefaultColor;
                    }
                    break;

                case CHARACTER_EDIT_COLUMN_SPEED:
                    if (row == stats->speed) {
                        color = '0' + DBGPRT_COLOR_CYAN;
                    } else if (row == sDebugMenu_CharacterEdit_DefaultStats.speed) {
                        color = sDebugMenu_CharacterEdit_DefaultColor;
                    }
                    break;

                case CHARACTER_EDIT_COLUMN_SPECIAL:
                    checkbox = 0x80; // ⎕
                    if ((stats->specials >> row) & 1) {
                        color = '0' + DBGPRT_COLOR_CYAN;
                        checkbox = 0x81; // ⍂
                    } else if (row == CHARACTER_EDIT_SPECIAL_DEFAULT) {
                        color = sDebugMenu_CharacterEdit_DefaultColor;
                    }
                    break;
            }

            switch (column) {
                case CHARACTER_EDIT_COLUMN_NAME:
                case CHARACTER_EDIT_COLUMN_PERFORMANCE:
                case CHARACTER_EDIT_COLUMN_SPEED:
                    DebugPrint_Printf(DBGPRT_CALLBACK "%c" DBGPRT_COLOR_RAW "%c"
                                                      "%s\n",
                                      callbackArg, color, D_8008E548[column][row]);
                    callbackArg += 1;
                    break;

                case CHARACTER_EDIT_COLUMN_SPECIAL:
                    DebugPrint_Printf(DBGPRT_CALLBACK "%c" DBGPRT_COLOR_RAW "%c"
                                                      "%c:%s\n",
                                      callbackArg, color, checkbox, D_8008E548[column][row]);
                    callbackArg += 1;
                    break;
            }
        }

        DebugPrint_Close();
        posX += sDebugMenu_CharacterEdit_ColumnWidths[column] * DBGPRT_FONT_CHAR_WIDTH;
    }
}

void DebugMenu_CharacterEdit_Update(void) {
    DebugMenu_Page_CharacterEdit_UpdateController();
    DebugMenu_Page_CharacterEdit_RetrieveStats();
    DebugMenu_Page_CharacterEdit_Draw(NULL, 0x20, 0x20);
    DebugMenu_Page_CharacterEdit_ApplyStats();
}

void DebugMenu_CharacterEdit_Draw(Gfx **gfxP) {
    DebugMenu_Page_CharacterEdit_Draw(gfxP, 0x20, 0x20);
}
