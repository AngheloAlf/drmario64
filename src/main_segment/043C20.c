#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "rom_offsets.h"
#include "other_symbols.h"


INCLUDE_RODATA("asm/nonmatchings/main_segment/043C20", D_800B22B0);

#if 0
void func_8006D870(void) {
    struct_800F3E50 *temp_a0;
    void *temp_v0;
    void *temp_v1;
    u32 i;

    B_800E5980 = &D_80124610;
    B_800F3E50 = ALIGN_PTR(&D_80124610);
    bzero(B_800F3E50, sizeof(struct_800F3E50));

    B_800E5980 = &B_800F3E50[1];
    i = 0;
    while (i < ARRAY_COUNT(B_800EF440)) {
        temp_v1 = ALIGN_PTR(B_800E5980);
        B_800EF440[i] = temp_v1;
        B_800E5980 = temp_v1 + 0x2FB8;
        i += 1;

    }
    temp_v0 = temp_v1 + 0x2FC0;
    B_800F48C0 = temp_v0;
    B_800E5980 = temp_v0 + 0x3000;
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
extern u32 B_800EFCD0;
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

void func_8006E0EC(void) {
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
    temp_s3->unk_430 = func_80045098(&B_800E5980, D_8000E9B0, D_8000E9B4);
    temp_s3->unk_444 = func_80045098(&B_800E5980, D_8000E9D8, D_8000E9DC);
    if (B_800EBCF0 != 5) {
        temp_s3->unk_448 = func_80045098(&B_800E5980, D_8000EA40, D_8000EA44);
    }
    temp_s3->unk_884 = (struct_80124610 *) B_800E5980;
    var_s1 = 1;
    var_v1 = &temp_s3->unk_000[4];
    B_800E5980 = DecompressRomToRam(D_8000E9E0, B_800E5980, D_8000E9E4 - D_8000E9E0);
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
    func_8007E2E0(&B_800E5980);
    var_s1_2 = 0;
    var_s0 = 0x9D0;
    func_8007E2FC(D_80088403);
    do {
        func_80062B84(&temp_s3->unk_000[var_s0]);
        var_s1_2 += 1;
        var_s0 += 0x2C;
    } while (var_s1_2 < 2U);
    func_8005CFD4((struct_80124610 *) &temp_s3->unk_000[0xA28], &B_800E5980, 0x100, 0xA, 5, 0, 0);
    temp_a2 = temp_s3->unk_A70 * 2;
    temp_s3->unk_A50 = (s32) ((s32) (0x140 - (temp_s3->unk_A64 * 0x14)) >> 1);
    temp_s3->unk_A54 = (s32) ((s32) (0xF0 - temp_a2) >> 1);
    func_80038BE0(&temp_s3->unk_000[0xAD8], &B_800E5980, temp_a2);
    switch (B_800EFCD0) {                           /* switch 1 */
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
        switch (B_800EFCD0) {                       /* switch 2 */
        case 0x0:                                   /* switch 2 */
        case 0x4:                                   /* switch 2 */
            temp_s3->unk_898 = 1;
            func_8005E36C(&B_80123794, &B_800E5980, 0xF);
            func_8005E48C(&B_80123794, 2);
            var_s1_3 = 0;
            temp_s3->unk_438 = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2 = 0x44C;
            temp_s3->unk_434 = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_198, gRomOffset_N64WaveTables_Start.unk_19C);
            do {
                func_8005E36C(&temp_s3->unk_000[var_s2], &B_800E5980, var_s1_3 + 0x10);
                var_s1_3 += 1;
                var_s2 += 0x40;
            } while (var_s1_3 < 3);
            func_8005EBA8(&temp_s3->unk_000[0x50C], &B_800E5980);
            var_s1_4 = 1;
            var_s0_2 = 0x630;
            do {
                func_8005EAFC(&temp_s3->unk_000[var_s0_2], &temp_s3->unk_000[0x50C]);
                var_s1_4 += 1;
                var_s0_2 += 0x124;
            } while (var_s1_4 < 3);
            temp_s0 = &temp_s3->unk_000[0x91C];
            func_8005CFD4((struct_80124610 *) temp_s0, &B_800E5980, 0x1000, 0x14, 0xF, 0x28, 0xF);
            temp_s3->unk_940 = 1;
            func_8005D314((struct_80124610 *) temp_s0, &D_800A8AD0);
            func_8005E0BC((struct_80124610 *) temp_s0);
            temp_s3->unk_93C = 1;
            temp_s3->unk_938 = 0;
            B_800E5980 = func_8007780C(B_800E5980);
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
                func_8005E36C(var_a0, &B_800E5980, temp_a2_2);
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
                if (B_800EFCD0 == 1) {
                    var_a0_2 = temp_s3;
                    do {
                        temp_v0 = *(&B_800EF608 + ((&B_800FAE78)[var_s1_7] * 0xD0));
                        var_s1_7 += 1;
                        var_a0_2->unk_8B4 = (s32) temp_v0;
                        var_a0_2 += 4;
                    } while (var_s1_7 < 2);
                }
            }
            temp_s3->unk_438 = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            temp_s3->unk_43C = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_188, gRomOffset_N64WaveTables_Start.unk_18C);
            return;
        case 0x2:                                   /* switch 2 */
        case 0x6:                                   /* switch 2 */
            var_s4 = &B_80123794;
            var_s1_8 = 0;
            temp_s3->unk_438 = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_180, gRomOffset_N64WaveTables_Start.unk_184);
            var_s2_3 = 0;
            temp_s3->unk_440 = func_80045098(&B_800E5980, gRomOffset_N64WaveTables_Start.unk_190, gRomOffset_N64WaveTables_Start.unk_194);
            var_a0_3 = &B_80123794;
            do {
                temp_a2_3 = *(&B_80123790 + var_s2_3);
                var_s4 += 0x3C4;
                var_s2_3 += 0x3C4;
                var_s1_8 += 1;
                func_8005E36C(var_a0_3, &B_800E5980, temp_a2_3);
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
INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006E0EC);
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

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_8006F684);

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

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071A4C);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071CE0);

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071EF0);

void func_80071F0C(void) {
}

INCLUDE_ASM("asm/nonmatchings/main_segment/043C20", func_80071F14);