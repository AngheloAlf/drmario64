/**
 * Original name unknown
 *
 * Seems to be a modified version of the nnsched/test_music.c file from the libmus demos.
 * All the "original names" from this file (and its header) come from said sdk file.
 */

#include "audio/music_driver.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "unk.h"
#include "main_segment_variables.h"
#include "PR/sched.h"
#include "nnsched.h"
#include "dmadata.h"

void DmaRomToRam(RomOffset segmentRom, void *segmentVram, size_t segmentSize);

void NnSchedInstall(void);
void NnSchedWaitFrame(void);
void NnSchedDoTask(musTask *musicTask);

/**
 * Original name: nn_mus_sched
 *
 * music library scheduler callback structure
 */
musSched nn_mus_sched = {
    NnSchedInstall,
    NnSchedWaitFrame,
    NnSchedDoTask,
};

/**
 * Original name: InitMusicDriver
 */
size_t InitMusicDriver(NNSched *sc, void *heap, size_t heap_length, size_t arg3, s32 arg4, s32 arg5,
                       size_t fxbank_size UNUSED, s32 arg7, OSPri thread_priority) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98 = ALIGN_PTR(heap);
    musConfig init;
    s32 i;

    temp_s0->unk_04 = heap;
    temp_s0->unk_08 = heap_length;
    heap = temp_s0 + 1;

    temp_s0->sc = sc;

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

    temp_s0->fxbank = ALIGN_PTR(heap);
    temp_s0->unk_20 = arg3;
    heap = temp_s0->fxbank + temp_s0->unk_20;

    temp_s0->unk_24 = ALIGN_PTR(heap);
    temp_s0->unk_28 = arg7;
    heap = temp_s0->unk_24 + temp_s0->unk_28;

    for (i = 0; i < temp_s0->unk_28; i++) {
        temp_s0->unk_24[i] = 0;
    }

    osCreateMesgQueue(&temp_s0->dma_queue, temp_s0->dma_messages, ARRAY_COUNT(temp_s0->dma_messages));

    heap = ALIGN_PTR(heap);
    heap_length -= ((uintptr_t)heap - (uintptr_t)temp_s0->unk_04);

    init.control_flag = 0;
    init.channels = 24;
    init.sched = sc;
    init.thread_priority = thread_priority;
    init.heap = heap;
    init.heap_length = heap_length;
    init.fifo_length = 0x40;
    init.ptr = NULL;
    init.wbk = NULL;
    init.default_fxbank = NULL;
    init.syn_output_rate = 32000;
    init.syn_updates = 0x100;
    init.syn_rsp_cmds = 0x1000;
    init.syn_retraceCount = 1;
    init.syn_num_dma_bufs = 36;
    init.syn_dma_buf_size = 0x1000;

    // ??
    init.syn_updates = 0x80;
    init.syn_rsp_cmds = 0x800;
    init.syn_num_dma_bufs = 32;
    init.syn_dma_buf_size = 0x280;

    /* set for NN scheduler this function must be called before 'musInitialize' otherwise default scheduler will be
     * initialised and used */
    MusSetScheduler(&nn_mus_sched);

    return MusInitialize(&init) + ((uintptr_t)heap - (uintptr_t)temp_s0->unk_04);
}

bool func_8002D3B0(RomOffset segmentRom, size_t segmentSize, void *wbank) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    if (MusAsk(MUSFLAG_SONGS) == 0) {
        DmaRomToRam(segmentRom, temp_s0->unk_0C, segmentSize);
        MusPtrBankInitialize(temp_s0->unk_0C, wbank);
        return true;
    }

    return false;
}

bool func_8002D428(s32 index, RomOffset segmentRom, size_t segmentSize) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    if (func_8002D51C(index) != 0) {
        return false;
    }
    DmaRomToRam(segmentRom, temp_s1->unk_14[index].unk_0, segmentSize);
    return true;
}

void func_8002D4A4(s32 index) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_14[index].unk_8 = MusStartSong(temp_s1->unk_14[index].unk_0);
}

musHandle func_8002D4F8(s32 index) {
    return gAudio_800FAF98->unk_14[index].unk_8;
}

s32 func_8002D51C(s32 index) {
    return MusHandleAsk(gAudio_800FAF98->unk_14[index].unk_8);
}

/**
 * _gc_songFadeSong / _gc_songStop
 */
s32 func_8002D554(s32 index, s32 speed) {
    return MusHandleStop(gAudio_800FAF98->unk_14[index].unk_8, speed);
}

/**
 * _gc_songFadeSong
 */
s32 func_8002D58C(s32 index, s32 volume) {
    return MusHandleSetVolume(gAudio_800FAF98->unk_14[index].unk_8, volume);
}

s32 func_8002D5C4(s32 index, s32 pan) {
    return MusHandleSetPan(gAudio_800FAF98->unk_14[index].unk_8, pan);
}

s32 func_8002D5FC(s32 index, s32 tempo) {
    return MusHandleSetTempo(gAudio_800FAF98->unk_14[index].unk_8, tempo);
}

s32 func_8002D634(s32 index) {
    return MusHandlePause(gAudio_800FAF98->unk_14[index].unk_8);
}

s32 func_8002D66C(s32 index) {
    return MusHandleUnPause(gAudio_800FAF98->unk_14[index].unk_8);
}

