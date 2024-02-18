#include "066580.h"

#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_variables.h"
#include "nnsched.h"

char D_800AB170[] = "ＡＢＣＤＥＦＧＨＪＫＬＭＮＰＱＲＳＴＶＷＸＹ１２３４５６７８９０";

char D_800AB1B4[32] = "ABCDEFGHJKLMNPQRSTVWXY1234567890";

char D_800AB1D4[] = "01234567890123456789";

u32 D_800AB1EC[] = {
    0x0B626835,
    0x0763337A,
    0x0F4D6F49,
    0x06343069,
};

u32 D_800AB1FC[] = {
    0x03DF4B61,
    0x040E7254,
    0x0A456B4F,
    0x092E476F,
};

u32 D_800AB20C[] = {
    0x08C26B8A,
    0x0D73B9A1,
    0x053AD652,
    0x024DF62E,
};

u32 D_800AB21C[] = {
    0x81021794, 0xF4967A99, 0xB403DEC6, 0x7FD52F56, 0x5086D67F, 0xD10A4924, 0x939AEA49, 0x24925292,
    0x492494A4, 0x92492529, 0x79775FFF, 0x00942FFE, 0xB95EA2BC, 0xC3EB108E, 0xA377F5BF, 0xEFAC4D93,
    0x6307CC7F, 0xBAE8741C, 0x46B6AF5C, 0x8F73890D, 0xFEA85A79, 0x5536EA9C, 0xC7F04155, 0x3A6E4D2D,
    0xC567B808, 0x1AEE23E9, 0x7F8454BA, 0xA7586398, 0x69A0CCE8, 0xE7FF0027, 0xF90A7044, 0x62C46329,
};

u32 D_800AB29C[] = {
    0xE435FBDF, 0xE2384C76, 0xD702AE2A, 0x9E8D9B77, 0xED3B7F7A, 0x3DA8B55B, 0xD8A8F1CA, 0xB42CF9E0,
    0x4FA87E8F, 0xCC992492, 0x53B51492, 0x4924A4B8, 0xFF00CE0F, 0x8ADD0B06, 0x8FA63E2B, 0x78205490,
    0x22350C22, 0x3505266A, 0x33505A8C, 0xD4D5240B, 0x0FEB4FF4, 0x767F5FFE, 0xFAF5B816, 0x27D68FE8,
    0xCCFEB8FF, 0x00A9B536, 0x5B32E2F9, 0xC35FEAC7, 0xD0B7E2D5, 0xD0AE7BEA, 0xCE95D9FD, 0x61F91740,
};

u8 *func_8007E760(char *dst, u8 arg1, u8 arg2, u8 arg3, u32 arg4, u16 arg5, u8 arg6[4]) {
    s32 temp_t0;
    u8 temp_t1;
    u8 temp_t6_2;
    s32 var_s2;
    u32 var_t8;
    u32 var_t5;
    u32 var_t4;
    s32 temp_t9;
    u8 *var_s1;
    u16 *temp;
    u16 *temp2;

    temp_t1 = framecont & 0x1F;
    temp_t6_2 = (framecont >> 5) & 0x1F;

    temp_t0 = arg1 + arg2 + arg3;
    temp_t0 += arg4 & 0x3FF;
    temp_t0 += (arg4 >> 0xA) & 0x3FF;
    temp_t0 += arg5 & 0xFF;
    temp_t0 += arg5 >> 8;
    temp_t0 += arg6[0] + arg6[1] + arg6[2] + arg6[3];
    temp_t0 &= 0x3FF;

    var_t8 = temp_t0 & 3;
    var_t8 <<= 0x14;
    var_t8 |= arg4 & 0xFFFFF;
    var_t8 <<= 8;
    var_t8 |= arg6[0];

    var_t5 = arg6[3];
    var_t5 <<= 8;
    var_t5 |= arg6[2];
    var_t5 <<= 8;
    var_t5 |= arg6[1];
    var_t5 <<= 6;
    var_t5 |= arg2 & 0x3F;

    var_t4 = temp_t0;
    var_t4 &= 0x3FC;
    var_t4 |= arg3 & 3;
    var_t4 <<= 2;
    var_t4 |= arg1 & 3;
    var_t4 <<= 2;
    var_t4 |= arg2 >> 6;
    var_t4 <<= 0x10;
    var_t4 |= arg5;

    var_t8 ^= D_800AB1EC[temp_t0 & 3];
    var_t5 ^= D_800AB1FC[temp_t0 & 3];
    var_t4 ^= D_800AB20C[temp_t0 & 3];

    var_t8 ^= D_800AB21C[temp_t1];
    var_t5 ^= D_800AB21C[temp_t1];
    var_t4 ^= D_800AB21C[temp_t1];

    var_t8 ^= D_800AB29C[temp_t6_2];
    var_t5 ^= D_800AB29C[temp_t6_2];
    var_t4 ^= D_800AB29C[temp_t6_2];

    temp = (u16 *)D_800AB170;
    temp2 = (u16 *)dst;
    var_s1 = D_800AB1D4;

    temp_t9 = temp_t1;
    *temp2++ = temp[temp_t9];
    *var_s1++ = D_800AB1B4[temp_t9];

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t8 & 0x1F;
        var_t8 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t5 & 0x1F;
        var_t5 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    for (var_s2 = 0; var_s2 < 6; var_s2++) {
        temp_t9 = var_t4 & 0x1F;
        var_t4 >>= 5;
        *temp2++ = temp[temp_t9];
        *var_s1++ = D_800AB1B4[temp_t9];
    }

    temp_t9 = temp_t6_2;
    *temp2++ = temp[temp_t9];
    *var_s1++ = D_800AB1B4[temp_t9];

    return D_800AB1D4;
}
