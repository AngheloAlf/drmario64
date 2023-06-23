#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "boot_functions.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

// extern UNK_TYPE D_8008E370;
// extern UNK_TYPE D_8008E380;
// extern UNK_TYPE D_8008E398;
// extern UNK_TYPE D_8008E3B8;
// extern UNK_TYPE D_8008E3BC;
// extern UNK_TYPE D_8008E3C0;
// extern UNK_TYPE D_8008E400;
// extern UNK_TYPE D_8008E420;
// extern UNK_TYPE D_8008E454;
extern u8 *D_8008E480[];
extern const char *D_8008E490[];
extern const char *D_8008E4A0[];
// extern UNK_TYPE D_8008E4AC;
// extern UNK_TYPE D_8008E4DC;
// extern UNK_TYPE D_8008E4F0;
// extern UNK_TYPE D_8008E508;
extern UNK_TYPE1 D_8008E538[];
extern UNK_TYPE1 D_8008E540[];
extern s32 *D_8008E548[];
extern s32 D_8008E558[];
extern s8 D_8008E568[];
extern s8 D_8008E574[];
extern s8 D_8008E57C[];
extern s8 D_8008E584[];
extern UNK_TYPE1 D_8008E590[];
extern UNK_TYPE1 D_8008E598[];
extern const char *D_8008E5A0[];
extern s32 D_8008E5B0;
extern s32 D_8008E5B4[];

extern s32 D_800990C0_cn[];
extern const char *D_800990D0_cn[];
extern const char *D_800990E8_cn[];
extern const char *D_80099108_cn[];
extern const char *D_80099110_cn[];
extern const char *D_80099150_cn[];
extern const char *D_80099170_cn[];
extern const char *D_800991A4_cn[];
//! extern u8 *D_8008E480[];
//! extern const char *D_8008E490[];
//! extern const char *D_8008E4A0[];
// extern UNK_TYPE D_800991FC_cn;
// extern UNK_TYPE D_8009922C_cn;
// extern UNK_TYPE D_80099240_cn;
// extern UNK_TYPE D_80099258_cn;
//! extern UNK_TYPE1 D_8008E538[];
extern UNK_TYPE1 D_80099290_cn[];
//! extern s32 *D_8008E548[];
//! extern s32 D_8008E558[];
//! extern s8 D_8008E568[];
//! extern s8 D_8008E574[];
//! extern s8 D_8008E57C[];
//! extern s8 D_8008E584[];
//! extern UNK_TYPE1 D_8008E590[];
//! extern UNK_TYPE1 D_8008E598[];
//! extern const char *D_8008E5A0[];
//! extern s32 D_8008E5B0;
//! extern s32 D_8008E5B4[];

extern s32 B_800FC500_cn;
extern s32 B_800FC504_cn;
extern s32 B_800FC508_cn;

#if VERSION_US
const char STR_800AD2E0[] RODATA = "MajorityRensa";

const char STR_800AD2F0[] RODATA = "WidErase";

const char STR_800AD2FC[] RODATA = "Rensa&Attack";

const char STR_800AD30C[] RODATA = "Rensa&Erase";

const char STR_800AD318[] RODATA = "SmallRensa";

const char STR_800AD324[] RODATA = "FastErase";

const char STR_800AD330[] RODATA = "Normal";

const char STR_800AD338[] RODATA = "Badline1";

const char STR_800AD344[] RODATA = "Badline2";

const char STR_800AD350[] RODATA = "LastVsn";

const char STR_800AD358[] RODATA = "LastVsnh";

const char STR_800AD364[] RODATA = "Last";

const char STR_800AD36C[] RODATA = "Narrow";

const char STR_800AD374[] RODATA = "Dead";

const char STR_800AD37C[] RODATA = "On";

const char STR_800AD380[] RODATA = "Off";

const char STR_800AD384[] RODATA = "Plain4";

const char STR_800AD38C[] RODATA = "Plain3";

const char STR_800AD394[] RODATA = "Plain2";

const char STR_800AD39C[] RODATA = "Plain1";

const char STR_800AD3A4[] RODATA = "Peach";

const char STR_800AD3AC[] RODATA = "Koopa";

const char STR_800AD3B4[] RODATA = "Kamek";

const char STR_800AD3BC[] RODATA = "PakkunFlower";

const char STR_800AD3CC[] RODATA = "Telesa";

const char STR_800AD3D4[] RODATA = "Hanachan";

const char STR_800AD3E0[] RODATA = "Heihoo";

const char STR_800AD3E8[] RODATA = "Chiropoo";

const char STR_800AD3F4[] RODATA = "PukuPuku";

const char STR_800AD400[] RODATA = "Bomhei";

const char STR_800AD408[] RODATA = "NokoNoko";

const char STR_800AD414[] RODATA = "Mario";

const char STR_800AD41C[] RODATA = "FasterNW";

const char STR_800AD428[] RODATA = "NoWait";

const char STR_800AD430[] RODATA = "Fastest";

const char STR_800AD438[] RODATA = "Faster";

const char STR_800AD440[] RODATA = "Fast";

const char STR_800AD448[] RODATA = "Slow";

const char STR_800AD450[] RODATA = "Slower";

const char STR_800AD458[] RODATA = "SpSlow";

const char STR_800AD460[] RODATA = "PreemPtive";

const char STR_800AD46C[] RODATA = "Rensa";

const char STR_800AD474[] RODATA = "Hard";

const char STR_800AD47C[] RODATA = "Easy";

const char STR_800AD484[] RODATA = "Pile";

const char STR_800AD48C[] RODATA = "Few Vir";

const char STR_800AD494[] RODATA = "Many Vir";

const char STR_800AD4A0[] RODATA = "Damage";

const char STR_800AD4A8[] RODATA = "Random";

const char STR_800AD4B0[] RODATA = "Unconditional";

const char STR_800AD4C0[] RODATA = "--------------";

const char STR_800AD4D0[] RODATA = "Lose";

const char STR_800AD4D8[] RODATA = "be Erase";

const char STR_800AD4E4[] RODATA = "be Attack";

const char STR_800AD4F0[] RODATA = "Rapid";

const char STR_800AD4F8[] RODATA = "beNoWait";

const char STR_800AD504[] RODATA = "beSlow";

const char STR_800AD50C[] RODATA = "beFast";

const char STR_800AD514[] RODATA = "Not Move";

const char STR_800AD520[] RODATA = "Waver";

const char STR_800AD528[] RODATA = "Rotate";

const char STR_800AD530[] RODATA = "----------";

const char STR_800AD53C[] RODATA = "SlideFS";

const char STR_800AD544[] RODATA = "SlideS";

const char STR_800AD54C[] RODATA = "DownS";

const char STR_800AD554[] RODATA = "VirusLv";

const char STR_800AD55C[] RODATA = "@c2";

const char STR_800AD560[] RODATA = "%s\n\n\n\n\n\n";

const char STR_800AD56C[] RODATA = "%6s\n\n";

const char STR_800AD574[] RODATA = "@c2S_er Slow Fast F_er Fest N_Wt F_NW";

const char STR_800AD59C[] RODATA = "@m%c%03d  ";

const char STR_800AD5A8[] RODATA = "\n\n";

const char STR_800AD5AC[] RODATA = "@c3<- CharacterMenu\t\t\t\t\tLogicMenu ->";

