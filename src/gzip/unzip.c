#include "gzip.h"
#include "macros_defines.h"
#include "alignment.h"
#include "boot_functions.h"

typedef struct struct_8001D7F8 {
    /* 0x0 */ u8 *unk_0;    // dstAddr
    /* 0x4 */ size_t unk_4; // uncompressedSize
} struct_8001D7F8;          // size >= 0x8

typedef struct struct_80029C04 {
    /* 0x0 */ RomOffset segmentRom;
    /* 0x4 */ size_t segmentSize;
} struct_80029C04; // size >= 0x8

/**
 * Original name: ofd
 */
extern struct_8001D7F8 ofd;

/**
 * Original name: ifd
 */
extern struct_80029C04 ifd;

/**
 * Original name: bytes_in
 */
extern s32 bytes_in;
/**
 * Original name: bytes_out
 */
extern s32 bytes_out;

// unused
u32 D_8000EDD0[] = {
    0xDF000000,
    0x00000000,
};

s32 unzip(void);
u32 updcrc(u8 *arg0, size_t arg1);
void clear_bufs(void);

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

/**
 * Original name: crc_32_tab
 */
u32 crc_32_tab[0x100] = {
    0,          0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3, 0x0EDB8832,
    0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
    0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 0x136C9856, 0x646BA8C0, 0xFD62F97A,
    0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3,
    0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
    0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB,
    0xB6662D3D, 0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01, 0x6B6B51F4,
    0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
    0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 0x4DB26158, 0x3AB551CE, 0xA3BC0074,
    0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525,
    0x206F85B3, 0xB966D409, 0xCE61E49F, 0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
    0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615,
    0x73DC1683, 0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7, 0xFED41B76,
    0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
    0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6,
    0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7,
    0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
    0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7,
    0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45, 0xA00AE278,
    0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
    0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, 0xBDBDF21C, 0xCABAC28A, 0x53B39330,
    0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
};

/**
 * Original name: crc
 */
u32 crc_132 = 0xFFFFFFFF;

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
