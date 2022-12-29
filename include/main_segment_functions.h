#ifndef MAIN_SEGMENT_FUNCTIONS_H
#define MAIN_SEGMENT_FUNCTIONS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "PR/sched.h"
#include "unknown_structs.h"
#include "unk.h"
#include "rom_offsets.h"


// void mainproc();

void func_80029ED0(struct_800EB670 *arg0, u8 viModeIndex, u8 retraceCount);
OSMesgQueue *func_8002A0CC(struct_800EB670 *arg0, UNK_PTR arg1);
OSMesgQueue *func_8002A0D4(struct_800EB670 *arg0);
void func_8002A0DC(struct_800EB670 * /*arg*/);
void func_8002A184(struct_800EB670 *arg0, struct_800FAF98_unk_64 *arg1, OSMesgQueue *arg2);
void func_8002A1DC(struct_800EB670 *arg0, struct_800FAF98_unk_64 *arg1);
void func_8002A26C(struct_800EB670 *arg0, OSMesg msg);
void func_8002A2B8(struct_800EB670 * arg0);
//void func_8002A3F4(struct_800EB670 *arg0, OSMesg arg1);
void func_8002A4D8(struct_800EB670 * arg0);
void func_8002A51C(struct_800EB670 *arg0, struct_800EB670_unk_66C *arg1);

UNK_TYPE joyInit(UNK_TYPE);
void joyProcCore(void);
void joyCursorFastSet(u16 mask, u8 index);
s32 joyResponseCheck();

