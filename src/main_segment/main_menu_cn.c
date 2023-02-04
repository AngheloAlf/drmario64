#include "libultra.h"
#include "include_asm.h"
#include "macros_defines.h"
#include "unknown_structs.h"
#include "main_segment_functions.h"
#include "main_segment_variables.h"
#include "boot_functions.h"
#include "boot_variables.h"
#include "rom_offsets.h"
#include "audio/audio_stuff.h"
#include "buffers.h"
#include "libc/assert.h"
#include "graphic.h"

#if VERSION_CN
INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048660_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048698_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800486D4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004872C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800487B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048854_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004892C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800489B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048A54_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048AD8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048B7C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048C54_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048D88_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048E58_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048F20_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048F78_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80048FEC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049034_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004907C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800490C4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800490D0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800490DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800490E8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800490F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004910C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049124_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800491A4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049274_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800492F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004947C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049528_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049690_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049754_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049988_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049AB8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049B8C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049D00_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4AD0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4AE0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4AF8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4B10_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4B38_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4B60_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4B80_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C4BBC_cn);
#endif

#if VERSION_CN
ASM_RODATA;

const char _mesP1[] = "这是单人游戏模式。~z";

const char _mes2P[] = "这是双人游戏模式。~z";

const char _mes4P[] = "这是最多四人的多人~n游戏模式。~z";

const char _mesOpt[] = "这里有各种游戏设定~n和选项。~z";

const char _mesSt[] =
    "发生在马力欧医生和~n感冒狂人之间的精彩~n故事。~w2~h通过送给对手垃圾,~n逼迫他们退出游戏。~w2~h或消灭自己所有的病~"
    "n毒来赢得胜利。 "
    "~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesLv[] =
    "持续游戏直到在一局~n中失败。~w2~h消灭所有病毒才能过~n关。~w2~h游戏难度等级越高,~n需要消灭的病毒就越~n多。~w2~"
    "h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesVsCom[] =
    "这是你和电脑对抗的~n机会。~w2~h选定任意一个你喜欢~n的对手开始游戏。~w2~h通过送给对手垃圾, "
    "~n逼迫他们退出游戏。~w2~h或消灭自己所有的~n病毒来赢得胜利。 "
    "~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesVcFlash[] =
    "消灭所有的闪光病毒~n以取胜。~w2~h选定任意一个你喜欢~n的对手开始游戏。~w2~h通过送给对手垃圾, "
    "~n逼迫他们退出游戏~w2~h或消灭自己所有的病~n毒来赢得胜利。 "
    "~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesLvTaiQ[] =
    "在这个模式中病毒会~n高速繁殖。~w2~h连消病毒可以降低~n它们的繁殖速度。~w2~h消灭病毒以保持瓶子~n清洁。~w2~"
    "h按L键可以加快病毒~n的繁殖。~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~"
    "h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesLvTimeAt[] =
    "尽力在限定时间内争~n取最高分。~w2~h同时消灭很多病毒可~n争取最高分。~w2~h再补充一点！~n游戏中可以按任意~"
    "n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesNs1[] = "请输入你的名字。~w2~h如果是第一次游戏，~n请选择：~n新游戏或玩家。~w2~h~z";

const char _mesNs2[] = "请输入你的名字。~z";

const char _mesVsMan[] =
    "和另外一个玩家比赛。~w2~h通过送给对手垃圾,~n逼迫他们退出游戏~w2~h或消灭自己所有的病~n毒来赢得胜利。 "
    "~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesVmFlash[] =
    "消灭所有的闪光病毒~n以取胜。~w2~h完成连消能送给对手垃圾。~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~"
    "n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesVmTimeAt[] =
    "尽力在限定时间内取~n得最高分。~w2~h一次消灭多个病毒可~n得高分。~w2~h再补充一点！~n游戏中可以按任意~"
    "n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesVsNum[] = "有多少玩家？~z";

