#ifndef _028820_H
#define _028820_H

#include "libultra.h"
#include "libc/stdbool.h"
#include "stack.h"

typedef void (*struct_800EA290_unk_11EC_callback)(void*);

typedef struct struct_800EA290_unk_11EC {
    /* 0x0 */ struct_800EA290_unk_11EC_callback callback;
    /* 0x4 */ void *arg;
} struct_800EA290_unk_11EC; // size = 0x8

typedef struct struct_800EA290 {
    /* 0x0000 */ STACK(stack, 0x1000);
    /* 0x1000 */ OSThread thread;
    /* 0x11B0 */ OSMesgQueue mq;
    /* 0x11C8 */ OSMesg msg[9];
    /* 0x11EC */ struct_800EA290_unk_11EC unk_11EC[10];
    /* 0x123C */ s32 unk_123C;
    /* 0x1240 */ s32 unk_1240;
} struct_800EA290; // size >= 0x1244


void func_80040A00(void *arg0);
bool func_80040A58(void);
void func_80040A64(void);
void func_80040AE4(void);
void func_80040B10(struct_800EA290_unk_11EC_callback callback, void* arg);
s32 func_80040BA4(void);


extern struct_800EA290 B_800EA290;

#endif
