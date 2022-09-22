#include "ultra64.h"
#include "include_asm.h"

extern OSThread B_80010E60;
extern OSThread B_80011010;
extern void (*D_8000E190)();
void func_80000580(void* arg0);
extern u64 B_800131C0;

extern s32 D_11A60;
extern s32 D_11A70;
extern s32 D_11A70_;
extern s32 D_4F980;
extern s32 D_80029C40[];
extern s32 D_80029C48;
extern s32 D_80029C4C;
extern OSMesgQueue B_80029C08;
extern OSMesg B_8001F8C0[];
extern u64 B_800151C0[];

extern void (*D_80029C44)();

void *func_80000620(s32 *arg0, void *arg1, u32 arg2);
void *func_80002380(s32 *arg1, s32, u32);


void func_800004F0(void *arg0) {
    func_80000620(&D_11A60, D_80029C40, (u32)&D_11A70 - (u32)&D_11A60);
    func_80002380(&D_11A70_, D_80029C40[0], (u32)&D_4F980 - (u32)&D_11A70_);

    bzero((void*)D_80029C48, D_80029C4C - D_80029C48);
    D_80029C44(arg0);
}

void func_80000580(void* arg0) {
    osCreatePiManager(0x96, &B_80029C08, B_8001F8C0, 0x32);
    osCreateThread(&B_80011010, 3, func_800004F0, arg0, &B_800151C0, 0xA);
    osStartThread(&B_80011010);

    while (1) {
        (*D_8000E190)();
    }
}