const char STR_800AD5D4[] RODATA = "@c2Logic             State\n@c7 @m%c%02d:%-14s @m%c%02d:%-14s\n\n";

const char STR_800AD614[] RODATA = "@c2OLVrs  ErVrs  ErL1   HeiEr   WidEr   HeightP\n@c7";

const char STR_800AD648[] RODATA = " @m%c%05d%% ";

const char STR_800AD658[] RODATA = " @m%c%05d ";

const char STR_800AD664[] RODATA = "@c2\tALNB   FC     FV     C      V\n@c2Hei@c7  -----";

const char STR_800AD698[] RODATA = "  @m%c%05d";

const char STR_800AD6A4[] RODATA = "\n\n@c2Wid@c7";

const char STR_800AD6B0[] RODATA = "@c2OnVrs  Rensa  MRensa HiEr    WallP   ErOL3\n@c7 @m%c%05d  @m%c%05d  @m%c%05d  "
                                   "@m%c%05d%%  @m%c%02d:%-3s  @m%c%05d\n\n";

const char STR_800AD728[] RODATA = "@c2\tLine2  Line3  Line4~8\n@c2Hei@c7";

const char STR_800AD74C[] RODATA = "\n\n@c2DebugSpeed PlayerCom\n@c7 @m%c%03d        @m%c%03d:%-14s\n\n\n\n\n";

const char STR_800AD790[] RODATA = "Man";

const char STR_800AD794[] RODATA = "@c3<- SpeedMenu\t\t\t\t\tCharacterMenu ->";
#endif

#if VERSION_CN
ASM_RODATA;

const char STR_800C4200_cn[] = "MajorityRensa";

const char STR_800C4210_cn[] = "WidErase";

const char STR_800C421C_cn[] = "Rensa&Attack";

const char STR_800C422C_cn[] = "Rensa&Erase";

const char STR_800C4238_cn[] = "SmallRensa";

const char STR_800C4244_cn[] = "FastErase";

const char STR_800C4250_cn[] = "Normal";

const char STR_800C4258_cn[] = "Badline1";

const char STR_800C4264_cn[] = "Badline2";

const char STR_800C4270_cn[] = "LastVsn";

const char STR_800C4278_cn[] = "LastVsnh";

const char STR_800C4284_cn[] = "Last";

const char STR_800C428C_cn[] = "Narrow";

const char STR_800C4294_cn[] = "Dead";

const char STR_800C429C_cn[] = "On";

const char STR_800C42A0_cn[] = "Off";

const char STR_800C42A4_cn[] = "Plain4";

const char STR_800C42AC_cn[] = "Plain3";

const char STR_800C42B4_cn[] = "Plain2";

const char STR_800C42BC_cn[] = "Plain1";

const char STR_800C42C4_cn[] = "Peach";

const char STR_800C42CC_cn[] = "Koopa";

const char STR_800C42D4_cn[] = "Kamek";

const char STR_800C42DC_cn[] = "PakkunFlower";

const char STR_800C42EC_cn[] = "Telesa";

const char STR_800C42F4_cn[] = "Hanachan";

const char STR_800C4300_cn[] = "Heihoo";

const char STR_800C4308_cn[] = "Chiropoo";

const char STR_800C4314_cn[] = "PukuPuku";

const char STR_800C4320_cn[] = "Bomhei";

const char STR_800C4328_cn[] = "NokoNoko";

const char STR_800C4334_cn[] = "Mario";

const char STR_800C433C_cn[] = "FasterNW";

const char STR_800C4348_cn[] = "NoWait";

const char STR_800C4350_cn[] = "Fastest";

const char STR_800C4358_cn[] = "Faster";

const char STR_800C4360_cn[] = "Fast";

const char STR_800C4368_cn[] = "Slow";

const char STR_800C4370_cn[] = "Slower";

const char STR_800C4378_cn[] = "SpSlow";

const char STR_800C4380_cn[] = "PreemPtive";

const char STR_800C438C_cn[] = "Rensa";

const char STR_800C4394_cn[] = "Hard";

const char STR_800C439C_cn[] = "Easy";

const char STR_800C43A4_cn[] = "Pile";

const char STR_800C43AC_cn[] = "Few Vir";

const char STR_800C43B4_cn[] = "Many Vir";

const char STR_800C43C0_cn[] = "Damage";

const char STR_800C43C8_cn[] = "Random";

const char STR_800C43D0_cn[] = "Unconditional";

const char STR_800C43E0_cn[] = "--------------";

const char STR_800C43F0_cn[] = "Lose";

const char STR_800C43F8_cn[] = "be Erase";

const char STR_800C4404_cn[] = "be Attack";

const char STR_800C4410_cn[] = "Rapid";

const char STR_800C4418_cn[] = "beNoWait";

const char STR_800C4424_cn[] = "beSlow";

const char STR_800C442C_cn[] = "beFast";

const char STR_800C4434_cn[] = "Not Move";

const char STR_800C4440_cn[] = "Waver";

const char STR_800C4448_cn[] = "Rotate";

const char STR_800C4450_cn[] = "----------";

const char STR_800C445C_cn[] = "SlideFS";

const char STR_800C4464_cn[] = "SlideS";

const char STR_800C446C_cn[] = "DownS";

const char STR_800C4474_cn[] = "VirusLv";

const char STR_800AD55C[] = "@c2";

const char STR_800AD560[] = "%s\n\n\n\n\n\n";

const char STR_800AD56C[] = "%6s\n\n";

const char STR_800AD574[] = "@c2S_er Slow Fast F_er Fest N_Wt F_NW";

const char STR_800AD59C[] = "@m%c%03d  ";

const char STR_800AD5A8[] = "\n\n";

const char STR_800AD5AC[] = "@c3<- CharacterMenu\t\t\t\t\tLogicMenu ->";

const char STR_800C44F4_cn[] = "@c2Logic             State\n@c7 @m%c%02d:%-14s @m%c%02d:%-14s\n\n";

const char STR_800C4534_cn[] = "@c2OLVrs  ErVrs  ErL1   HeiEr   WidEr   HeightP\n@c7";

const char STR_800C4568_cn[] = " @m%c%05d%% ";

const char STR_800C4578_cn[] = " @m%c%05d ";

const char STR_800C4584_cn[] = "@c2\tALNB   FC     FV     C      V\n@c2Hei@c7  -----";

const char STR_800C45B8_cn[] = "  @m%c%05d";

const char STR_800C45C4_cn[] = "\n\n@c2Wid@c7";

const char STR_800C45D0_cn[] = "@c2OnVrs  Rensa  MRensa HiEr    WallP   ErOL3\n@c7 @m%c%05d  @m%c%05d  @m%c%05d  "
                               "@m%c%05d%%  @m%c%02d:%-3s  @m%c%05d\n\n";

const char STR_800C4648_cn[] = "@c2\tLine2  Line3  Line4~8\n@c2Hei@c7";

const char STR_800C466C_cn[] = "\n\n@c2DebugSpeed PlayerCom\n@c7 @m%c%03d        @m%c%03d:%-14s\n\n\n\n\n";

const char STR_800C46B0_cn[] = "Man";

const char STR_800C46B4_cn[] = "@c3<- SpeedMenu\t\t\t\t\tCharacterMenu ->";
#endif

