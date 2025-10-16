#include "hasm.h"

.section .text, "ax"

LEAF(gspS2DEX_fifoTextStart)
.incbin "rsp/s2dex.textbin.bin"
END(gspS2DEX_fifoTextStart)
EXPORT(gspS2DEX_fifoTextEnd)

#if VERSION_CN
.section .rodata, "a"
#else
.section .data, "wa"
#endif

SYM_START(gspS2DEX_fifoDataStart)
.incbin "rsp/s2dex.databin.bin"
SYM_END(gspS2DEX_fifoDataStart)
EXPORT(gspS2DEX_fifoDataEnd)
