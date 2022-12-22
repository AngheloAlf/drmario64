/**
 * Originally part of dm_virus_init.c
 */

#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", init_map_all);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", clear_map);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F00C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F074);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F09C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F0E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F13C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F1E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F204);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F25C);

INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", func_8005F2B0);

u32 func_8005F310(struct_virus_map_data *arg0, s32 arg1, s32 arg2) {
    struct_virus_map_data_unk_000 *ptr = arg0->unk_000;
    u8 index = ((arg2 - 1) * 8) + arg1;
    u32 value = (u32)ptr[index].unk_0;

    return (~value) >> 31;
}

#ifdef NON_MATCHING
bool dm_check_color(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3) {
    struct {
        u8 unk_0;
        u8 unk_1;
    } dumb;
    // u8 sp0;
    // s8 sp1;
    u8 temp_t0;
    u16 new_var;
    struct_virus_map_data_unk_000 *temp_v1 = arg0->unk_000;
    temp_t0 = arg1 + ((arg2 - 1) * 8);
    if ((arg1 & 0xFFFF) >= 2U) {
        if (temp_v1[temp_t0 - 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 - 2].unk_0 == temp_v1[temp_t0 - 1].unk_0) {
                return false;
            }
        }
    }

    if ((arg1 != 0) & (arg1 != 7)) {
        if (temp_v1[temp_t0 - 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 + 1].unk_0 == temp_v1[temp_t0 - 1].unk_0) {
                return false;
            }
        }
    }

    if (arg1 < 6U) {
        if (temp_v1[temp_t0 + 1].unk_0 == arg3) {
            if (temp_v1[temp_t0 + 2].unk_0 == temp_v1[temp_t0 + 1].unk_0) {
                return false;
            }
        }
    }

    new_var = arg1;
    dumb.unk_0 = (arg2 * 8) + arg1;
    dumb.unk_1 = ((arg2 + 1) * 8) + arg1;
    if ((arg2 & 0xFFFF) < 0xFU) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }

    dumb.unk_1 = arg1 + ((arg2 - 2) * 8);
    if (((arg2 - 4) & 0xFFFF) < 0xCU) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }

    dumb.unk_0 = ((arg2 - 2) * 8) + arg1;
    dumb.unk_1 = ((arg2 - 3) * 8) + new_var;
    if ((arg2 & 0xFFFF) >= 6U) {
        if (temp_v1[dumb.unk_0].unk_0 == arg3) {
            if (temp_v1[dumb.unk_1].unk_0 == temp_v1[dumb.unk_0].unk_0) {
                return false;
            }
        }
    }
    return true;
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/dm_virus_init/035300", dm_check_color);
#endif

bool dm_check_color_2(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3) {
    struct_virus_map_data_unk_000 *ptr = arg0->unk_000;
    u8 temp_t0;

    temp_t0 = (arg1 + ((arg2 - 1) * 8));
    if (arg1 >= 2U) {
        if (ptr[temp_t0 - 2].unk_0 == arg3) {
            return false;
        }
    }

    if (arg1 < 6U) {
        if (ptr[temp_t0 + 2].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = (arg1 + ((arg2 - 3) * 8));
    if ((arg2 & 0xFFFF) >= 6U) {
        if (ptr[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    temp_t0 = (arg1 + ((arg2 + 1) * 8));
    if ((arg2 & 0xFFFF) < 0xFU) {
        if (ptr[temp_t0].unk_0 == arg3) {
            return false;
        }
    }

    return true;
}

void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst,
                       struct_virus_map_disp_order *virusDispOrderSrc, struct_virus_map_disp_order *virusDispOrderDst) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(virusMapDst->unk_000); i++) {
        virusMapDst->unk_000[i].unk_0 = -1;
        virusMapDst->unk_000[i].unk_2 = 0;
        virusMapDst->unk_000[i].unk_1 = 0;
        virusMapDst->unk_000[i].unk_0 = virusMapSrc->unk_000[i].unk_0;
        virusMapDst->unk_000[i].unk_1 = virusMapSrc->unk_000[i].unk_1;
        virusMapDst->unk_000[i].unk_2 = virusMapSrc->unk_000[i].unk_2;
    }

    for (i = 0; i < ARRAY_COUNT(virusDispOrderDst->unk_00); i++) {
        virusDispOrderDst->unk_00[i] = virusDispOrderSrc->unk_00[i];
    }
}

s32 func_8005F698(u32 arg0, struct_80123700 *arg1) {
    s32 ret;

    switch (arg0) {
        case 1:
        case 3:
            ret = func_8005F6F0(arg1->unk_16C);
            break;

        default:
            if (arg1->unk_026 <= 0x17) {
                ret = arg1->unk_026;
            } else {
                ret = 0x17;
            }
            ret = (ret + 1) * 4;
            break;
    }

    return ret;
}

extern u8 D_800B1BC8[];

s32 func_8005F6F0(s32 arg0) {
    return D_800B1BC8[arg0];
}
