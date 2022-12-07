#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"
#include "buffers.h"
#include "audio/audio_stuff.h"

INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B22B0);

#if 0
void func_8006D870(void) {
    struct_800F3E50 *temp_a0;
    void *temp_v0;
    void *temp_v1;
    u32 i;

    heapTop = &Heap_bufferp;
    B_800F3E50 = ALIGN_PTR(&Heap_bufferp);
    bzero(B_800F3E50, sizeof(struct_800F3E50));

    heapTop = &B_800F3E50[1];
    i = 0;
    while (i < ARRAY_COUNT(B_800EF440)) {
        temp_v1 = ALIGN_PTR(heapTop);
        B_800EF440[i] = temp_v1;
        heapTop = temp_v1 + 0x2FB8;
        i += 1;

    }
    temp_v0 = temp_v1 + 0x2FC0;
    B_800F48C0 = temp_v0;
    heapTop = temp_v0 + 0x3000;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006D870);
#endif

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006D91C);

#if 0
? func_80038BE0(s8 *, struct_80124610 **, s32);     /* extern */
? func_8005E36C(s8 *, struct_80124610 **, s32);     /* extern */
? func_8005E48C(s8 *, ?);                           /* extern */
? func_8005EAFC(s8 *, s8 *);                        /* extern */
? func_8005EBA8(s8 *, struct_80124610 **);          /* extern */
? func_80062B84(s8 *);                              /* extern */
? func_8006A938(?);                                 /* extern */
? func_8007E2E0(struct_80124610 **);                /* extern */
? func_8007E2FC(u8);                                /* extern */
extern ? B_800EF560;
extern ? B_800EF608;
extern u32 evs_gamesel;
extern u8 B_800FAE78;
extern u8 B_8012372C;
extern ? B_8012374C;
extern ? B_8012374F;
extern ? B_80123790;
extern s8 B_80123794;
extern s32 B_8012386C;
extern u8 D_80088403;
extern s8 D_80088408;
extern s32 D_80088414;
extern s8 D_800A8AD0;

/**
 * Original name: dm_game_init_static
 */
void dm_game_init_static(void) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s1_10;
    s32 var_s1_11;
    s32 var_s1_12;
    s32 var_s1_13;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s1_8;
    s32 var_s1_9;
    s32 var_s2;
    s32 var_s2_3;
    s32 var_v1_2;
    s8 *temp_s0;
    s8 *var_a0;
    s8 *var_a0_3;
    s8 *var_s2_2;
    s8 *var_s4;
    s8 *var_v0;
    s8 *var_v0_2;
    s8 *var_v1;
    struct_800F3E50 *temp_s3;
    struct_800F3E50 *var_a0_2;
    u16 temp_v0;
    u32 var_s1_2;
    u8 temp_v1_3;
    void *temp_a1;
    void *temp_v0_2;

    temp_s3 = B_800F3E50;
    temp_s3->unk_3B0 = 0;
    temp_s3->unk_878 = 0x7F;
    temp_s3->unk_430 = tiLoadTexData(&heapTop, D_8000E9B0, D_8000E9B4);
    temp_s3->unk_444 = tiLoadTexData(&heapTop, D_8000E9D8, D_8000E9DC);
    if (main_no != 5) {
        temp_s3->unk_448 = tiLoadTexData(&heapTop, D_8000EA40, D_8000EA44);
    }
    temp_s3->unk_884 = (struct_80124610 *) heapTop;
    var_s1 = 1;
    var_v1 = &temp_s3->unk_000[4];
    heapTop = DecompressRomToRam(D_8000E9E0, heapTop, D_8000E9E4 - D_8000E9E0);
    do {
        var_v1->unk_8AC = 0;
        var_s1 -= 1;
        var_v1 -= 4;
    } while (var_s1 >= 0);
    temp_s3->unk_394 = 0;
    temp_s3->unk_398 = 1;
    temp_s3->unk_898 = 2;
    func_8006A938(0);
    temp_s3->unk_9AC = 0;
    temp_s3->unk_9B0 = 0;
    temp_s3->unk_9B4 = 0;
    temp_s3->unk_9B8 = 0;
    func_8007E2E0(&heapTop);
    var_s1_2 = 0;
    var_s0 = 0x9D0;
    func_8007E2FC(D_80088403);
    do {
        func_80062B84(&temp_s3->unk_000[var_s0]);
        var_s1_2 += 1;
        var_s0 += 0x2C;
    } while (var_s1_2 < 2U);
    msgWnd_init2((struct_80124610 *) &temp_s3->unk_000[0xA28], &heapTop, 0x100, 0xA, 5, 0, 0);
    temp_a2 = temp_s3->unk_A70 * 2;
    temp_s3->unk_A50 = (s32) ((s32) (0x140 - (temp_s3->unk_A64 * 0x14)) >> 1);
    temp_s3->unk_A54 = (s32) ((s32) (0xF0 - temp_a2) >> 1);
    func_80038BE0(&temp_s3->unk_000[0xAD8], &heapTop, temp_a2);
    switch (evs_gamesel) {                           /* switch 1 */
    case 0x0:                                       /* switch 1 */
        temp_a1 = (B_800FAE78 * 0xD0) + &B_800EF560;
        if (B_800FAE78 == 8) {
        case 0x4:                                   /* switch 1 */
            D_80088414 = 0xDD18;
        } else {
            switch (*B_801236F0) {                  /* switch 3; irregular */
            case 0x0:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012372C * 8))->unk_4C;
                break;
            case 0x2:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012386C * 8))->unk_64;
                break;
            case 0x3:                               /* switch 3 */
                D_80088414 = (temp_a1 + (B_8012386C * 0xC))->unk_7C;
                break;
            }
        }
