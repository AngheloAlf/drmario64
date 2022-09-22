#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"

extern s32 D_11A60;
extern s32 D_11A70;
extern s32 D_11A70_;
extern s32 D_4F980;
extern s32 D_80029C40[];
extern s32 D_80029C48;
extern s32 D_80029C4C;
// libultra
extern OSMesg B_8001F8C0[];
// ?
extern void (*D_80029C44)();

void func_800004F0(void *arg0) {
    func_80000620(&D_11A60, D_80029C40, (u32)&D_11A70 - (u32)&D_11A60);
    func_80002380(&D_11A70_, D_80029C40[0], (u32)&D_4F980 - (u32)&D_11A70_);

    bzero((void*)D_80029C48, D_80029C4C - D_80029C48);
    D_80029C44(arg0);
}

void func_80000580(void* arg0) {
    osCreatePiManager(150, &B_80029C08, B_8001F8C0, 50);
    osCreateThread(&B_80011010, 3, func_800004F0, arg0, STACK_TOP(B_800131C0), 10);
    osStartThread(&B_80011010);

    while (1) {
        (*D_8000E190)();
    }
}
