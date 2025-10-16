/**
 * http://n64devkit.square7.ch/info/submission/gateway/01-01.html
 */

#include "gateway.h"

#include "libc/stdbool.h"
#include "macros_defines.h"

#ifdef NN_SC_PERF
bool sGatewayInitialized = false;

static OSPiHandle sGatewayHandle;

OSPiHandle *Gateway_GetHandle(void) {
    if (sGatewayInitialized) {
        return &sGatewayHandle;
    }

    sGatewayHandle.type = 0;
    sGatewayHandle.baseAddress = PHYS_TO_K1(GATEWAY_HALT_REG_START_ADDR);
    sGatewayHandle.latency = GATEWAY_HALT_REG_LATENCY;
    sGatewayHandle.pulse = GATEWAY_HALT_REG_PULSE;
    sGatewayHandle.pageSize = GATEWAY_HALT_REG_PAGESIZE;
    sGatewayHandle.relDuration = GATEWAY_HALT_REG_RELDURATION;
    sGatewayHandle.domain = 1;
    sGatewayHandle.speed = 0;
    bzero(&sGatewayHandle.transferInfo, sizeof(__OSTranxInfo));
    osEPiLinkHandle(&sGatewayHandle);
    sGatewayInitialized = true;

    return &sGatewayHandle;
}

#define SET 0xFFFFFFFF
#define CLEAR 0

s32 Gateway_80002AE8_cn(bool set) {
    OSPiHandle *handle = Gateway_GetHandle();
    u32 data = SET;

    if (!set) {
        data = CLEAR;
    }

    return osEPiWriteIo(handle, GATEWAY_HALT_REG_START_ADDR, data);
}
#endif
