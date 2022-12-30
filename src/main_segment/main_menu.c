/**
 * Original filename: main_menu.c
 */

#include "ultra64.h"
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

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80045DD0);

f32 func_80045E18(f32 arg0, f32 arg1) {
    return WrapF(0.0f, 1.0f, arg0 + arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80045E48);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80045E94);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80045EF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", transFunc_finger);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046008);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046068);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800460DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004613C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800461B0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADC50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADC60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800ADC78);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800ADC90);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800ADCB8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADCE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADD3C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADD40);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADD60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADD80);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADDBC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADDF0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800ADF2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE070);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE1D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE33C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE4C8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE5E8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE650);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE66C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE794);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE898);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE9B8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AE9CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEB3C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AED50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEEA4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEED0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEF04);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEF38);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEF74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AEFE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF014);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF048);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF070);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF09C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF0CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF0FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF134);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF16C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF18C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF1BC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF234);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF268);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF29C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF2E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF304);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF324);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF390);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF3C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF3F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF42C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF460);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF498);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF4C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF4EC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF514);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF518);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF52C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AF530);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046250);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046368);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046408);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800464BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800464F8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004655C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800465B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046614);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046670);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004667C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046688);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046694);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800466A0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800466B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800466D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046734);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800467E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046844);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046A3C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046B18);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046C74);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046D3C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80046F58);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047074);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004714C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800472D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047420);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800474EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047584);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuTitle_draw);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF660);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF6D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF6DC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF6E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF708);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047720);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800477BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047828);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800479A8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800479EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80047AA4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF83C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048444);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048634);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048680);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800486C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048708);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048B8C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048C48);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048CC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048D34);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80048FA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049034);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049080);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800490B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800490D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049224);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800492D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049348);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049540);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049578);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049594);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004970C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049754);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800497D0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049894);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800498C4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AF890);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAC8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAD4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAD8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAEC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAF8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFAFC);

const char D_800AFB08[] = "Ｙｅｓ";
const char D_800AFB10[] = "Ｎｏ";

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB38);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB48);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFB68);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800498E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049A5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049C54);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049CD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80049EA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A160);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A1F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A240);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A3F4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFB90);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A4CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A680);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A780);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A814);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFBB0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFBD8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFBE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFBEC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFBF0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC14);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC1C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A860);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A8D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004A94C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AC98);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004ACF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD10);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD3C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004AD84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004ADC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B114);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B2C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B318);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B43C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B488);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B500);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B774);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B7B8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B8CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B98C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004B9F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BB14);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BB58);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BC2C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BEB4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC40);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC48);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC64);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFC74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFCDC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFCEC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFCF0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFCFC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD00);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD0C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD10);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD20);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD30);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD3C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD40);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD4C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD60);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD6C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD74);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD78);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFD80);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004BF10);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C1F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C2E8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C4BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C820);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C864);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004C974);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CA30);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CAA0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CCD0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CD14);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CE48);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004CFB8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D070);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D258);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D2A0);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFE2C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFE58);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEA8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEB0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800AFEB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFECC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFED0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEDC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEE0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEE4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800AFEE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D6DC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D734);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004D828);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004DA40);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004DD14);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E270);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E2B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E2F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E4F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E764);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004E8E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004EB94);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0028);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0038);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0050);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B005C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B006C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0078);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B008C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0094);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00AC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00B8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B00EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004ED70);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_init);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0310);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0320);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0338);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0350);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B035C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0360);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0364);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0378);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B037C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0380);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B039C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03A0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03A4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03C0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03C4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03EC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B03F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0404);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0410);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B041C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0424);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B043C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0448);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004F2D8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8004F33C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_input);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_update);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0940);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80050B5C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0968);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B096C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B09F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B09FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A08);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A0C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A20);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A24);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuMain_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800513F0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80051480);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800514C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80051974);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800519CC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800519EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0A50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A5C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A6C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0A7C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0B0C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0B14);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0B18);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0B1C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0B20);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_update);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuStory_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800529FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvSel_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80052DF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvSel_input);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvSel_update);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuLvSel_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005380C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0B50);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", RO_800B0B54);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053C2C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053C84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053CEC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80053FBC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800540B8);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0C5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0D84);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0D94);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0D9C);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DA0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DAC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DB4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DB8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DC4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DC8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DD4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0DD8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_update);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuChSel_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80054A94);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800550F4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055154);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800551BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055254);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800552EC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055598);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_input);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_update);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B0F5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuPlay2_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80055DFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_init);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800560D4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_input);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1168);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_update);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuNmEnt_draw);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056C84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056CAC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056CC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056DF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056E1C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80056E38);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057014);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005712C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B11A4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B11CC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B11E0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B11F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1210);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800574B4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005768C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1220);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1230);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B123C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057724);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057740);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057898);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800578C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800578E4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057AFC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057BE8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057C50);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057D24);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057E68);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80057F6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_8005806C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800581C8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800582FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800583C4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800585BC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800586A4);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1290);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1298);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12A8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12B8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12C8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12D8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12E4);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12F0);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B12FC);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1308);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1314);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80058838);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80058A24);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1320);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1330);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1340);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1350);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1360);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1370);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80058A9C);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B13F8);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B13FC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRank_init);

