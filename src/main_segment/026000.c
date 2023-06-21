#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "libc/stdarg.h"

#if VERSION_US
void func_8003E1E0(Gfx **gfxP) {
    Gfx *gfx = *gfxP;

    gSPDisplayList(gfx++, D_8008E290);

    *gfxP = gfx;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026000", func_8003E208);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026000", func_8003E278);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026000", func_8003E3F0);
#endif

#if VERSION_US
UNK_TYPE func_8003E430(struct_8008E364 *arg0, va_list args) {
    struct_8008E364_unk_4 *ptr = arg0->unk_4;

    ptr->gfxP = va_arg(args, Gfx **);
    ptr->unk_04 = va_arg(args, UNK_FUN_PTR);
    ptr->unk_08 = va_arg(args, UNK_TYPE);
    ptr->unk_0A = va_arg(args, UNK_TYPE);

    ptr->unk_0C = 0;
    ptr->unk_0E = 0;
    ptr->unk_10 = 0;

    if (ptr->gfxP != NULL) {
        func_8003E1E0(ptr->gfxP);
    }

    return 0;
}
#endif

#if VERSION_US
UNK_TYPE func_8003E4AC(void) {
    return 0;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026000", func_8003E4B4);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_800400C0_cn);
#endif

#if VERSION_CN
extern Color_RGB8 D_80099090_cn[];

void func_8003E208(Gfx **gfxP, s32 index) {
    Gfx *gfx = *gfxP;
    Color_RGB8 *color = &D_80099090_cn[index % 8U];

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, 255);

    *gfxP = gfx;
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_80040158_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_8003E3F0);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_800402F8_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_80040388_cn);
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_80040390_cn);
#endif

#if VERSION_US
s32 func_8003E69C(Gfx **gfxP, func_8003E69C_arg1 arg1, s32 arg2, s32 arg3) {
    return func_8003CDA0(&D_8008E364, gfxP, arg1, arg2, arg3);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_8003E69C);
#endif

#if VERSION_US
void func_8003E6D8(void) {
    func_8003CDD4(&D_8008E364);
}
#endif

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026000", func_8003E6D8);
#endif

#if VERSION_US || VERSION_CN
void func_8003E6F8(const char *fmt UNUSED, ...) {
#if VERSION_US
    va_list args;

    va_start(args, fmt);

    func_8003D6D0(&D_8008E364, fmt, args);

    va_end(args);
#endif
}
#endif