void func_8003E730(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003E730);
#endif

#if VERSION_CN
void func_8003E730(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];

    if (arg3 != B_800E5914) {
        return;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            func_8003E3F0(gfxP, arg1 + ((2 - B_800FC500_cn) * 6), arg2 + 8, 0x5E);
        }
    } else {
        s32 var_t0;
        u8 *temp_a3;

        var_t0 = 0;
        if (buttonPressed & L_JPAD) {
            var_t0++;
        }
        if (buttonPressed & R_JPAD) {
            var_t0--;
        }

        B_800FC500_cn = CLAMP(B_800FC500_cn + var_t0, 0, 2);

        var_t0 = 0;
        if (buttonCurrent & U_JPAD) {
            var_t0++;
        }
        if (buttonCurrent & D_JPAD) {
            var_t0--;
        }

        temp_a3 = D_8008E480[arg3 / 21] + (((arg3 % 7) * 3) + 3) + ((arg3 / 7) - (arg3 / 21 * 3));
        *temp_a3 = CLAMP(*temp_a3 + (var_t0 * D_800990C0_cn[B_800FC500_cn]), 0, 0x1E);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003E8C8);
#endif

#if VERSION_CN
#ifdef NON_MATCHING
void func_8003E8C8(Gfx **gxfP, s32 arg1, s32 arg2) {
    s32 var_s1;
    s32 var_s5;

    func_8003E69C(gxfP, func_8003E730, arg1, arg2 + 8);
    func_8003E6F8(STR_800AD55C);

    for (var_s5 = 0; var_s5 < 4; var_s5++) {
        func_8003E6F8(STR_800AD560, D_8008E490[var_s5]);
    }

    func_8003E6D8();
    func_8003E69C(gxfP, func_8003E730, arg1 + 0x2A, arg2 + 8);
    func_8003E6F8(STR_800AD55C);

    for (var_s5 = 0; var_s5 < 4; var_s5++) {
        for (var_s1 = 0; var_s1 < 3; var_s1++) {
            func_8003E6F8(STR_800AD56C, D_8008E4A0[var_s1]);
        }
    }

    func_8003E6D8();
    func_8003E69C(gxfP, func_8003E730, arg1 + 0x54, arg2);
    func_8003E6F8(STR_800AD574);
    func_8003E6D8();
    func_8003E69C(gxfP, func_8003E730, arg1 + 0x5A, arg2 + 8);

    for (var_s5 = 0; var_s5 < 4; var_s5++) {
        for (var_s1 = 0; var_s1 < 3; var_s1++) {
            s32 var_s3;

            for (var_s3 = 1; var_s3 < 8; var_s3++) {
                func_8003E6F8(STR_800AD59C, var_s5 * 0x15 + var_s1 * 7 + var_s3 - 1,
                              D_8008E480[var_s5][var_s3 * 3 + var_s1]);
            }

            func_8003E6F8(STR_800AD5A8);
        }
    }

    func_8003E6D8();
    func_8003E69C(gxfP, func_8003E730, arg1, arg2 + 0xC8);
    func_8003E6F8(STR_800AD5AC);
    func_8003E6D8();
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026550", func_8003E8C8);
#endif
#endif

#if VERSION_US || VERSION_CN
void func_8003EB20(void) {
    struct_ai_param *temp_a1 = &ai_param[B_800E591C][B_800E5920];
    s16 *temp_v0 = B_800E58C0;

    *temp_v0++ = B_800E591C;
    *temp_v0++ = B_800E5920;
    *temp_v0++ = temp_a1->unk_00;
    *temp_v0++ = temp_a1->unk_02;
    *temp_v0++ = temp_a1->unk_04;
    *temp_v0++ = temp_a1->unk_08;
    *temp_v0++ = temp_a1->unk_0A;
    *temp_v0++ = temp_a1->unk_0C;
    *temp_v0++ = temp_a1->unk_0E;
    *temp_v0++ = temp_a1->unk_10;
    *temp_v0++ = temp_a1->unk_12;
    *temp_v0++ = temp_a1->unk_14;
    *temp_v0++ = temp_a1->unk_16;
    *temp_v0++ = temp_a1->unk_18;
    *temp_v0++ = temp_a1->unk_1A;
    *temp_v0++ = temp_a1->unk_1C;
    *temp_v0++ = temp_a1->unk_1E;
    *temp_v0++ = temp_a1->unk_20;
    *temp_v0++ = temp_a1->unk_22;
    *temp_v0++ = temp_a1->unk_24;
    *temp_v0++ = temp_a1->unk_26;
    *temp_v0++ = temp_a1->unk_2A;
    *temp_v0++ = temp_a1->unk_06;
    *temp_v0++ = temp_a1->unk_2C;
    *temp_v0++ = temp_a1->unk_2E;
    *temp_v0++ = temp_a1->unk_30;
    *temp_v0++ = temp_a1->unk_32;
    *temp_v0++ = temp_a1->unk_34;
    *temp_v0++ = temp_a1->unk_36;
    *temp_v0++ = evs_gamespeed;
    *temp_v0++ = aiDebugP1 + 1;
}
#endif

#if VERSION_US || VERSION_CN
void func_8003ECDC(void) {
    s16 *temp_v0 = B_800E58C0;
    struct_ai_param *temp_a0 = &ai_param[B_800E591C][B_800E5920];

    B_800E591C = *temp_v0++;
    B_800E5920 = *temp_v0++;
    temp_a0->unk_00 = *temp_v0++;
    temp_a0->unk_02 = *temp_v0++;
    temp_a0->unk_04 = *temp_v0++;
    temp_a0->unk_08 = *temp_v0++;
    temp_a0->unk_0A = *temp_v0++;
    temp_a0->unk_0C = *temp_v0++;
    temp_a0->unk_0E = *temp_v0++;
    temp_a0->unk_10 = *temp_v0++;
    temp_a0->unk_12 = *temp_v0++;
    temp_a0->unk_14 = *temp_v0++;
    temp_a0->unk_16 = *temp_v0++;
    temp_a0->unk_18 = *temp_v0++;
    temp_a0->unk_1A = *temp_v0++;
    temp_a0->unk_1C = *temp_v0++;
    temp_a0->unk_1E = *temp_v0++;
    temp_a0->unk_20 = *temp_v0++;
    temp_a0->unk_22 = *temp_v0++;
    temp_a0->unk_24 = *temp_v0++;
    temp_a0->unk_28 = temp_a0->unk_26 = *temp_v0++;
    temp_a0->unk_2A = *temp_v0++;
    temp_a0->unk_06 = *temp_v0++;
    temp_a0->unk_2C = *temp_v0++;
    temp_a0->unk_2E = *temp_v0++;
    temp_a0->unk_30 = *temp_v0++;
    temp_a0->unk_32 = *temp_v0++;
    temp_a0->unk_34 = *temp_v0++;
    temp_a0->unk_36 = *temp_v0++;
    evs_gamespeed = *temp_v0++;
    aiDebugP1 = *temp_v0++ - 1;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003EEA4);
#endif

#if VERSION_CN
void func_80040EAC_cn(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s16 var_t0;
    s16 var_t2;
    s32 var_t1;

    if (arg3 != B_800E5918) {
        return;
    }

    var_t2 = 0;
    var_t1 = 2;
    if (arg3 == 0) {
        var_t0 = 5;
    } else if (arg3 == 1) {
        var_t0 = 7;
    } else if (arg3 == 0x15) {
        var_t0 = 1;
    } else if (arg3 < 0x1D) {
        var_t2 = -0x270F;
        var_t0 = 0x270F;
        var_t1 = 5;
    } else if (arg3 == 0x1D) {
        var_t0 = 0x14;
        var_t1 = 3;
    } else if (arg3 == 0x1E) {
        var_t0 = 0x10;
        var_t1 = 3;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            func_8003E3F0(gfxP, arg1 + (((var_t1 - B_800FC504_cn) - 1) * 6), arg2 + 8, 0x5E);
        }
    } else {
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1 -= 1;
        }

        B_800FC504_cn = CLAMP(B_800FC504_cn + var_a1, 0, var_t1 - 1);

        var_a1 = 0;
        if (buttonCurrent & U_JPAD) {
            var_a1++;
        }
        if (buttonCurrent & D_JPAD) {
            var_a1 -= 1;
        }

        B_800E58C0[arg3] = CLAMP(B_800E58C0[arg3] + D_800990C0_cn[B_800FC504_cn] * var_a1, var_t2, var_t0);
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F050);
#endif

