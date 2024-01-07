#include "gzip.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "alignment.h"
#include "boot_functions.h"

#if VERSION_US || VERSION_CN
/**
 * Original name: expand_gzip
 */
size_t expand_gzip(RomOffset segmentRom, void *dstAddr, size_t segmentSize) {
    ifd.segmentRom = segmentRom;
    ifd.segmentSize = segmentSize;
    ofd.unk_0 = dstAddr;
    ofd.unk_4 = 0;
    clear_bufs();
    unzip();
    return ofd.unk_4;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: auRomDataRead
 */
size_t auRomDataRead(struct_80029C04 *arg0, u8 *arg1, size_t blockSize) {
    size_t alignedSize;

    if (blockSize > arg0->segmentSize) {
        blockSize = arg0->segmentSize;
    }

    alignedSize = ALIGN8(blockSize);
    if (alignedSize > 0) {
        DmaData_RomToRam(arg0->segmentRom, arg1, alignedSize);
    }

    arg0->segmentSize -= alignedSize;
    arg0->segmentRom += alignedSize;
    if ((s32)arg0->segmentSize < 0) {
        arg0->segmentSize = 0;
    }
    return blockSize;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: data_write
 */
size_t data_write(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2) {
    u8 *var_v1 = arg0->unk_0;
    size_t i;

    for (i = 0; i < arg2; i++) {
        *var_v1++ = arg1[i];
    }

    arg0->unk_0 = var_v1;
    arg0->unk_4 += arg2;

    return arg2;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: unzip
 */
s32 unzip(void) {
    u8 sp10[8];
    u8 sp18[8 * 3] UNUSED;
    s32 temp_v0;
    s32 i;

    updcrc(NULL, 0);
    temp_v0 = inflate();

    if (temp_v0 == 3) {
        return -1;
    }
    if (temp_v0 != 0) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        sp10[i] = (inptr < insize) ? inbuf[inptr++] : fill_inbuf(0);
    }
    return 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: updcrc
 */
u32 updcrc(u8 *arg0, size_t arg1) {
    u32 var_a2 = -1;

    if (arg0 != NULL) {
        var_a2 = crc_132;
        while (arg1 > 0) {
            var_a2 = crc_32_tab[(var_a2 ^ *arg0) & 0xFF] ^ (var_a2 >> 8);
            arg0 += 1;
            arg1 -= 1;
        }
    }

    crc_132 = var_a2;
    return ~var_a2;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original names: clear_bufs
 */
void clear_bufs(void) {
    outcnt = 0;
    inptr = 0;
    insize = 0;
    bytes_out = 0;
    bytes_in = 0;
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: fill_inbuf
 */
s32 fill_inbuf(s32 arg0) {
    insize = 0;
    do {
        s32 temp_v0 = auRomDataRead(&ifd, &inbuf[insize], 0x2000 - insize);

        if ((temp_v0 == 0) || (temp_v0 == -1)) {
            break;
        }
        insize = insize + temp_v0;
    } while (insize < ARRAY_COUNTU(inbuf));

    if (insize == 0) {
        if (arg0 != 0) {
            return -1;
        }
    }

    bytes_in += insize;
    inptr = 1;
    return inbuf[0];
}
#endif

#if VERSION_US || VERSION_CN
void func_800022A8(struct_8001D7F8 *arg0, u8 *arg1, size_t arg2) {
    do {
        size_t temp_v0 = data_write(arg0, arg1, arg2);

        if (temp_v0 == arg2) {
            break;
        }

        arg2 -= temp_v0;
        arg1 += temp_v0;
    } while (true);
}
#endif

#if VERSION_US || VERSION_CN
/**
 * Original name: flush_window
 */
void flush_window(void) {
    if (outcnt != 0) {
        updcrc(window, outcnt);
        func_800022A8(&ofd, window, outcnt);
        bytes_out += outcnt;
        outcnt = 0;
    }
}
#endif