void menuRank_input(struct_800F3E5C_unk_02678 *arg0) {
    struct_800F3E5C_unk_02678_unk_590 *temp_s0 = &arg0->unk_590[arg0->unk_0014];
    u16 pressedButton = func_80059E1C(arg0->unk_0000, 0);
    s32 direction;
    SndIndex sndIndex;

    func_80059E3C(arg0->unk_0000, 0);
    direction = 0;
    sndIndex = SND_INDEX_INVALID;
    if ((arg0->unk_0364 == 0.0f) && (arg0->unk_0368 < 0.0f)) {
        func_800585BC(arg0, 1, 0.0f);
    }

    if (!(temp_s0->unk_03C8 < 1.0f) && !(temp_s0->unk_03CC < 0.0f) && !(temp_s0->unk_03EC < 1.0f) &&
        !(temp_s0->unk_03F0 < 0.0f)) {
        if (arg0->unk_0008 == 0) {
            if (pressedButton & (L_JPAD | L_TRIG)) {
                direction--;
            }
            if (pressedButton & (R_JPAD | R_TRIG)) {
                direction++;
            }
        }

        if (pressedButton & B_BUTTON) {
            func_80058838(arg0, arg0->unk_0014, -1, 1.0f);
            sndIndex = SND_INDEX_68;
            func_80059E7C(arg0->unk_0000, 0);
        } else if (direction != 0) {
            arg0->unk_0010 = arg0->unk_000C;

            arg0->unk_000C = WrapI(0, 3, arg0->unk_000C + direction);
            sndIndex = SND_INDEX_63;
            func_800586A4(arg0, arg0->unk_0014, -1, 1.0f, -(direction * 0x140));
            arg0->unk_0018 = arg0->unk_0014;
            arg0->unk_0014 = (arg0->unk_0014 + 1) & 1;
            func_80058A9C(arg0, arg0->unk_0014, arg0->unk_0004, arg0->unk_000C);
            func_800585BC(arg0, -1, 1.0f);
            func_800586A4(arg0, arg0->unk_0014, 1, 0.0f, direction * 0x140);
        }

        if (sndIndex > SND_INDEX_INVALID) {
            dm_snd_play(sndIndex);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRank_update);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", menuRank_draw);

INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1430);
INCLUDE_RODATA("asm/nonmatchings/main_segment/main_menu", D_800B1438);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_800599E0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059A58);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059AA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059AF0);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059B5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059BC8);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059C34);

/* drMarioRetrace? */
void func_80059CA0(struct_watchMenu *arg0) {
    osRecvMesg(&arg0->unk_0000C, NULL, OS_MESG_BLOCK);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059CC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059CDC);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059CF4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D04);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D14);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D24);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D34);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D44);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D54);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D64);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D74);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D84);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059D94);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DA4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DB4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DC4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DD4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DE4);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059DF4);

u16 func_80059DFC(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return gControllerHoldButtons[main_joy[arg1]];
}

