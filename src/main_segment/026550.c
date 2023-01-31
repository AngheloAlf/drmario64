#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"

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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003E730);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003E8C8);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003EB20);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003ECDC);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003EEA4);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F050);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F360);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F474);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F568);
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

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003F7DC);
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

ASM_TEXT;

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003FB00);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003FD0C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003FD88);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8003FEE4);
#endif

ASM_RODATA;

#if VERSION_US
const char STR_800ADAC8[] RODATA = "<ﾄｸｼｭ>";

const char STR_800ADAD0[] RODATA = "<ｽﾋﾟｰﾄﾞ>";

const char STR_800ADADC[] RODATA = "<ｾｲｶｸ>";

const char STR_800ADAE4[] RODATA = "<ｷｬﾗｸﾀｰ>";

const char STR_800ADAF0[] RODATA = "@c2[ｷｬﾗｸﾀｰｴﾃﾞｨｯﾄ]\n\n";

const char STR_800ADB04[] RODATA = "@c2ﾂﾖｻ ";

const char STR_800ADB0C[] RODATA = "%c";

const char STR_800ADB10[] RODATA = "@c2%s\n";

const char STR_800ADB18[] RODATA = "@m%c@c%c%s\n";

const char STR_800ADB24[] RODATA = "@m%c@c%c%c:%s\n";
#endif

ASM_TEXT;

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_8004015C);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_80040238);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_80040578);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_80040624);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_800409A0);
#endif

#if VERSION_US
INCLUDE_ASM("asm/us/nonmatchings/main_segment/026550", func_800409DC);
#endif
