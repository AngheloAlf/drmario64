#include "ultra64.h"

// TODO: move to a header
extern OSThread B_80010E60;
extern OSThread B_80011010;
extern void (*D_8000E190)();
extern void func_80000580(void* arg0);
extern u64 B_800131C0;
extern void func_80007C90(OSThread*);

void func_80000460(void) {
}

void func_80000468(void) {
    func_80007C90(&B_80011010);
}

void func_80000488(void* arg0) {
    D_8000E190 = arg0;
}

void bootproc(void) {
    __osInitialize_common(); // TODO: use osInitialize
    osCreateThread(&B_80010E60, 1, func_80000580, NULL, &B_800131C0, 1);
    osStartThread(&B_80010E60);
}