u16 func_80059E1C(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return gControllerPressedButtons[main_joy[arg1]];
}

u16 func_80059E3C(struct_800F3E5C_unk_02678_unk_0000 *arg0 UNUSED, s32 arg1) {
    return joycur[main_joy[arg1]];
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059E5C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059E6C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059E7C);

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", func_80059E8C);

void menuTitle_setTitle(struct_watchMenu *arg0, enum_struct_800F3E5C_unk_111CC arg1) {
    func_80047420(&arg0->unk_02548, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main_segment/main_menu", _setFadeDir);

/**
 * Original name: menuAll_init
 */
void menuAll_init(struct_watchMenu *arg0, UNK_PTR *arg1, struct_800EB670 *arg2) {
    UNK_PTR sp10 = *arg1;
    UNK_PTR temp_v0;
    s32 i;
    RomOffsetPair *pairArray = _romDataTbl;

    arg0->unk_00000 = arg2;
    arg0->unk_02460 = sp10;
    osCreateMesgQueue(&arg0->unk_0000C, arg0->unk_00024, ARRAY_COUNT(arg0->unk_00024));
    func_8002A184(arg2, &arg0->unk_00004, &arg0->unk_0000C);

    for (i = 0; i < ARRAY_COUNT(arg0->unk_00048); i++) {
        arg0->unk_02448[i] = &arg0->unk_00048[i];
        arg0->unk_02454[i] = &arg0->unk_00C48[i];
    }

    sp10 = init_menu_bg(sp10, evs_level_21 != 0);
    arg0->unk_02478 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CHAR].start, pairArray[ROMDATATBL_MENU_CHAR].end);
    arg0->unk_0247C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_COMMON].start, pairArray[ROMDATATBL_MENU_COMMON].end);
    arg0->unk_02484 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_LEVEL].start, pairArray[ROMDATATBL_MENU_LEVEL].end);
    arg0->unk_02488 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_MAIN].start, pairArray[ROMDATATBL_MENU_MAIN].end);
    arg0->unk_0248C = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_NAME].start, pairArray[ROMDATATBL_MENU_NAME].end);
    arg0->unk_02490 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P2].start, pairArray[ROMDATATBL_MENU_P2].end);
    arg0->unk_02494 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_P4].start, pairArray[ROMDATATBL_MENU_P4].end);
    arg0->unk_02498 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_RANK].start, pairArray[ROMDATATBL_MENU_RANK].end);
    arg0->unk_0249C =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_SETUP].start, pairArray[ROMDATATBL_MENU_SETUP].end);
    arg0->unk_024A0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_STORY].start, pairArray[ROMDATATBL_MENU_STORY].end);
    arg0->unk_024A4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_AL].start, pairArray[ROMDATATBL_GAME_AL].end);
    arg0->unk_024A8 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_GAME_P1].start, pairArray[ROMDATATBL_GAME_P1].end);
    arg0->unk_024AC = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_CONT].start, pairArray[ROMDATATBL_MENU_CONT].end);
    arg0->unk_024B0 =
        tiLoadTexData(&sp10, pairArray[ROMDATATBL_TUTORIAL_KASA].start, pairArray[ROMDATATBL_TUTORIAL_KASA].end);
    arg0->unk_024B4 = tiLoadTexData(&sp10, pairArray[ROMDATATBL_MENU_KASA].start, pairArray[ROMDATATBL_MENU_KASA].end);

    func_80046250(&arg0->unk_024B8, 0, 0);
    func_800474EC(&arg0->unk_02548, arg0, 0x70, 0x12);

    arg0->unk_111D0 = D_8008E8B4;
    arg0->unk_111CC = D_8008E8B4;
    arg0->unk_111C8 = D_8008E8B4;
    arg0->unk_111DC = 1.0f;
    arg0->unk_111C0 = 0;
    arg0->unk_111D8 = 0;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;
    arg0->unk_111C4 = -1;
    arg0->unk_111D4 = MAIN_NO_6;
    arg0->unk_111E4 = 1;
    arg0->unk_111E0 = -(1.0f / 30.0f);
    arg0->unk_111E8 = 1;
    arg0->unk_111F4 = 0x7F;

    RecWritingMsg_init(&arg0->recMessage, &sp10);
    arg0->unk_02464 = sizeof(struct_800F3E5C_unk_02470);

    for (i = 0; i < ARRAY_COUNTU(arg0->unk_02470); i++) {
        temp_v0 = ALIGN_PTR(sp10);
        arg0->unk_02468[i] = arg0->unk_02470[i] = temp_v0;
        sp10 = temp_v0 + arg0->unk_02464;
    }

    for (i = 0; i < ARRAY_COUNT(game_state_data); i++) {
        game_state_data[i].unk_000 = 0;
        game_state_data[i].unk_004 = 0;
    }

    evs_one_game_flg = 0;
    *arg1 = sp10;
}

