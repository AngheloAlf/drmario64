#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "PR/libmus.h"

extern musSched D_800883F0;

#ifdef NON_EQUIVALENT
s32 func_8002D170(struct_800EB670 *arg0, struct_800FAF98 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg7, s32 arg8) {
    musConfig sp10;
    s32 temp_s1;
    struct_800FAF98 *temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 i;
    s32 var_s1;

    temp_v0 = ALIGN16((uintptr_t)arg1);
    B_800FAF98 = temp_v0;
    temp_v0->unk_0C = ALIGN16((uintptr_t)&temp_v0->unk_BC);
    temp_v0->unk_04 = arg1;
    temp_v0->unk_08 = arg2;
    temp_v0->unk_00 = arg0;
    temp_v0->unk_10 = arg3;
    temp_v0->unk_14 = ALIGN16((uintptr_t)temp_v0->unk_0C + arg3);
    temp_v0->unk_18 = arg5;
    var_s1 = &temp_v0->unk_14[arg5];

    for (i = 0; i < temp_v0->unk_18; i++) {
        temp_v0->unk_14[i].unk_0 = ALIGN16((uintptr_t)var_s1);
        temp_v0->unk_14[i].unk_4 = arg4;
        temp_v0->unk_14[i].unk_8 = 0;
        temp_v1 = temp_v0->unk_14[i].unk_0;
        var_s1 = temp_v1 + arg4;
    }

    temp_v0->unk_1C = (s32) ALIGN16((uintptr_t)var_s1);
    temp_v0->unk_24 = (s32) ALIGN16((uintptr_t)temp_v0->unk_1C + arg3);
    temp_v0->unk_20 = arg3;
    temp_v0->unk_28 = arg8;

    temp_s1 = &temp_v0->unk_24[arg8];
    for (i = 0; i < temp_v0->unk_28; i++) {
        temp_v0->unk_24[i] = 0;
    }

    osCreateMesgQueue(&temp_v0->unk_2C, temp_v0->unk_44, ARRAY_COUNT(temp_v0->unk_44));
    temp_s1 = ALIGN16((uintptr_t)temp_s1);
    sp10.channels = 0x18;
    sp10.fifo_length = 0x40;
    sp10.syn_output_rate = 0x7D00;
    sp10.syn_updates = 0x100;
    sp10.syn_retraceCount = 1;
    sp10.syn_num_dma_bufs = 0x24;
    sp10.syn_updates = 0x80;
    sp10.syn_rsp_cmds = 0x1000;
    sp10.syn_rsp_cmds = 0x800;
    sp10.syn_num_dma_bufs = 0x20;
    sp10.control_flag = 0;
    sp10.sched = arg0;
    sp10.thread_priority = arg8;
    sp10.heap = temp_s1;
    sp10.ptr = 0;
    sp10.wbk = 0;
    sp10.default_fxbank = 0;
    sp10.syn_dma_buf_size = 0x1000;
    sp10.syn_dma_buf_size = 0x280;
    sp10.heap_length = arg2 - (temp_s1 - temp_v0->unk_04);
    MusSetScheduler(&D_800883F0);
    return MusInitialize(&sp10) + (temp_s1 - temp_v0->unk_04);
}
#else
INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D170);
#endif

bool func_8002D3B0(romoffset_t segmentRom, size_t segmentSize, void *wbank) {
    struct_800FAF98 *temp_s0 = B_800FAF98;

    if (MusAsk(MUSFLAG_SONGS) == 0) {
        func_8002D8D0(segmentRom, temp_s0->unk_0C, segmentSize);
        MusPtrBankInitialize(temp_s0->unk_0C, wbank);
        return true;
    }
    return false;
}

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D428);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D4A4);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D4F8);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D51C);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D554);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D58C);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D5C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D5FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D634);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D66C);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D6A4);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D710);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D720);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D768);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D7C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D7E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D810);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D840);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D870);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D8A0);

void func_8002D8D0(romoffset_t segmentRom, void *segmentVram, size_t segmentSize) {
    struct_800FAF98 *temp = B_800FAF98;
    s32 remainingSize = segmentSize;
    romoffset_t currentRom = segmentRom;
    uintptr_t currentVram = (uintptr_t)segmentVram;

    while (remainingSize != 0) {
        OSIoMesg mb;
        OSMesg msg;
        size_t blkSize = remainingSize;

        if (remainingSize > 0x4000) {
            blkSize = 0x4000;
        }

        osInvalDCache((void *)currentVram, blkSize);
        osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, &temp->unk_2C);
        osRecvMesg(&temp->unk_2C, &msg, OS_MESG_BLOCK);
        currentRom += blkSize;
        remainingSize -= blkSize;
        currentVram += blkSize;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D984);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D9E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002DA48);
