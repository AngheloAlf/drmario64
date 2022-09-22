#include "ultra64.h"
#include "include_asm.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "segment_symbols.h"

// libultra
extern OSMesg B_8001F8C0[];
// ?
extern void (*D_80029C44)();

void func_800004F0(void *arg0) {
    func_80000620(SEGMENT_ROM_START(segment_11A60), SEGMENT_START(segment_11A60), SEGMENT_ROM_SIZE(segment_11A60));
    func_80002380(SEGMENT_ROM_START(segment_11A70), SEGMENT_START(segment_11A60)[0], SEGMENT_ROM_SIZE(segment_11A70));

    bzero(SEGMENT_START(segment_11A60)[2], SEGMENT_START(segment_11A60)[3] - SEGMENT_START(segment_11A60)[2]);
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