block_23:
        switch (evs_gamesel) {                       /* switch 2 */
        case 0x0:                                   /* switch 2 */
        case 0x4:                                   /* switch 2 */
            temp_s3->unk_898 = 1;
            func_8005E36C(&B_80123794, &heapTop, 0xF);
            func_8005E48C(&B_80123794, 2);
            var_s1_3 = 0;
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2 = 0x44C;
            temp_s3->unk_434 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_198, gRomOffset_N64WaveTables_Start.unk_19C);
            do {
                func_8005E36C(&temp_s3->unk_000[var_s2], &heapTop, var_s1_3 + 0x10);
                var_s1_3 += 1;
                var_s2 += 0x40;
            } while (var_s1_3 < 3);
            func_8005EBA8(&temp_s3->unk_000[0x50C], &heapTop);
            var_s1_4 = 1;
            var_s0_2 = 0x630;
            do {
                func_8005EAFC(&temp_s3->unk_000[var_s0_2], &temp_s3->unk_000[0x50C]);
                var_s1_4 += 1;
                var_s0_2 += 0x124;
            } while (var_s1_4 < 3);
            temp_s0 = &temp_s3->unk_000[0x91C];
            msgWnd_init2((struct_80124610 *) temp_s0, &heapTop, 0x1000, 0x14, 0xF, 0x28, 0xF);
            temp_s3->unk_940 = 1;
            msgWnd_addStr((struct_80124610 *) temp_s0, &D_800A8AD0);
            msgWnd_skip((struct_80124610 *) temp_s0);
            temp_s3->unk_93C = 1;
            temp_s3->unk_938 = 0;
            heapTop = func_8007780C(heapTop);
            return;
        case 0x1:                                   /* switch 2 */
        case 0x3:                                   /* switch 2 */
        case 0x5:                                   /* switch 2 */
            var_s1_5 = 0;
            var_s2_2 = &B_80123794;
            var_s0_3 = 0;
            var_a0 = &B_80123794;
            do {
                temp_a2_2 = *(&B_80123790 + var_s0_3);
                var_s2_2 += 0x3C4;
                var_s0_3 += 0x3C4;
                var_s1_5 += 1;
                func_8005E36C(var_a0, &heapTop, temp_a2_2);
                var_a0 = var_s2_2;
            } while (var_s1_5 < 2);
            var_s1_6 = 1;
            if (D_80088408 == 0) {
                var_v0 = &temp_s3->unk_000[4];
                do {
                    var_v0->unk_8B4 = 0;
                    var_s1_6 -= 1;
                    var_v0 -= 4;
                } while (var_s1_6 >= 0);
                var_s1_7 = 0;
                if (evs_gamesel == 1) {
                    var_a0_2 = temp_s3;
                    do {
                        temp_v0 = *(&B_800EF608 + ((&B_800FAE78)[var_s1_7] * 0xD0));
                        var_s1_7 += 1;
                        var_a0_2->unk_8B4 = (s32) temp_v0;
                        var_a0_2 += 4;
                    } while (var_s1_7 < 2);
                }
            }
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            temp_s3->unk_43C = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_188, gRomOffset_N64WaveTables_Start.unk_18C);
            return;
        case 0x2:                                   /* switch 2 */
        case 0x6:                                   /* switch 2 */
            var_s4 = &B_80123794;
            var_s1_8 = 0;
            temp_s3->unk_438 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2_3 = 0;
            temp_s3->unk_440 = tiLoadTexData(&heapTop, gRomOffset_N64WaveTables_Start.unk_190, gRomOffset_N64WaveTables_Start.unk_194);
            var_a0_3 = &B_80123794;
            do {
                temp_a2_3 = *(&B_80123790 + var_s2_3);
                var_s4 += 0x3C4;
                var_s2_3 += 0x3C4;
                var_s1_8 += 1;
                func_8005E36C(var_a0_3, &heapTop, temp_a2_3);
                var_a0_3 = var_s4;
            } while (var_s1_8 < 4);
            var_s1_9 = 3;
            var_v0_2 = &temp_s3->unk_000[0xC];
            do {
                var_v0_2->unk_8CC = 0;
                var_s1_9 -= 1;
                var_v0_2 -= 4;
            } while (var_s1_9 >= 0);
            var_s1_10 = 0;
            var_a0_4 = 0;
            do {
                temp_v0_2 = (*(&B_8012374F + var_a0_4) * 4) + temp_s3;
                var_s1_10 += 1;
                temp_v0_2->unk_8CC = (s32) (temp_v0_2->unk_8CC + 1);
                var_a0_4 += 0x3C4;
            } while (var_s1_10 < 4);
            temp_s3->unk_8BC = 0;
            var_s1_11 = 0;
            var_v1_2 = 0;
            do {
                var_s1_11 += 1;
                if (*(&B_8012374C + var_v1_2) == 0) {
                    temp_s3->unk_8BC = (s32) (temp_s3->unk_8BC + 1);
                }
                var_v1_2 += 0x3C4;
            } while (var_s1_11 < 4);
            temp_v1 = temp_s3->unk_8CC;
            if (temp_v1 != 1) {
                var_s1_12 = 0;
                goto block_56;
            }
            temp_v0_3 = temp_s3->unk_8D0;
            var_s1_12 = 0;
            if (temp_v0_3 == temp_v1) {
                temp_v1_2 = temp_s3->unk_8D4;
                if (temp_v1_2 == temp_v0_3) {
                    if (temp_s3->unk_8D8 == temp_v1_2) {
                        temp_s3->unk_8C0 = 0;
                        return;
                    }
                    goto block_57;
                }
            }
