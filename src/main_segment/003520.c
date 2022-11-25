#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"


INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D170);

INCLUDE_ASM("asm/nonmatchings/main_segment/003520", func_8002D3B0);

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