const char _mesVs4P[] =
    "四人自由比赛。~w2~h通过送给对手垃圾,~n逼迫他们退出游戏~w2~h或消灭自己所有的病~n毒来赢得胜利。 "
    "~w2~h连消的颜色决定你的~n垃圾药丸送到哪里去。~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~"
    "n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mes4PTag[] =
    "二对二模式。~w2~h通过送给对手垃圾, ~n逼迫他们退出游戏，~w2~h或消灭自己所有的病~n毒来赢得胜利。 "
    "~w2~h连消的颜色决定你的~n垃圾药丸送到哪里去。~w2~h送给同伴的垃圾药丸~n放置在你们~w2~h小型垃圾箱中，然后~n又加入到~"
    "w2~h你或你的同伴随后送~n给对手的垃圾中去。~w2~h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~"
    "w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mes4PFlash[] =
    "消灭所有的闪光病毒~n以取胜。~w2~h你可以将对手的屏幕~n塞满垃圾。~w2~h连消的颜色决定你的~n垃圾药丸送到哪里去。~w2~"
    "h再补充一点！~n游戏中可以按任意~n一个Ｃ键来观察药丸~n落下的位置，~w2~h再按一次可以取消这~n个效果。~w2~h~z";

const char _mesRec[] = "在这里可以看游戏纪~n录。~z";

const char _mesTutol[] = "在这里可以学习游戏~n规则和技巧。~z";

const char _mesName[] = "在这里可以更改或删~n除你的名字。~z";

const char _mesVsCnt[] = "在这里可以设置一盘~n比赛的局数。~z";

const char _mesSnd[] = "在这里可以进行声音~n设置。~w2~h你也可以欣赏游戏音~n乐和音效。~w2~h~z";

const char _mesBak[] = "在这里可以删除所有~n存档。~z";

const char _mesMisc[] = "在这里可以设置其他~n游戏项目。~z";

const char _mesRecMs1[] = "你想看哪一条纪录？~z";

const char _mesRecMs2[] = "你想看哪个模式的~n纪录？~z";

const char _mesRule1[] = "这些是控制键的~n讲解。~z";

const char _mesRule2[] = "这是游戏的基本~n讲解。~z";

const char _mesRule3[] = "这些是双人游戏的~n讲解。~z";

const char _mesRule4[] = "这些是四人游戏的~n讲解。~z";

const char _mesKotu[] = "让我来给你一些~n提示。~z";

const char _mesNameSel[] = "你想对那个名字进行~n什么操作？~z";

const char _mesNameErase[] =
    "如果你删除那个名字，~n那么就把相关的游戏~n数据也一同删掉了。~w2~h你真的想删除这个~n名字?~w2~h~z";

const char _mesNameErase2[] = "名字和游戏数据删除~n完毕。~z";

const char _mesVsCnt2[] = "选择一盘比赛中的~n局数。 ~z";

const char _mesSound[] = "用十字键选择，~nA键确定。~z";

const char _mesStereo[] = "音乐以立体声播放。~z";

const char _mesMono[] = "音乐以单声道播放。~z";

const char _mesDoErase[] = "删除所有的游戏数据。~w2~h你真的想删除所有的~n游戏数据吗？~w2~h~z";

const char _mesDoErase1[] = "所有存储的游戏数据~n删除完毕。~z";

const char _mesNoCont2[] = "请关闭电源，插入更~n多共游机。~z";

const char _mesNoCont3[] = "请关闭电源，插入更~n多共游机。~z";

const char _mesNoCont4[] = "请关闭电源，插入更~n多共游机。~z";

const char _mesScore[] = "你可以打开或关闭屏~n幕上的得分显示。~z";

const char _mesScoreOnOff[] = "请选择得分显示模式。~z";

const char STR_800C5B80_cn[] = "存储中~n请勿关闭电源.~z";

const char STR_800C5B98_cn[] = "删除中~n请勿关闭电源.~z";
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5BB0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5BB4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5BC8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5BCC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049E68_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049F38_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80049FD4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A008_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A19C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A240_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A2BC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A498_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A4EC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5CF8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5D70_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5DA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004A5D0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004AF9C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B1C8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B230_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B294_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B2F0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B7B4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B88C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B928_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004B9B4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BC10_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BCB4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BD1C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BD64_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BD90_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004BF44_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C008_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C0AC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C304_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C34C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C378_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C538_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C5A8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C648_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C738_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C778_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C7A4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5EE4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C5F28_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6160_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C616C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6170_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6184_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6190_cn);
#endif

