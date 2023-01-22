#include "gzip.h"
#include "include_asm.h"
#include "macros_defines.h"

#if VERSION_US
void *func_80000720(s32 arg0) {
    D_8000E324 += arg0;

    if (D_8000E324 <= 0x4000) {
        void *var_v0 = gzip_malloc_addr;

        gzip_malloc_addr = var_v0 + arg0;
        return var_v0;
    }

    return NULL;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80000820_cn);
#endif

#if VERSION_US
void func_8000075C(void) {
    D_8000E324 = 0;
    gzip_malloc_addr = gzip_mem_buff;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80000868_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80000778);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80000888_cn);
#endif

#if VERSION_US
#ifdef NON_MATCHING
UNK_TYPE func_80000D0C(void *arg0) {
    void *temp_a0;
    void *temp_s0;

    while (arg0 != NULL) {
        temp_a0 = arg0 - 8;
        // temp_s0 = temp_a0->unk_4;
        temp_s0 = (void *)((s32 *)temp_a0)[1];
        func_8000075C();
        arg0 = temp_s0;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80000D0C);
#endif
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80000E7C_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80000D48);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80000EC8_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80001260);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_800014C4_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80001480);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_80001760_cn);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", func_80001620);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", func_8000194C_cn);
#endif

/**
 * Original name: inflate_block
 */
#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/gzip/inflate", inflate_block);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/gzip/inflate", inflate_block);
#endif

/**
 * Original name: inflate
 */
s32 inflate(void) {
    s32 sp10;
    s32 ret;
    u32 var_s0 = 0;

    outcnt = 0;
    bk = 0;
    B_8001F998 = 0;
    D_8000E324 = 0;
    gzip_malloc_addr = gzip_mem_buff;

    while (true) {
        hufts = 0;
        ret = inflate_block(&sp10);
        if (ret != 0) {
            break;
        }

        if (var_s0 < hufts) {
            var_s0 = hufts;
        }

        if (sp10 != 0) {
            while (bk >= 8) {
                bk -= 8;
                inptr -= 1;
            }

            flush_window();
            ret = 0;
            break;
        }
    }

    return ret;
}