bool func_8002D6A4(RomOffset segmentRom, size_t segmentSize) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    if (MusAsk(MUSFLAG_EFFECTS) == 0) {
        DmaRomToRam(segmentRom, temp_s0->fxbank, segmentSize);
        MusFxBankInitialize(temp_s0->fxbank);
        return true;
    }
    return false;
}

void *func_8002D710(void) {
    return gAudio_800FAF98->fxbank;
}

void func_8002D720(s32 index, s32 number) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_24[index] = MusStartEffect(number);
}

void func_8002D768(s32 index, s32 number, s32 volume, s32 pan, s32 restartflag, s32 priority) {
    Audio_struct_800FAF98 *temp_s1 = gAudio_800FAF98;

    temp_s1->unk_24[index] = MusStartEffect2(number, volume, pan, restartflag, priority);
}

s32 func_8002D7C4(s32 index) {
    return gAudio_800FAF98->unk_24[index];
}

s32 func_8002D7E0(s32 index) {
    return MusHandleAsk(gAudio_800FAF98->unk_24[index]);
}

s32 func_8002D810(s32 index, s32 speed) {
    return MusHandleStop(gAudio_800FAF98->unk_24[index], speed);
}

s32 func_8002D840(s32 index, s32 volume) {
    return MusHandleSetVolume(gAudio_800FAF98->unk_24[index], volume);
}

s32 func_8002D870(s32 index, s32 pan) {
    return MusHandleSetPan(gAudio_800FAF98->unk_24[index], pan);
}

s32 func_8002D8A0(s32 index, f32 offset) {
    return MusHandleSetFreqOffset(gAudio_800FAF98->unk_24[index], offset);
}

/**
 * Original name: DmaRomToRam
 *
 * Download an area of ROM to RAM. Note this function limits the size of any DMA
 * generated to 16k so as to cause clashes with audio DMAs.
 */
void DmaRomToRam(RomOffset segmentRom, void *segmentVram, size_t segmentSize) {
    Audio_struct_800FAF98 *temp = gAudio_800FAF98;
    s32 remainingSize = segmentSize;
    RomOffset currentRom = segmentRom;
    uintptr_t currentVram = (uintptr_t)segmentVram;

    while (remainingSize != 0) {
        OSIoMesg mb;
        OSMesg msg;
        size_t blkSize = MIN(remainingSize, 0x4000);

        osInvalDCache((void *)currentVram, blkSize);

        DMADATA_COPY_BLOCK(&mb, currentRom, currentVram, blkSize, &temp->dma_queue);

#if VERSION_US
        osRecvMesg(&temp->dma_queue, &msg, OS_MESG_BLOCK);
#endif

        currentRom += blkSize;
        currentVram += blkSize;
        remainingSize -= blkSize;

#if VERSION_CN || VERSION_GW
        osRecvMesg(&temp->dma_queue, &msg, OS_MESG_BLOCK);
#endif
    }
}

/**
 * Original name: NnSchedInstall
 *
 * Initialise the NN scheduler callback functions for the music library. This function
 * is called once by the audio thread before entering an infinite loop.
 */
void NnSchedInstall(void) {
    Audio_struct_800FAF98 *temp_s0 = gAudio_800FAF98;

    /* create message queues for WaitFrame and DoTask functions */
    osCreateMesgQueue(&temp_s0->nnframe_queue, temp_s0->nnframe_messages, ARRAY_COUNT(temp_s0->nnframe_messages));
    osCreateMesgQueue(&temp_s0->nntask_queue, temp_s0->nntask_messages, ARRAY_COUNT(temp_s0->nntask_messages));

    /* add waitframe client */
    nnScAddClient(temp_s0->sc, &temp_s0->nnclient, &temp_s0->nnframe_queue);
}

/**
 * Original name: NnSchedWaitFrame
 *
 * Wait for a retrace message for the music library. This function is called by the
 * audio threads inifinite loop to wait for a retrace message. The 'syn_retraceCount'
 * parameter of the musConfig structure must contain the number of retraces per
 * message received.
 */
void NnSchedWaitFrame(void) {
    NNScMsg *message;
    OSMesgQueue *temp_s0 = &gAudio_800FAF98->nnframe_queue;

    do {
        osRecvMesg(temp_s0, (OSMesg)&message, OS_MESG_BLOCK);

        /* bin any missed syncs! */
        osRecvMesg(temp_s0, NULL, OS_MESG_NOBLOCK);
    } while (*message != NN_SC_RETRACE_MSG);
}

/**
 * Original name: NnSchedDoTask
 *
 * Process a audio task for the music library. This function is called by the audio
 * threads inifinite loop to generate an audio task and wait for its completion.
 */
void NnSchedDoTask(musTask *musicTask) {
    Audio_struct_800FAF98 *temp_a1 = gAudio_800FAF98;
    OSScTask scTask;
    OSMesg msg;

    scTask.list.t.data_ptr = musicTask->data;
    scTask.list.t.data_size = musicTask->data_size;
    scTask.list.t.ucode = musicTask->ucode;
    scTask.list.t.ucode_data = musicTask->ucode_data;

    scTask.next = 0;
    scTask.msgQ = &temp_a1->nntask_queue;
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

    osSendMesg(nnScGetAudioMQ(temp_a1->sc), &scTask, OS_MESG_BLOCK);
    osRecvMesg(&temp_a1->nntask_queue, NULL, OS_MESG_BLOCK);
}
