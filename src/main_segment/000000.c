#include "ultra64.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "audio/audio_stuff.h"
#include "other_symbols.h"


void func_80029C50(void) {
    func_80038BD8();

    switch (osTvType) {
        case OS_TV_NTSC:
            func_80029ED0(&B_800EB670, OS_VI_NTSC_LAN1, 1);
            B_800EBCF0 = 0;
            break;
        case OS_TV_MPAL:
            func_80029ED0(&B_800EB670, OS_VI_MPAL_LAN1, 1);
            B_800EBCF0 = 0;
            break;
        case OS_TV_PAL:
            func_80029ED0(&B_800EB670, OS_VI_PAL_LAN1, 1);
            B_800EBCF0 = 9;
            break;
        default:
            func_80029ED0(&B_800EB670, OS_VI_NTSC_LAN1, 1);
            B_800EBCF0 = 9;
            break;
    }

    func_8002AD38(&B_800EB670);
    func_8002B490(&D_80205000);
    func_8002B7A8(&B_800EB670);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_DITHER_OFF | OS_VI_GAMMA_OFF);
    func_8002A5B0(4);
    B_800F1CE0 = func_8002A954();
    if (!(B_800F1CE0 & 0xFF) && (B_800EBCF0 == 0)) {
        B_800EBCF0 = 8;
    }
    func_8002EDDC();
    func_80000488(func_8006D620);

    while (true) {
        u32 temp_s0 = B_800EBCF0;

        switch (B_800EBCF0) {
            case 0x0:
                B_800EBCF0 = func_8002DB20();
                break;
            case 0x1:
                B_800EBCF0 = func_8002E230();
                break;
            case 0x3:
                B_800EBCF0 = func_80075F98(&B_800EB670);
                break;
            case 0x4:
                B_800EBCF0 = func_80075A2C(&B_800EB670);
                break;
            case 0x5:
                B_800EBCF0 = func_8006F684(&B_800EB670);
                break;
            case 0x6:
                B_800EBCF0 = func_8005B2D4(&B_800EB670);
                break;
            case 0x7:
                B_800EBCF0 = func_80071A4C(&B_800EB670);
                break;
            case 0x8:
            case 0x9:
            case 0xA:
                B_800EBCF0 = func_8007657C(&B_800EB670);
                break;
            case 0x2:
                func_8007AA84(&B_800EB670);
                if (((D_800AACEC == 0) | (D_800AACEC == 0xC)) != 0) {
                    D_800AACEC += 1;
                    B_800EBCF0 = 2;
                } else if ((u32) (D_800AACEC - 0xA) >= 2U && (u32) (D_800AACEC - 0x16) >= 2U) {
                    B_800EBCF0 = 1;
                } else {
                    B_800EBCF0 = 7;
                }
                break;
        }
        B_800EB4F0 = temp_s0;
    }
}
