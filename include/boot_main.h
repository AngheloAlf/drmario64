#ifndef BOOT_MAIN_H
#define BOOT_MAIN_H

#include "libultra.h"

#include "hasm.h"
#include "stack.h"

void Main_StopThread(void);
void func_80000488(void (*arg0)());

extern STACK(gBootThreadStack, BOOT_STACK_SIZE);

#endif