void func_8005A2AC(struct_watchMenu *arg0) {
    func_8002A1DC(arg0->unk_00000, &arg0->unk_00004);
    D_8008E8B4 = arg0->unk_111CC;
}

void func_8005A2EC(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            func_8004F2D8(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            func_80051974(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            func_80052DF0(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            func_800550F4(&arg0->unk_02678[index]);
            break;

        default:
            break;
    }
}

void menuAll_changeMenu(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    arg0->unk_02470[index] = arg0->unk_02468[index];
    bzero(arg0->unk_02470[index], arg0->unk_02464);
    arg0->unk_111E4 = 1;
    arg0->unk_111E8 = 1;
    arg0->unk_111EC = 0;
    arg0->unk_111F0 = 0;

    if (arg0->unk_111CC != ENUM_STRUCT_800F3E5C_UNK_111CC_0) {
        menuTitle_setTitle(arg0, arg0->unk_111CC);
    }

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            menuMain_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            menuStory_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            menuLvSel_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            menuPlay2_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
            menuChSel_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_3:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_6:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_9:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_12:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_15:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_19:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_24:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_28:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_32:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_63:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_64:
            menuNmEnt_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_49:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_50:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_51:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_52:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_53:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_54:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_56:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_57:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_58:
            menuRank_init(&arg0->unk_02678[index], arg0, &arg0->unk_02470[index]);
            break;

        default:
            break;
    }
}

void menuAll_input(struct_watchMenu *arg0) {
    s32 index = arg0->unk_111C0;

    if ((arg0->unk_111E0 > 0.0f) && (arg0->unk_111DC > 0.0f)) {
        func_8005A2EC(arg0);
        return;
    }

    switch (arg0->unk_111CC) {
        case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
            menuMain_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
            menuStory_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
            menuLvSel_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
            menuPlay2_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
            menuChSel_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_3:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_6:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_9:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_12:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_15:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_19:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_24:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_28:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_32:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_63:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_64:
            menuNmEnt_input(&arg0->unk_02678[index]);
            break;

        case ENUM_STRUCT_800F3E5C_UNK_111CC_49:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_50:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_51:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_52:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_53:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_54:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_56:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_57:
        case ENUM_STRUCT_800F3E5C_UNK_111CC_58:
            menuRank_input(&arg0->unk_02678[index]);
            break;

        default:
            break;
    }
}

void menuAll_update(struct_watchMenu *arg0) {
    enum_struct_800F3E5C_unk_111CC var_a0;
    f32 temp_f2_2;
    f32 var_f2;
    struct_800F3E5C_unk_024B8 *var_v1 = &arg0->unk_024B8;
    s32 var_s0;
    s32 var_v1_2;

    arg0->unk_111DC = CLAMP(arg0->unk_111DC + arg0->unk_111E0, 0.0f, 1.0f);

    temp_f2_2 = (arg0->unk_111DC - 0.5) * 1.2 + 0.5;
    if (temp_f2_2 < 0.0f) {
        var_f2 = 1.0f;
    } else if (temp_f2_2 > 1.0f) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 1.0 - temp_f2_2;
    }

    temp_f2_2 = var_f2;
    for (var_s0 = 0; var_s0 < ARRAY_COUNT(var_v1->unk_7C); var_s0++) {
        var_v1->unk_7C[var_s0] = temp_f2_2;
        var_v1->unk_6C[var_s0] = temp_f2_2;
    }

    func_800464F8(&arg0->unk_024B8, 1, 0);
    func_80047584(&arg0->unk_02548, &arg0->unk_024B8);

    for (var_s0 = 0; var_s0 < 2; var_s0++) {
        if (var_s0 != 0) {
            var_v1_2 = arg0->unk_111C0;
        } else {
            var_v1_2 = arg0->unk_111C4;
        }
        if (var_v1_2 < 0) {
            continue;
        }

        if (var_s0 != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        switch (var_a0) {
            case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
                menuMain_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
                menuStory_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
                menuLvSel_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
                menuPlay2_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
                menuChSel_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_3:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_6:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_9:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_12:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_15:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_19:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_24:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_28:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_32:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_63:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_64:
                menuNmEnt_update(&arg0->unk_02678[var_v1_2]);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_49:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_50:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_51:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_52:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_53:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_54:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_56:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_57:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_58:
                menuRank_update(&arg0->unk_02678[var_v1_2]);
                break;

            default:
                break;
        }
    }

    arg0->unk_111E4 = 0;
    arg0->unk_111EC++;
}

void menuAll_drawBg(struct_watchMenu *arg0, Gfx **gfxP) {
    Gfx *gfx = *gfxP;
    struct_800F3E5C_unk_024B8 *temp_s4 = &arg0->unk_024B8;
    s32 temp_s3;
    s32 i;
    s32 var_s2;

    func_80046844(temp_s4, &gfx);
    draw_menu_bg(&gfx, arg0->unk_024B8.unk_0C + 0.0f, -arg0->unk_024B8.unk_10 - 120.0f);

    gSPDisplayList(gfx++, RO_800ADC60);
    func_80046844(temp_s4, &gfx);

    var_s2 = 0;
    temp_s3 = func_80059D04(arg0, 2);
    for (i = 0; i < 5; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i << 6), 0, 1.0f, 1.0f);
    }

    for (; i < 10; i++) {
        var_s2 += func_80046C74(temp_s4, &gfx, temp_s3, var_s2, (i - 5) << 6, 200.0f, 1.0f, -1.0f);
    }

    *gfxP = gfx;
}

