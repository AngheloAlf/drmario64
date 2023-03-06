#ifndef GATEWAY_H
#define GATEWAY_H

#include "libultra.h"
#include "libc/stdbool.h"

/**
 * http://n64devkit.square7.ch/info/submission/gateway/01-01.html
 */

#define GATEWAY_HALT_REG_START_ADDR   0x0FF70000
#define GATEWAY_HALT_REG_SIZE         0x32
#define GATEWAY_HALT_REG_LATENCY      0x5
#define GATEWAY_HALT_REG_PULSE        0x0C
#define GATEWAY_HALT_REG_PAGESIZE     0xD
#define GATEWAY_HALT_REG_RELDURATION  0x2

s32 Gateway_80002AE8_cn(bool set);

#endif
