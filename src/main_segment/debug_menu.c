/**
 * Debug menu
 *
 * Name is made up
 */

#include "debug_menu.h"
#include "screen_print/debug_print.h"
#include "util.h"
#include "macros_defines.h"
#include "main_segment_variables.h"

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
    D_800884C0,
    D_800884F0,
    aiSlideFSpeed,
};

const char *D_8008E490[] = {
    "VirusLv",
    "DownS",
    "SlideS",
    "SlideFS",
};

void DebugMenu_8003E730(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];

    if (arg3 != B_800E5914) {
        return;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            DebugPrint_8003E3F0(gfxP, arg1 + ((2 - B_800E58B0) * 6), arg2 + 8, '^');
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

        temp_a3 = &D_8008E480[arg3 / 21][(arg3 % 7) + 1][(arg3 / 7) - (arg3 / 21 * 3)];
        *temp_a3 = CLAMP(*temp_a3 + (var_t0 * D_8008E370[B_800E58B0]), 0, 30);
    }
}

const char *D_8008E4A0[] = {
    "Easy",
    "Normal",
    "Hard",
};

void DebugMenu_8003E8C8(Gfx **gxfP, s32 arg1, s32 arg2) {
    DebugPrint_8003E69C_arg1 temp = DebugMenu_8003E730;
    s32 i;
    s32 j;

    DebugPrint_8003E69C(gxfP, temp, arg1, arg2 + 8);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "");

    for (i = 0; i < ARRAY_COUNT(D_8008E490); i++) {
        DebugPrint_Printf("%s\n\n\n\n\n\n", D_8008E490[i]);
    }

    DebugPrint_8003E6D8();
    DebugPrint_8003E69C(gxfP, temp, arg1 + 0x2A, arg2 + 8);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "");

    for (i = 0; i < 4; i++) {
        for (j = 0; j < ARRAY_COUNT(D_8008E4A0); j++) {
            DebugPrint_Printf("%6s\n\n", D_8008E4A0[j]);
        }
    }

    DebugPrint_8003E6D8();
    DebugPrint_8003E69C(gxfP, temp, arg1 + 0x54, arg2);

    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "S_er Slow Fast F_er Fest N_Wt F_NW");

    DebugPrint_8003E6D8();
    DebugPrint_8003E69C(gxfP, temp, arg1 + 0x5A, arg2 + 8);

    for (i = 0; i < ARRAY_COUNT(D_8008E480); i++) {
        for (j = 0; j < ARRAY_COUNT(*D_8008E480[i]); j++) {
            s32 k;

            for (k = 1; k < 8; k++) {
                DebugPrint_Printf(DBGPRT_CALLBACK "%c%03d  ", 0x15 * i + 7 * j + k - 1, D_8008E480[i][k][j]);
            }

            DebugPrint_Printf("\n\n");
        }
    }

    DebugPrint_8003E6D8();
    DebugPrint_8003E69C(gxfP, temp, arg1, arg2 + 0xC8);
    DebugPrint_Printf(DBGPRT_COLOR(CYAN) "<- CharacterMenu\t\t\t\t\tLogicMenu ->");
    DebugPrint_8003E6D8();
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

void DebugMenu_8003EEA4(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s32 var_t0;
    s32 var_t2;
    s32 var_t1;

    if (arg3 != B_800E5918) {
        return;
    }

    var_t2 = 0;
    var_t1 = 2;
    if (arg3 == 0) {
        var_t0 = 5;
    } else if (arg3 == 1) {
        var_t0 = 7;
    } else if (arg3 == 0x15) {
        var_t0 = 1;
    } else if (arg3 < 0x1D) {
        var_t2 = -0x270F;
        var_t0 = 0x270F;
        var_t1 = 5;
    } else if (arg3 == 0x1D) {
        var_t0 = 0x14;
        var_t1 = 3;
    } else if (arg3 == 0x1E) {
        var_t0 = 0x10;
        var_t1 = 3;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            DebugPrint_8003E3F0(gfxP, arg1 + (((var_t1 - B_800E58B4) - 1) * 6), arg2 + 8, '^');
        }
    } else {
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1 -= 1;
        }

        B_800E58B4 = CLAMP(B_800E58B4 + var_a1, 0, var_t1 - 1);

        var_a1 = 0;
        if (buttonCurrent & U_JPAD) {
            var_a1++;
        }
        if (buttonCurrent & D_JPAD) {
            var_a1 -= 1;
        }

        B_800E58C0[arg3] = CLAMP(B_800E58C0[arg3] + D_8008E370[B_800E58B4] * var_a1, var_t2, var_t0);
    }
}