void menuAll_draw(struct_watchMenu *arg0, Gfx **gfxP) {
    u8 color;
    s32 i;

    arg0->unk_02448[gfx_gtask_no] = &arg0->unk_00048[gfx_gtask_no];
    arg0->unk_02454[gfx_gtask_no] = &arg0->unk_00C48[gfx_gtask_no];

    color = CLAMP((s32)((((arg0->unk_111DC - 0.5) * 1.2) + 0.5) * 255.0), 0, 255);

    gDPSetEnvColor(gGfxHead++, color, color, color, 255);

    menuAll_drawBg(arg0, gfxP);
    menuTitle_draw(&arg0->unk_02548, &gGfxHead);

    for (i = 0; i < 2; i++) {
        enum_struct_800F3E5C_unk_111CC var_a0;
        s32 index;

        if (i != 0) {
            index = arg0->unk_111C0;
        } else {
            index = arg0->unk_111C4;
        }
        if (index < 0) {
            continue;
        }

        if (i != 0) {
            var_a0 = arg0->unk_111CC;
        } else {
            var_a0 = arg0->unk_111C8;
        }

        gDPSetEnvColor(gGfxHead++, color, color, color, 255);

        switch (var_a0) {
            case ENUM_STRUCT_800F3E5C_UNK_111CC_0:
                menuMain_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_4:
                menuStory_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_7:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_10:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_13:
                menuLvSel_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_17:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_21:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_26:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_30:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_34:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_41:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_43:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_45:
                menuPlay2_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_16:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_20:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_25:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_29:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_33:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_40:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_42:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_44:
                menuChSel_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_3:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_6:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_9:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_12:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_15:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_19:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_24:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_28:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_32:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_63:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_64:
                menuNmEnt_draw(&arg0->unk_02678[index], gfxP);
                break;

            case ENUM_STRUCT_800F3E5C_UNK_111CC_49:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_50:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_51:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_52:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_53:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_54:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_56:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_57:
            case ENUM_STRUCT_800F3E5C_UNK_111CC_58:
                menuRank_draw(&arg0->unk_02678[index], gfxP);
                break;

            default:
                break;
        }
    }

    RecWritingMsg_draw(&arg0->recMessage, &gGfxHead);

    arg0->unk_111E8 = 0;
    arg0->unk_111F0++;
}

