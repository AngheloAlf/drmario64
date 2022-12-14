#include "ultra64.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

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

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E1E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E208);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E278);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E3F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E430);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E4AC);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E4B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E69C);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E6D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E6F8);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E730);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003E8C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003EB20);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003ECDC);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003EEA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003F050);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003F360);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003F474);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003F568);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD7F0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD864);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD898);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD8CC);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD8E8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD8F4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD904);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD914);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD91C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD928);

INCLUDE_RODATA("asm/nonmatchings/main_segment/014590", STR_800AD92C);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003F7DC);

ASM_RODATA;

const char STR_800AD980[] RODATA = "??????????????????????????????";

const char STR_800AD98C[] RODATA = "????????????";

const char STR_800AD994[] RODATA = "????????????";

const char STR_800AD99C[] RODATA = "???????????????????????????";

const char STR_800AD9A8[] RODATA = "?????????";

const char STR_800AD9AC[] RODATA = "???????????????";

const char STR_800AD9B4[] RODATA = "??????????????????????????????";

const char STR_800AD9C0[] RODATA = "??????????????????";

const char STR_800AD9C8[] RODATA = "??????????????????";

const char STR_800AD9D0[] RODATA = "???????????????";

const char STR_800AD9D8[] RODATA = "????????????";

const char STR_800AD9E0[] RODATA = "?????????";

const char STR_800AD9E4[] RODATA = "???????????????";

const char STR_800AD9EC[] RODATA = "???????????????????????????";

const char STR_800AD9F8[] RODATA = "???????????????";

const char STR_800ADA00[] RODATA = "???????????????";

const char STR_800ADA08[] RODATA = "??????????????????";

const char STR_800ADA10[] RODATA = "?????????????????????";

const char STR_800ADA18[] RODATA = "???????????????????????????";

const char STR_800ADA24[] RODATA = "?????????";

const char STR_800ADA28[] RODATA = "?????????";

const char STR_800ADA2C[] RODATA = "?????????";

const char STR_800ADA30[] RODATA = "???????????????????????????";

const char STR_800ADA3C[] RODATA = "??????????????????";

const char STR_800ADA44[] RODATA = "????????????";

const char STR_800ADA4C[] RODATA = "?????????";

const char STR_800ADA50[] RODATA = "??????????????????";

const char STR_800ADA58[] RODATA = "??????????????????????????????";

const char STR_800ADA64[] RODATA = "???????????????";

const char STR_800ADA6C[] RODATA = "???????????????";

const char STR_800ADA74[] RODATA = "?????????????????????";

const char STR_800ADA7C[] RODATA = "?????????";

const char STR_800ADA80[] RODATA = "?????????";

const char STR_800ADA84[] RODATA = "???????????????";

const char STR_800ADA8C[] RODATA = "???????????????????????????";

ASM_TEXT;

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003FB00);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003FD0C);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003FD88);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8003FEE4);

ASM_RODATA;

const char STR_800ADAC8[] RODATA = "<????????????>";

const char STR_800ADAD0[] RODATA = "<??????????????????>";

const char STR_800ADADC[] RODATA = "<????????????>";

const char STR_800ADAE4[] RODATA = "<??????????????????>";

const char STR_800ADAF0[] RODATA = "@c2[????????????????????????????????????]\n\n";

const char STR_800ADB04[] RODATA = "@c2????????? ";

const char STR_800ADB0C[] RODATA = "%c";

const char STR_800ADB10[] RODATA = "@c2%s\n";

const char STR_800ADB18[] RODATA = "@m%c@c%c%s\n";

const char STR_800ADB24[] RODATA = "@m%c@c%c%c:%s\n";

ASM_TEXT;

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_8004015C);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_80040238);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_80040578);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_80040624);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_800409A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/014590", func_800409DC);
