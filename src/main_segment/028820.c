#include "libultra.h"
#include "include_asm.h"
#include "unk.h"
#include "macros_defines.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

void func_80040A00(void *arg0 UNUSED) {
    struct_800EA290 *ptr = &B_800EA290;

    while (true) {
        struct_800EA290_unk_11EC *sp10;

        osRecvMesg(&ptr->mq, (OSMesg *)&sp10, OS_MESG_BLOCK);
        sp10->callback(sp10->arg);
        ptr->unk_1240--;
    }
}

s32 func_80040A58(void) {
    return D_8008E5D0;
}

void func_80040A64(void) {
    struct_800EA290 *ptr = &B_800EA290;

    ptr->unk_123C = 0;
    ptr->unk_1240 = 0;
    osCreateMesgQueue(&ptr->mq, ptr->msg, ARRAY_COUNT(ptr->msg));
    osCreateThread(&ptr->thread, 6, func_80040A00, NULL, STACK_TOP(ptr->stack), 2);
    osStartThread(&ptr->thread);
    D_8008E5D0 = 1;
}

void func_80040AE4(void) {
    osDestroyThread(&B_800EA290.thread);
    D_8008E5D0 = 0;
}

void func_80040B10(struct_800EA290_unk_11EC_callback callback, void *arg) {
    struct_800EA290 *ptr = &B_800EA290;
    struct_800EA290_unk_11EC *temp_a2_2;

    ptr->unk_1240++;
    temp_a2_2 = &ptr->unk_11EC[ptr->unk_123C];
    ptr->unk_123C = (ptr->unk_123C + 1) % ARRAY_COUNT(ptr->unk_11EC);
    temp_a2_2->callback = callback;
    temp_a2_2->arg = arg;
    osSendMesg(&ptr->mq, temp_a2_2, OS_MESG_BLOCK);
}

s32 func_80040BA4(void) {
    return B_800EA290.unk_1240;
}
