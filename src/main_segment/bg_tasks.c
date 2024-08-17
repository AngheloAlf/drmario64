/**
 * This system implements a manager that allows running asynchrnous tasks on its own thread which has the lowest
 * priority.
 *
 * This manager allows to queue up to 10 tasks. If more tasks than the 10 tasks limit are added before those are
 * completed then the oldest tasks will be dropped. It is recommended to wait for all the queue to complete before
 * destroying the manager.
 *
 * No original names for this system.
 */

#include "bg_tasks.h"

#include "macros_defines.h"
#include "dm_thread.h"

bool sBgTasksManager_Initialized = false;

extern BgTasksManager sBgTasksManager_Manager;

void BgTasksManager_ThreadEntry(void *arg UNUSED) {
    BgTasksManager *manager = &sBgTasksManager_Manager;

    while (true) {
        BgTask *task;

        osRecvMesg(&manager->mq, (OSMesg *)&task, OS_MESG_BLOCK);
        task->callback(task->arg);
        manager->remainingTasks--;
    }
}

bool BgTasksManager_IsInitialized(void) {
    return sBgTasksManager_Initialized;
}

void BgTasksManager_Init(void) {
    BgTasksManager *manager = &sBgTasksManager_Manager;

    manager->currentTaskIndex = 0;
    manager->remainingTasks = 0;
    osCreateMesgQueue(&manager->mq, manager->msg, ARRAY_COUNT(manager->msg));

    osCreateThread(&manager->thread, THREAD_ID_BG_TASK, BgTasksManager_ThreadEntry, NULL, STACK_TOP(manager->stack),
                   THREAD_PRI_BG_TASK);
    osStartThread(&manager->thread);

    sBgTasksManager_Initialized = true;
}

void BgTasksManager_Destroy(void) {
    osDestroyThread(&sBgTasksManager_Manager.thread);
    sBgTasksManager_Initialized = false;
}

void BgTasksManager_SendTask(BgTaskCallback callback, void *arg) {
    BgTasksManager *manager = &sBgTasksManager_Manager;
    BgTask *task;

    manager->remainingTasks++;

    task = &manager->tasks[manager->currentTaskIndex];
    manager->currentTaskIndex = (manager->currentTaskIndex + 1) % ARRAY_COUNT(manager->tasks);

    task->callback = callback;
    task->arg = arg;
    osSendMesg(&manager->mq, task, OS_MESG_BLOCK);
}

s32 BgTasksManager_GetRemainingTasks(void) {
    return sBgTasksManager_Manager.remainingTasks;
}
