#include "audio/audio_stuff.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "PR/sched.h"
#include "000280.h"

#if VERSION_US || VERSION_CN
musSched D_800883F0 = {
    func_8002D984,
    func_8002D9E4,
    func_8002DA48,
};
#endif

#if VERSION_US || VERSION_CN
size_t func_8002D170(struct_800EB670 *sched, void *heap, size_t heap_length, size_t arg3, s32 arg4, s32 arg5, size_t arg6 UNUSED, s32 arg7, OSPri thread_priority) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98 = ALIGN_PTR(heap);
    musConfig sp10;
    s32 i;

    temp_s0->unk_04 = heap;
    temp_s0->unk_08 = heap_length;
    heap = temp_s0 + 1;

    temp_s0->sched = sched;

    temp_s0->unk_0C = ALIGN_PTR(heap);
    temp_s0->unk_10 = arg3;
    heap = temp_s0->unk_0C + arg3;

    temp_s0->unk_14 = ALIGN_PTR(heap);
    temp_s0->unk_18 = arg5;
    heap = temp_s0->unk_14 + temp_s0->unk_18;

    for (i = 0; i < temp_s0->unk_18; i++) {
        temp_s0->unk_14[i].unk_0 = ALIGN_PTR(heap);
        temp_s0->unk_14[i].unk_4 = arg4;
        temp_s0->unk_14[i].unk_8 = 0;

        heap = temp_s0->unk_14[i].unk_0 + arg4;
    }

    temp_s0->unk_1C = ALIGN_PTR(heap);
    temp_s0->unk_20 = arg3;
    heap = temp_s0->unk_1C + temp_s0->unk_20;

    temp_s0->unk_24 = ALIGN_PTR(heap);
    temp_s0->unk_28 = arg7;
    heap = temp_s0->unk_24 + temp_s0->unk_28;

    for (i = 0; i < temp_s0->unk_28; i++) {
        temp_s0->unk_24[i] = 0;
    }

    osCreateMesgQueue(&temp_s0->unk_2C, temp_s0->unk_44, ARRAY_COUNT(temp_s0->unk_44));
    heap = ALIGN_PTR(heap);
    heap_length -= ((uintptr_t)heap - (uintptr_t)temp_s0->unk_04);

    sp10.control_flag = 0;
    sp10.channels = 24;
    sp10.sched = sched;
    sp10.thread_priority = thread_priority;
    sp10.heap = heap;
    sp10.heap_length = heap_length;
    sp10.fifo_length = 0x40;
    sp10.ptr = NULL;
    sp10.wbk = NULL;
    sp10.default_fxbank = NULL;
    sp10.syn_output_rate = 32000;
    sp10.syn_updates = 0x100;
    sp10.syn_rsp_cmds = 0x1000;
    sp10.syn_retraceCount = 1;
    sp10.syn_num_dma_bufs = 36;
    sp10.syn_dma_buf_size = 0x1000;

    // ??
    sp10.syn_updates = 0x80;
    sp10.syn_rsp_cmds = 0x800;
    sp10.syn_num_dma_bufs = 32;
    sp10.syn_dma_buf_size = 0x280;

    MusSetScheduler(&D_800883F0);

    return MusInitialize(&sp10) + ((uintptr_t)heap - (uintptr_t)temp_s0->unk_04);
}
#endif

#if VERSION_US || VERSION_CN
bool func_8002D3B0(RomOffset segmentRom, size_t segmentSize, void *wbank) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    if (MusAsk(MUSFLAG_SONGS) == 0) {
        func_8002D8D0(segmentRom, temp_s0->unk_0C, segmentSize);
        MusPtrBankInitialize(temp_s0->unk_0C, wbank);
        return true;
    }

    return false;
}
#endif

#if VERSION_US || VERSION_CN
bool func_8002D428(s32 index, RomOffset segmentRom, size_t segmentSize) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    if (func_8002D51C(index) != 0) {
        return false;
    }
    func_8002D8D0(segmentRom, temp_s1->unk_14[index].unk_0, segmentSize);
    return true;
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D4A4(s32 index) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_14[index].unk_8 = MusStartSong(temp_s1->unk_14[index].unk_0);
}
#endif