void DebugMenu_8003F050(Gfx **gxfP, s32 arg1, s32 arg2) {
    s16 *temp = B_800E58C0;
    s32 index = 0;
    s32 i;

    DebugPrint_8003E69C(gxfP, DebugMenu_8003EEA4, arg1, arg2);

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
    DebugPrint_8003E6D8();
}

void DebugMenu_8003F360(void) {
    struct_ai_char_data *temp_a1 = &ai_char_data[B_800E5928];
    s16 *var_a3 = B_800E58C0;
    s32 i;

    *var_a3++ = B_800E5928;
    *var_a3++ = temp_a1->unk_00;
    *var_a3++ = temp_a1->unk_01;
    *var_a3++ = temp_a1->unk_02;

    for (i = 0; i < ARRAY_COUNT(temp_a1->unk_04); i++) {
        *var_a3++ = temp_a1->unk_04[i];
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
    temp_t3->unk_01 = *var_t1++;
    temp_t3->unk_02 = *var_t1++;

    for (i = 0; i < ARRAY_COUNT(temp_t3->unk_04); i++) {
        temp_t3->unk_04[i] = *var_t1++;
    }

    for (i = B_800E592C; i < B_800E592C + 4; i++) {
        temp_t3->unk_0C[i] = *var_t1++;
        temp_t3->unk_1C[i] = *var_t1++;
        temp_t3->unk_3C[i] = *var_t1++;
        temp_t3->unk_4C[i] = *var_t1++;
    }
}

void DebugMenu_8003F568(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s32 var_t1;
    s32 var_t4;
    s32 var_t0;
    s32 var_t5;
    s32 var_t6;

    if (arg3 != B_800E5924) {
        return;
    }

    var_t5 = 0;
    var_t6 = 0;
    var_t4 = 0;
    var_t0 = 2;

    if (arg3 == 0) {
        var_t1 = 0xF;
    } else if (arg3 == 1) {
        var_t1 = 1;
    } else if (arg3 == 2) {
        var_t4 = 1;
        var_t1 = 7;
    } else if (arg3 == 3) {
        var_t4 = -0x64;
        var_t1 = 0x64;
        var_t0 = 3;
    } else if (arg3 < 0xC) {
        var_t1 = 5;
    } else if (arg3 < 0x1B) {
        switch ((arg3 - 0xC) & 3) {
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
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            DebugPrint_8003E3F0(gfxP, arg1 + (((var_t0 - B_800E58B8) - 1) * 6), arg2 + 8, '^');
        }
    } else {
        s32 var_a2 = 1;
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1 -= 1;
        }

        B_800E58B8 = CLAMP(B_800E58B8 + var_a1, 0, var_t0 - 1);

        if (var_t5 != 0) {
            switch (B_800E58C0[arg3 - 1]) {
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
            switch (B_800E58C0[arg3 - 1]) {
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

            B_800E58C0[arg3] = CLAMP(B_800E58C0[arg3] + D_8008E370[B_800E58B8] * var_a1, var_t4, var_t1);
        }
    }
}

void DebugMenu_8003F7DC(Gfx **gxfP, s32 arg1, s32 arg2) {
    s16 *new_var = B_800E58C0;
    s32 var_s0 = 0;
    s32 i;

    DebugPrint_8003E69C(gxfP, DebugMenu_8003F568, arg1, arg2);

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
    DebugPrint_8003E6D8();
}

void DebugMenu_8003FB00(void) {
    s32 temp_s0 = joycur[0];
    s32 temp;

    temp = 0;
    if (gControllerPressedButtons[0] & L_CBUTTONS) {
        temp--;
    }
    if (gControllerPressedButtons[0] & R_CBUTTONS) {
        temp++;
    }

    B_800E5930 = WrapI(0, ENUM_800E5930_MAX, B_800E5930 + temp);

    temp = 0;
    if (temp_s0 & L_TRIG) {
        temp--;
    }
    if (temp_s0 & R_TRIG) {
        temp++;
    }

    switch (B_800E5930) {
        case ENUM_800E5930_0:
            B_800E5918 = WrapI(0, 0x1F, B_800E5918 + temp);
            DebugMenu_8003EB20();
            DebugMenu_8003F050(NULL, 0x10, 0x10);
            DebugMenu_8003ECDC();
            break;

        case ENUM_800E5930_1:
            B_800E5924 = WrapI(0, 0x1C, B_800E5924 + temp);
            if (temp > 0) {
                if (B_800E5924 == 0) {
                    B_800E592C = WrapI(0, 0x10, B_800E592C + 4);
                    if (B_800E592C != 0) {
                        B_800E5924 = 0xC;
                    }
                } else if (B_800E5924 == 0xC) {
                    B_800E592C = 0;
                }
            } else if (temp < 0) {
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
            DebugMenu_8003F7DC(NULL, 0x10, 0x10);
            DebugMenu_8003F474();
            break;

        case ENUM_800E5930_2:
            B_800E5914 = WrapI(0, 0x54, B_800E5914 + temp);
            DebugMenu_8003E8C8(NULL, 0x10, 0x10);
            break;
    }
}

void DebugMenu_8003FD0C(Gfx **gxfP) {
    switch (B_800E5930) {
        case ENUM_800E5930_0:
            DebugMenu_8003F050(gxfP, 0x10, 0x10);
            break;

        case ENUM_800E5930_1:
            DebugMenu_8003F7DC(gxfP, 0x10, 0x10);
            break;

        case ENUM_800E5930_2:
            DebugMenu_8003E8C8(gxfP, 0x10, 0x10);
            break;
    }
}

void DebugMenu_8003FD88(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 button = gControllerPressedButtons[0];
    struct_800E5938 *temp_a2 = &B_800E5938[B_800E5934];
    s32 temp_a0 = arg3 >> 5;
    s32 temp_a3 = arg3 & 0x1F;

    if (temp_a0 != B_800E596C) {
        return;
    }

    if (temp_a3 != B_800E5970[temp_a0]) {
        return;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            DebugPrint_SetColor(gfxP, DBGPRT_COLOR_WHITE);
            DebugPrint_8003E3F0(gfxP, arg1 - 6, arg2, '>');
        }
    } else if (button & A_BUTTON) {
        switch (temp_a0) {
            case 0x0:
                B_800E5934 = B_800E5970[0];
                return;

            case 0x1:
                temp_a2->unk_0 = B_800E5970[1];
                break;

            case 0x2:
                temp_a2->unk_1 = B_800E5970[2];
                break;

            case 0x3:
                temp_a2->unk_2 ^= 1 << B_800E5970[3];
                break;
        }
    }
}

const char *D_8008E4AC[] = {
    "ﾏﾘｵ",        // "Mario"
    "ﾉｺﾉｺ",       // "Koopa Troopa"
    "ﾎﾞﾑﾍｲ",      // "Bob-omb"
    "ﾌﾟｸﾌﾟｸ",     // "Cheep cheep"
    "ﾁｮﾛﾌﾟｰ",     // "Monty Mole"
    "ﾌﾟﾛﾍﾟﾗﾍｲﾎｰ", // "Fly Guy"
    "ﾊﾅﾁｬﾝ",      // "Wiggler"
    "ﾃﾚｻ",        // "Teresa", Boo?
    "ﾊﾟｯｸﾝﾌﾗﾜｰ",  // "Piranha Plant"
    "ｶﾒｯｸ",       // "Kamek"
    "ｸｯﾊﾟ",       // "Bowser"
    "ﾌﾟﾘﾝｾｽﾋﾟｰﾁ", // "Princess Peach"
};

const char *D_8008E4DC[] = {
    "ｽﾋﾟｰﾄﾞ",    // "Speed"
    "ﾊﾞﾗﾝｽ",     // "Balance"
    "ｺｳｹﾞｷ",     // "Attack"
    "ﾀﾞｲﾚﾝｻﾈﾗｲ", // "Big chain"
    "ﾖｺｽﾞｷ",     //
};

const char *D_8008E4F0[] = {
    "ﾋｼﾞｮｳﾆｵｿｲ", // "Very slow"
    "ｵｿｲ",       // "Slow"
    "ﾌﾂｳ",       // "Normal"
    "ﾊﾔｲ",       // "Quick"
    "ﾋｼﾞｮｳﾆﾊﾔｲ", // "Very quick"
    "ﾓｯﾄﾓﾊﾔｲ",   // "More quick"
};

const char *D_8008E508[] = {
    "ｾﾝｾｲｺｳｹﾞｷ",  // "Preemptive attack"
    "ｶｳﾝﾀｰ",      // "Counter"
    "ﾗｯｸ",        // "Luck"
    "ﾏﾖｲ",        // "Bewilderment"
    "ｸﾙｸﾙﾏﾜｽ",    // "Rotate"
    "ﾁｮｳﾊﾂ",      // "Provoke"
    "ﾄﾞｳﾖｳ",      //
    "ｽﾋﾟｰﾄﾞｱｯﾌﾟ", // "Speed up"
    "ｵｲｱｹﾞﾙ",     //
    "ﾃﾇｷ",        // "Shoddy"
    "ｵｲｺﾐ",       //
    "ﾃﾞﾌｫﾙﾄ",     // "Default"
};

s8 D_8008E538[] = {
    0x00, 0x02, 0x03, 0x05, 0x04, 0x00, 0x00, 0x00,
};

#if VERSION_CN
#define D_8008E540_ARR D_80099290_cn
#else
#define D_8008E540_ARR D_8008E540
#endif

s8 D_8008E540_ARR[] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x00, 0x00,
};

const char **D_8008E548[] = {
    D_8008E4AC,
    D_8008E4DC,
    D_8008E4F0,
    D_8008E508,
};

s32 D_8008E558[] = {
    0x0000000C,
    0x00000005,
    0x00000006,
    0x0000000C,
};

s8 D_8008E568[] = {
    0x00, 0xF2, 0x00, 0x00, 0x02, 0xFE, 0x00, 0x02, 0xFE, 0x04, 0x02, 0x00,
};

s8 D_8008E574[] = {
    0x21, 0x28, 0x19, 0x0A, 0x22, 0x00, 0x00, 0x00,
};

s8 D_8008E57C[] = {
    0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x00, 0x00,
};

s8 D_8008E584[] = {
    0x06, 0x04, 0x0A, 0xFE, 0xFE, 0xFE, 0xF6, 0x04, 0x02, 0xFA, 0x04, 0x00,
};

s32 DebugMenu_8003FEE4(void) {
    s32 var_t1 = 0;
    struct_800E5938 sp8 = B_800E5938[B_800E5934];
    s32 i;

    for (i = 0; i < D_8008E558[3]; i++) {
        s32 var_a1;

        switch (sp8.unk_2 & (1 << i)) {
            case 0x1:
                var_a1 = (sp8.unk_0 == 2) && (sp8.unk_1 >= 4);
                break;

            case 0x2:
                var_a1 = sp8.unk_0 == 2;
                break;

            case 0x4:
                break;

            case 0x8:
                break;

            case 0x10:
                break;

            case 0x20:
                break;

            case 0x40:
                break;

            case 0x80:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x100:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x200:
                var_a1 = sp8.unk_1 < 2;
                break;

            case 0x400:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x800:
                switch (B_800E5934) {
                    case 0x0:
                        break;

                    case 0x1:
                        var_a1 = sp8.unk_2 & 0x58;
                        break;

                    case 0x4:
                        var_a1 = sp8.unk_1 == 5;
                        break;

                    case 0x5:
                        var_a1 = sp8.unk_2 & 0x10;
                        break;

                    case 0x7:
                        var_a1 = sp8.unk_2 & 0x80;
                        break;

                    case 0x8:
                        var_a1 = sp8.unk_2 & 8;
                        break;

                    case 0x9:
                        var_a1 = (sp8.unk_1 >= 4);
                        break;

                    case 0xA:
                        var_a1 = 0;
                        if ((sp8.unk_1 >= 4) || (sp8.unk_2 & 0x402)) {
                            var_a1 = 1;
                        }
                        break;

                    case 0xB:
                        break;
                }
                break;
        }

        //! @bug: reading variable maybe not set
        if (var_a1 != 0) {
            sp8.unk_2 &= ~(1 << i);
        }
    }

    if (sp8.unk_2 & 0x800) {
        var_t1 += D_8008E568[B_800E5934];
    }

    if (sp8.unk_0 >= 0) {
        var_t1 += D_8008E574[sp8.unk_0];
    }

    if (sp8.unk_1 >= 0) {
        var_t1 += D_8008E57C[sp8.unk_1];
    }

    for (i = 0; i < 0xCU; i++) {
        if ((sp8.unk_2 >> i) & 1) {
            var_t1 += D_8008E584[i];
        }
    }

    return var_t1;
}

s8 D_8008E590[] = {
    0x00, 0x00, 0x01, 0x02, 0x04, 0x03, 0x00, 0x00,
};

s8 D_8008E598[] = {
    0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x05,
};

void DebugMenu_8004015C(void) {
    struct_800E5968 *temp = &B_800E5968;
    s32 i;

    for (i = 0; i < D_8008E558[0]; i++) {
        struct_ai_char_data *temp2 = &ai_char_data_org[i];
        struct_ai_char_data *var_a1 = &ai_char_data[i];
        struct_800E5938 *var_v1 = &B_800E5938[i];

        var_v1->unk_0 = D_8008E590[var_a1->unk_04[7]];
        var_v1->unk_1 = D_8008E598[var_a1->unk_01];

        if (!B_800E58BC) {
            var_v1->unk_2 = 0x800;
        }

        if (i == B_800E5934) {
            temp->unk_0 = D_8008E590[temp2->unk_04[7]];
            temp->unk_1 = D_8008E598[temp2->unk_01];
        }
    }

    B_800E58BC = true;
}

void DebugMenu_80040238(void) {
    s32 i;

    for (i = 0; i < D_8008E558[0]; i++) {
        struct_ai_char_data *temp_a2 = &ai_char_data_org[i];
        struct_ai_char_data *temp_t8 = &ai_char_data[i];
        struct_800E5938 *temp_t9 = &B_800E5938[i];
        s32 j;
        s32 index;

        for (j = 0; j < 8; j++) {
            temp_t8->unk_04[j] = D_8008E538[temp_t9->unk_0];
        }

        //! FAKE: renaming D_80099290_cn to D_8008E540 produces different codegen
        temp_t8->unk_01 = D_8008E540_ARR[temp_t9->unk_1];

        index = 0;

        if (temp_t9->unk_2 & 0x800) {
            for (j = 0; j < 4; j++) {
                temp_t8->unk_0C[index] = temp_a2->unk_0C[j];
                temp_t8->unk_1C[index] = temp_a2->unk_1C[j];
                temp_t8->unk_3C[index] = temp_a2->unk_3C[j];
                temp_t8->unk_4C[index] = temp_a2->unk_4C[j];
                index++;
            }
        }

        for (j = 0; j < D_8008E558[3]; j++) {
            switch (temp_t9->unk_2 & (1 << j)) {
                case 0x1:
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

                case 0x2:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 8;
                    temp_t8->unk_4C[index] = 7;
                    index++;
                    break;

                case 0x4:
                    temp_t8->unk_02 = 0x32;
                    break;

                case 0x8:
                    temp_t8->unk_0C[index] = 2;
                    temp_t8->unk_1C[index] = 0x21;
                    temp_t8->unk_3C[index] = 2;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x10:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x20:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x40:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 3;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x80:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 7;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x100:
                    temp_t8->unk_0C[index] = 4;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 6;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x200:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 5;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x400:
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

void DebugMenu_80040578(void) {
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

    B_800E596C = WrapI(0, 4, B_800E596C + horizontal);
    B_800E5970[B_800E596C] = WrapI(0, D_8008E558[B_800E596C], B_800E5970[B_800E596C] + vertical);
}

const char *D_8008E5A0[] = {
    "<ｷｬﾗｸﾀｰ>", // "<Character>"
    "<ｾｲｶｸ>",   // "<Performance>"
    "<ｽﾋﾟｰﾄﾞ>", // "<Speed>"
    "<ﾄｸｼｭ>",   // "<Special>"
};

s32 D_8008E5B0 = 0x00000035;

s32 D_8008E5B4[] = {
    0x0000000B,
    0x0000000A,
    0x0000000A,
    0x0000000E,
};

void DebugMenu_80040624(Gfx **gfxP, s32 arg1, s32 arg2) {
    struct_800E5938 *temp_s5 = &B_800E5938[B_800E5934];
    s32 var_s0 = CLAMP(DebugMenu_8003FEE4() / 10, 0, 10);
    s32 var_a2;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s7;

    DebugPrint_8003E69C(gfxP, DebugMenu_8003FD88, arg1, arg2);

    // "Character edit"
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "[ｷｬﾗｸﾀｰｴﾃﾞｨｯﾄ]\n\n");
    // "Strength"?
    DebugPrint_Printf(DBGPRT_COLOR(GREEN) "ﾂﾖｻ ");

    for (var_s1 = 0; var_s1 < var_s0; var_s1++) {
        DebugPrint_Printf("%c", 0x83);
    }

    for (; var_s1 < 10; var_s1++) {
        DebugPrint_Printf("%c", 0x82);
    }

    DebugPrint_8003E6D8();

    arg1 += 6;
    arg2 += 0x20;

    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        DebugPrint_8003E69C(gfxP, DebugMenu_8003FD88, arg1, arg2);

        DebugPrint_Printf(DBGPRT_COLOR(GREEN) "%s\n", D_8008E5A0[var_s1]);

        var_s2 = var_s1 << 5;

        for (var_s0_2 = 0; var_s0_2 < D_8008E558[var_s1]; var_s0_2++) {
            var_a2 = 0x37;

            switch (var_s1) {
                case 0:
                    if (var_s0_2 == B_800E5934) {
                        var_a2 = 0x33;
                    }
                    break;

                case 1:
                    if (var_s0_2 == temp_s5->unk_0) {
                        var_a2 = 0x33;
                    } else if (var_s0_2 == B_800E5968.unk_0) {
                        var_a2 = D_8008E5B0;
                    }
                    break;

                case 2:
                    if (var_s0_2 == temp_s5->unk_1) {
                        var_a2 = 0x33;
                    } else if (var_s0_2 == B_800E5968.unk_1) {
                        var_a2 = D_8008E5B0;
                    }
                    break;

                case 3:
                    var_s7 = 0x80;
                    if ((temp_s5->unk_2 >> var_s0_2) % 2 != 0) {
                        var_a2 = 0x33;
                        var_s7 = 0x81;
                    } else if (var_s0_2 == 0xB) {
                        var_a2 = D_8008E5B0;
                    }
                    break;
            }

            switch (var_s1) {
                case 0:
                case 1:
                case 2:
                    DebugPrint_Printf(DBGPRT_CALLBACK "%c" DBGPRT_COLOR_RAW "%c%s\n", var_s2, var_a2,
                                      D_8008E548[var_s1][var_s0_2]);
                    var_s2 += 1;
                    break;

                case 3:
                    DebugPrint_Printf(DBGPRT_CALLBACK "%c" DBGPRT_COLOR_RAW "%c%c:%s\n", var_s2, var_a2, var_s7,
                                      D_8008E548[var_s1][var_s0_2]);
                    var_s2 += 1;
                    break;
            }
        }

        DebugPrint_8003E6D8();
        arg1 += D_8008E5B4[var_s1] * 6;
    }
}

void DebugMenu_800409A0(void) {
    DebugMenu_80040578();
    DebugMenu_8004015C();
    DebugMenu_80040624(NULL, 0x20, 0x20);
    DebugMenu_80040238();
}

void DebugMenu_800409DC(Gfx **gfxP) {
    DebugMenu_80040624(gfxP, 0x20, 0x20);
}
