#ifndef MAIN_SEGMENT_FUNCTIONS_H
#define MAIN_SEGMENT_FUNCTIONS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unknown_structs.h"
#include "unk.h"


// void func_80029C50();
void func_80029ED0(struct_800EB670* arg0, u8 arg1, u8 retraceCount);
// void func_8002A0CC();
// void func_8002A0D4();
void func_8002A0DC(struct_800EB670*);
// void func_8002A184();
// void func_8002A1DC();
void func_8002A26C(struct_800EB670 *arg0, OSMesg msg);
void func_8002A2B8(struct_800EB670*);
void func_8002A3F4(struct_800EB670 *arg0, OSMesg arg1);
void func_8002A4D8(struct_800EB670*);
// void func_8002A51C();
UNK_TYPE func_8002A5B0(UNK_TYPE);
// void func_8002A700();
// void func_8002A8F8();
s8 func_8002A954();
// void func_8002AA80();
// void func_8002AAD8();
// void func_8002AAE8();
// void func_8002AB28();
// void func_8002ABC0();
// void func_8002AC64();
// void func_8002ACE0();
void func_8002AD38(struct_800EB670* arg0);
// void func_8002AE58();
// void func_8002AF7C();
// void func_8002AFA4();
// void func_8002AFC4();
// void func_8002AFE4();
// void func_8002B000();
// void func_8002B028();
// void func_8002B078();
// void func_8002B098();
// void func_8002B0E4();
// void func_8002B100();
// void func_8002B13C();
// void func_8002B15C();
// void func_8002B178();
// void func_8002B194();
// void func_8002B1B4();
// void func_8002B344();
// void func_8002B370();
// void func_8002B394();
void func_8002B490(UNK_TYPE *);
void func_8002B4BC(struct_800EB670 *);
// void func_8002B5E4();
// void func_8002B710();
// void func_8002B728();
// void func_8002B754();
void func_8002B7A8(struct_800EB670 *arg0);
// void func_8002B800();
// void func_8002B834();
// void func_8002B9D8();
// void func_8002BAB8();
// void func_8002BBD8();
// void func_8002BC58();
// void func_8002BD20();
// void func_8002BEE4();
// void func_8002BF90();
// void func_8002C048();
// void func_8002C1E8();
// void func_8002C388();
// void func_8002C4EC();
// void func_8002C688();
// void func_8002C7C0();
// void func_8002C914();
// void func_8002CA68();
// void func_8002CD08();
// void func_8002CF04();
// void func_8002D170();
bool func_8002D3B0(romoffset_t segmentRom, size_t segmentSize, void *wbank);
// void func_8002D428();
// void func_8002D4A4();
// void func_8002D4F8();
// void func_8002D51C();
// void func_8002D554();
// void func_8002D58C();
// void func_8002D5C4();
// void func_8002D5FC();
// void func_8002D634();
// void func_8002D66C();
// void func_8002D6A4();
// void func_8002D710();
// void func_8002D720();
// void func_8002D768();
// void func_8002D7C4();
// void func_8002D7E0();
// void func_8002D810();
// void func_8002D840();
// void func_8002D870();
// void func_8002D8A0();
void func_8002D8D0(romoffset_t segmentRom, void *segmentVram, size_t segmentSize);
// void func_8002D984();
// void func_8002D9E4();
// void func_8002DA48();
u32 func_8002DB20();
// void func_8002DC10();
u32 func_8002E230();
// void func_8002E830();
// void func_8002E8B0();
// void func_8002EB00();
// void func_8002EB74();
// void func_8002ED14();
// void func_8002ED2C();
UNK_TYPE func_8002EDDC();
// void func_8002EFF0();
// void func_8002F180();
// void func_8002F2EC();
// void func_8002F924();
// void func_8002F9CC();
// void func_8002FDF0();
// void func_80030810();
// void func_800308FC();
// void func_800310C8();
// void func_80031218();
// void func_8003135C();
// void func_800313F0();
// void func_8003145C();
// void func_8003151C();
// void func_8003157C();
// void func_800325AC();
// void func_80033474();
// void func_80034200();
// void func_80034310();
// void func_80034380();
// void func_80034798();
// void func_80034AB0();
// void func_80034D54();
// void func_80034E80();
// void func_8003510C();
// void func_80035234();
// void func_80035494();
// void func_80035704();
// void func_80035CF4();
// void func_800362A0();
// void func_80036560();
// void func_800365B0();
// void func_800365C8();
// void func_8003661C();
// void func_800366A4();
// void func_80036718();
// void func_8003678C();
// void func_800367E0();
// void func_800367F0();
// void func_800367FC();
// void func_80036808();
// void func_80036818();
// void func_800369BC();
// void func_80036A64();
// void func_80036B6C();
// void func_80036BC8();
// void func_80036C58();
// void func_80036CFC();
// void func_80036D58();
// void func_80036DB4();
// void func_80036E10();
// void func_80036E6C();
// void func_80036EC8();
// void func_80036F1C();
// void func_80036F70();
// void func_80037068();
// void func_80037248();
// void func_80037294();
// void func_800372E0();
// void func_8003732C();
// void func_80037378();
// void func_800373C8();
// void func_80037418();
// void func_80037468();
// void func_800374B8();
// void func_80037710();
// void func_8003772C();
// void func_80037748();
// void func_80037764();
// void func_80037780();
// void func_8003779C();
// void func_80037808();
// void func_800378B0();
// void func_80037950();
// void func_800379D4();
// void func_80037A5C();
// void func_80037B74();
// void func_80037C7C();
// void func_80037D40();
// void func_80037DF0();
// void func_80037EB4();
// void func_80037F64();
// void func_80038038();
// void func_800380F0();
// void func_80038168();
// void func_800381DC();
// void func_80038254();
// void func_800382C8();
// void func_80038340();
// void func_800383B4();
// void func_8003842C();
// void func_800384A0();
// void func_80038518();
// void func_8003858C();
// void func_800386AC();
// void func_80038824();
// void func_80038878();
// void func_800388E0();
// void func_80038938();
// void func_800389A8();
// void func_80038A94();
// void func_80038B18();
// void func_80038BD0();
UNK_TYPE func_80038BD8();
// void func_80038BE0();
// void func_80038C38();
// void func_80038C7C();
// void func_80038CBC();
// void func_80038E1C();
// void func_80038E24();
// void func_80038E30();
// void func_80038E44();
// void func_80038E50();
// void func_80038EF0();
// void func_8003901C();
// void func_800393DC();
// void func_800394A0();
// void func_8003974C();
// void func_80039BE0();
// void func_80039D08();
// void func_80039E14();
// void func_80039F74();
// void func_8003A1B4();
// void func_8003A26C();
// void func_8003A618();
// void func_8003A7E4();
// void func_8003A89C();
// void func_8003A8F4();
// void func_8003A950();
// void func_8003A9A0();
// void func_8003ACB4();
// void func_8003AD88();
// void func_8003AE08();
// void func_8003AEE4();
// void func_8003B054();
// void func_8003B1C4();
// void func_8003B30C();
// void func_8003B454();
// void func_8003B59C();
// void func_8003BA98();
// void func_8003BEF8();
// void func_8003BFD8();
// void func_8003C094();
// void func_8003C1A4();
// void func_8003C2B4();
// void func_8003C3C0();
// void func_8003C600();
// void func_8003C6F4();
// void func_8003CDA0();
// void func_8003CDD4();
// void func_8003CDF8();
// void func_8003CE20();
// void func_8003CE5C();
// void func_8003CF2C();
// void func_8003CFA8();
// void func_8003D110();
// void func_8003D41C();
// void func_8003D4C8();
// void func_8003D6D0();
// void func_8003E1E0();
// void func_8003E208();
// void func_8003E278();
// void func_8003E3F0();
// void func_8003E430();
// void func_8003E4AC();
// void func_8003E4B4();
// void func_8003E69C();
// void func_8003E6D8();
// void func_8003E6F8();
// void func_8003E730();
// void func_8003E8C8();
// void func_8003EB20();
// void func_8003ECDC();
// void func_8003EEA4();
// void func_8003F050();
// void func_8003F360();
// void func_8003F474();
// void func_8003F568();
// void func_8003F7DC();
// void func_8003FB00();
// void func_8003FD0C();
// void func_8003FD88();
// void func_8003FEE4();
// void func_8004015C();
// void func_80040238();
// void func_80040578();
// void func_80040624();
// void func_800409A0();
// void func_800409DC();
// void func_80040A00();
// void func_80040A58();
// void func_80040A64();
// void func_80040AE4();
// void func_80040B10();
// void func_80040BA4();
// void func_80040BB0();
// void func_80040D34();
// void func_80040E3C();
// void func_80040F34();
// void func_8004113C();
// void func_80041334();
// void func_80041480();
// void func_80041668();
// void func_800417B4();
// void func_8004199C();
// void func_80041A54();
// void func_80041DE0();
// void func_80041F94();
// void func_8004216C();
// void func_80042364();
// void func_80042468();
// void func_80042650();
// void func_800427E0();
// void func_800429B8();
// void func_80042B48();
// void func_80042D20();
// void func_80042E04();
// void func_80042FEC();
// void func_800430D0();
// void func_800432A8();
// void func_8004338C();
// void func_8004371C();
// void func_800438D0();
// void func_80043A14();
// void func_80043BEC();
// void func_80043DDC();
// void func_80043F18();
// void func_80044058();
// void func_80044238();
// void func_800443F4();
// void func_800445C4();
// void func_80044780();
// void func_80044940();
// void func_80044B18();
// void func_80044C28();
// void func_80044E08();
// void func_80044F18();
// void func_8004502C();
// void func_80045098();
// void func_80045110();
// void func_800451C4();
// void func_800452B0();
// void func_800453D8();
// void func_8004554C();
// void func_80045748();
// void func_80045914();
// void func_80045AAC();
// void func_80045DD0();
// void func_80045E18();
// void func_80045E48();
// void func_80045E94();
// void func_80045EF4();
// void func_80045F68();
// void func_80046008();
// void func_80046068();
// void func_800460DC();
// void func_8004613C();
// void func_800461B0();
// void func_80046250();
// void func_80046368();
// void func_80046408();
// void func_800464BC();
// void func_800464F8();
// void func_8004655C();
// void func_800465B8();
// void func_80046614();
// void func_80046670();
// void func_8004667C();
// void func_80046688();
// void func_80046694();
// void func_800466A0();
// void func_800466B8();
// void func_800466D0();
// void func_80046734();
// void func_800467E0();
// void func_80046844();
// void func_80046A3C();
// void func_80046B18();
// void func_80046C74();
// void func_80046D3C();
// void func_80046F58();
// void func_80047074();
// void func_8004714C();
// void func_800472D0();
// void func_80047420();
// void func_800474EC();
// void func_80047584();
// void func_800475A8();
// void func_80047720();
// void func_800477BC();
// void func_80047828();
// void func_800479A8();
// void func_800479EC();
// void func_80047AA4();
// void func_80048444();
// void func_80048634();
// void func_80048680();
// void func_800486C8();
// void func_80048708();
// void func_80048B8C();
// void func_80048C48();
// void func_80048CC8();
// void func_80048D34();
// void func_80048FA0();
// void func_80049034();
// void func_80049080();
// void func_800490B8();
// void func_800490D4();
// void func_80049224();
// void func_800492D8();
// void func_80049348();
// void func_80049540();
// void func_80049578();
// void func_80049594();
// void func_8004970C();
// void func_80049754();
// void func_800497D0();
// void func_80049894();
// void func_800498C4();
// void func_800498E0();
// void func_80049A5C();
// void func_80049C54();
// void func_80049CD4();
// void func_80049EA4();
// void func_8004A160();
// void func_8004A1F4();
// void func_8004A240();
// void func_8004A3F4();
// void func_8004A4CC();
// void func_8004A680();
// void func_8004A780();
// void func_8004A814();
// void func_8004A860();
// void func_8004A8D8();
// void func_8004A94C();
// void func_8004AC98();
// void func_8004ACF4();
// void func_8004AD10();
// void func_8004AD3C();
// void func_8004AD84();
// void func_8004ADC4();
// void func_8004B114();
// void func_8004B2C8();
// void func_8004B318();
// void func_8004B43C();
// void func_8004B488();
// void func_8004B500();
// void func_8004B774();
// void func_8004B7B8();
// void func_8004B8CC();
// void func_8004B98C();
// void func_8004B9F0();
// void func_8004BB14();
// void func_8004BB58();
// void func_8004BC2C();
// void func_8004BEB4();
// void func_8004BF10();
// void func_8004C1F0();
// void func_8004C2E8();
// void func_8004C4BC();
// void func_8004C820();
// void func_8004C864();
// void func_8004C974();
// void func_8004CA30();
// void func_8004CAA0();
// void func_8004CCD0();
// void func_8004CD14();
// void func_8004CE48();
// void func_8004CFB8();
// void func_8004D070();
// void func_8004D258();
// void func_8004D2A0();
// void func_8004D6DC();
// void func_8004D734();
// void func_8004D828();
// void func_8004DA40();
// void func_8004DD14();
// void func_8004E270();
// void func_8004E2B4();
// void func_8004E2F4();
// void func_8004E4F4();
// void func_8004E764();
// void func_8004E8E0();
// void func_8004EB94();
// void func_8004ED70();
// void func_8004EEC8();
// void func_8004F2D8();
// void func_8004F33C();
// void func_8004F358();
// void func_800508BC();
// void func_80050B5C();
// void func_800512AC();
// void func_800513F0();
// void func_80051480();
// void func_800514C4();
// void func_80051540();
// void func_80051974();
// void func_800519CC();
// void func_800519EC();
// void func_80051A28();
// void func_80051E94();
// void func_800522CC();
// void func_800529FC();
// void func_80052A40();
// void func_80052DF0();
// void func_80052E48();
// void func_80053194();
// void func_8005348C();
// void func_8005380C();
// void func_80053850();
// void func_80053C2C();
// void func_80053C84();
// void func_80053CEC();
// void func_80053FBC();
// void func_800540B8();
// void func_800541CC();
// void func_800544C4();
// void func_80054734();
// void func_80054A94();
// void func_80054B60();
// void func_800550F4();
// void func_80055154();
// void func_800551BC();
// void func_80055254();
// void func_800552EC();
// void func_80055598();
// void func_800556E0();
// void func_80055C08();
// void func_80055CE0();
// void func_80055DFC();
// void func_80055E40();
// void func_800560D4();
// void func_800560F0();
// void func_80056824();
// void func_80056990();
// void func_80056C84();
// void func_80056CAC();
// void func_80056CC8();
// void func_80056DF0();
// void func_80056E1C();
// void func_80056E38();
// void func_80057014();
// void func_8005712C();
// void func_800574B4();
// void func_8005768C();
// void func_80057724();
// void func_80057740();
// void func_80057898();
// void func_800578C8();
// void func_800578E4();
// void func_80057AFC();
// void func_80057BE8();
// void func_80057C50();
// void func_80057D24();
// void func_80057E68();
// void func_80057F6C();
// void func_8005806C();
// void func_800581C8();
// void func_800582FC();
// void func_800583C4();
// void func_800585BC();
// void func_800586A4();
// void func_80058838();
// void func_80058A24();
// void func_80058A9C();
// void func_8005911C();
// void func_800592D4();
// void func_8005954C();
// void func_800596B4();
// void func_800599E0();
// void func_80059A58();
// void func_80059AA4();
// void func_80059AF0();
// void func_80059B5C();
// void func_80059BC8();
// void func_80059C34();
// void func_80059CA0();
// void func_80059CC4();
// void func_80059CDC();
// void func_80059CF4();
// void func_80059D04();
// void func_80059D14();
// void func_80059D24();
// void func_80059D34();
// void func_80059D44();
// void func_80059D54();
// void func_80059D64();
// void func_80059D74();
// void func_80059D84();
// void func_80059D94();
// void func_80059DA4();
// void func_80059DB4();
// void func_80059DC4();
// void func_80059DD4();
// void func_80059DE4();
// void func_80059DF4();
// void func_80059DFC();
// void func_80059E1C();
// void func_80059E3C();
// void func_80059E5C();
// void func_80059E6C();
// void func_80059E7C();
// void func_80059E8C();
// void func_80059E9C();
// void func_80059EB8();
// void func_80059F1C();
// void func_8005A2AC();
// void func_8005A2EC();
// void func_8005A434();
// void func_8005A720();
// void func_8005A974();
// void func_8005AD30();
// void func_8005AEF4();
u32 func_8005B2D4(struct_800EB670 *);
// void func_8005B658();
// void func_8005B7F0();
// void func_8005B858();
// void func_8005B898();
// void func_8005B8D8();
// void func_8005B8F0();
// void func_8005B940();
// void func_8005B974();
// void func_8005B998();
// void func_8005BAAC();
// void func_8005BB24();
// void func_8005BEA0();
// void func_8005BF18();
// void func_8005C4BC();
// void func_8005C548();
// void func_8005C90C();
// void func_8005C998();
// void func_8005CF20();
// void func_8005CF78();
// void func_8005CFD4();
// void func_8005D09C();
// void func_8005D0EC();
// void func_8005D314();
// void func_8005D3F8();
// void func_8005D428();
// void func_8005D78C();
// void func_8005E0B4();
// void func_8005E0BC();
// void func_8005E0D0();
// void func_8005E0D8();
// void func_8005E0EC();
// void func_8005E104();
// void func_8005E120();
// void func_8005E154();
// void func_8005E174();
// void func_8005E32C();
// void func_8005E358();
// void func_8005E36C();
// void func_8005E40C();
// void func_8005E48C();
// void func_8005E4A8();
// void func_8005E4E0();
// void func_8005E4FC();
// void func_8005E5B0();
// void func_8005E67C();
// void func_8005E750();
// void func_8005E998();
// void func_8005EAFC();
// void func_8005EBA8();
// void func_8005EBDC();
// void func_8005EBE4();
// void func_8005EC40();
// void func_8005ED74();
// void func_8005EE64();
// void func_8005EE98();
// void func_8005EF50();
// void func_8005EFC0();
// void func_8005F00C();
// void func_8005F074();
// void func_8005F09C();
// void func_8005F0E4();
// void func_8005F13C();
// void func_8005F1E0();
// void func_8005F204();
// void func_8005F25C();
// void func_8005F2B0();
// void func_8005F310();
// void func_8005F33C();
// void func_8005F54C();
// void func_8005F634();
// void func_8005F698();
// void func_8005F6F0();
// void func_8005F700();
// void func_8005FC50();
// void func_8005FC6C();
// void func_8005FCC4();
// void func_8005FE68();
// void func_8005FF00();
// void func_800601F0();
// void func_80060270();
// void func_800602B8();
// void func_80060348();
// void func_80060424();
// void func_800604D8();
// void func_8006075C();
// void func_80060910();
// void func_800609B8();
// void func_80060A6C();
// void func_80060C1C();
// void func_80060E10();
// void func_80060F60();
// void func_80060FA0();
// void func_80060FCC();
// void func_800610E0();
// void func_80061184();
// void func_80061194();
// void func_8006121C();
// void func_8006126C();
// void func_800613D0();
// void func_80061490();
// void func_8006151C();
// void func_800615BC();
// void func_80061678();
// void func_800618B0();
// void func_80061954();
// void func_80061A14();
// void func_80061C50();
// void func_80061D20();
// void func_80061DB8();
// void func_80061E7C();
// void func_80061FE4();
// void func_800620FC();
// void func_8006258C();
// void func_800626A4();
// void func_80062898();
// void func_800628A4();
// void func_800628BC();
// void func_800628E4();
// void func_80062900();
// void func_80062920();
// void func_80062978();
// void func_80062990();
// void func_800629AC();
// void func_800629C8();
// void func_800629E4();
// void func_80062A08();
// void func_80062A24();
// void func_80062A40();
// void func_80062A5C();
// void func_80062A8C();
// void func_80062AA8();
// void func_80062AC4();
// void func_80062AE0();
// void func_80062AFC();
// void func_80062B18();
// void func_80062B34();
// void func_80062B50();
// void func_80062B84();
// void func_80062BC4();
// void func_80062BD4();
// void func_80062DA4();
// void func_80062DD8();
// void func_80062E84();
// void func_80062EC0();
// void func_80062FB8();
// void func_800630F8();
// void func_80063238();
// void func_80063378();
// void func_800633C0();
// void func_800633FC();
// void func_80063440();
// void func_800634E8();
// void func_800635BC();
// void func_80063844();
// void func_800638AC();
// void func_80063A80();
// void func_80063FF4();
// void func_8006408C();
// void func_80064130();
// void func_8006417C();
// void func_80064198();
// void func_80064298();
// void func_8006431C();
// void func_800643E0();
// void func_80064628();
// void func_80064748();
// void func_80064848();
// void func_800648C0();
// void func_80064940();
// void func_8006498C();
// void func_800649CC();
// void func_80064E4C();
// void func_80064F18();
// void func_80065BC4();
// void func_800666FC();
// void func_80066808();
// void func_8006683C();
// void func_800669A0();
// void func_800669C4();
// void func_80066F68();
// void func_8006729C();
// void func_800673FC();
// void func_800674EC();
// void func_800675C8();
// void func_80067668();
// void func_80067834();
// void func_80067F58();
// void func_80068950();
// void func_80068AA0();
// void func_80068C24();
// void func_80068DC0();
// void func_80068DE8();
// void func_80068E24();
// void func_80069160();
// void func_80069188();
// void func_800691F8();
// void func_800695A8();
// void func_8006967C();
// void func_80069990();
// void func_80069ACC();
// void func_80069BCC();
// void func_80069E20();
// void func_8006A098();
// void func_8006A198();
// void func_8006A2BC();
// void func_8006A480();
// void func_8006A6E8();
// void func_8006A938();
// void func_8006A978();
// void func_8006AC60();
// void func_8006AE04();
// void func_8006AEFC();
// void func_8006B0A4();
// void func_8006B270();
// void func_8006B8E0();
// void func_8006BBEC();
// void func_8006BC5C();
// void func_8006BD00();
// void func_8006BDFC();
// void func_8006C1D0();
// void func_8006C580();
// void func_8006C6FC();
// void func_8006C88C();
// void func_8006D0E8();
// void func_8006D150();
// void func_8006D254();
void func_8006D620();
// void func_8006D7B0();
// void func_8006D870();
// void func_8006D91C();
// void func_8006E0EC();
// void func_8006E80C();
// void func_8006E884();
// void func_8006F628();
u32 func_8006F684(struct_800EB670 *);
// void func_8006F950();
// void func_8006FFD0();
// void func_8007023C();
// void func_80070360();
// void func_80071624();
// void func_80071A44();
u32 func_80071A4C(struct_800EB670 *);
// void func_80071CE0();
// void func_80071EF0();
// void func_80071F0C();
// void func_80071F14();
// void func_80071FA0();
// void func_80072028();
// void func_800721A0();
// void func_800721BC();
// void func_800721D8();
// void func_80072204();
// void func_80072230();
// void func_8007224C();
// void func_80072268();
// void func_80072280();
// void func_800723EC();
// void func_80072428();
// void func_8007248C();
// void func_80072968();
// void func_80072AB4();
// void func_800733AC();
// void func_800739D8();
// void func_80074330();
// void func_80074954();
// void func_80074B08();
// void func_80074EF0();
// void func_80074FE0();
// void func_800752B8();
// void func_800755F0();
u32 func_80075A2C(struct_800EB670 *);
// void func_80075CF8();
// void func_80075F30();
u32 func_80075F98(struct_800EB670 *);
// void func_8007636C();
u32 func_8007657C(struct_800EB670 *);
// void func_800767DC();
// void func_800768E0();
// void func_80076CA0();
// void func_80076CCC();
// void func_80076DB4();
// void func_800770E8();
// void func_80077170();
// void func_800771EC();
// void func_800773F0();
// void func_8007744C();
// void func_8007746C();
// void func_800774C4();
// void func_80077504();
// void func_800777E8();
// void func_8007780C();
// void func_8007786C();
// void func_800778E8();
// void func_80077D68();
// void func_80077E2C();
// void func_80077FA4();
// void func_80078094();
// void func_80078648();
// void func_8007865C();
// void func_8007873C();
// void func_80078F78();
// void func_800791D0();
// void func_800796F4();
// void func_80079B24();
// void func_8007A154();
// void func_8007A440();
// void func_8007A9DC();
UNK_TYPE func_8007AA84(struct_800EB670 *);
// void func_8007AEBC();
// void func_8007AEF4();
// void func_8007B62C();
// void func_8007B650();
// void func_8007BC20();
// void func_8007BC54();
// void func_8007BD30();
// void func_8007BEEC();
// void func_8007BFE0();
// void func_8007C0C4();
// void func_8007C244();
// void func_8007C480();
// void func_8007C4AC();
// void func_8007C4D8();
// void func_8007C540();
// void func_8007C5A8();
// void func_8007C624();
// void func_8007C6D8();
// void func_8007C780();
// void func_8007C7E8();
// void func_8007C894();
// void func_8007C9C8();
// void func_8007CAFC();
// void func_8007CBE4();
// void func_8007CC68();
// void func_8007CCFC();
// void func_8007CD78();
// void func_8007CFB4();
// void func_8007D078();
// void func_8007D108();
// void func_8007D1C8();
// void func_8007D224();
// void func_8007D260();
// void func_8007D348();
// void func_8007D410();
// void func_8007D4CC();
// void func_8007D568();
// void func_8007D644();
// void func_8007D74C();
// void func_8007D83C();
// void func_8007DB78();
// void func_8007DD70();
// void func_8007DF64();
// void func_8007E260();
// void func_8007E2E0();
// void func_8007E2FC();
// void func_8007E418();
// void func_8007E5C4();
// void func_8007E638();
// void func_8007E760();
// void func_8007EA20();
// void func_8007EA38();
// void func_8007EA58();
// void func_8007EAEC();
// void func_8007EC54();
// void func_8007EE18();
// void func_8007F004();
// void func_8007F04C();
// void func_8007F094();
// void func_8007F420();
// void func_8007F720();
// void func_8007F890();
// void func_8007F990();
// void func_8007F9D0();
// void func_8007FA00();
// void func_8007FB4C();
// void func_8007FDE4();
// void func_8007FE10();
// void func_8007FE40();
// void func_80080090();
// void func_80080110();
// void func_80080228();
// void func_800802F4();
// void func_80080374();
// void func_80080428();
// void func_80080480();
// void func_800804E0();
// void func_80080550();
// void func_800805C0();
// void func_8008064C();
// void func_800806D4();
// void func_80080710();
// void func_80080738();
// void func_8008075C();
// void func_80080768();
// void func_800807C4();
// void func_800807E8();
// void func_80080810();
// void func_80080840();
// void func_8008089C();
// void func_80080920();
// void func_80080928();
// void func_80080934();
// void func_80080940();
// void func_8008094C();
// void func_80080954();
// void func_8008095C();
// void func_80080968();
// void func_800809CC();
// void func_80080A44();
// void func_80080A50();
// void func_80080AB4();
// void func_80080B34();
// void func_80080BCC();
// void func_80080EC4();
// void func_80081430();
// void func_800814BC();
// void func_80081620();
// void func_80081734();
// void func_800817A4();
// void func_80081980();
// void func_8008199C();
// void func_80081A54();
// void func_80081AAC();
// void func_80081B10();
// void func_80081BD4();
// void func_80081CE8();
// void func_80081E7C();
// void func_80082014();
// void func_800820A8();
// void func_800821E4();
// void func_800823AC();
// void func_800823E4();
// void func_80082494();
// void func_8008263C();
// void func_800828A8();
// void func_800828FC();
// void func_8008291C();
// void func_8008294C();
// void func_8008296C();
// void func_80082978();
// void func_80082AA0();
// void func_80082B84();
// void func_80082B98();
// void func_80082BBC();
// void func_80082C2C();
// void func_80082CA0();
// void func_80082CB0();
// void func_80082CE0();
// void func_80082CF0();
// void func_80082D00();
// void func_80082D10();
// void func_80082D68();
// void func_80082D78();
// void func_80082D84();
// void func_80082D94();
// void func_80082DA0();
// void func_80082E0C();
// void func_80082EA8();
// void func_80082ED0();
// void func_80082EDC();
// void func_80082EEC();
// void func_80082EF8();
// void func_80082F0C();
// void func_80082F20();
// void func_80082F28();
// void func_80082F70();
// void func_80082F7C();
// void func_80082F84();
// void func_80082FF4();
// void func_80083004();
// void func_80083054();
// void func_800830A4();
// void func_800830F4();
// void func_80083104();
// void func_800831D4();
// void func_80083210();
// void func_80083220();
// void func_80083264();
// void func_800832D4();
// void func_800832E0();
// void func_80083338();
// void func_80083604();
// void func_80083698();
// void func_800837E4();
// void func_80083AC4();
// void func_80083ADC();
// void func_80083B20();
// void func_80083B64();
// void func_80083BC0();
// void func_80083D34();
// void func_80083E04();
// void func_80083E10();
// void func_80083E7C();
// void func_80084020();
// void func_8008402C();
// void func_80084090();
// void func_800840F0();
// void func_800841D0();
// void func_80084308();
// void func_80084490();
// void func_800844DC();
// void func_8008450C();
// void func_80084524();
// void func_80084530();
// void func_8008455C();
// void func_800845D0();
// void func_800845D4();
// void func_80084648();


#endif