void func_8002BD20(s32 red, s32 green, s32 blue, s32 alpha, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void load_TexPal(TexturePtr tlut);
void func_8002BF90(TexturePtr tlut, u32 pal);
void func_8002C048(TexturePtr texture, s32 width, s32 height);
void func_8002C1E8(TexturePtr texture, s32 width, s32 height);
void func_8002C388(TexturePtr texture, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt);
void func_8002C4EC(TexturePtr texture, s32 width, s32 height);
// void func_8002C688();
// void draw_Tex();
// void func_8002C914();
// void func_8002CA68();
// void func_8002CD08();
// void func_8002CF04();

enum_main_no main11(void);
void adjust_story_ai(void);
enum_main_no main12(void);

void sgenrand(u32 arg0);
u16 genrand(s32);

// void func_8002EB00();
// void func_8002EB74();
void aifMakeFlagSet(struct_80123700 *arg0);
void aifGameInit(void);
void aifFirstInit(void);
void func_8002EFF0(struct_80123700 *arg0);
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
// void aiCOM_MissTake();
void func_800365B0(struct_800365B0_arg0 *arg0, UNK_PTR arg1, UNK_TYPE arg2);
// void func_800365C8();
// void func_8003661C();
// void func_800366A4();
// void dm_init_config_save();
void func_8003678C(struct_800F7470 *arg0);
// void func_800367E0();
// void func_800367F0();
// void func_800367FC();
// void func_80036808();
void dm_init_save_mem(struct_800EF560 *arg0);
void dm_init_system_mem(void);
void dm_story_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void dm_level_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void dm_taiQ_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void dm_timeAt_sort_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void dm_vscom_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vc_fl_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vsman_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vm_fl_set(s32 arg0, s32 arg1, s32 arg2);
void dm_vm_ta_set(s32 arg0, s32 arg1, s32 arg2);
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
s32 func_800386AC(struct_800365B0_arg0 *arg0, char arg1[4]);
s32 EepRom_Init(void);
s32 EepRom_InitFirst(s32 arg0, s32 arg1);
void EepRom_InitVars(void);
UNK_PTR func_80038938(UNK_TYPE arg0);
// void func_800389A8();
s32 EepRom_ReadAll(void);
s32 EepRom_WriteAll(s32 arg0, s32 arg1); /* Original name: EepRom_WriteAll */
void func_80038BD0(UNK_TYPE arg0);
void EepRom_DumpDataSize(void);
// void setSleepTimer();

// void func_80038EF0();
// void func_8003901C();
// void func_800393DC();
// void func_800394A0();
// void func_8003974C();
// void func_80039BE0();
// void func_80039D08();
void *func_80039E14(void *arg0);
s32 func_80039F74(void);
void func_8003A1B4(Gfx **gfxP);
void *func_8003A26C(void *arg0);
s32 func_8003A618(void);
void func_8003A7E4(Gfx **gfxP);
void *func_8003A89C(void *arg0, s32 arg1);
s32 func_8003A8F4(void);
void func_8003A950(Gfx **gfxP);

// void func_8003A9A0();
// void func_8003ACB4();
void func_8003AD88(Gfx **gfxP);
UNK_TYPE func_8003AE08(Gfx **gfxP, s32 arg1, UNK_TYPE arg2);
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

void func_80040A00(void *arg0);
s32 func_80040A58(void);
void func_80040A64(void);
void func_80040AE4(void);
void func_80040B10(void (*callback)(s32), s32 arg);
s32 func_80040BA4(void);

void gfxSetScissor(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
// void func_80040D34();
void FillRectRGBA(Gfx **gfxP, s32 x0, s32 y0, s32 x1, s32 y1, s32 red, s32 green, s32 blue, s32 alpha);
// void func_80040F34();
// void func_8004113C();
// void func_80041334();
// void func_80041480();
// void func_80041668();
// void func_800417B4();
// void func_8004199C();
void StretchTexBlock(StretchTexBlock_arg0 *arg0);
void StretchTexBlock_ScisRect(StretchTexBlock_arg0 *arg0);
void func_80041F94(StretchTexBlock_arg0 *arg0);
void func_8004216C(StretchTexBlock_arg0 *arg0);
void StretchAlphaTexBlock(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void func_80042468(StretchTexBlock_arg0 *arg0);
void func_80042650(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void func_800427E0(StretchTexBlock_arg0 *arg0);
void func_800429B8(Gfx **gfxP, s32 arg1, s32 arg2, TexturePtr tlut, UNK_PTR arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
void func_80042B48(StretchTexBlock_arg0 *arg0);
void func_80042D20(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void StretchTexBlock4i_LoadTex(StretchTexBlock_arg0 *arg0);
void StretchTexBlock4i(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void func_800430D0(StretchTexBlock_arg0 *arg0);
void func_800432A8(Gfx **gfxP, s32 arg1, s32 arg2, UNK_PTR arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void StretchTexTile(StretchTexTile_arg0 *arg0);
void func_8004371C(StretchTexTile_arg0 *arg0);
// void func_800438D0();
void func_80043A14(StretchTexTile_arg0 *arg0);
void func_80043BEC(StretchTexTile_arg0 *arg0);
void StretchAlphaTexTile(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, f32 argB, f32 argC, f32 argD, f32 argE);
// void func_80043F18();
// void func_80044058();
// void func_80044238();
// void func_800443F4();
void StretchTexTile8(Gfx **gfxP, UNK_TYPE arg1, UNK_TYPE arg2, UNK_TYPE arg3, UNK_TYPE arg4, UNK_TYPE arg5, UNK_TYPE arg6, UNK_TYPE arg7, UNK_TYPE arg8, f32 arg9, f32 argA, f32 argB, f32 argC);
// void func_80044780();
// void func_80044940();
// void func_80044B18();
// void func_80044C28();
void func_80044E08(Gfx **gfxP, u16 arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB);
// void func_80044F18();
// void func_8004502C();
UNK_TYPE tiLoadTexData(UNK_PTR *arg0, romoffset_t segmentRom, romoffset_t segmentRomEnd);
// void func_80045110();
// void func_800451C4();
// void tiStretchTexBlock();
// void func_800453D8();
// void func_8004554C();
// void func_80045748();
// void func_80045914();
// void drawCursorPattern();
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
void func_80046250(struct_800F3E5C_unk_024B8 *arg0, UNK_TYPE arg1, UNK_TYPE arg2);
// void func_80046368();
// void func_80046408();
// void func_800464BC();
void func_800464F8(struct_800F3E5C_unk_024B8 *arg0, UNK_TYPE arg1, UNK_TYPE arg2);
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
void func_80046844(struct_800F3E5C_unk_024B8 *arg0, Gfx **gfxP);
// void func_80046A3C();
// void func_80046B18();
s32 func_80046C74(struct_800F3E5C_unk_024B8 *arg0, Gfx **gfxP, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
// void func_80046D3C();
// void func_80046F58();
// void func_80047074();
// void func_8004714C();
// void func_800472D0();
void func_80047420(UNK_TYPE *arg0, enum_struct_800F3E5C_unk_111CC arg1);
void func_800474EC(UNK_TYPE *arg0, struct_800F3E5C *arg1, UNK_TYPE arg2, UNK_TYPE arg3);
void func_80047584(UNK_TYPE *arg0, struct_800F3E5C_unk_024B8 *arg1);
void menuTitle_draw(UNK_TYPE *arg0, Gfx **gfxP);
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
void menuMain_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
void func_8004F2D8(struct_800F3E5C_unk_02678 *arg0);
// void func_8004F33C();
void menuMain_input(struct_800F3E5C_unk_02678 *arg0);
void menuMain_update(struct_800F3E5C_unk_02678 *arg0);
// void func_80050B5C();
void menuMain_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_800513F0();
// void func_80051480();
// void func_800514C4();
void menuStory_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
void func_80051974(struct_800F3E5C_unk_02678 *arg0);
// void func_800519CC();
// void func_800519EC();
void menuStory_input(struct_800F3E5C_unk_02678 *arg0);
void menuStory_update(struct_800F3E5C_unk_02678 *arg0);
void menuStory_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_800529FC();
void menuLvSel_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
void func_80052DF0(struct_800F3E5C_unk_02678 *arg0);
void menuLvSel_input(struct_800F3E5C_unk_02678 *arg0);
void menuLvSel_update(struct_800F3E5C_unk_02678 *arg0);
void menuLvSel_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_8005380C();
void menuChSel_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
// void func_80053C2C();
// void func_80053C84();
// void func_80053CEC();
// void func_80053FBC();
// void func_800540B8();
void menuChSel_input(struct_800F3E5C_unk_02678 *arg0);
void menuChSel_update(struct_800F3E5C_unk_02678 *arg0);
void menuChSel_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_80054A94();
void menuPlay2_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
void func_800550F4(struct_800F3E5C_unk_02678 *arg0);
// void func_80055154();
// void func_800551BC();
// void func_80055254();
// void func_800552EC();
// void func_80055598();
void menuPlay2_input(struct_800F3E5C_unk_02678 *arg0);
void menuPlay2_update(struct_800F3E5C_unk_02678 *arg0);
void menuPlay2_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_80055DFC();
void menuNmEnt_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
// void func_800560D4();
void menuNmEnt_input(struct_800F3E5C_unk_02678 *arg0);
void menuNmEnt_update(struct_800F3E5C_unk_02678 *arg0);
void menuNmEnt_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
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
void func_800585BC(struct_800F3E5C_unk_02678 *arg0, UNK_TYPE arg1, f32 arg2);
void func_800586A4(struct_800F3E5C_unk_02678 *arg0, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3, f32 arg4);
void func_80058838(struct_800F3E5C_unk_02678 *arg0, UNK_TYPE arg1, UNK_TYPE arg2, f32 arg3);
// void func_80058A24();
void func_80058A9C(struct_800F3E5C_unk_02678 *arg0, UNK_TYPE arg1, UNK_TYPE arg2, UNK_TYPE arg3);
void menuRank_init(struct_800F3E5C_unk_02678 *arg0, struct_800F3E5C *arg1, struct_800F3E5C_unk_02470 **arg2);
void menuRank_input(struct_800F3E5C_unk_02678 *arg0);
void menuRank_update(struct_800F3E5C_unk_02678 *arg0);
void menuRank_draw(struct_800F3E5C_unk_02678 *arg0, Gfx **gfxP);
// void func_800599E0();
// void func_80059A58();
// void func_80059AA4();
// void func_80059AF0();
// void func_80059B5C();
// void func_80059BC8();
// void func_80059C34();
void func_80059CA0(struct_800F3E5C *arg0);
// void func_80059CC4();
// void func_80059CDC();
// void func_80059CF4();
s32 func_80059D04(struct_800F3E5C *arg0, s32 arg1);
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
u16 func_80059DFC(struct_800F3E5C_unk_02678_unk_0000 *arg0, s32 arg1);
u16 func_80059E1C(struct_800F3E5C_unk_02678_unk_0000 *arg0, s32 arg1);
u16 func_80059E3C(struct_800F3E5C_unk_02678_unk_0000 *arg0, s32 arg1);
// void func_80059E5C();
// void func_80059E6C();
void func_80059E7C(struct_800F3E5C_unk_02678_unk_0000 *arg0, UNK_TYPE arg1);
// void func_80059E8C();
void menuTitle_setTitle(struct_800F3E5C *arg0, enum_struct_800F3E5C_unk_111CC arg1);
// void _setFadeDir();
void menuAll_init(struct_800F3E5C *arg0, UNK_PTR *arg1, struct_800EB670 *arg2);
void func_8005A2AC(struct_800F3E5C *arg0);
void func_8005A2EC(struct_800F3E5C *arg0);
void menuAll_changeMenu(struct_800F3E5C *arg0);

void menuAll_input(struct_800F3E5C *arg0);
void menuAll_update(struct_800F3E5C *arg0);
void menuAll_drawBg(struct_800F3E5C *arg0, Gfx **gfxP);
void menuAll_draw(struct_800F3E5C *arg0, Gfx **gfxP);
enum_main_no main_menu(struct_800EB670 * arg0);
void graphic_menu(void);

s32 fontStr_nextChar(const char *arg0);
s32 fontStr_length(const char *arg0);
s32 fontStr_charSize(const char *arg0, s32 arg1);
u16 func_8005B8D8(u8 arg0);
s32 font2index(const char *arg0);
void ascii2index(s32 character, s32 arg1, s32 *indexP, s32 *sizeP);
void font16_initDL(Gfx **gfxP);
void font16_initDL2(Gfx **gfxP);
bool fontXX_draw(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, const char * arg5);
bool fontXX_drawID(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
bool fontXX_draw2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, const char *arg5);
bool fontXX_drawID2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
bool fontAsc_draw(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, const char * arg5);
bool fontAsc_drawID(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
bool fontAsc_draw2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, const char * arg5);
bool fontAsc_drawID2(Gfx **gfxP, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

void init_map_all(struct_800EBEF0 *arg0);
void clear_map(struct_800EBEF0 *arg0, UNK_TYPE arg1, UNK_TYPE arg2);
// void func_8005F00C();
// void func_8005F074();
// void func_8005F09C();
// void func_8005F0E4();
s32 get_virus_color_count(struct_800EBEF0 *arg0, s8 *arg1, s8 *arg2, s8 *arg3);
s32 get_virus_count(struct_800EBEF0 *arg0);
// void func_8005F204();
void set_virus(struct_800EBEF0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u16 func_8005F2B0(void);
u32 func_8005F310(struct_virus_map_data *arg0, s32 arg1, s32 arg2);
bool dm_check_color(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3);
bool dm_check_color_2(struct_virus_map_data *arg0, u16 arg1, s32 arg2, u8 arg3);
void dm_virus_map_copy(struct_virus_map_data *virusMapSrc, struct_virus_map_data *virusMapDst, struct_virus_map_disp_order *virusDispOrderSrc, struct_virus_map_disp_order *virusDispOrderDst);
s32 dm_get_first_virus_count(enum_evs_gamemode evsGamemode, struct_80123700 *arg1);
s32 func_8005F6F0(s32 arg0);
void _dm_virus_init(u32 arg0, struct_80123700 *arg1, struct_virus_map_data *arg2, struct_virus_map_disp_order *arg3, UNK_TYPE arg4);
void dm_virus_init(u32 arg0, struct_80123700 *arg1, struct_virus_map_data *arg2, struct_virus_map_disp_order *arg3);
void func_8005FC6C(struct_8005FC6C_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3);
void _makeFlash_checkOrdre(struct_8005FC6C_arg0 *arg0);
// void func_8005FE68();
// void make_flash_virus_pos();
UNK_TYPE func_800601F0(struct_80123700 *, s32);
void func_80060270(struct_80123700 *, UNK_TYPE);
UNK_TYPE dm_make_score(struct_80123700 *arg0, s32 arg1);
// void func_80060348();
// void func_80060424();
UNK_TYPE set_down_flg(struct_800EBEF0 *arg0);
// void go_down();
 void erase_anime(struct_800EBEF0 *arg0);
// void func_800609B8();
// void func_80060A6C();
// void func_80060C1C();
// void func_80060E10();
// void func_80060F60();
// void func_80060FA0();
// void func_80060FCC();
// void func_800610E0();
// void func_80061184();
UNK_TYPE update_flash_virus_count(struct_80123700 *arg0, struct_800EBEF0 *arg1, UNK_TYPE arg2);
u8 func_8006121C(struct_80123700 *arg0, struct_800EBEF0 *arg1, UNK_TYPE arg2);
void dm_set_virus(struct_80123700 *, struct_800EBEF0 *, struct_virus_map_data *, struct_virus_map_disp_order *);
// void func_800613D0();
void func_80061490(struct_80123700 *arg0, struct_800EBEF0 *arg1);
void dm_make_erase_h_line(struct_80123700 *, struct_800EBEF0 *, s32, s32, s32);
bool dm_h_erase_chack(struct_800EBEF0 *arg0);
void dm_h_erase_chack_set(struct_80123700 *arg0, struct_800EBEF0 *arg1);
void dm_make_erase_w_line(struct_80123700 *, struct_800EBEF0 *, s32, s32, s32);
bool dm_w_erase_chack(struct_800EBEF0 *arg0);
void dm_w_erase_chack_set(struct_80123700 *arg0, struct_800EBEF0 *arg1);
void dm_h_ball_chack(struct_800EBEF0 *arg0);
void dm_w_ball_chack(struct_800EBEF0 *arg0);
// void func_80061DB8();
// void func_80061E7C();
void dm_calc_erase_score_pos(struct_80123700 *arg0, struct_800EBEF0 *arg1, dm_calc_erase_score_pos_arg2 *arg2);
// void func_800620FC();
// void func_8006258C();
// void func_800626A4();
UNK_PTR *dm_game_heap_top(void);
// void func_800628A4();
// void func_800628BC();
UNK_TYPE dm_get_mtx_buf();
UNK_TYPE dm_get_vtx_buf();
// void initEtcWork();
void func_80062978(s32 index, s32 arg1);
// void func_80062990();
// void func_800629AC();
// void func_800629C8();
// void func_800629E4();
void func_80062A08(s32 index);
void func_80062A24(s32 index);
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
s32 func_80062DD8(UNK_PTR arg0, UNK_TYPE arg1, UNK_TYPE arg2, UNK_TYPE arg3, UNK_TYPE arg4, UNK_TYPE arg5, UNK_TYPE arg6);
// void func_80062E84();
void func_80062EC0(struct_800F3E50_unk_0B8 *arg0);
// void scoreNums_set();
void backup_game_state(UNK_TYPE arg0);
// void resume_game_state();
// void func_80063378();
// void func_800633C0();
void func_800633FC(void);
void dm_warning_h_line_se(void);
void dm_play_count_down_se(void);
// void func_800635BC();
// void func_80063844();
// void func_800638AC();
// void func_80063A80();
// void func_80063FF4();
// void func_8006408C();
void func_80064130(s32 arg0, s32 arg1);
// void func_8006417C();
s32 retryMenu_input(s32 arg0);
// void func_80064298();
// void func_8006431C();
void set_bottom_up_virus(struct_80123700 *, struct_800EBEF0 *);
bool bottom_up_bottle_items(struct_800EBEF0 *arg0);
void add_taiQ_bonus_wait(struct_80123700 *arg0);
// void countLeadingZeros();
// void dm_game_eep_write_callback();
void func_80064940(s32);
bool func_8006498C(s32 arg0, s32 arg1, s32 arg2);
void dm_save_all(void);
// void func_80064E4C();
s32 dm_game_main_cnt_1P(struct_80123700 *arg0, struct_800EBEF0 *arg1, s32 arg2);
s32 dm_game_main_cnt(struct_80123700 *arg0, struct_800EBEF0 *arg1, s32 index);
// void func_800666FC();
// void func_80066808();
void dm_set_pause_and_volume(struct_80123700 **arg0, s32 arg1);
void func_800669A0(struct_80123700 *arg0);
void dm_calc_big_virus_pos(struct_80123700 *arg0);
s32 dm_game_main_1p(void);
// void func_8006729C();
// void func_800673FC();
// void func_800674EC();
// void func_800675C8();
// void func_80067668();
// void dm_game_main_2p();
// void dm_game_main_4p();
bool dm_game_demo_1p(void);
// void dm_game_demo_2p();
// void dm_game_demo_4p();
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
void push_any_key_draw(s32 arg0, s32 arg1);
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
void dm_draw_KaSaMaRu(Gfx **gfxP, UNK_TYPE *arg1, UNK_TYPE *arg2, bool messageIsSpeaking, s32 arg4, s32 arg5, s32 arg6, u32 arg7);
// void func_8006C1D0();
// void func_8006C580();
// void func_8006C6FC();
// void func_8006C88C();
void func_8006D0E8(void);
// void dm_make_key();
// void key_control_main();
void func_8006D620();
void dm_effect_make(void);
void dm_game_init_heap(void);
void dm_game_init(bool arg0);
void dm_game_init_static(void);
void dm_game_init_snap_bg(void);
void dm_game_draw_snap_bg(Gfx **gfxP, UNK_TYPE *arg1, UNK_TYPE *arg2, UNK_TYPE arg3);
// void func_8006F628();
enum_main_no dm_game_main(struct_800EB670 *arg0);
s32 dm_game_main2();
enum_main_no dm_game_main3(UNK_TYPE arg0);
void dm_game_graphic(void);
void dm_game_graphic2(void);
void dm_game_graphic_onDoneSawp(void);
void func_80071A44(void);
enum_main_no main_techmes(struct_800EB670 * arg0);
void graphic_techmes(void);
// void func_80071EF0();
// void func_80071F0C();
void func_80071F14(UNK_TYPE *arg0, UNK_PTR *arg1);
void func_80071FA0(UNK_TYPE *arg0);
// void tutolWnd_draw();
// void func_800721A0();
// void func_800721BC();
void func_800721D8(UNK_TYPE *arg0);
// void func_80072204();
// void func_80072230();
// void func_8007224C();
// void func_80072268();
// void func_80072280();
// void func_800723EC();
// void func_80072428();
// void func_8007248C();
// void func_80072968();
UNK_TYPE dm_manual_1_main(void);
UNK_TYPE dm_manual_2_main(void);
UNK_TYPE dm_manual_3_main(void);
UNK_TYPE dm_manual_4_main(void);
// void func_80074954();
// void func_80074B08();
// void func_80074EF0();
// void func_80074FE0();
void dm_manual_draw_fg(UNK_TYPE *arg0, UNK_TYPE *arg1);
void dm_manual_all_init(void);
enum_main_no dm_manual_main(struct_800EB670 *arg0);
void dm_manual_graphic(void);
// void func_80075F30();
enum_main_no dm_title_main(struct_800EB670 *arg0);
void dm_title_graphic(void);
enum_main_no main_boot_error(struct_800EB670 *arg0);
void graphic_boot_error(void);
// void story_zoomfade();
void func_80076CA0(struct_80076CA0_arg0 *arg0, struct_800E8750 *arg1);
// void func_80076CCC();
// void curtain_proc_org();
// void func_800770E8();
void *func_80077170(BgRomDataIndex index, void *dstAddr);
// void func_800771EC();
void func_800773F0(void);
void func_8007744C(void);
void func_8007746C(void);
bool func_800774C4(void);
void story_spot(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3, UNK_PTR arg4);
void func_800777E8(Gfx **gfxP, s32 arg1, s32 arg2, s32 arg3);
void *init_coffee_break(void *dstAddr);
void init_coffee_break_cnt(void);
// void func_800778E8();
void *init_menu_bg(void *dstAddr, bool arg1);
void draw_menu_bg(Gfx **gfxP, s32 arg1, s32 arg2);
void *init_title(void *dstAddr, bool arg1);
s32 demo_title(Gfx **gfxP, bool arg1);
// void func_80078648();
// void func_8007865C();
// void story_st_new_op();
// void story_st_new();
// void story_st_new2_f();
// void story_st_new2();
// void story_m_end();
// void story_st_new_w9();
// void story_w_end();
void func_8007A9DC(void);
UNK_TYPE main_story(struct_800EB670 *);
void init_objMtx(void);
void graphic_story(void);
// void func_8007B62C();
UNK_TYPE lws_anim(Gfx **gfxP, Mtx *mtx, UNK_PTR arg2, UNK_TYPE arg3, UNK_PTR arg4);

f32 func_8007BC20(f32 arg0);
// void func_8007BC54();
// void func_8007BD30();
// void func_8007BEEC();
// void func_8007BFE0();
// void func_8007C0C4();
// void func_8007C244();
// void func_8007C480();
s16 angleF2S(f32 arg0);
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
void randomize00(void);
void randomseed(s32 seed);
s32 irandom(void);
s32 random(s32 arg0);

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
// void replay_record_init_buffer();
void replay_record_init(s32 playcount);
// void replay_record();
void replay_play_init(void);
// void replay_play();
// void func_8007E760();

// void func_8007EA20();
// void func_8007EA38();
// void func_8007EA58();
// void func_8007EAEC();
// void func_8007EC54();
// void func_8007EC98();
// void matrixMulL();
void makeTransrateMatrix(Mtx *mtx, u32 x, u32 y, u32 z);
void makeScaleMatrix(Mtx *mtx, u32 scale);
// void makeMatrix();
// void matrixConv();
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