block_56:
block_57:
            var_a0_5 = 0;
            temp_s3->unk_8C0 = 1;
            temp_s3->unk_8C8 = 0;
            temp_s3->unk_8C4 = 0;
            do {
                if (*(&B_8012374F + var_a0_5) == 0) {
                    temp_s3->unk_8C4 = (s32) (temp_s3->unk_8C4 | (1 << var_s1_12));
                }
                var_s1_12 += 1;
                var_a0_5 += 0x3C4;
            } while (var_s1_12 < 4);
            var_s1_13 = 0;
            var_a0_6 = 0;
            do {
                temp_v1_3 = *(&B_8012374F + var_a0_6);
                if (temp_v1_3 == 1) {
                    temp_s3->unk_8C8 = (s32) (temp_s3->unk_8C8 | (temp_v1_3 << var_s1_13));
                }
                var_s1_13 += 1;
                var_a0_6 += 0x3C4;
            } while (var_s1_13 < 4);
        default:                                    /* switch 1 */
        default:                                    /* switch 2 */
            return;
        }
        break;
    case 0x1:                                       /* switch 1 */
    case 0x2:                                       /* switch 1 */
    case 0x3:                                       /* switch 1 */
    case 0x5:                                       /* switch 1 */
    case 0x6:                                       /* switch 1 */
        if (D_80088408 == 0) {
            D_80088414 = 0;
        }
        goto block_23;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", dm_game_init_static);