#if VERSION_CN
#ifdef NON_EQUIVALENT
// maybe equivalent, hard to tell
void func_8003F050(Gfx **gxfP, s32 arg1, s32 arg2) {
    s16 *temp_v0;
    s16 *temp_v0_2;
    s16 *var_s2;
    s16 *var_s2_2;
    s16 *var_s2_3;
    s16 *var_s2_4;
    s16 *var_s2_5;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_t5;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s1;
    s32 var_s1_2;
    s8 *var_a0;
    s32 v1;
    const char *arg5;

    const char *a0;

    func_8003E69C(gxfP, func_80040EAC_cn, arg1, arg2);
    func_8003E6F8(STR_800C44F4_cn, 0, B_800E58C0[0], D_800990D0_cn[B_800E58C0[0]], 1, B_800E58C0[1],
                  D_800990E8_cn[B_800E58C0[1]]);
    func_8003E6F8(STR_800C4534_cn);

    var_s1 = 2;
    var_s0 = 0;

    var_s2 = &B_800E58C0[var_s1];
    for (; var_s0 < 6; var_s0++) {
        if ((var_s0 == 3) || (var_s0 == 4)) {
            func_8003E6F8(STR_800C4568_cn, var_s1++, *var_s2++);
        } else {
            func_8003E6F8(STR_800C4578_cn, var_s1++, *var_s2++);
        }
    }

    func_8003E6F8(STR_800AD5A8);
    func_8003E6F8(STR_800C4584_cn);
    var_s2 = &B_800E58C0[var_s1];

    for (var_s0 = 1; var_s0 < 5; var_s0++) {
        func_8003E6F8(STR_800C45B8_cn, var_s1++, var_s2[var_s0]);
    }

    func_8003E6F8(STR_800C45C4_cn);

    var_s2 = &B_800E58C0[var_s1];
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        func_8003E6F8(STR_800C45B8_cn, var_s1++, *var_s2++);
    }

    func_8003E6F8(STR_800AD5A8);
    temp_v0 = &B_800E58C0[var_s1];

    func_8003E6F8(STR_800C45D0_cn, var_s1, temp_v0[0], var_s1 + 1, temp_v0[1], var_s1 + 2, temp_v0[2], var_s1 + 3,
                  temp_v0[3], var_s1 + 4, temp_v0[4], D_80099108_cn[temp_v0[4]], var_s1 + 5, temp_v0[5]);
    func_8003E6F8(STR_800C4648_cn);

    var_s1 = var_s1 + 6;
    var_s2 = &B_800E58C0[var_s1];
    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        func_8003E6F8(STR_800C45B8_cn, var_s1++, *var_s2++);
    }

    func_8003E6F8(STR_800C45C4_cn);

    var_s2 = &B_800E58C0[var_s1];
    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        func_8003E6F8(STR_800C45B8_cn, var_s1++, *var_s2++);
    }

    temp_v0_2 = &B_800E58C0[var_s1];
    v1 = temp_v0_2[1];
    if (v1 != 0) {
        arg5 = D_80099110_cn[temp_v0_2[1] - 1];
    } else {
        arg5 = STR_800C46B0_cn;
    }

    func_8003E6F8(STR_800C466C_cn, var_s1, temp_v0_2[0], var_s1 + 1, v1, arg5);

    func_8003E6F8(STR_800C46B4_cn);
    func_8003E6D8();
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026550", func_8003F050);
#endif
#endif

#if VERSION_US || VERSION_CN
void func_8003F360(void) {
    struct_ai_char_data *temp_a1 = &ai_char_data[B_800E5928];
    s16 *var_a3 = B_800E58C0;
    s32 i;

    *var_a3++ = B_800E5928;
    *var_a3++ = temp_a1->unk_00;
    *var_a3++ = temp_a1->unk_01;
    *var_a3++ = temp_a1->unk_02;

    for (i = 0; i < ARRAY_COUNT(temp_a1->unk_04); i++) {
        *var_a3++ = temp_a1->unk_04[i];
    }

    for (i = B_800E592C; i < B_800E592C + 4; i++) {
        *var_a3++ = temp_a1->unk_0C[i];
        *var_a3++ = temp_a1->unk_1C[i];
        *var_a3++ = temp_a1->unk_3C[i];
        *var_a3++ = temp_a1->unk_4C[i];
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8003F474(void) {
    struct_ai_char_data *temp_t3 = &ai_char_data[B_800E5928];
    s16 *var_t1 = B_800E58C0;
    s32 i;

    B_800E5928 = *var_t1++;
    temp_t3->unk_00 = *var_t1++;
    temp_t3->unk_01 = *var_t1++;
    temp_t3->unk_02 = *var_t1++;

    for (i = 0; i < ARRAY_COUNT(temp_t3->unk_04); i++) {
        temp_t3->unk_04[i] = *var_t1++;
    }

    for (i = B_800E592C; i < B_800E592C + 4; i++) {
        temp_t3->unk_0C[i] = *var_t1++;
        temp_t3->unk_1C[i] = *var_t1++;
        temp_t3->unk_3C[i] = *var_t1++;
        temp_t3->unk_4C[i] = *var_t1++;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F568);
#endif

#if VERSION_CN
void func_8004168C_cn(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 buttonPressed = gControllerPressedButtons[0];
    u16 buttonCurrent = joycur[0];
    s16 var_t1;
    s16 var_t4;
    s32 temp_v1;
    s32 var_t0;
    s32 var_t5;
    s32 var_t6;

    if (arg3 != B_800E5924) {
        return;
    }

    var_t5 = 0;
    var_t6 = 0;
    var_t4 = 0;
    var_t0 = 2;

    if (arg3 == 0) {
        var_t1 = 0xF;
    } else if (arg3 == 1) {
        var_t1 = 1;
    } else if (arg3 == 2) {
        var_t4 = 1;
        var_t1 = 7;
    } else if (arg3 == 3) {
        var_t4 = -0x64;
        var_t1 = 0x64;
        var_t0 = 3;
    } else if (arg3 < 0xC) {
        var_t1 = 5;
    } else if (arg3 < 0x1B) {
        switch ((arg3 - 0xC) & 3) {
            case 0:
                var_t1 = 0xC;
                var_t0 = 3;
                break;

            case 1:
                var_t1 = 0x3E7;
                var_t5 = 1;
                var_t0 = 3;
                break;

            case 2:
                var_t1 = 0xA;
                var_t0 = 3;
                break;

            case 3:
                var_t1 = 0x3E7;
                var_t6 = 1;
                var_t0 = 3;
                break;

            default:
                var_t0 = 3;
                break;
        }
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            func_8003E3F0(gfxP, arg1 + (((var_t0 - B_800FC508_cn) - 1) * 6), arg2 + 8, 0x5E);
        }
    } else {
        s32 var_a2 = 1;
        s32 var_a1;

        var_a1 = 0;
        if (buttonPressed & L_JPAD) {
            var_a1++;
        }
        if (buttonPressed & R_JPAD) {
            var_a1 -= 1;
        }

        B_800FC508_cn = CLAMP(B_800FC508_cn + var_a1, 0, var_t0 - 1);

        if (var_t5 != 0) {
            switch (B_800E58C0[arg3 - 1]) {
                case 0x0:
                case 0x1:
                case 0x3:
                case 0x6:
                case 0x7:
                case 0x8:
                case 0x9:
                case 0xB:
                    var_a2 = 0;
                    break;
            }
        } else if (var_t6 != 0) {
            switch (B_800E58C0[arg3 - 1]) {
                case 0x0:
                case 0x1:
                case 0x2:
                    var_a2 = 0;
                    break;
            }
        }

        if (var_a2 != 0) {
            var_a1 = 0;
            if (buttonCurrent & U_JPAD) {
                var_a1++;
            }
            if (buttonCurrent & D_JPAD) {
                var_a1 -= 1;
            }

            B_800E58C0[arg3] = CLAMP(B_800E58C0[arg3] + D_800990C0_cn[B_800FC508_cn] * var_a1, var_t4, var_t1);
        }
    }
}
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD7F0);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD864);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD898);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD8CC);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD8E8);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD8F4);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD904);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD914);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD91C);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD928);
#endif

