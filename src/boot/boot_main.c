#include "ultra64.h"
#include "boot_functions.h"
#include "boot_variables.h"

void func_80000460(void) {
}

void func_80000468(void) {
    osStopThread(&B_80011010);
}

void func_80000488(void* arg0) {
    D_8000E190 = arg0;
}

void bootproc(void) {
    osInitialize();
    osCreateThread(&B_80010E60, 1, func_80000580, NULL, &B_800131C0, 1);
    osStartThread(&B_80010E60);
}