/**
 * Original name: main_menu
 */
enum_main_no main_menu(struct_800EB670 *arg0) {
    UNK_PTR sp10 = Heap_bufferp;
    struct_watchMenu *ptr = ALIGN_PTR(Heap_bufferp);
    s32 i;
    u16 value;

    if (main_old == MAIN_NO_3) {
        D_8008E8B4 = 0;
        D_8008E788 = 0;
        B_800EB4F4 = 0;
        B_800EFCB0 = 0;
    }
    func_80040A64();
    sp10 = &ptr[1];
    bzero(ptr, sizeof(struct_watchMenu));
    watchMenu = ptr;
    menuAll_init(ptr, &sp10, arg0);

    evs_playmax = joyResponseCheck();

    value = 0xF30;
    for (i = ARRAY_COUNT(joyflg) - 1; i >= 0; i--) {
        joyflg[i] = value;
    }

    joycur1 = 0x18;
    joycur2 = 6;
    gGfxHead = gGfxGlist[gfx_gtask_no];
    dm_seq_play(0xC);

    while ((ptr->unk_111D4 == MAIN_NO_6) || (ptr->unk_111DC < 1.0f)) {
        if (graphic_no == GRAPHIC_NO_0) {
            while ((pendingGFX != 0) || (func_80040BA4() != 0)) {
                func_80059CA0(ptr);
            }

            menuAll_changeMenu(ptr);
        }

        if (ptr->unk_111D8 > 0) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                joycur[i] = 0;
                gControllerPressedButtons[i] = 0;
                gControllerPrevHoldButtons[i] = 0;
                gControllerHoldButtons[i] = 0;
            }
        } else {
            joyProcCore();
        }

        func_80059CA0(ptr);
        menuAll_input(ptr);
        menuAll_update(ptr);
        dm_audio_update();

        if (ptr->unk_111CC != ptr->unk_111D0) {
            ptr->unk_111C8 = ptr->unk_111CC;
            ptr->unk_111CC = ptr->unk_111D0;
            ptr->unk_111C4 = ptr->unk_111C0;
            ptr->unk_111C0 ^= 1;
            graphic_no = GRAPHIC_NO_0;
        } else {
            graphic_no = GRAPHIC_NO_5;
        }
    }

    graphic_no = GRAPHIC_NO_5;

    while (ptr->unk_111F4 != 0xF) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    graphic_no = GRAPHIC_NO_0;
    dm_seq_stop();

    while ((pendingGFX != 0) || !func_8002B178() || (func_80040BA4() != 0)) {
        osRecvMesg(&ptr->unk_0000C, NULL, OS_MESG_BLOCK);
        dm_audio_update();
    }

    func_8005A2AC(ptr);
    func_80040AE4();

    return ptr->unk_111D4;
}

void graphic_menu(void) {
    struct_watchMenu *ptr = watchMenu;

    if ((ptr->unk_111D4 != MAIN_NO_6) && (ptr->unk_111DC == 1.0f)) {
        osSetThreadPri(NULL, 0xF);
        ptr->unk_111F4 = 0xF;
        return;
    }

    if (gGfxHead != gGfxGlist[gfx_gtask_no]) {
        gDPFullSync(gGfxHead++);
        gSPEndDisplayList(gGfxHead++);

        osWritebackDCacheAll();
        gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no],
                     (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx), 0, OS_SC_SWAPBUFFER);
        gGfxHead = gGfxGlist[gfx_gtask_no];
    }

    osSetThreadPri(NULL, 0xF);
    F3RCPinitRtn();
    F3ClearFZRtn(0);
    menuAll_draw(ptr, &gGfxHead);
    osSetThreadPri(NULL, 0x7F);
}