#if VERSION_CN
ASM_RODATA;

const char STR_800AFB08[] = "确定";

const char STR_800AFB10[] = "取消";
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C61B0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C61B4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C61D0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C61E0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C61E4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6200_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004C960_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004CBB4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004CC50_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004CE4C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D174_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D218_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D280_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D488_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6228_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D588_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D760_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D874_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D918_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004D980_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DA14_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DAA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DE20_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DE8C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DEB8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DEE0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DF44_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004DFA0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6248_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6270_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E32C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E4F0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E54C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E6DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E714_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004E7CC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EAE4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EB38_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EC80_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004ED54_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EDE0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EF48_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004EF9C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004F080_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004F374_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004F3D0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004F79C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004F888_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004FAD4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004FF18_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8004FF6C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800500B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050180_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050224_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800504BC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050510_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050670_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050814_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800508F8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050B48_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6284_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62AC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62B4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62BC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62D0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62D8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62DC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62EC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C62F4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6304_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C636C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C637C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C638C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C639C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63A0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63AC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63B0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63BC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63C0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63CC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63D0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63DC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63E0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63EC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63F0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C63FC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6404_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80050BA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800510A8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800510F8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800511F0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80051440_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800517C0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80051E48_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80051E9C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80051EEC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80052178_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80052420_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800525F8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C64BC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C64F8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6538_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6540_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6548_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C655C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C656C_cn);
#endif

#if VERSION_CN
extern const char *_tblMain_5279[];
extern const char *_tblPlay1_5280[];
extern const char *_tblPlay2_5281[];
extern const char *_tblBaTyp_5282[];
extern const char *_tblOpt_5283[];
extern const char *_tblTutol_5284[];
extern const char *_tblSound_5285[];
extern const char *_tblMisc_5286[];
extern const char *_loopTbl_5287[];

bool menuMain_setMsgStr(MenuMain *menuMain, enum MainMenuMode mode, s32 arg2) {
    bool var_s4 = false;
    const char **var_a3 = NULL;
    const char *var_s2 = NULL;
    s32 var_s1;

    switch (mode) {
        case MAINMENUMODE_MENUMAIN_0:
            var_a3 = _tblMain_5279;
            break;
        case MAINMENUMODE_1:
            var_a3 = _tblPlay1_5280;
            break;
        case MAINMENUMODE_22:
            var_a3 = _tblPlay2_5281;
            break;
        case MAINMENUMODE_35:
            var_s2 = _mesVsNum;
            break;
        case MAINMENUMODE_46:
            var_a3 = _tblOpt_5283;
            break;
        case MAINMENUMODE_70:
            var_a3 = _tblMisc_5286;
            break;
        case MAINMENUMODE_73:
            var_s2 = _mesScoreOnOff;
            break;
        case MAINMENUMODE_36:
        case MAINMENUMODE_37:
        case MAINMENUMODE_38:
        case MAINMENUMODE_39:
            var_a3 = _tblBaTyp_5282;
            break;
        case MAINMENUMODE_59:
            var_a3 = _tblTutol_5284;
            break;
        case MAINMENUMODE_71:
            var_s2 = _tblSound_5285[menuMain->unk_1C64.unk_004];
            break;
        case MAINMENUMODE_47:
            var_s2 = _mesRecMs1;
            break;
        case MAINMENUMODE_48:
        case MAINMENUMODE_MENURANK_55:
            var_s2 = _mesRecMs2;
            break;
        case MAINMENUMODE_62:
            var_s2 = _mesNameSel;
            break;
        case MAINMENUMODE_65:
            var_s2 = _mesNameErase;
            break;
        case MAINMENUMODE_66:
            var_s2 = _mesNameErase2;
            break;
        case MAINMENUMODE_72:
            var_s2 = _mesVsCnt2;
            break;
        case MAINMENUMODE_67:
        case MAINMENUMODE_68:
            var_s2 = _mesDoErase;
            break;
        case MAINMENUMODE_69:
            var_s2 = _mesDoErase1;
            break;
        case MAINMENUMODE_2:
        case MAINMENUMODE_5:
        case MAINMENUMODE_8:
        case MAINMENUMODE_11:
        case MAINMENUMODE_14:
        case MAINMENUMODE_18:
        case MAINMENUMODE_23:
        case MAINMENUMODE_27:
        case MAINMENUMODE_31:
            var_s2 = _mesNs1;
            break;
        case MAINMENUMODE_61:
            var_s2 = _mesNs2;
            break;

        default:
            break;
    }
    if (var_a3 != NULL) {
        var_s2 = var_a3[arg2];
    }
    var_s1 = 0;
    while (var_s1 < 0x10U) {
        if ((var_s2 == _loopTbl_5287[var_s1]) && msgWnd_isEnd(&menuMain->unk_2308)) {
            menuMain->unk_2304 = NULL;
        }
        var_s1 += 1;
    }

    if (var_s2 != menuMain->unk_2304) {
        msgWnd_clear(&menuMain->unk_2308);
        if (var_s2 != NULL) {
            msgWnd_addStr(&menuMain->unk_2308, var_s2);
            var_s4 = true;
        }
        menuMain->unk_2304 = var_s2;
    }
    return var_s4;
}
#endif