#if VERSION_US
INCLUDE_RODATA("asm/us/nonmatchings/main_segment/026550", STR_800AD92C);
#endif

#if VERSION_CN
ASM_RODATA;

const char STR_800C4710_cn[] = "@c2Character         WaitAttack Speed       Luck\n@c7 @m%c%02d:%-14s @m%c%02d:%-3s     "
                               "@m%c%02d:%-8s @m%c%03d%%\n\n";

const char STR_800C4784_cn[] = "@c2%-18s %-18s\n@c7 @m%c%02d:%-14s  @m%c%02d:%-14s\n\n";

const char STR_800C47B8_cn[] = "@c2  ExCondition        Sub   ExEffect       Sub\n";

const char STR_800C47EC_cn[] = "@c2%02d @c7@m%c%03d:%-14s ";

const char STR_800C4808_cn[] = "@m%c---   ";

const char STR_800C4814_cn[] = "@m%c%03d%c  ";

const char STR_800C4824_cn[] = "@m%c%03d:%-10s ";

const char STR_800C4834_cn[] = "@m%c---";

const char STR_800C483C_cn[] = "@m%c%03d";

const char STR_800C4848_cn[] = "\n";

const char STR_800C484C_cn[] = "@c3<- LogicMenu\t\t\t\t\t\tSpeedMenu ->";
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F7DC);
#endif

#if VERSION_CN
#if 0
void func_8003F7DC(Gfx **gxfP, s32 arg1, s32 arg2) {
    ? var_a3;
    s16 *temp_v0_2;
    s16 *var_s5;
    s16 *var_s6;
    s16 temp_a2_2;
    s16 temp_a3_2;
    s16 temp_t2;
    s16 temp_t3;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_t4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s3;
    s32 var_s3_2;
    s8 **var_s1;
    s8 **var_s2;
    s8 *temp_a2;

    func_8003E69C(gxfP, func_8004168C_cn, arg1, arg2);
    var_s0 = 4;
    var_s3 = 0;
    var_s6 = B_800E58C0 + 0xA;
    var_s5 = B_800E58C0 + 8;
    func_8003E6F8(STR_800C4710_cn, 0, B_800E58C0->unk_0, D_80099110_cn[B_800E58C0->unk_0], 1, (s32) B_800E58C0->unk_2, D_80099108_cn[B_800E58C0->unk_2], 2, (s32) B_800E58C0->unk_4, D_80099150_cn[B_800E58C0->unk_4], 3, (s32) B_800E58C0->unk_6);
    var_s2 = D_800990E8_cn + 4;
    var_s1 = D_800990E8_cn;
    do {
        temp_a3 = var_s0;
        temp_t3 = *var_s6;
        var_s6 += 4;
        temp_t2 = *var_s5;
        var_s5 += 4;
        temp_t4 = var_s0 + 1;
        var_s0 += 2;
        temp_a2 = *var_s2;
        var_s2 += 8;
        var_s3 += 1;
        func_8003E6F8(STR_800C4784_cn, *var_s1, temp_a2, temp_a3, (s32) temp_t2, D_800990D0_cn[temp_t2], temp_t4, (s32) temp_t3, D_800990D0_cn[temp_t3]);
        var_s1 += 8;
    } while (var_s3 < 4);
    func_8003E6F8(STR_800C47B8_cn);
    var_s3_2 = 0;
    do {
        temp_s0 = var_s0 + 1;
        temp_a3_2 = B_800E58C0[var_s0];
        func_8003E6F8(STR_800C47EC_cn, B_800E592C + var_s3_2 + 1, var_s0, temp_a3_2, D_80099170_cn[temp_a3_2]);
        temp_v0 = B_800E58C0[temp_s0].unk_-2;
        switch (temp_v0) {
            case 0x0:
            case 0x1:
            case 0x3:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xB:
                func_8003E6F8(STR_800C4808_cn, temp_s0);
                var_s0_2 = temp_s0 + 1;
                break;
            default:
                temp_v0_2 = &B_800E58C0[temp_s0];
                if (temp_v0_2->unk_-2 == 2) {
                    var_a3 = 0x25;
                } else {
                    var_a3 = 0x20;
                }
                func_8003E6F8(STR_800C4814_cn, temp_s0, temp_v0_2->unk_0, var_a3);
                var_s0_2 = temp_s0 + 1;
                break;
        }
        temp_a2_2 = B_800E58C0[var_s0_2];
        temp_s0_2 = var_s0_2 + 1;
        func_8003E6F8(STR_800C4824_cn, var_s0_2, temp_a2_2, D_800991A4_cn[temp_a2_2]);
        temp_v0_3 = B_800E58C0[temp_s0_2].unk_-2;
        if ((temp_v0_3 < 3) && (temp_v0_3 >= 0)) {
            func_8003E6F8(STR_800C4834_cn, temp_s0_2);
            var_s0 = temp_s0_2 + 1;
        } else {
            func_8003E6F8(STR_800C483C_cn, temp_s0_2, B_800E58C0[temp_s0_2].unk_0);
            var_s0 = temp_s0_2 + 1;
        }
        func_8003E6F8(STR_800AD5A8);
        var_s3_2 += 1;
    } while (var_s3_2 < 4);
    func_8003E6F8(STR_800C4848_cn);
    func_8003E6F8(STR_800C484C_cn);
    func_8003E6D8();
}
#else
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/026550", func_8003F7DC);
#endif
#endif