#if VERSION_US || VERSION_CN
musHandle func_8002D4F8(s32 index) {
    return gAudio_800FAF98->unk_14[index].unk_8;
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D51C(s32 index) {
    return MusHandleAsk(gAudio_800FAF98->unk_14[index].unk_8);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * _gc_songFadeSong / _gc_songStop
 */
s32 func_8002D554(s32 index, s32 speed) {
    return MusHandleStop(gAudio_800FAF98->unk_14[index].unk_8, speed);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * _gc_songFadeSong
 */
s32 func_8002D58C(s32 index, s32 volume) {
    return MusHandleSetVolume(gAudio_800FAF98->unk_14[index].unk_8, volume);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D5C4(s32 index, s32 pan) {
    return MusHandleSetPan(gAudio_800FAF98->unk_14[index].unk_8, pan);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D5FC(s32 index, s32 tempo) {
    return MusHandleSetTempo(gAudio_800FAF98->unk_14[index].unk_8, tempo);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D634(s32 index) {
    return MusHandlePause(gAudio_800FAF98->unk_14[index].unk_8);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D66C(s32 index) {
    return MusHandleUnPause(gAudio_800FAF98->unk_14[index].unk_8);
}
#endif

#if VERSION_US || VERSION_CN
bool func_8002D6A4(RomOffset segmentRom, size_t segmentSize) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    if (MusAsk(MUSFLAG_EFFECTS) == 0) {
        func_8002D8D0(segmentRom, temp_s0->unk_1C, segmentSize);
        MusFxBankInitialize(temp_s0->unk_1C);
        return true;
    }
    return false;
}
#endif

#if VERSION_US || VERSION_CN
void *func_8002D710(void) {
    return gAudio_800FAF98->unk_1C;
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D720(s32 index, s32 number) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_24[index] = MusStartEffect(number);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D768(s32 index, s32 number, s32 volume, s32 pan, s32 restartflag, s32 priority) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_24[index] = MusStartEffect2(number, volume, pan, restartflag, priority);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D7C4(s32 index) {
    return gAudio_800FAF98->unk_24[index];
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D7E0(s32 index) {
    return MusHandleAsk(gAudio_800FAF98->unk_24[index]);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D810(s32 index, s32 speed) {
    return MusHandleStop(gAudio_800FAF98->unk_24[index], speed);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D840(s32 index, s32 volume) {
    return MusHandleSetVolume(gAudio_800FAF98->unk_24[index], volume);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D870(s32 index, s32 pan) {
    return MusHandleSetPan(gAudio_800FAF98->unk_24[index], pan);
}
#endif

#if VERSION_US || VERSION_CN
s32 func_8002D8A0(s32 index, f32 offset) {
    return MusHandleSetFreqOffset(gAudio_800FAF98->unk_24[index], offset);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D8D0(RomOffset segmentRom, void *segmentVram, size_t segmentSize) {
    Audio_struct_800FAF98 *temp = gAudio_800FAF98;
    s32 remainingSize = segmentSize;
    RomOffset currentRom = segmentRom;
    uintptr_t currentVram = (uintptr_t)segmentVram;

    while (remainingSize != 0) {
        OSIoMesg mb;
        OSMesg msg;
        size_t blkSize = MIN(remainingSize, 0x4000);

        osInvalDCache((void *)currentVram, blkSize);

#if VERSION_US
        osPiStartDma(&mb, OS_MESG_PRI_NORMAL, OS_READ, currentRom, (void *)currentVram, blkSize, &temp->unk_2C);
        osRecvMesg(&temp->unk_2C, &msg, OS_MESG_BLOCK);
        currentRom += blkSize;
        remainingSize -= blkSize;
#endif

#if VERSION_CN
        mb.hdr.pri = 0;
        mb.hdr.retQueue = &temp->unk_2C;
        mb.dramAddr = (void *)currentVram;
        mb.devAddr = currentRom;
        mb.size = blkSize;
        osEPiStartDma(DmaData_80000690_cn(), &mb, 0);
        currentRom += blkSize;
        remainingSize -= blkSize;
        osRecvMesg(&temp->unk_2C, &msg, OS_MESG_BLOCK);
#endif

        currentVram += blkSize;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D984(void) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    osCreateMesgQueue(&temp_s0->unk_6C, temp_s0->unk_84, ARRAY_COUNT(temp_s0->unk_84));
    osCreateMesgQueue(&temp_s0->unk_94, temp_s0->unk_AC, ARRAY_COUNT(temp_s0->unk_AC));
    func_8002A184(temp_s0->sched, &temp_s0->unk_64, &temp_s0->unk_6C);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002D9E4(void) {
    s16 *sp10;
    OSMesgQueue *temp_s0 = &gAudio_800FAF98->unk_6C;

    do {
        osRecvMesg(temp_s0, (OSMesg)&sp10, OS_MESG_BLOCK);
        osRecvMesg(temp_s0, NULL, OS_MESG_NOBLOCK);
    } while (*sp10 != 1);
}
#endif

#if VERSION_US || VERSION_CN
void func_8002DA48(musTask *musicTask) {
    Audio_struct_800FAF98 *temp_a1 = gAudio_800FAF98;
    OSScTask scTask;
    void *msg;

    scTask.list.t.data_ptr = musicTask->data;
    scTask.list.t.data_size = musicTask->data_size;
    scTask.list.t.ucode = musicTask->ucode;
    scTask.list.t.ucode_data = musicTask->ucode_data;

    scTask.next = 0;
    scTask.msgQ = &temp_a1->unk_94;
    scTask.msg = &msg;

    scTask.list.t.type = M_AUDTASK;
    scTask.list.t.ucode_boot = (void *)rspbootTextStart;
    scTask.list.t.ucode_boot_size = (uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart;
    scTask.list.t.flags = 0;
    scTask.list.t.ucode_size = SP_UCODE_SIZE;
    scTask.list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    scTask.list.t.dram_stack = NULL;
    scTask.list.t.dram_stack_size = 0;
    scTask.list.t.output_buff = NULL;
    scTask.list.t.output_buff_size = NULL;
    scTask.list.t.yield_data_ptr = NULL;
    scTask.list.t.yield_data_size = 0;

    osSendMesg(func_8002A0CC(temp_a1->sched), &scTask, OS_MESG_BLOCK);
    osRecvMesg(&temp_a1->unk_94, NULL, OS_MESG_BLOCK);
}
#endif