#if VERSION_CN
INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C66B8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C66C8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C66E0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C66EC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C66FC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6708_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C671C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6724_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C673C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6748_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C675C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6768_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6770_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C677C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80052B94_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80052CFC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80053228_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800532BC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69A0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69B0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69C8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69E0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69EC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69F0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C69F4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A08_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A0C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A10_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A2C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A30_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A34_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A50_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A54_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A68_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A7C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A88_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6A94_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6AA0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6AAC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6AB4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6ACC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6AD8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800532E4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80054AB8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6FC8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80054E34_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800556AC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80055888_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005591C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80055970_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800559F8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80055F30_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80055FB8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80055FD8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80056024_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005653C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80056A70_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005734C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800573A0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005785C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800578E4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80057CA8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80058054_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800584E8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6FE8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C6FEC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7078_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7088_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7098_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C70D4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C70E4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C70F4_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7184_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C718C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005853C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800589E0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80058A3C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80058AB8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80058E0C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80058F40_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C72D4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80059078_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800593C0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800596C4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80059AB0_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C73FC_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C740C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7414_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7424_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C742C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C743C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C744C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80059BC4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A208_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A29C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A310_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A3C4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A478_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A77C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005A8E4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005AF08_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005B044_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005B1B4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005B208_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005B56C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800B0F5C);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005B594_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005BDD0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005BFA4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C348_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C380_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C3AC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C4F0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C52C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C558_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C77E0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C780_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005C8B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005CC68_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", _posX_0_9712);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", _posX_1_9713);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", _posX_2_9714);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", _posX_4_9715);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7888_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005CF4C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D004_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D030_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D1BC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D1FC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D228_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D468_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D564_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D5F4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D6D0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D860_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005D9A4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005DAE4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005DC98_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7898_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C78A8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C78B4_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005DE18_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005DF38_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005E1A0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005E2A0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005E4B0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005E76C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7908_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7910_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7920_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7930_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7940_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7950_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C795C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7968_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7974_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7980_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C798C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7998_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C79A8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C79B8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C79C8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C79D8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C79E8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005E80C_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7A70_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005EEFC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005F174_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005F42C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005F5F8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005F988_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FA40_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FA9C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FAF8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FB80_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FC14_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FCA8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FD3C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FD70_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FD88_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDB0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDC0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDD0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDE0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FDF0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE00_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE10_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE20_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE30_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE40_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE50_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE60_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE70_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE80_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FE90_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FEA0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FEA8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FECC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FEF0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF14_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF28_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF3C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF50_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF64_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FF90_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_8005FFE8_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80060490_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7AA8_cn);

INCLUDE_RODATA("asm/cn/nonmatchings/main_segment/main_menu_cn", RO_800C7AB0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800604E0_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_800605DC_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80060848_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80060A14_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80060D84_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", func_80060F8C_cn);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", main_menu);

INCLUDE_ASM("asm/cn/nonmatchings/main_segment/main_menu_cn", graphic_menu);
#endif