#if VERSION_US || VERSION_CN
void func_8003FB00(void) {
    s32 temp_s0 = joycur[0];
    s32 temp;

    temp = 0;
    if (gControllerPressedButtons[0] & L_CBUTTONS) {
        temp--;
    }
    if (gControllerPressedButtons[0] & R_CBUTTONS) {
        temp++;
    }

    B_800E5930 = WrapI(0, ENUM_800E5930_MAX, B_800E5930 + temp);

    temp = 0;
    if (temp_s0 & L_TRIG) {
        temp--;
    }
    if (temp_s0 & R_TRIG) {
        temp++;
    }

    switch (B_800E5930) {
        case ENUM_800E5930_0:
            B_800E5918 = WrapI(0, 0x1F, B_800E5918 + temp);
            func_8003EB20();
            func_8003F050(NULL, 0x10, 0x10);
            func_8003ECDC();
            break;

        case ENUM_800E5930_1:
            B_800E5924 = WrapI(0, 0x1C, B_800E5924 + temp);
            if (temp > 0) {
                if (B_800E5924 == 0) {
                    B_800E592C = WrapI(0, 0x10, B_800E592C + 4);
                    if (B_800E592C != 0) {
                        B_800E5924 = 0xC;
                    }
                } else if (B_800E5924 == 0xC) {
                    B_800E592C = 0;
                }
            } else if (temp < 0) {
                if (B_800E5924 == 0xB) {
                    if (B_800E592C != 0) {
                        B_800E5924 = 0x1B;
                        B_800E592C = WrapI(0, 0x10, B_800E592C - 4);
                    }
                } else if (B_800E5924 == 0x1B) {
                    B_800E592C = 0xC;
                }
            }

            func_8003F360();
            func_8003F7DC(NULL, 0x10, 0x10);
            func_8003F474();
            break;

        case ENUM_800E5930_2:
            B_800E5914 = WrapI(0, 0x54, B_800E5914 + temp);
            func_8003E8C8(NULL, 0x10, 0x10);
            break;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_8003FD0C(Gfx **gxfP) {
    switch (B_800E5930) {
        case ENUM_800E5930_0:
            func_8003F050(gxfP, 0x10, 0x10);
            break;

        case ENUM_800E5930_1:
            func_8003F7DC(gxfP, 0x10, 0x10);
            break;

        case ENUM_800E5930_2:
            func_8003E8C8(gxfP, 0x10, 0x10);
            break;
    }
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003FD88);
#endif

#if VERSION_CN
void func_8003FD88(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3) {
    u16 button = gControllerPressedButtons[0];
    struct_800E5938 *temp_a2 = &B_800E5938[B_800E5934];
    s32 temp_a0 = arg3 >> 5;
    s32 temp_a3 = arg3 & 0x1F;

    if (temp_a0 != B_800E596C) {
        return;
    }

    if (temp_a3 != B_800E5970[temp_a0]) {
        return;
    }

    if (gfxP != NULL) {
        B_800E5910++;
        if (B_800E5910 & 0x10) {
            func_8003E208(gfxP, 7);
            func_8003E3F0(gfxP, arg1 - 6, arg2, 0x3E);
        }
    } else if (button & 0x8000) {
        switch (temp_a0) {
            case 0x0:
                B_800E5934 = B_800E5970[0];
                return;

            case 0x1:
                temp_a2->unk_0 = B_800E5970[1];
                break;

            case 0x2:
                temp_a2->unk_1 = B_800E5970[2];
                break;

            case 0x3:
                temp_a2->unk_2 ^= 1 << B_800E5970[3];
                break;
        }
    }
}
#endif

ASM_RODATA;

#if VERSION_US
const char STR_800AD980[] RODATA = "ﾌﾟﾘﾝｾｽﾋﾟｰﾁ";

const char STR_800AD98C[] RODATA = "ｸｯﾊﾟ";

const char STR_800AD994[] RODATA = "ｶﾒｯｸ";

const char STR_800AD99C[] RODATA = "ﾊﾟｯｸﾝﾌﾗﾜｰ";

const char STR_800AD9A8[] RODATA = "ﾃﾚｻ";

const char STR_800AD9AC[] RODATA = "ﾊﾅﾁｬﾝ";

const char STR_800AD9B4[] RODATA = "ﾌﾟﾛﾍﾟﾗﾍｲﾎｰ";

const char STR_800AD9C0[] RODATA = "ﾁｮﾛﾌﾟｰ";

const char STR_800AD9C8[] RODATA = "ﾌﾟｸﾌﾟｸ";

const char STR_800AD9D0[] RODATA = "ﾎﾞﾑﾍｲ";

const char STR_800AD9D8[] RODATA = "ﾉｺﾉｺ";

const char STR_800AD9E0[] RODATA = "ﾏﾘｵ";

const char STR_800AD9E4[] RODATA = "ﾖｺｽﾞｷ";

const char STR_800AD9EC[] RODATA = "ﾀﾞｲﾚﾝｻﾈﾗｲ";

const char STR_800AD9F8[] RODATA = "ｺｳｹﾞｷ";

const char STR_800ADA00[] RODATA = "ﾊﾞﾗﾝｽ";

const char STR_800ADA08[] RODATA = "ｽﾋﾟｰﾄﾞ";

const char STR_800ADA10[] RODATA = "ﾓｯﾄﾓﾊﾔｲ";

const char STR_800ADA18[] RODATA = "ﾋｼﾞｮｳﾆﾊﾔｲ";

const char STR_800ADA24[] RODATA = "ﾊﾔｲ";

const char STR_800ADA28[] RODATA = "ﾌﾂｳ";

const char STR_800ADA2C[] RODATA = "ｵｿｲ";

const char STR_800ADA30[] RODATA = "ﾋｼﾞｮｳﾆｵｿｲ";

const char STR_800ADA3C[] RODATA = "ﾃﾞﾌｫﾙﾄ";

const char STR_800ADA44[] RODATA = "ｵｲｺﾐ";

const char STR_800ADA4C[] RODATA = "ﾃﾇｷ";

const char STR_800ADA50[] RODATA = "ｵｲｱｹﾞﾙ";

const char STR_800ADA58[] RODATA = "ｽﾋﾟｰﾄﾞｱｯﾌﾟ";

const char STR_800ADA64[] RODATA = "ﾄﾞｳﾖｳ";

const char STR_800ADA6C[] RODATA = "ﾁｮｳﾊﾂ";

const char STR_800ADA74[] RODATA = "ｸﾙｸﾙﾏﾜｽ";

const char STR_800ADA7C[] RODATA = "ﾏﾖｲ";

const char STR_800ADA80[] RODATA = "ﾗｯｸ";

const char STR_800ADA84[] RODATA = "ｶｳﾝﾀｰ";

const char STR_800ADA8C[] RODATA = "ｾﾝｾｲｺｳｹﾞｷ";
#endif

#if VERSION_CN
ASM_RODATA;

const char STR_800C48A0_cn[] = "ﾌﾟﾘﾝｾｽﾋﾟｰﾁ";

const char STR_800C48AC_cn[] = "ｸｯﾊﾟ";

const char STR_800C48B4_cn[] = "ｶﾒｯｸ";

const char STR_800C48BC_cn[] = "ﾊﾟｯｸﾝﾌﾗﾜｰ";

const char STR_800C48C8_cn[] = "ﾃﾚｻ";

const char STR_800C48CC_cn[] = "ﾊﾅﾁｬﾝ";

const char STR_800C48D4_cn[] = "ﾌﾟﾛﾍﾟﾗﾍｲﾎｰ";

const char STR_800C48E0_cn[] = "ﾁｮﾛﾌﾟｰ";

const char STR_800C48E8_cn[] = "ﾌﾟｸﾌﾟｸ";

const char STR_800C48F0_cn[] = "ﾎﾞﾑﾍｲ";

const char STR_800C48F8_cn[] = "ﾉｺﾉｺ";

const char STR_800C4900_cn[] = "ﾏﾘｵ";

const char STR_800C4904_cn[] = "ﾖｺｽﾞｷ";

const char STR_800C490C_cn[] = "ﾀﾞｲﾚﾝｻﾈﾗｲ";

const char STR_800C4918_cn[] = "ｺｳｹﾞｷ";

const char STR_800C4920_cn[] = "ﾊﾞﾗﾝｽ";

const char STR_800C4928_cn[] = "ｽﾋﾟｰﾄﾞ";

const char STR_800C4930_cn[] = "ﾓｯﾄﾓﾊﾔｲ";

const char STR_800C4938_cn[] = "ﾋｼﾞｮｳﾆﾊﾔｲ";

const char STR_800C4944_cn[] = "ﾊﾔｲ";

const char STR_800C4948_cn[] = "ﾌﾂｳ";

const char STR_800C494C_cn[] = "ｵｿｲ";

const char STR_800C4950_cn[] = "ﾋｼﾞｮｳﾆｵｿｲ";

const char STR_800C495C_cn[] = "ﾃﾞﾌｫﾙﾄ";

const char STR_800C4964_cn[] = "ｵｲｺﾐ";

const char STR_800C496C_cn[] = "ﾃﾇｷ";

const char STR_800C4970_cn[] = "ｵｲｱｹﾞﾙ";

const char STR_800C4978_cn[] = "ｽﾋﾟｰﾄﾞｱｯﾌﾟ";

const char STR_800C4984_cn[] = "ﾄﾞｳﾖｳ";

const char STR_800C498C_cn[] = "ﾁｮｳﾊﾂ";

const char STR_800C4994_cn[] = "ｸﾙｸﾙﾏﾜｽ";

const char STR_800C499C_cn[] = "ﾏﾖｲ";

const char STR_800C49A0_cn[] = "ﾗｯｸ";

const char STR_800C49A4_cn[] = "ｶｳﾝﾀｰ";

const char STR_800C49AC_cn[] = "ｾﾝｾｲｺｳｹﾞｷ";
#endif

#if VERSION_US || VERSION_CN
s32 func_8003FEE4(void) {
    s32 var_t1 = 0;
    struct_800E5938 sp8 = B_800E5938[B_800E5934];
    s32 i;

    for (i = 0; i < D_8008E558[3]; i++) {
        s32 var_a1;

        switch (sp8.unk_2 & (1 << i)) {
            case 0x1:
                var_a1 = (sp8.unk_0 == 2) && (sp8.unk_1 >= 4);
                break;

            case 0x2:
                var_a1 = sp8.unk_0 == 2;
                break;

            case 0x4:
                break;

            case 0x8:
                break;

            case 0x10:
                break;

            case 0x20:
                break;

            case 0x40:
                break;

            case 0x80:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x100:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x200:
                var_a1 = sp8.unk_1 < 2;
                break;

            case 0x400:
                var_a1 = (sp8.unk_1 >= 4);
                break;

            case 0x800:
                switch (B_800E5934) {
                    case 0x0:
                        break;

                    case 0x1:
                        var_a1 = sp8.unk_2 & 0x58;
                        break;

                    case 0x4:
                        var_a1 = sp8.unk_1 == 5;
                        break;

                    case 0x5:
                        var_a1 = sp8.unk_2 & 0x10;
                        break;

                    case 0x7:
                        var_a1 = sp8.unk_2 & 0x80;
                        break;

                    case 0x8:
                        var_a1 = sp8.unk_2 & 8;
                        break;

                    case 0x9:
                        var_a1 = (sp8.unk_1 >= 4);
                        break;

                    case 0xA:
                        var_a1 = 0;
                        if ((sp8.unk_1 >= 4) || (sp8.unk_2 & 0x402)) {
                            var_a1 = 1;
                        }
                        break;

                    case 0xB:
                        break;
                }
                break;
        }

        //! @bug: reading variable maybe not set
        if (var_a1 != 0) {
            sp8.unk_2 &= ~(1 << i);
        }
    }

    if (sp8.unk_2 & 0x800) {
        var_t1 += D_8008E568[B_800E5934];
    }

    if (sp8.unk_0 >= 0) {
        var_t1 += D_8008E574[sp8.unk_0];
    }

    if (sp8.unk_1 >= 0) {
        var_t1 += D_8008E57C[sp8.unk_1];
    }

    for (i = 0; i < 0xCU; i++) {
        if ((sp8.unk_2 >> i) & 1) {
            var_t1 += D_8008E584[i];
        }
    }

    return var_t1;
}
#endif

#if VERSION_US || VERSION_CN
void func_8004015C(void) {
    struct_800E5968 *temp = &B_800E5968;
    s32 i;

    for (i = 0; i < D_8008E558[0]; i++) {
        struct_ai_char_data *temp2 = &ai_char_data_org[i];
        struct_ai_char_data *var_a1 = &ai_char_data[i];
        struct_800E5938 *var_v1 = &B_800E5938[i];

        var_v1->unk_0 = D_8008E590[var_a1->unk_04[7]];
        var_v1->unk_1 = D_8008E598[var_a1->unk_01];

        if (!B_800E58BC) {
            var_v1->unk_2 = 0x800;
        }

        if (i == B_800E5934) {
            temp->unk_0 = D_8008E590[temp2->unk_04[7]];
            temp->unk_1 = D_8008E598[temp2->unk_01];
        }
    }

    B_800E58BC = true;
}
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_80040238);
#endif

#if VERSION_CN
void func_80040238(void) {
    s32 i;

    for (i = 0; i < D_8008E558[0]; i++) {
        struct_ai_char_data *temp_a2 = &ai_char_data_org[i];
        struct_ai_char_data *temp_t8 = &ai_char_data[i];
        struct_800E5938 *temp_t9 = &B_800E5938[i];
        s32 j;
        s32 index;

        for (j = 0; j < 8; j++) {
            temp_t8->unk_04[j] = D_8008E538[temp_t9->unk_0];
        }

        //! FAKE: renaming D_80099290_cn to D_8008E540 produces different codegen
        temp_t8->unk_01 = D_80099290_cn[temp_t9->unk_1];

        index = 0;

        if (temp_t9->unk_2 & 0x800) {
            for (j = 0; j < 4; j++) {
                temp_t8->unk_0C[index] = temp_a2->unk_0C[j];
                temp_t8->unk_1C[index] = temp_a2->unk_1C[j];
                temp_t8->unk_3C[index] = temp_a2->unk_3C[j];
                temp_t8->unk_4C[index] = temp_a2->unk_4C[j];
                index++;
            }
        }

        for (j = 0; j < D_8008E558[3]; j++) {
            switch (temp_t9->unk_2 & (1 << j)) {
                case 0x1:
                    temp_t8->unk_0C[index] = 0xC;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 4;
                    temp_t8->unk_4C[index] = 1;
                    index++;

                    temp_t8->unk_0C[index] = 0xC;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 8;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x2:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 8;
                    temp_t8->unk_4C[index] = 7;
                    index++;
                    break;

                case 0x4:
                    temp_t8->unk_02 = 0x32;
                    break;

                case 0x8:
                    temp_t8->unk_0C[index] = 2;
                    temp_t8->unk_1C[index] = 0x21;
                    temp_t8->unk_3C[index] = 2;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x10:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x20:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 1;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x40:
                    temp_t8->unk_0C[index] = 3;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 3;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x80:
                    temp_t8->unk_0C[index] = 1;
                    temp_t8->unk_1C[index] = 0;
                    temp_t8->unk_3C[index] = 7;
                    temp_t8->unk_4C[index] = 0;
                    index++;
                    break;

                case 0x100:
                    temp_t8->unk_0C[index] = 4;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 6;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x200:
                    temp_t8->unk_0C[index] = 5;
                    temp_t8->unk_1C[index] = 5;
                    temp_t8->unk_3C[index] = 5;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;

                case 0x400:
                    temp_t8->unk_0C[index] = 0xA;
                    temp_t8->unk_1C[index] = 0xA;
                    temp_t8->unk_3C[index] = 4;
                    temp_t8->unk_4C[index] = 1;
                    index++;
                    break;
            }
        }

        for (j = index; j < 0x10; j++) {
            temp_t8->unk_0C[j] = 0;
            temp_t8->unk_1C[j] = 0;
            temp_t8->unk_3C[j] = 0;
            temp_t8->unk_4C[j] = 0;
        }
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_80040578(void) {
    s32 vertical = 0;
    s32 horizontal = 0;

    if (gControllerPressedButtons[0] & L_JPAD) {
        horizontal--;
    }
    if (gControllerPressedButtons[0] & R_JPAD) {
        horizontal++;
    }

    if (gControllerPressedButtons[0] & U_JPAD) {
        vertical--;
    }
    if (gControllerPressedButtons[0] & D_JPAD) {
        vertical++;
    }

    B_800E596C = WrapI(0, 4, B_800E596C + horizontal);
    B_800E5970[B_800E596C] = WrapI(0, D_8008E558[B_800E596C], B_800E5970[B_800E596C] + vertical);
}
#endif

#if VERSION_US
const char STR_800ADAC8[] = "<ﾄｸｼｭ>";

const char STR_800ADAD0[] = "<ｽﾋﾟｰﾄﾞ>";

const char STR_800ADADC[] = "<ｾｲｶｸ>";

const char STR_800ADAE4[] = "<ｷｬﾗｸﾀｰ>";
#endif

#if VERSION_CN
const char STR_800C49E8_cn[] = "<ﾄｸｼｭ>";

const char STR_800C49F0_cn[] = "<ｽﾋﾟｰﾄﾞ>";

const char STR_800C49FC_cn[] = "<ｾｲｶｸ>";

const char STR_800C4A04_cn[] = "<ｷｬﾗｸﾀｰ>";
#endif

#if VERSION_US || VERSION_CN
const char STR_800ADAF0[] = "@c2[ｷｬﾗｸﾀｰｴﾃﾞｨｯﾄ]\n\n";

const char STR_800ADB04[] = "@c2ﾂﾖｻ ";

const char STR_800ADB0C[] = "%c";

const char STR_800ADB10[] = "@c2%s\n";

const char STR_800ADB18[] = "@m%c@c%c%s\n";

const char STR_800ADB24[] = "@m%c@c%c%c:%s\n";
#endif

#if VERSION_US || VERSION_CN
void func_80040624(Gfx **gfxP, s32 arg1, s32 arg2) {
    struct_800E5938 *temp_s5 = &B_800E5938[B_800E5934];
    s32 var_s0 = CLAMP(func_8003FEE4() / 10, 0, 10);
    s32 var_a2;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s7;

    func_8003E69C(gfxP, func_8003FD88, arg1, arg2);

    func_8003E6F8(STR_800ADAF0);
    func_8003E6F8(STR_800ADB04);

    for (var_s1 = 0; var_s1 < var_s0; var_s1++) {
        func_8003E6F8(STR_800ADB0C, 0x83);
    }

    for (; var_s1 < 10; var_s1++) {
        func_8003E6F8(STR_800ADB0C, 0x82);
    }

    func_8003E6D8();

    arg1 += 6;
    arg2 += 0x20;

    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        func_8003E69C(gfxP, func_8003FD88, arg1, arg2);

        func_8003E6F8(STR_800ADB10, D_8008E5A0[var_s1]);

        var_s2 = var_s1 << 5;

        for (var_s0_2 = 0; var_s0_2 < D_8008E558[var_s1]; var_s0_2++) {
            var_a2 = 0x37;

            switch (var_s1) {
                case 0:
                    if (var_s0_2 == B_800E5934) {
                        var_a2 = 0x33;
                    }
                    break;

                case 1:
                    if (var_s0_2 == temp_s5->unk_0) {
                        var_a2 = 0x33;
                    } else if (var_s0_2 == B_800E5968.unk_0) {
                        var_a2 = D_8008E5B0;
                    }
                    break;

                case 2:
                    if (var_s0_2 == temp_s5->unk_1) {
                        var_a2 = 0x33;
                    } else if (var_s0_2 == B_800E5968.unk_1) {
                        var_a2 = D_8008E5B0;
                    }
                    break;

                case 3:
                    var_s7 = 0x80;
                    if ((temp_s5->unk_2 >> var_s0_2) % 2 != 0) {
                        var_a2 = 0x33;
                        var_s7 = 0x81;
                    } else if (var_s0_2 == 0xB) {
                        var_a2 = D_8008E5B0;
                    }
                    break;
            }

            switch (var_s1) {
                case 0:
                case 1:
                case 2:
                    func_8003E6F8(STR_800ADB18, var_s2, var_a2, D_8008E548[var_s1][var_s0_2]);
                    var_s2 += 1;
                    break;

                case 3:
                    func_8003E6F8(STR_800ADB24, var_s2, var_a2, var_s7, D_8008E548[var_s1][var_s0_2]);
                    var_s2 += 1;
                    break;
            }
        }

        func_8003E6D8();
        arg1 += D_8008E5B4[var_s1] * 6;
    }
}
#endif

#if VERSION_US || VERSION_CN
void func_800409A0(void) {
    func_80040578();
    func_8004015C();
    func_80040624(NULL, 0x20, 0x20);
    func_80040238();
}
#endif

#if VERSION_US || VERSION_CN
void func_800409DC(Gfx **gfxP) {
    func_80040624(gfxP, 0x20, 0x20);
}
#endif