#endif

INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", RO_800B2314);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", RO_800B2330);

INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B233C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B2340);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B2344);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B2348);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B2354);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B2358);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006E80C);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006E884);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006F628);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", dm_game_main);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006F950);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006FFD0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B23C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", RO_800B23CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B23D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8007023C);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80070360);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071624);

void func_80071A44(void) {
}

/**
 * Original name: main_techmes
 */
enum_main_no main_techmes(struct_800EB670 *arg0) {
    OSMesgQueue sp20;
    OSMesg sp38[8];
    struct_800FAF98_unk_64 sp58;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 var_a0;
    bool var_s3;
    struct_800F3E50 *temp_s2;
    u8 temp_s1;

    var_s3 = true;
    osCreateMesgQueue(&sp20, sp38, ARRAY_COUNT(sp38));
    func_8002A184(arg0, &sp58, &sp20);
    func_8006D870();
    temp_s2 = B_800F3E50;

    dm_game_init_static();
    heapTop = init_menu_bg(heapTop, false);
    msgWnd_init2(&temp_s2->unk_91C, &heapTop, 0x1000, 0x12, 0x10, 0x34, 0x22);
    msgWnd_addStr(&temp_s2->unk_91C, EndingLastMessage);
    temp_s1 = D_80088401;
    temp_s2->unk_91C.unk_20 = 1;
    temp_s2->unk_91C.unk_24 = 1;
    D_80088401 = 0;
    func_8006D91C(false);
    D_80088401 = temp_s1;
    func_8002B078(0x17);

    while (var_s3) {
        osRecvMesg(&sp20, NULL, 1);
        joyProcCore();

        switch (temp_s2->unk_9AC) {
            case 0x0:
                if (temp_s2->unk_9B0 == 0xFF) {
                    temp_s2->unk_9AC = 1;
                } else {
                    temp_v1_3 = temp_s2->unk_9B0 + 4;
                    var_a0 = 0xFF;
                    if (temp_v1_3 <= 0xFF) {
                        var_a0 = temp_v1_3;
                    }
                    temp_s2->unk_9B0 = var_a0;
                }
                break;

            case 0x1:
                if (func_8005E0B4(&temp_s2->unk_91C) != 0) {
                    temp_s2->unk_9AC++;
                } else {
                    func_8005D428(&temp_s2->unk_91C);
                }
                break;

            case 0x2:
                if (gControllerPressedButtons[B_800EBD16[0]] & ALL_BUTTONS) {
                    temp_s2->unk_9AC = 3;
                }
                break;

            case 0x3:
                if (temp_s2->unk_9B0 == 0) {
                    var_s3 = false;
                } else {
                    temp_v1_5 = temp_s2->unk_9B0 - 4;
                    temp_s2->unk_9B0 = (temp_v1_5 & (~temp_v1_5 >> 0x1F));
                }
                break;
        }

        dm_audio_update();
        graphic_no = 6;
    }

    graphic_no = 0;
    dm_audio_stop();

    while (!dm_audio_is_stopped() || (pendingGFX != 0)) {
        osRecvMesg(&sp20, NULL, 1);
        dm_audio_update();
    }

    func_8002A1DC(arg0, &sp58);
    return MAIN_NO_3;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071CE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071EF0);

void func_80071F0C(void) {
}

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071F14);
