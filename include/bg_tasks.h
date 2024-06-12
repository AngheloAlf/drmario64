#ifndef BG_TASK_H
#define BG_TASK_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "stack.h"

typedef void (*BgTaskCallback)(void*);

typedef struct BgTask {
    /* 0x0 */ BgTaskCallback callback;
    /* 0x4 */ void *arg;
} BgTask; // size = 0x8

typedef struct BgTasksManager {
    /* 0x0000 */ STACK(stack, 0x1000);
    /* 0x1000 */ OSThread thread;
    /* 0x11B0 */ OSMesgQueue mq;
    /* 0x11C8 */ OSMesg msg[9];
    /* 0x11EC */ BgTask tasks[10];
    /* 0x123C */ s32 currentTaskIndex;
    /* 0x1240 */ s32 remainingTasks;
} BgTasksManager; // size = 0x1248

bool BgTasksManager_IsInitialized(void);
void BgTasksManager_Init(void);
void BgTasksManager_Destroy(void);
void BgTasksManager_SendTask(BgTaskCallback callback, void* arg);
s32 BgTasksManager_GetRemainingTasks(void);

#endif
