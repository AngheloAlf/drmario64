#include "libultra.h"
#include "libc/stdbool.h"
#include "macros_defines.h"

extern OSPiHandle B_80019CD0_cn;

extern bool D_8000F4F0_cn;

OSPiHandle *func_80002A30_cn(void) {
    if (D_8000F4F0_cn) {
        return &B_80019CD0_cn;
    }

    B_80019CD0_cn.type = 0;
    B_80019CD0_cn.baseAddress = PHYS_TO_K1(0x0FF70000);
    B_80019CD0_cn.latency = 5;
    B_80019CD0_cn.pulse = 0xC;
    B_80019CD0_cn.pageSize = 0xD;
    B_80019CD0_cn.relDuration = 2;
    B_80019CD0_cn.domain = 1;
    B_80019CD0_cn.speed = 0;
    bzero(&B_80019CD0_cn.transferInfo, sizeof(__OSTranxInfo));
    osEPiLinkHandle(&B_80019CD0_cn);
    D_8000F4F0_cn = true;
    return &B_80019CD0_cn;
}

void func_80002AE8_cn(s32 arg0) {
    OSPiHandle *temp_v0 = func_80002A30_cn();
    u32 var_a2 = 0xFFFFFFFF;

    if (arg0 == 0) {
        var_a2 = 0;
    }
    osEPiWriteIo(temp_v0, 0x0FF70000U, var_a2);
}
