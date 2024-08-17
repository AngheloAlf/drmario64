#include "assets/coffee/coffee01.h"

#include "libc/assert.h"

#include "alignment.h"
#include "lws.h"
#include "macros_defines.h"

#define coffee01_D_05014E80_COUNT (15)
#define coffee01_D_05014E98_COUNT (15)
#define coffee01_D_05015A40_COUNT (9)
#define coffee01_D_0501A1D8_COUNT (13)
#define coffee01_D_05020138_COUNT (12)
#define coffee01_D_05024288_COUNT (17)
#define coffee01_D_050242A0_COUNT (17)

extern Lws *coffee01_D_05000000[];
extern Gfx coffee01_D_05000020[];
extern u16 coffee01_D_05000028[];
extern u8 coffee01_D_05000048[];
extern u16 coffee01_D_05000688[];
extern u8 coffee01_D_050006A8[];
extern u16 coffee01_D_050007A8[];
extern u8 coffee01_D_050007C8[];
extern u16 coffee01_D_05000FC8[];
extern u8 coffee01_D_05000FE8[];
extern u16 coffee01_D_050017E8[];
extern u8 coffee01_D_05001808[];
extern u16 coffee01_D_05002008[];
extern u8 coffee01_D_05002028[];
extern u16 coffee01_D_05002828[];
extern u8 coffee01_D_05002848[];
extern u16 coffee01_D_05003048[];
extern u8 coffee01_D_05003068[];
extern u16 coffee01_D_05003868[];
extern u8 coffee01_D_05003888[];
extern u16 coffee01_D_05004088[];
extern u8 coffee01_D_050040A8[];
extern u16 coffee01_D_050048A8[];
extern u8 coffee01_D_050048C8[];
extern u16 coffee01_D_050050C8[];
extern u8 coffee01_D_050050E8[];
extern u16 coffee01_D_050058E8[];
extern u8 coffee01_D_05005908[];
extern u16 coffee01_D_05005B08[];
extern u8 coffee01_D_05005D08[];
extern u16 coffee01_D_050064E8[];
extern u8 coffee01_D_05006508[];
extern u16 coffee01_D_05006908[];
extern u8 coffee01_D_05006928[];
extern u16 coffee01_D_05006D28[];
extern u8 coffee01_D_05006D48[];
extern u16 coffee01_D_05007548[];
extern u8 coffee01_D_05007568[];
extern u16 coffee01_D_05007768[];
extern u8 coffee01_D_05007788[];
extern u16 coffee01_D_05007988[];
extern u8 coffee01_D_050079A8[];
extern u16 coffee01_D_05007E08[];
extern u8 coffee01_D_05007E28[];
extern u16 coffee01_D_05008228[];
extern u8 coffee01_D_05008248[];
extern u16 coffee01_D_05008888[];
extern u8 coffee01_D_050088A8[];
extern u16 coffee01_D_05008EE8[];
extern u8 coffee01_D_05008F08[];
extern u16 coffee01_D_05009108[];
extern u8 coffee01_D_05009128[];
extern u16 coffee01_D_05009768[];
extern u8 coffee01_D_05009788[];
extern u16 coffee01_D_05009988[];
extern u8 coffee01_D_050099A8[];
extern u16 coffee01_D_05009BA8[];
extern u8 coffee01_D_05009DA8[];
extern u16 coffee01_D_0500A5A0[];
extern u8 coffee01_D_0500A5C0[];
extern u16 coffee01_D_0500AD90[];
extern u8 coffee01_D_0500ADB0[];
extern u16 coffee01_D_0500B580[];
extern u8 coffee01_D_0500B5A0[];
extern u16 coffee01_D_0500BD70[];
extern u8 coffee01_D_0500BD90[];
extern u16 coffee01_D_0500C560[];
extern u8 coffee01_D_0500C580[];
extern u16 coffee01_D_0500CD80[];
extern u8 coffee01_D_0500CDA0[];
extern u16 coffee01_D_0500D570[];
extern u8 coffee01_D_0500D590[];
extern u16 coffee01_D_0500D790[];
extern u8 coffee01_D_0500D7B0[];
extern u16 coffee01_D_0500D9B0[];
extern u8 coffee01_D_0500D9D0[];
extern u16 coffee01_D_0500DBD0[];
extern u8 coffee01_D_0500DBF0[];
extern u16 coffee01_D_0500DDF0[];
extern u8 coffee01_D_0500DE10[];
extern u16 coffee01_D_0500E010[];
extern u8 coffee01_D_0500E030[];
extern u16 coffee01_D_0500E490[];
extern u8 coffee01_D_0500E4B0[];
extern u16 coffee01_D_0500E910[];
extern u8 coffee01_D_0500E930[];
extern u16 coffee01_D_0500EFC0[];
extern u8 coffee01_D_0500EFE0[];
extern u16 coffee01_D_0500F1E0[];
extern u8 coffee01_D_0500F3E0[];
extern u16 coffee01_D_0500FA20[];
extern u8 coffee01_D_0500FC20[];
extern u16 coffee01_D_05010260[];
extern u8 coffee01_D_05010460[];
extern u16 coffee01_D_05010AA0[];
extern u8 coffee01_D_05010CA0[];
extern u32 coffee01_D_05011420[];
extern Vtx coffee01_D_05011440[];
extern Gfx coffee01_D_05011480[];
extern u32 coffee01_D_05011570[];
extern Vtx coffee01_D_05011590[];
extern Gfx coffee01_D_050115D0[];
extern u32 coffee01_D_050116C0[];
extern Vtx coffee01_D_050116E0[];
extern Gfx coffee01_D_05011760[];
extern u32 coffee01_D_050118C0[];
extern Vtx coffee01_D_050118E0[];
extern Gfx coffee01_D_050119E0[];
extern u32 coffee01_D_05011C20[];
extern Vtx coffee01_D_05011C40[];
extern Gfx coffee01_D_05011D40[];
extern u32 coffee01_D_05011F80[];
extern Vtx coffee01_D_05011FA0[];
extern Gfx coffee01_D_05011FE0[];
extern u32 coffee01_D_050120D0[];
extern Vtx coffee01_D_050120F0[];
extern Gfx coffee01_D_05012130[];
extern u32 coffee01_D_05012220[];
extern Vtx coffee01_D_05012240[];
extern Gfx coffee01_D_05012280[];
extern u32 coffee01_D_05012370[];
extern Vtx coffee01_D_05012390[];
extern Gfx coffee01_D_050123D0[];
extern u32 coffee01_D_050124C0[];
extern Vtx coffee01_D_050124E0[];
extern Gfx coffee01_D_05012520[];
extern u32 coffee01_D_05012610[];
extern Vtx coffee01_D_05012630[];
extern Gfx coffee01_D_05012670[];
extern u32 coffee01_D_05012760[];
extern Vtx coffee01_D_05012780[];
extern Gfx coffee01_D_050127C0[];
extern u32 coffee01_D_050128B0[];
extern Vtx coffee01_D_050128D0[];
extern Gfx coffee01_D_05012910[];
extern u32 coffee01_D_05012A00[];
extern Vtx coffee01_D_05012A20[];
extern Gfx coffee01_D_05012B20[];
extern u32 coffee01_D_05012D60[];
extern Vtx coffee01_D_05012D80[];
extern Gfx coffee01_D_05012DC0[];
extern u32 coffee01_D_05012EB0[];
extern Vtx coffee01_D_05012ED0[];
extern Gfx coffee01_D_05012F10[];
extern u32 coffee01_D_05013000[];
extern Vtx coffee01_D_05013020[];
extern Gfx coffee01_D_05013160[];
extern u32 coffee01_D_05013298[];
extern Vtx coffee01_D_050132B8[];
extern Gfx coffee01_D_050132F8[];
extern u32 coffee01_D_050133E8[];
extern Vtx coffee01_D_05013408[];
extern Gfx coffee01_D_05013508[];
extern u32 coffee01_D_05013748[];
extern Vtx coffee01_D_05013768[];
extern Gfx coffee01_D_050137C8[];
extern u32 coffee01_D_050138C0[];
extern Vtx coffee01_D_050138E0[];
extern Gfx coffee01_D_05013940[];
extern u32 coffee01_D_05013A38[];
extern Vtx coffee01_D_05013A58[];
extern Gfx coffee01_D_05013A98[];
extern u32 coffee01_D_05013B88[];
extern Vtx coffee01_D_05013BA8[];
extern Gfx coffee01_D_05013BE8[];
extern u32 coffee01_D_05013CD8[];
extern Vtx coffee01_D_05013CF8[];
extern Gfx coffee01_D_05013D38[];
extern u32 coffee01_D_05013E28[];
extern Vtx coffee01_D_05013E48[];
extern Gfx coffee01_D_05013E88[];
extern u32 coffee01_D_05013F78[];
extern Vtx coffee01_D_05013F98[];
extern Gfx coffee01_D_05014018[];
extern u32 coffee01_D_050140A8[];
extern Vtx coffee01_D_050140C8[];
extern Gfx coffee01_D_05014108[];
extern u32 coffee01_D_050141F8[];
extern Vtx coffee01_D_05014218[];
extern Gfx coffee01_D_05014298[];
extern u32 coffee01_D_050143F8[];
extern Vtx coffee01_D_05014418[];
extern Gfx coffee01_D_05014458[];
extern u32 coffee01_D_05014548[];
extern Vtx coffee01_D_05014568[];
extern Gfx coffee01_D_050145A8[];
extern u32 coffee01_D_05014698[];
extern Vtx coffee01_D_050146B8[];
extern Gfx coffee01_D_050147B8[];
extern u32 coffee01_D_050148D8[];
extern Vtx coffee01_D_050148F8[];
extern Gfx coffee01_D_050149D8[];
extern u32 coffee01_D_05014AF0[];
extern Vtx coffee01_D_05014B10[];
extern Gfx coffee01_D_05014C10[];
extern u32 coffee01_D_05014D30[];
extern Vtx coffee01_D_05014D50[];
extern Gfx coffee01_D_05014D90[];
extern Lws coffee01_D_05014E80;
extern Lws coffee01_D_05014E98;
extern Lws_unk_10 coffee01_D_05014EB0[];
extern Lws_unk_10 coffee01_D_05015018[];
extern Lws_unk_14 coffee01_D_05015180[];
extern u32 coffee01_D_050159EC[];
extern Lws coffee01_D_05015A40;
extern Lws_unk_10 coffee01_D_05015A58[];
extern Lws_unk_14 coffee01_D_05015B30[];
extern u32 coffee01_D_0501A1A0[];
extern Lws coffee01_D_0501A1D8;
extern Lws_unk_10 coffee01_D_0501A1F0[];
extern Lws_unk_14 coffee01_D_0501A328[];
extern u32 coffee01_D_050200AC[];
extern Lws coffee01_D_05020138;
extern Lws_unk_10 coffee01_D_05020150[];
extern Lws_unk_14 coffee01_D_05020270[];
extern u32 coffee01_D_05024218[];
extern Lws coffee01_D_05024288;
extern Lws coffee01_D_050242A0;
extern Lws_unk_10 coffee01_D_050242B8[];
extern Lws_unk_10 coffee01_D_05024450[];
extern Lws_unk_14 coffee01_D_050245E8[];

Lws *coffee01_D_05000000[] = {
    &coffee01_D_05014E80, // COFFEE01_LWS_INDEX_0
    &coffee01_D_05014E98, // COFFEE01_LWS_INDEX_1
    &coffee01_D_05015A40, // COFFEE01_LWS_INDEX_2
    &coffee01_D_0501A1D8, // COFFEE01_LWS_INDEX_3
    &coffee01_D_05020138, // COFFEE01_LWS_INDEX_4
    &coffee01_D_05024288, // COFFEE01_LWS_INDEX_5
    &coffee01_D_050242A0, // COFFEE01_LWS_INDEX_6
};
static_assert(ARRAY_COUNT(coffee01_D_05000000) == COFFEE01_LWS_INDEX_MAX, "");

/* unreferenced data */
Gfx coffee01_D_05000020[] = {
    gsSPEndDisplayList(),
};

u16 coffee01_D_05000028[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05000048.palette.inc"
};

u8 coffee01_D_05000048[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05000048.ci4.inc"
};

u16 coffee01_D_05000688[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050006A8.palette.inc"
};

u8 coffee01_D_050006A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050006A8.ci4.inc"
};

u16 coffee01_D_050007A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050007C8.palette.inc"
};

u8 coffee01_D_050007C8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050007C8.ci4.inc"
};

u16 coffee01_D_05000FC8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05000FE8.palette.inc"
};

u8 coffee01_D_05000FE8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05000FE8.ci4.inc"
};

#if VERSION_US || VERSION_GW

u16 coffee01_D_050017E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05001808.palette.inc"
};

u8 coffee01_D_05001808[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05001808.ci4.inc"
};

u16 coffee01_D_05002008[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002028.palette.inc"
};

u8 coffee01_D_05002028[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002028.ci4.inc"
};

u16 coffee01_D_05002828[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002848.palette.inc"
};

u8 coffee01_D_05002848[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002848.ci4.inc"
};

u16 coffee01_D_05003048[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003068.palette.inc"
};

u8 coffee01_D_05003068[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003068.ci4.inc"
};

u16 coffee01_D_05003868[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003888.palette.inc"
};

u8 coffee01_D_05003888[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003888.ci4.inc"
};

u16 coffee01_D_05004088[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050040A8.palette.inc"
};

u8 coffee01_D_050040A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050040A8.ci4.inc"
};

u16 coffee01_D_050048A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050048C8.palette.inc"
};

u8 coffee01_D_050048C8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050048C8.ci4.inc"
};

u16 coffee01_D_050050C8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050050E8.palette.inc"
};

u8 coffee01_D_050050E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050050E8.ci4.inc"
};

u16 coffee01_D_050058E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005908.palette.inc"
};

u8 coffee01_D_05005908[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005908.ci4.inc"
};
#endif

u16 coffee01_D_05005B08[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005D08.palette.inc"
};

u8 coffee01_D_05005D08[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005D08.ci8.inc"
};

u16 coffee01_D_050064E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006508.palette.inc"
};

u8 coffee01_D_05006508[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006508.ci4.inc"
};

u16 coffee01_D_05006908[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006928.palette.inc"
};

u8 coffee01_D_05006928[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006928.ci4.inc"
};

u16 coffee01_D_05006D28[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006D48.palette.inc"
};

u8 coffee01_D_05006D48[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05006D48.ci4.inc"
};

#if VERSION_US || VERSION_GW
u16 coffee01_D_05007548[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007568.palette.inc"
};

u8 coffee01_D_05007568[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007568.ci4.inc"
};

u16 coffee01_D_05007768[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007788.palette.inc"
};

u8 coffee01_D_05007788[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007788.ci4.inc"
};
#endif

u16 coffee01_D_05007988[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050079A8.palette.inc"
};

u8 coffee01_D_050079A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050079A8.ci4.inc"
};

u16 coffee01_D_05007E08[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007E28.palette.inc"
};

u8 coffee01_D_05007E28[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007E28.ci4.inc"
};

u16 coffee01_D_05008228[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008248.palette.inc"
};

u8 coffee01_D_05008248[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008248.ci4.inc"
};

u16 coffee01_D_05008888[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050088A8.palette.inc"
};

u8 coffee01_D_050088A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050088A8.ci4.inc"
};

#if VERSION_US || VERSION_GW
u16 coffee01_D_05008EE8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008F08.palette.inc"
};

u8 coffee01_D_05008F08[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008F08.ci4.inc"
};
#endif

u16 coffee01_D_05009108[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009128.palette.inc"
};

u8 coffee01_D_05009128[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009128.ci4.inc"
};

#if VERSION_US || VERSION_GW
u16 coffee01_D_05009768[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009788.palette.inc"
};

u8 coffee01_D_05009788[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009788.ci4.inc"
};

u16 coffee01_D_05009988[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050099A8.palette.inc"
};

u8 coffee01_D_050099A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050099A8.ci4.inc"
};
#endif

u16 coffee01_D_05009BA8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009DA8.palette.inc"
};

u8 coffee01_D_05009DA8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009DA8.ci8.inc"
};

u16 coffee01_D_0500A5A0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500A5C0.palette.inc"
};

u8 coffee01_D_0500A5C0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500A5C0.ci4.inc"
};

u16 coffee01_D_0500AD90[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500ADB0.palette.inc"
};

u8 coffee01_D_0500ADB0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500ADB0.ci4.inc"
};

u16 coffee01_D_0500B580[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500B5A0.palette.inc"
};

u8 coffee01_D_0500B5A0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500B5A0.ci4.inc"
};

u16 coffee01_D_0500BD70[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500BD90.palette.inc"
};

u8 coffee01_D_0500BD90[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500BD90.ci4.inc"
};

u16 coffee01_D_0500C560[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500C580.palette.inc"
};

u8 coffee01_D_0500C580[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500C580.ci4.inc"
};

u16 coffee01_D_0500CD80[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500CDA0.palette.inc"
};

u8 coffee01_D_0500CDA0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500CDA0.ci4.inc"
};

#if VERSION_US || VERSION_GW
u16 coffee01_D_0500D570[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D590.palette.inc"
};

u8 coffee01_D_0500D590[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D590.ci4.inc"
};

u16 coffee01_D_0500D790[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D7B0.palette.inc"
};

u8 coffee01_D_0500D7B0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D7B0.ci4.inc"
};

u16 coffee01_D_0500D9B0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D9D0.palette.inc"
};

u8 coffee01_D_0500D9D0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D9D0.ci4.inc"
};

u16 coffee01_D_0500DBD0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DBF0.palette.inc"
};

u8 coffee01_D_0500DBF0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DBF0.ci4.inc"
};

u16 coffee01_D_0500DDF0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DE10.palette.inc"
};

u8 coffee01_D_0500DE10[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DE10.ci4.inc"
};
#endif

u16 coffee01_D_0500E010[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E030.palette.inc"
};

u8 coffee01_D_0500E030[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E030.ci4.inc"
};

u16 coffee01_D_0500E490[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E4B0.palette.inc"
};

u8 coffee01_D_0500E4B0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E4B0.ci4.inc"
};

u16 coffee01_D_0500E910[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E930.palette.inc"
};

u8 coffee01_D_0500E930[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500E930.ci4.inc"
};

#if VERSION_US || VERSION_GW
u16 coffee01_D_0500EFC0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500EFE0.palette.inc"
};

u8 coffee01_D_0500EFE0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500EFE0.ci4.inc"
};
#endif

u16 coffee01_D_0500F1E0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500F3E0.palette.inc"
};

u8 coffee01_D_0500F3E0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500F3E0.ci8.inc"
};

u16 coffee01_D_0500FA20[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500FC20.palette.inc"
};

u8 coffee01_D_0500FC20[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500FC20.ci8.inc"
};

u16 coffee01_D_05010260[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05010460.palette.inc"
};

u8 coffee01_D_05010460[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05010460.ci8.inc"
};

u16 coffee01_D_05010AA0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05010CA0.palette.inc"
};

u8 coffee01_D_05010CA0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05010CA0.ci8.inc"
};

#if VERSION_CN
u16 coffee01_D_050058E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005908.palette.inc"
};

u8 coffee01_D_05005908[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05005908.ci4.inc"
};

u16 coffee01_D_0500D790[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D7B0.palette.inc"
};

u8 coffee01_D_0500D7B0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D7B0.ci4.inc"
};

u16 coffee01_D_0500D570[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D590.palette.inc"
};

u8 coffee01_D_0500D590[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D590.ci4.inc"
};

u16 coffee01_D_05007768[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007788.palette.inc"
};

u8 coffee01_D_05007788[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007788.ci4.inc"
};

u16 coffee01_D_0500D9B0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D9D0.palette.inc"
};

u8 coffee01_D_0500D9D0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500D9D0.ci4.inc"
};

u16 coffee01_D_05008EE8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008F08.palette.inc"
};

u8 coffee01_D_05008F08[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05008F08.ci4.inc"
};

u16 coffee01_D_0500DDF0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DE10.palette.inc"
};

u8 coffee01_D_0500DE10[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DE10.ci4.inc"
};

u16 coffee01_D_0500EFC0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500EFE0.palette.inc"
};

u8 coffee01_D_0500EFE0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500EFE0.ci4.inc"
};

u16 coffee01_D_05009988[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050099A8.palette.inc"
};

u8 coffee01_D_050099A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050099A8.ci4.inc"
};

u16 coffee01_D_05009768[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009788.palette.inc"
};

u8 coffee01_D_05009788[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05009788.ci4.inc"
};

u16 coffee01_D_0500DBD0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DBF0.palette.inc"
};

u8 coffee01_D_0500DBF0[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_0500DBF0.ci4.inc"
};

u16 coffee01_D_05007548[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007568.palette.inc"
};

u8 coffee01_D_05007568[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05007568.ci4.inc"
};

u16 coffee01_D_050017E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05001808.palette.inc"
};

u8 coffee01_D_05001808[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05001808.ci4.inc"
};

u16 coffee01_D_05002008[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002028.palette.inc"
};

u8 coffee01_D_05002028[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002028.ci4.inc"
};

u16 coffee01_D_05002828[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002848.palette.inc"
};

u8 coffee01_D_05002848[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05002848.ci4.inc"
};

u16 coffee01_D_05003048[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003068.palette.inc"
};

u8 coffee01_D_05003068[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003068.ci4.inc"
};

u16 coffee01_D_05003868[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003888.palette.inc"
};

u8 coffee01_D_05003888[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_05003888.ci4.inc"
};

u16 coffee01_D_05004088[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050040A8.palette.inc"
};

u8 coffee01_D_050040A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050040A8.ci4.inc"
};

u16 coffee01_D_050048A8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050048C8.palette.inc"
};

u8 coffee01_D_050048C8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050048C8.ci4.inc"
};

u16 coffee01_D_050050C8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050050E8.palette.inc"
};

u8 coffee01_D_050050E8[] ALIGNED(8) = {
#include "assets/coffee/coffee01/coffee01_D_050050E8.ci4.inc"
};
#endif

/* unreferenced data */
u32 coffee01_D_05011420[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05011440[] = {
#include "assets/coffee/coffee01/coffee01_D_05011440.vtx.inc.c"
};

Gfx coffee01_D_05011480[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05009768),
    gsDPLoadTextureBlock_4b(coffee01_D_05009788, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05011440, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05011570[] = {
    0xFFFFFF60, 0x000000A0, 0xFFFFFF88, 0x00000078, 0x00000000, 0x00000000, 0x000000A0, 0x00000000,
};

Vtx coffee01_D_05011590[] = {
#include "assets/coffee/coffee01/coffee01_D_05011590.vtx.inc.c"
};

Gfx coffee01_D_050115D0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_05000688),
    gsDPLoadTextureBlock_4b(coffee01_D_050006A8, G_IM_FMT_CI, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05011590, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050116C0[] = {
    0xFFFFFFC0, 0x00000040, 0xFFFFFFE0, 0x00000020, 0x00000000, 0x00000000, 0x00000040, 0x00000000,
};

Vtx coffee01_D_050116E0[] = {
#include "assets/coffee/coffee01/coffee01_D_050116E0.vtx.inc.c"
};

Gfx coffee01_D_05011760[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_050007A8),
    gsDPLoadTextureBlock_4b(coffee01_D_050007C8, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050116E0, 8, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05000FC8),
    gsDPLoadTextureBlock_4b(coffee01_D_05000FE8, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050118C0[] = {
    0xFFFFFF80, 0x00000080, 0xFFFFFFE0, 0x00000020, 0x00000000, 0x00000000, 0x00000080, 0x00000000,
};

Vtx coffee01_D_050118E0[] = {
#include "assets/coffee/coffee01/coffee01_D_050118E0.vtx.inc.c"
};

Gfx coffee01_D_050119E0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_050017E8),
    gsDPLoadTextureBlock_4b(coffee01_D_05001808, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050118E0, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05002008),
    gsDPLoadTextureBlock_4b(coffee01_D_05002028, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05002828),
    gsDPLoadTextureBlock_4b(coffee01_D_05002848, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(10, 8, 9, 0, 11, 10, 9, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05003048),
    gsDPLoadTextureBlock_4b(coffee01_D_05003068, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(14, 12, 13, 0, 15, 13, 12, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05011C20[] = {
    0xFFFFFF80, 0x00000080, 0xFFFFFFE0, 0x00000020, 0x00000000, 0x00000000, 0x00000080, 0x00000000,
};

Vtx coffee01_D_05011C40[] = {
#include "assets/coffee/coffee01/coffee01_D_05011C40.vtx.inc.c"
};

Gfx coffee01_D_05011D40[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05003868),
    gsDPLoadTextureBlock_4b(coffee01_D_05003888, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05011C40, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05004088),
    gsDPLoadTextureBlock_4b(coffee01_D_050040A8, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_050048A8),
    gsDPLoadTextureBlock_4b(coffee01_D_050048C8, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(10, 8, 9, 0, 11, 10, 9, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_050050C8),
    gsDPLoadTextureBlock_4b(coffee01_D_050050E8, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(14, 12, 13, 0, 15, 13, 12, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05011F80[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05011FA0[] = {
#include "assets/coffee/coffee01/coffee01_D_05011FA0.vtx.inc.c"
};

Gfx coffee01_D_05011FE0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_050058E8),
    gsDPLoadTextureBlock_4b(coffee01_D_05005908, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05011FA0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050120D0[] = {
    0xFFFFFFE4, 0x0000001C, 0xFFFFFFF2, 0x0000000E, 0x00000000, 0x00000000, 0x0000001C, 0x00000000,
};

Vtx coffee01_D_050120F0[] = {
#include "assets/coffee/coffee01/coffee01_D_050120F0.vtx.inc.c"
};

Gfx coffee01_D_05012130[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_05005B08),
    gsDPLoadTextureBlock(coffee01_D_05005D08, G_IM_FMT_CI, G_IM_SIZ_8b, 56, 36, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050120F0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012220[] = {
    0xFFFFFFC8, 0x00000038, 0xFFFFFFE6, 0x0000001E, 0x00000000, 0x00000000, 0x00000038, 0x00000000,
};

Vtx coffee01_D_05012240[] = {
#include "assets/coffee/coffee01/coffee01_D_05012240.vtx.inc.c"
};

Gfx coffee01_D_05012280[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_050064E8),
    gsDPLoadTextureBlock_4b(coffee01_D_05006508, G_IM_FMT_CI, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012240, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012370[] = {
    0xFFFFFFDA, 0x00000026, 0xFFFFFFEE, 0x00000014, 0x00000000, 0x00000000, 0x00000026, 0x00000000,
};

Vtx coffee01_D_05012390[] = {
#include "assets/coffee/coffee01/coffee01_D_05012390.vtx.inc.c"
};

Gfx coffee01_D_050123D0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_05006908),
    gsDPLoadTextureBlock_4b(coffee01_D_05006928, G_IM_FMT_CI, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012390, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050124C0[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_050124E0[] = {
#include "assets/coffee/coffee01/coffee01_D_050124E0.vtx.inc.c"
};

Gfx coffee01_D_05012520[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05007548),
    gsDPLoadTextureBlock_4b(coffee01_D_05007568, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050124E0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012610[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05012630[] = {
#include "assets/coffee/coffee01/coffee01_D_05012630.vtx.inc.c"
};

Gfx coffee01_D_05012670[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05007768),
    gsDPLoadTextureBlock_4b(coffee01_D_05007788, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012630, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012760[] = {
    0xFFFFFFE3, 0x00000020, 0xFFFFFFFF, 0x00000022, 0x00000001, 0x00000001, 0x00000022, 0x00000000,
};

Vtx coffee01_D_05012780[] = {
#include "assets/coffee/coffee01/coffee01_D_05012780.vtx.inc.c"
};

Gfx coffee01_D_050127C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_05007988),
    gsDPLoadTextureBlock_4b(coffee01_D_050079A8, G_IM_FMT_CI, 64, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012780, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050128B0[] = {
    0xFFFFFFE2, 0x0000001E, 0x00000000, 0x00000023, 0x00000004, 0x00000004, 0x00000023, 0x00000000,
};

Vtx coffee01_D_050128D0[] = {
#include "assets/coffee/coffee01/coffee01_D_050128D0.vtx.inc.c"
};

Gfx coffee01_D_05012910[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_05007E08),
    gsDPLoadTextureBlock_4b(coffee01_D_05007E28, G_IM_FMT_CI, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050128D0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012A00[] = {
    0xFFFFFF60, 0x000000A0, 0xFFFFFFE9, 0x00000016, 0xFFFFFFFA, 0xFFFFFFFA, 0x000000A0, 0x00000000,
};

Vtx coffee01_D_05012A20[] = {
#include "assets/coffee/coffee01/coffee01_D_05012A20.vtx.inc.c"
};

Gfx coffee01_D_05012B20[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05008228),
    gsDPLoadTextureBlock_4b(coffee01_D_05008248, G_IM_FMT_CI, 80, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012A20, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05008888),
    gsDPLoadTextureBlock_4b(coffee01_D_050088A8, G_IM_FMT_CI, 80, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 4, 6, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05000028),
    gsDPLoadTextureBlock_4b(coffee01_D_05000048, G_IM_FMT_CI, 80, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(10, 8, 9, 0, 11, 8, 10, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_05009108),
    gsDPLoadTextureBlock_4b(coffee01_D_05009128, G_IM_FMT_CI, 80, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(14, 12, 13, 0, 15, 12, 14, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012D60[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05012D80[] = {
#include "assets/coffee/coffee01/coffee01_D_05012D80.vtx.inc.c"
};

Gfx coffee01_D_05012DC0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05008EE8),
    gsDPLoadTextureBlock_4b(coffee01_D_05008F08, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012D80, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05012EB0[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05012ED0[] = {
#include "assets/coffee/coffee01/coffee01_D_05012ED0.vtx.inc.c"
};

Gfx coffee01_D_05012F10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_05009988),
    gsDPLoadTextureBlock_4b(coffee01_D_050099A8, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05012ED0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013000[] = {
    0xFFFFFFE6, 0x00000017, 0xFFFFFFFB, 0x00000032, 0x00000000, 0x00000000, 0x00000032, 0x00000000,
};

Vtx coffee01_D_05013020[] = {
#include "assets/coffee/coffee01/coffee01_D_05013020.vtx.inc.c"
};

Gfx coffee01_D_05013160[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_05009BA8),
    gsDPLoadTextureBlock(coffee01_D_05009DA8, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 51, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013020, 20, 0),
    gsSP2Triangles(2, 0, 1, 0, 5, 3, 4, 0),
    gsSP2Triangles(6, 0, 2, 0, 9, 7, 8, 0),
    gsSP2Triangles(11, 3, 10, 0, 10, 3, 5, 0),
    gsSP2Triangles(13, 6, 12, 0, 14, 12, 6, 0),
    gsSP2Triangles(15, 14, 6, 0, 15, 6, 2, 0),
    gsSP2Triangles(18, 16, 17, 0, 5, 7, 9, 0),
    gsSP2Triangles(10, 5, 9, 0, 16, 18, 10, 0),
    gsSP2Triangles(19, 10, 9, 0, 19, 15, 2, 0),
    gsSP2Triangles(19, 2, 16, 0, 10, 10, 19, 0),
    gsSP1Triangle(16, 10, 19, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013298[] = {
    0xFFFFFFF1, 0x0000000F, 0xFFFFFFF1, 0x0000000F, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000000F, 0x00000000,
};

Vtx coffee01_D_050132B8[] = {
#include "assets/coffee/coffee01/coffee01_D_050132B8.vtx.inc.c"
};

Gfx coffee01_D_050132F8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_05006D28),
    gsDPLoadTextureBlock_4b(coffee01_D_05006D48, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050132B8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050133E8[] = {
    0xFFFFFFB0, 0x00000050, 0x00000000, 0x00000064, 0x00000000, 0x00000000, 0x00000064, 0x00000000,
};

Vtx coffee01_D_05013408[] = {
#include "assets/coffee/coffee01/coffee01_D_05013408.vtx.inc.c"
};

Gfx coffee01_D_05013508[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500A5A0),
    gsDPLoadTextureBlock_4b(coffee01_D_0500A5C0, G_IM_FMT_CI, 80, 50, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013408, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500AD90),
    gsDPLoadTextureBlock_4b(coffee01_D_0500ADB0, G_IM_FMT_CI, 80, 50, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 4, 6, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500B580),
    gsDPLoadTextureBlock_4b(coffee01_D_0500B5A0, G_IM_FMT_CI, 80, 50, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(10, 8, 9, 0, 11, 8, 10, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500BD70),
    gsDPLoadTextureBlock_4b(coffee01_D_0500BD90, G_IM_FMT_CI, 80, 50, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(14, 12, 13, 0, 15, 12, 14, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013748[] = {
    0xFFFFFF92, 0x0000006E, 0x00000000, 0x0000003C, 0x00000005, 0x00000005, 0x0000006E, 0x00000000,
};

Vtx coffee01_D_05013768[] = {
#include "assets/coffee/coffee01/coffee01_D_05013768.vtx.inc.c"
};

Gfx coffee01_D_050137C8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500C560),
    gsDPLoadTextureBlock_4b(coffee01_D_0500C580, G_IM_FMT_CI, 128, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 7, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013768, 6, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSP2Triangles(5, 3, 4, 0, 5, 0, 3, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050138C0[] = {
    0xFFFFFF7E, 0x00000082, 0x00000000, 0x00000028, 0x00000000, 0x00000000, 0x00000082, 0x00000000,
};

Vtx coffee01_D_050138E0[] = {
#include "assets/coffee/coffee01/coffee01_D_050138E0.vtx.inc.c"
};

Gfx coffee01_D_05013940[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500CD80),
    gsDPLoadTextureBlock_4b(coffee01_D_0500CDA0, G_IM_FMT_CI, 160, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050138E0, 6, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSP2Triangles(5, 3, 4, 0, 5, 0, 3, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013A38[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05013A58[] = {
#include "assets/coffee/coffee01/coffee01_D_05013A58.vtx.inc.c"
};

Gfx coffee01_D_05013A98[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500D570),
    gsDPLoadTextureBlock_4b(coffee01_D_0500D590, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013A58, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013B88[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05013BA8[] = {
#include "assets/coffee/coffee01/coffee01_D_05013BA8.vtx.inc.c"
};

Gfx coffee01_D_05013BE8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500D790),
    gsDPLoadTextureBlock_4b(coffee01_D_0500D7B0, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013BA8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013CD8[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05013CF8[] = {
#include "assets/coffee/coffee01/coffee01_D_05013CF8.vtx.inc.c"
};

Gfx coffee01_D_05013D38[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500D9B0),
    gsDPLoadTextureBlock_4b(coffee01_D_0500D9D0, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013CF8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013E28[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05013E48[] = {
#include "assets/coffee/coffee01/coffee01_D_05013E48.vtx.inc.c"
};

Gfx coffee01_D_05013E88[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500DBD0),
    gsDPLoadTextureBlock_4b(coffee01_D_0500DBF0, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013E48, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05013F78[] = {
    0xFFFFFF60, 0x000000A0, 0x00000000, 0x000000F0, 0x00000000, 0x00000000, 0x000000F0, 0x00000000,
};

Vtx coffee01_D_05013F98[] = {
#include "assets/coffee/coffee01/coffee01_D_05013F98.vtx.inc.c"
};

/* unreferenced data */
Gfx coffee01_D_05014018[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05013F98, 8, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSP2Triangles(6, 4, 5, 0, 7, 5, 4, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050140A8[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_050140C8[] = {
#include "assets/coffee/coffee01/coffee01_D_050140C8.vtx.inc.c"
};

Gfx coffee01_D_05014108[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500DDF0),
    gsDPLoadTextureBlock_4b(coffee01_D_0500DE10, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050140C8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050141F8[] = {
    0xFFFFFFD5, 0x00000028, 0xFFFFFFFF, 0x00000067, 0xFFFFFFFD, 0xFFFFFFFD, 0x00000067, 0x00000000,
};

Vtx coffee01_D_05014218[] = {
#include "assets/coffee/coffee01/coffee01_D_05014218.vtx.inc.c"
};

Gfx coffee01_D_05014298[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500E010),
    gsDPLoadTextureBlock_4b(coffee01_D_0500E030, G_IM_FMT_CI, 64, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05014218, 8, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500E490),
    gsDPLoadTextureBlock_4b(coffee01_D_0500E4B0, G_IM_FMT_CI, 64, 35, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(6, 4, 5, 0, 7, 4, 6, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050143F8[] = {
    0xFFFFFFD7, 0x0000002A, 0xFFFFFFFC, 0x00000064, 0x00000000, 0x00000000, 0x00000064, 0x00000000,
};

Vtx coffee01_D_05014418[] = {
#include "assets/coffee/coffee01/coffee01_D_05014418.vtx.inc.c"
};

Gfx coffee01_D_05014458[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500E910),
    gsDPLoadTextureBlock_4b(coffee01_D_0500E930, G_IM_FMT_CI, 48, 70, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05014418, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05014548[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF8, 0x00000008, 0x00000000, 0x00000000, 0x00000008, 0x00000000,
};

Vtx coffee01_D_05014568[] = {
#include "assets/coffee/coffee01/coffee01_D_05014568.vtx.inc.c"
};

Gfx coffee01_D_050145A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPLoadTLUT_pal16(0, coffee01_D_0500EFC0),
    gsDPLoadTextureBlock_4b(coffee01_D_0500EFE0, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05014568, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05014698[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF4, 0x00000019, 0xFFFFFFFC, 0xFFFFFFFC, 0x00000019, 0x00000000,
};

Vtx coffee01_D_050146B8[] = {
#include "assets/coffee/coffee01/coffee01_D_050146B8.vtx.inc.c"
};

Gfx coffee01_D_050147B8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_0500F1E0),
    gsDPLoadTextureBlock(coffee01_D_0500F3E0, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 40, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050146B8, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 5, 3, 4, 0),
    gsSP2Triangles(8, 6, 7, 0, 2, 3, 5, 0),
    gsSP2Triangles(10, 8, 9, 0, 11, 8, 10, 0),
    gsSP2Triangles(0, 2, 5, 0, 13, 5, 12, 0),
    gsSP2Triangles(14, 5, 13, 0, 0, 5, 14, 0),
    gsSP2Triangles(14, 6, 8, 0, 0, 14, 8, 0),
    gsSP2Triangles(15, 0, 8, 0, 8, 11, 15, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_050148D8[] = {
    0xFFFFFFED, 0x00000014, 0xFFFFFFF4, 0x00000019, 0xFFFFFFFC, 0xFFFFFFFC, 0x00000019, 0x00000000,
};

Vtx coffee01_D_050148F8[] = {
#include "assets/coffee/coffee01/coffee01_D_050148F8.vtx.inc.c"
};

Gfx coffee01_D_050149D8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_0500FA20),
    gsDPLoadTextureBlock(coffee01_D_0500FC20, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 40, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_050148F8, 14, 0),
    gsSP2Triangles(2, 0, 1, 0, 5, 3, 4, 0),
    gsSP2Triangles(7, 0, 6, 0, 8, 3, 5, 0),
    gsSP2Triangles(11, 9, 10, 0, 5, 9, 11, 0),
    gsSP2Triangles(8, 5, 11, 0, 13, 11, 12, 0),
    gsSP2Triangles(8, 11, 13, 0, 13, 6, 0, 0),
    gsSP2Triangles(2, 8, 13, 0, 13, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05014AF0[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF3, 0x00000018, 0xFFFFFFFC, 0xFFFFFFFC, 0x00000018, 0x00000000,
};

Vtx coffee01_D_05014B10[] = {
#include "assets/coffee/coffee01/coffee01_D_05014B10.vtx.inc.c"
};

Gfx coffee01_D_05014C10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_05010260),
    gsDPLoadTextureBlock(coffee01_D_05010460, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 40, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05014B10, 16, 0),
    gsSP2Triangles(2, 0, 1, 0, 4, 2, 3, 0),
    gsSP2Triangles(0, 2, 4, 0, 6, 0, 5, 0),
    gsSP2Triangles(7, 5, 0, 0, 10, 8, 9, 0),
    gsSP2Triangles(11, 8, 3, 0, 13, 1, 12, 0),
    gsSP2Triangles(14, 12, 1, 0, 8, 10, 4, 0),
    gsSP2Triangles(3, 8, 4, 0, 4, 7, 0, 0),
    gsSP2Triangles(15, 2, 1, 0, 0, 14, 1, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 coffee01_D_05014D30[] = {
    0xFFFFFF60, 0x000000A0, 0xFFFFFF88, 0x00000078, 0x00000000, 0x00000000, 0x000000A0, 0x00000000,
};

Vtx coffee01_D_05014D50[] = {
#include "assets/coffee/coffee01/coffee01_D_05014D50.vtx.inc.c"
};

Gfx coffee01_D_05014D90[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(coffee01_D_05010AA0),
    gsDPLoadTextureBlock(coffee01_D_05010CA0, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 240, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(coffee01_D_05014D50, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 1, 0, 0),
    gsSPEndDisplayList(),
};

Lws coffee01_D_05014E80 = {
    0, 172, 60, coffee01_D_05014E80_COUNT, coffee01_D_05014EB0, coffee01_D_05015180,
};

Lws coffee01_D_05014E98 = {
    0, 172, 60, coffee01_D_05014E98_COUNT, coffee01_D_05015018, coffee01_D_05015180,
};

Lws_unk_10 coffee01_D_05014EB0[] = {
    { coffee01_D_050115D0, -1, 3, 0, 0, 0 },  { coffee01_D_05012280, -1, 8, 3, 0, 0 },
    { coffee01_D_050123D0, -1, 9, 11, 0, 0 }, { coffee01_D_05013508, -1, 7, 20, 0, 0 },
    { coffee01_D_050137C8, -1, 7, 27, 0, 0 }, { coffee01_D_05013940, -1, 7, 34, 0, 0 },
    { coffee01_D_05014298, -1, 4, 41, 0, 0 }, { coffee01_D_05014298, -1, 4, 45, 0, 0 },
    { coffee01_D_05014458, -1, 4, 49, 0, 0 }, { coffee01_D_050127C0, -1, 4, 53, 0, 0 },
    { coffee01_D_050127C0, -1, 4, 57, 0, 0 }, { coffee01_D_050127C0, -1, 4, 61, 0, 0 },
    { coffee01_D_05012910, -1, 4, 65, 0, 0 }, { coffee01_D_05012910, -1, 4, 69, 0, 0 },
    { coffee01_D_05012B20, -1, 4, 73, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_05014EB0) == coffee01_D_05014E80_COUNT, "");

Lws_unk_10 coffee01_D_05015018[] = {
    { coffee01_D_05014D90, -1, 3, 0, 0, 0 },  { coffee01_D_05012280, -1, 8, 3, 0, 0 },
    { coffee01_D_050123D0, -1, 9, 11, 0, 0 }, { coffee01_D_05013508, -1, 7, 20, 0, 0 },
    { coffee01_D_050137C8, -1, 7, 27, 0, 0 }, { coffee01_D_05013940, -1, 7, 34, 0, 0 },
    { coffee01_D_05014298, -1, 4, 41, 0, 0 }, { coffee01_D_05014298, -1, 4, 45, 0, 0 },
    { coffee01_D_05014458, -1, 4, 49, 0, 0 }, { coffee01_D_050127C0, -1, 4, 53, 0, 0 },
    { coffee01_D_050127C0, -1, 4, 57, 0, 0 }, { coffee01_D_050127C0, -1, 4, 61, 0, 0 },
    { coffee01_D_05012910, -1, 4, 65, 0, 0 }, { coffee01_D_05012910, -1, 4, 69, 0, 0 },
    { coffee01_D_05012B20, -1, 4, 73, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_05015018) == coffee01_D_05014E98_COUNT, "");

Lws_unk_14 coffee01_D_05015180[] = {
    { 0, 1, 0, 960, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 50, 2, 0, 960, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 172, -1, 0, 960, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 4, -800, -800, 80, -2880, 2880, -2880, 2375, 2375, 4096 },
    { 50, 5, -800, 1280, 80, -2880, 2880, -2928, 2375, 2375, 4096 },
    { 62, 6, -800, 1293, 80, -2880, 2880, -2864, 2375, 2375, 4096 },
    { 102, 7, -800, 1346, 80, -2880, 2880, -2896, 2375, 2375, 4096 },
    { 112, 8, -800, 1360, 80, -2880, 2880, -2832, 2375, 2375, 4096 },
    { 122, 9, -800, 1359, 80, -2880, 2880, -2896, 2375, 2375, 4096 },
    { 162, 10, -800, 1293, 80, -2880, 2880, -2864, 2375, 2375, 4096 },
    { 172, -1, -800, 1280, 80, -2880, 2880, -2928, 2375, 2375, 4096 },
    { 0, 12, 800, -800, 80, -2880, 2880, -2880, 2375, 2375, 4096 },
    { 50, 13, 800, 1341, 80, -2880, 2880, -2880, 2375, 2375, 4096 },
    { 72, 14, 800, 1314, 80, -2880, 2880, -2864, 2375, 2375, 4096 },
    { 82, 15, 800, 1304, 80, -2880, 2880, -2928, 2375, 2375, 4096 },
    { 92, 16, 800, 1314, 80, -2880, 2880, -2864, 2375, 2375, 4096 },
    { 132, 17, 800, 1357, 80, -2880, 2880, -2896, 2375, 2375, 4096 },
    { 142, 18, 800, 1368, 80, -2880, 2880, -2832, 2375, 2375, 4096 },
    { 152, 19, 800, 1367, 80, -2880, 2880, -2896, 2375, 2375, 4096 },
    { 172, -1, 800, 1341, 80, -2880, 2880, -2880, 2375, 2375, 4096 },
    { 0, 21, 0, -800, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 40, 22, 0, 560, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 50, 23, 0, 560, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 82, 24, 0, 520, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 112, 25, 0, 560, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 142, 26, 0, 520, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 172, -1, 0, 560, 160, -2880, 2880, -2880, 3276, 3276, 4096 },
    { 0, 28, 520, -800, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 40, 29, 520, 520, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 50, 30, 520, 520, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 82, 31, 520, 544, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 112, 32, 520, 520, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 142, 33, 520, 544, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 172, -1, 520, 520, 160, -2880, 2880, -2880, 3563, 3563, 4096 },
    { 0, 35, -600, -800, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 40, 36, -600, 544, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 50, 37, -600, 544, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 82, 38, -600, 560, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 112, 39, -600, 544, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 142, 40, -600, 560, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 172, -1, -600, 544, 160, -2880, 2880, -2880, 5038, 5038, 4096 },
    { 0, 42, -960, -800, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 30, 43, -960, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 50, 44, -960, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 172, -1, -960, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 0, 46, 1040, -800, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 30, 47, 1040, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 50, 48, 1040, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 172, -1, 1040, 576, 240, -2880, 2880, -2880, 3276, 2703, 4096 },
    { 0, 50, 240, -800, 240, -2880, 2880, -2880, 2457, 2703, 4096 },
    { 30, 51, 240, 560, 240, -2880, 2880, -2880, 2457, 2703, 4096 },
    { 50, 52, 240, 560, 240, -2880, 2880, -2880, 2457, 2703, 4096 },
    { 172, -1, 240, 560, 240, -2880, 2880, -2880, 2457, 2703, 4096 },
    { 0, 54, -1240, -800, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 20, 55, -1240, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 50, 56, -1240, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 172, -1, -1240, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 0, 58, 176, -800, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 20, 59, 176, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 50, 60, 176, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 172, -1, 176, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 0, 62, 1160, -800, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 20, 63, 1160, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 50, 64, 1160, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 172, -1, 1160, 568, 320, -2880, 2880, -2880, 3850, 3850, 4096 },
    { 0, 66, -728, -800, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 20, 67, -728, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 50, 68, -728, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 172, -1, -728, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 0, 70, 600, -800, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 20, 71, 600, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 50, 72, 600, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 172, -1, 600, 568, 320, -2880, 2880, -2880, 3850, 3747, 4096 },
    { 0, 74, 0, -800, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 10, 75, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 50, 76, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 172, -1, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 coffee01_D_050159EC[] = {
    0x00000000, 0x0000004E, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000032, 0x0000004F, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x000000AC, 0xFFFFFFFF, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws coffee01_D_05015A40 = {
    0, 499, 60, coffee01_D_05015A40_COUNT, coffee01_D_05015A58, coffee01_D_05015B30,
};

Lws_unk_10 coffee01_D_05015A58[] = {
    { coffee01_D_050147B8, -1, 50, 0, 0, 0 },    { coffee01_D_05014C10, -1, 51, 50, 0, 0 },
    { coffee01_D_050149D8, -1, 52, 101, 0, 0 },  { coffee01_D_05013160, -1, 43, 153, 0, 0 },
    { coffee01_D_05012130, -1, 42, 196, 0, 0 },  { coffee01_D_050132F8, -1, 102, 238, 0, 0 },
    { coffee01_D_050132F8, -1, 101, 340, 0, 0 }, { coffee01_D_050132F8, -1, 102, 441, 0, 0 },
    { coffee01_D_050132F8, -1, 101, 543, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_05015A58) == coffee01_D_05015A40_COUNT, "");

Lws_unk_14 coffee01_D_05015B30[] = {
    { 0, 1, 0, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 2, 2, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 7, 3, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 12, 4, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 17, 5, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 22, 6, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 27, 7, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 32, 8, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 37, 9, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 42, 10, -1028, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 47, 11, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 52, 12, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 57, 13, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 62, 14, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 67, 15, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 77, 16, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 82, 17, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 87, 18, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 92, 19, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 97, 20, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 102, 21, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 107, 22, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 112, 23, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 117, 24, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 122, 25, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 127, 26, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 132, 27, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 137, 28, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 142, 29, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 147, 30, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 152, 31, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 157, 32, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 162, 33, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 167, 34, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 172, 35, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 177, 36, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 182, 37, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 187, 38, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 192, 39, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 197, 40, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 202, 41, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 207, 42, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 212, 43, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 217, 44, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 222, 45, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 227, 46, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 232, 47, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 233, 48, 1435, -4000, 400, -2880, 0, -2944, 4096, 4096, 4096 },
    { 237, 49, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 499, -1, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 51, 0, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 31, 52, 0, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 32, 53, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 37, 54, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 42, 55, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 47, 56, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 52, 57, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 57, 58, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 62, 59, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 67, 60, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 77, 61, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 82, 62, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 87, 63, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 92, 64, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 97, 65, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 102, 66, -642, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 107, 67, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 112, 68, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 117, 69, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 122, 70, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 127, 71, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 132, 72, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 137, 73, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 142, 74, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 147, 75, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 152, 76, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 157, 77, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 162, 78, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 167, 79, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 172, 80, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 177, 81, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 182, 82, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 187, 83, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 192, 84, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 197, 85, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 202, 86, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 207, 87, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 212, 88, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 217, 89, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 222, 90, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 227, 91, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 232, 92, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 237, 93, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 242, 94, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 247, 95, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 252, 96, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 257, 97, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 262, 98, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 263, 99, 1435, -4000, 400, -2880, 0, -2944, 4096, 4096, 4096 },
    { 267, 100, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 499, -1, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 102, 0, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 55, 103, 0, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 57, 104, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 63, 105, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 69, 106, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 75, 107, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 81, 108, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 87, 109, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 93, 110, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 99, 111, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 105, 112, -1028, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 111, 113, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 117, 114, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 123, 115, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 129, 116, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 135, 117, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 141, 118, -642, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 147, 119, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 153, 120, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 159, 121, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 165, 122, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 171, 123, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 177, 124, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 183, 125, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 189, 126, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 195, 127, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 201, 128, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 207, 129, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 213, 130, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 219, 131, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 225, 132, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 231, 133, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 237, 134, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 243, 135, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 249, 136, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 255, 137, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 261, 138, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 267, 139, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 273, 140, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 279, 141, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 285, 142, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 291, 143, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 297, 144, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 303, 145, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 309, 146, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 315, 147, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 321, 148, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 327, 149, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 333, 150, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 334, 151, 1433, -4000, 400, -2880, 0, -2946, 4096, 4096, 4096 },
    { 339, 152, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 499, -1, 1486, -4000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 154, -1600, -4000, 400, -2880, 8, -2753, 4096, 4096, 4096 },
    { 192, 155, -1600, -4000, 400, -2880, 8, -2753, 4096, 4096, 4096 },
    { 193, 156, -1440, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 201, 157, -1290, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 209, 158, -1250, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 217, 159, -1170, 592, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 225, 160, -1040, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 233, 161, -1000, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 241, 162, -940, 592, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 249, 163, -790, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 257, 164, -750, 600, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 265, 165, -670, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 273, 166, -540, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 281, 167, -500, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 289, 168, -400, 604, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 297, 169, -270, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 305, 170, -240, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 313, 171, -150, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 321, 172, -10, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 329, 173, 20, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 337, 174, 110, 580, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 345, 175, 220, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 353, 176, 270, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 361, 177, 350, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 369, 178, 440, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 370, 179, 440, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 378, 180, 480, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 386, 181, 570, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 394, 182, 690, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 402, 183, 730, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 410, 184, 810, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 418, 185, 940, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 426, 186, 980, 588, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 434, 187, 1060, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 442, 188, 1190, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 450, 189, 1230, 600, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 458, 190, 1330, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 466, 191, 1460, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 474, 192, 1490, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 482, 193, 1580, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 490, 194, 1720, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 498, 195, 1750, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 499, -1, 1830, -4000, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 0, 197, -1600, -4040, 400, -2880, 8, -2816, 4096, 4096, 4096 },
    { 192, 198, -1600, -4040, 400, -2880, 8, -2816, 4096, 4096, 4096 },
    { 193, 199, -1440, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 201, 200, -1290, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 209, 201, -1250, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 217, 202, -1170, 1032, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 225, 203, -1040, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 233, 204, -1000, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 241, 205, -940, 1032, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 249, 206, -790, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 257, 207, -750, 1040, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 265, 208, -670, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 273, 209, -540, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 281, 210, -500, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 289, 211, -400, 1044, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 297, 212, -270, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 305, 213, -240, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 313, 214, -150, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 321, 215, -10, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 329, 216, 20, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 337, 217, 110, 1020, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 345, 218, 220, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 353, 219, 270, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 361, 220, 350, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 369, 221, 440, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 370, 222, 440, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 378, 223, 480, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 386, 224, 570, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 394, 225, 690, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 402, 226, 730, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 410, 227, 810, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 418, 228, 940, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 426, 229, 980, 1028, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 434, 230, 1060, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 442, 231, 1190, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 450, 232, 1230, 1040, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 458, 233, 1330, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 466, 234, 1460, 1084, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 474, 235, 1490, 1044, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 482, 236, 1580, 1028, 400, -2880, 0, -2816, 4096, 4096, 4096 },
    { 490, 237, 1720, -4040, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 499, -1, 1786, -4653, 400, -2880, 0, -2974, 4096, 4096, 4096 },
    { 0, 239, -2096, -4000, 880, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 240, -1480, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 5, 241, -1552, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 8, 242, -1600, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 9, 243, -1600, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 13, 244, -1600, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 14, 245, -1320, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 18, 246, -1392, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 20, 247, -1440, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 21, 248, -1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 25, 249, -1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 26, 250, -1160, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 30, 251, -1232, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 33, 252, -1280, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 34, 253, -1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 37, 254, -1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 39, 255, -1000, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 42, 256, -1072, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 45, 257, -1120, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 46, 258, -1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 50, 259, -1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 51, 260, -840, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 55, 261, -912, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 57, 262, -960, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 59, 263, -960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 62, 264, -960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 64, 265, -679, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 67, 266, -752, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 70, 267, -800, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 71, 268, -800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 75, 269, -800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 76, 270, -520, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 80, 271, -591, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 82, 272, -640, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 83, 273, -640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 87, 274, -640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 88, 275, -360, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 92, 276, -431, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 95, 277, -480, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 96, 278, -480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 99, 279, -480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 101, 280, -200, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 104, 281, -271, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 107, 282, -323, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 108, 283, -322, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 112, 284, -320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 113, 285, -40, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 117, 286, -112, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 119, 287, -160, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 121, 288, -160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 124, 289, -160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 126, 290, 120, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 129, 291, 48, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 132, 292, 0, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 133, 293, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 137, 294, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 138, 295, 280, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 142, 296, 208, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 144, 297, 160, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 145, 298, 160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 149, 299, 160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 150, 300, 440, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 154, 301, 368, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 157, 302, 320, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 158, 303, 320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 161, 304, 320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 163, 305, 600, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 166, 306, 528, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 169, 307, 480, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 170, 308, 480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 174, 309, 480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 175, 310, 760, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 179, 311, 688, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 181, 312, 640, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 183, 313, 640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 186, 314, 640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 188, 315, 920, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 191, 316, 848, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 194, 317, 800, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 195, 318, 800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 199, 319, 800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 200, 320, 1080, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 204, 321, 1008, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 206, 322, 960, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 207, 323, 960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 211, 324, 960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 212, 325, 1240, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 216, 326, 1168, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 219, 327, 1116, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 220, 328, 1117, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 223, 329, 1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 225, 330, 1400, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 228, 331, 1328, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 231, 332, 1280, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 232, 333, 1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 236, 334, 1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 237, 335, 1560, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 241, 336, 1488, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 243, 337, 1440, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 245, 338, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 248, 339, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 499, -1, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 0, 341, -2056, -2990, 880, -2880, 2880, -2880, 4096, 6144, 4096 },
    { 7, 342, -2056, -2990, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 8, 343, -1440, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 11, 344, -1512, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 14, 345, -1560, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 15, 346, -1560, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 19, 347, -1560, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 20, 348, -1280, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 24, 349, -1352, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 26, 350, -1400, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 27, 351, -1400, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 31, 352, -1400, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 32, 353, -1120, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 36, 354, -1192, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 39, 355, -1240, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 40, 356, -1240, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 43, 357, -1240, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 45, 358, -960, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 48, 359, -1032, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 51, 360, -1080, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 52, 361, -1080, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 56, 362, -1080, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 57, 363, -800, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 61, 364, -872, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 63, 365, -920, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 65, 366, -920, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 68, 367, -920, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 70, 368, -639, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 73, 369, -712, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 76, 370, -760, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 77, 371, -760, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 81, 372, -760, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 82, 373, -480, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 86, 374, -551, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 88, 375, -600, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 89, 376, -600, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 93, 377, -600, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 94, 378, -320, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 98, 379, -391, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 101, 380, -440, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 102, 381, -440, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 105, 382, -440, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 107, 383, -160, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 110, 384, -231, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 113, 385, -283, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 118, 386, -280, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 119, 387, 0, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 123, 388, -72, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 125, 389, -120, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 127, 390, -120, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 130, 391, -120, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 132, 392, 160, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 135, 393, 88, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 138, 394, 40, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 139, 395, 40, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 143, 396, 40, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 144, 397, 320, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 148, 398, 248, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 150, 399, 200, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 151, 400, 200, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 155, 401, 200, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 156, 402, 480, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 160, 403, 408, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 163, 404, 360, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 164, 405, 360, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 167, 406, 360, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 169, 407, 640, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 172, 408, 568, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 175, 409, 520, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 176, 410, 520, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 180, 411, 520, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 181, 412, 800, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 185, 413, 728, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 187, 414, 680, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 189, 415, 680, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 192, 416, 680, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 194, 417, 960, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 197, 418, 888, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 200, 419, 840, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 201, 420, 840, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 205, 421, 840, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 206, 422, 1120, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 210, 423, 1048, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 212, 424, 1000, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 213, 425, 1000, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 217, 426, 1000, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 218, 427, 1280, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 222, 428, 1208, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 225, 429, 1156, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 229, 430, 1160, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 231, 431, 1440, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 234, 432, 1368, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 237, 433, 1320, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 238, 434, 1320, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 242, 435, 1320, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 243, 436, 1600, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 247, 437, 1528, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 249, 438, 1480, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 251, 439, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 254, 440, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 499, -1, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 0, 442, -2096, -4000, 880, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 31, 443, -2096, -4000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 32, 444, -1480, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 35, 445, -1552, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 38, 446, -1600, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 39, 447, -1600, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 43, 448, -1600, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 44, 449, -1320, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 48, 450, -1392, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 50, 451, -1440, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 51, 452, -1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 55, 453, -1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 56, 454, -1160, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 60, 455, -1232, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 63, 456, -1280, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 64, 457, -1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 67, 458, -1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 69, 459, -1000, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 75, 460, -1120, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 76, 461, -1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 80, 462, -1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 81, 463, -840, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 85, 464, -912, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 87, 465, -960, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 89, 466, -960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 92, 467, -960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 94, 468, -679, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 97, 469, -752, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 100, 470, -800, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 101, 471, -800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 105, 472, -800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 106, 473, -520, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 110, 474, -591, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 112, 475, -640, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 113, 476, -640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 117, 477, -640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 118, 478, -360, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 122, 479, -431, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 125, 480, -480, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 126, 481, -480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 129, 482, -480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 131, 483, -200, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 134, 484, -271, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 137, 485, -323, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 138, 486, -322, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 142, 487, -320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 143, 488, -40, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 147, 489, -112, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 149, 490, -160, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 151, 491, -160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 154, 492, -160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 156, 493, 120, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 159, 494, 48, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 162, 495, 0, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 163, 496, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 167, 497, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 168, 498, 280, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 172, 499, 208, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 174, 500, 160, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 175, 501, 160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 179, 502, 160, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 180, 503, 440, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 184, 504, 368, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 187, 505, 320, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 188, 506, 320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 191, 507, 320, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 193, 508, 600, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 196, 509, 528, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 199, 510, 480, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 200, 511, 480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 204, 512, 480, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 205, 513, 760, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 209, 514, 688, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 211, 515, 640, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 213, 516, 640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 216, 517, 640, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 218, 518, 920, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 221, 519, 848, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 224, 520, 800, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 225, 521, 800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 229, 522, 800, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 230, 523, 1080, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 234, 524, 1008, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 236, 525, 960, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 237, 526, 960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 241, 527, 960, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 242, 528, 1240, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 246, 529, 1168, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 249, 530, 1116, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 250, 531, 1117, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 253, 532, 1120, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 255, 533, 1400, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 258, 534, 1328, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 261, 535, 1280, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 262, 536, 1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 266, 537, 1280, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 267, 538, 1560, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 271, 539, 1488, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 273, 540, 1440, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 275, 541, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 278, 542, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 499, -1, 1440, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 0, 544, -2056, -2990, 880, -2880, 2880, -2880, 4096, 6144, 4096 },
    { 37, 545, -2056, -2990, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 38, 546, -1440, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 41, 547, -1512, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 44, 548, -1560, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 45, 549, -1560, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 49, 550, -1560, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 50, 551, -1280, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 54, 552, -1352, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 56, 553, -1400, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 57, 554, -1400, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 61, 555, -1400, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 62, 556, -1120, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 66, 557, -1192, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 69, 558, -1240, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 70, 559, -1240, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 73, 560, -1240, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 75, 561, -960, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 78, 562, -1032, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 81, 563, -1080, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 82, 564, -1080, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 86, 565, -1080, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 87, 566, -800, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 91, 567, -872, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 93, 568, -920, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 95, 569, -920, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 98, 570, -920, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 100, 571, -639, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 103, 572, -712, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 106, 573, -760, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 107, 574, -760, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 111, 575, -760, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 112, 576, -480, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 116, 577, -551, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 118, 578, -600, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 119, 579, -600, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 123, 580, -600, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 124, 581, -320, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 128, 582, -391, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 131, 583, -440, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 132, 584, -440, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 135, 585, -440, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 137, 586, -160, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 140, 587, -231, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 143, 588, -283, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 148, 589, -280, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 149, 590, 0, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 153, 591, -72, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 155, 592, -120, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 157, 593, -120, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 160, 594, -120, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 162, 595, 160, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 165, 596, 88, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 168, 597, 40, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 169, 598, 40, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 173, 599, 40, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 174, 600, 320, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 178, 601, 248, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 180, 602, 200, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 181, 603, 200, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 185, 604, 200, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 186, 605, 480, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 190, 606, 408, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 193, 607, 360, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 194, 608, 360, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 197, 609, 360, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 199, 610, 640, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 202, 611, 568, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 205, 612, 520, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 206, 613, 520, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 210, 614, 520, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 211, 615, 800, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 215, 616, 728, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 217, 617, 680, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 219, 618, 680, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 222, 619, 680, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 224, 620, 960, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 227, 621, 888, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 230, 622, 840, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 231, 623, 840, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 235, 624, 840, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 236, 625, 1120, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 240, 626, 1048, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 242, 627, 1000, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 243, 628, 1000, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 247, 629, 1000, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 248, 630, 1280, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 252, 631, 1208, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 255, 632, 1156, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 259, 633, 1160, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 261, 634, 1440, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 264, 635, 1368, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 267, 636, 1320, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 268, 637, 1320, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 272, 638, 1320, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 273, 639, 1600, 880, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 277, 640, 1528, 964, 880, -2880, 2880, -2880, 819, 1228, 4096 },
    { 279, 641, 1480, 957, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 281, 642, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 284, 643, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
    { 499, -1, 1480, -2990, 880, -2880, 2880, -2880, 409, 614, 4096 },
};

/* unreferenced data */
u32 coffee01_D_0501A1A0[] = {
    0x00000000, 0x00000285, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x000001F3, 0xFFFFFFFF, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws coffee01_D_0501A1D8 = {
    0, 604, 60, coffee01_D_0501A1D8_COUNT, coffee01_D_0501A1F0, coffee01_D_0501A328,
};

Lws_unk_10 coffee01_D_0501A1F0[] = {
    { coffee01_D_05013160, -1, 40, 0, 0, 0 },    { coffee01_D_050132F8, -1, 104, 40, 0, 0 },
    { coffee01_D_050132F8, -1, 104, 144, 0, 0 }, { coffee01_D_050147B8, -1, 61, 248, 0, 0 },
    { coffee01_D_05014C10, -1, 60, 309, 0, 0 },  { coffee01_D_050149D8, -1, 61, 369, 0, 0 },
    { coffee01_D_050147B8, -1, 61, 430, 0, 0 },  { coffee01_D_05014C10, -1, 60, 491, 0, 0 },
    { coffee01_D_05014C10, -1, 62, 551, 0, 0 },  { coffee01_D_050147B8, -1, 61, 613, 0, 0 },
    { coffee01_D_050149D8, -1, 61, 674, 0, 0 },  { coffee01_D_05014C10, -1, 61, 735, 0, 0 },
    { coffee01_D_050149D8, -1, 59, 796, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_0501A1F0) == coffee01_D_0501A1D8_COUNT, "");

Lws_unk_14 coffee01_D_0501A328[] = {
    { 0, 1, -1600, -4000, 400, -2880, 8, -2753, 4096, 4096, 4096 },
    { 1, 2, -1600, -4000, 400, -2880, 8, -2753, 4096, 4096, 4096 },
    { 2, 3, 1527, 588, 400, -2880, 2880, -2884, 4096, 4096, 4096 },
    { 4, 4, 1440, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 12, 5, 1290, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 20, 6, 1250, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 28, 7, 1170, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 36, 8, 1020, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 44, 9, 980, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 52, 10, 900, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 60, 11, 750, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 68, 12, 710, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 76, 13, 630, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 14, 480, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 92, 15, 440, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 100, 16, 360, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 108, 17, 210, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 116, 18, 170, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 124, 19, 90, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 132, 20, -60, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 140, 21, -100, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 148, 22, -180, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 156, 23, -330, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 164, 24, -370, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 172, 25, -450, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 180, 26, -600, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 188, 27, -640, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 196, 28, -720, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 204, 29, -870, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 212, 30, -910, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 220, 31, -990, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 228, 32, -1140, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 236, 33, -1180, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 244, 34, -1260, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 252, 35, -1410, 644, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 260, 36, -1450, 604, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 268, 37, -1530, 588, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 276, 38, -1680, -4000, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 603, 39, -3910, -4000, 400, -2880, 0, -2718, 4096, 4096, 4096 },
    { 604, -1, -3912, -4000, 400, -2880, -3, -2718, 4096, 4096, 4096 },
    { 0, 41, 2056, -1472, 880, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 42, 2056, -1475, 880, -2880, 2880, -2880, 824, 824, 4096 },
    { 3, 43, 2056, -1472, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 9, 44, 1584, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 12, 45, 1663, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 16, 46, 1716, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 17, 47, 1716, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 22, 48, 1716, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 23, 49, 1408, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 28, 50, 1487, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 30, 51, 1540, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 31, 52, 1540, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 36, 53, 1540, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 37, 54, 1233, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 42, 55, 1312, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 46, 56, 1364, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 47, 57, 1364, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 51, 58, 1364, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 53, 59, 1057, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 57, 60, 1136, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 60, 61, 1189, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 61, 62, 1189, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 66, 63, 1189, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 67, 64, 881, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 72, 65, 960, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 75, 66, 1013, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 77, 67, 1013, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 81, 68, 1013, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 83, 69, 706, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 87, 70, 785, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 90, 71, 838, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 91, 72, 838, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 96, 73, 838, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 97, 74, 530, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 102, 75, 609, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 105, 76, 662, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 106, 77, 662, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 111, 78, 662, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 112, 79, 355, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 117, 80, 434, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 120, 81, 486, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 121, 82, 486, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 125, 83, 486, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 127, 84, 179, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 131, 85, 258, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 135, 86, 314, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 136, 87, 314, -1040, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 141, 88, 311, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 142, 89, 3, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 147, 90, 82, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 149, 91, 135, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 151, 92, 135, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 155, 93, 135, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 157, 94, -171, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 161, 95, -92, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 165, 96, -40, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 166, 97, -40, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 171, 98, -40, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 172, 99, -347, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 177, 100, -268, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 179, 101, -215, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 180, 102, -215, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 185, 103, -215, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 186, 104, -522, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 191, 105, -443, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 195, 106, -391, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 196, 107, -391, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 199, 108, -391, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 202, 109, -698, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 205, 110, -619, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 209, 111, -566, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 210, 112, -566, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 215, 113, -566, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 216, 114, -874, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 221, 115, -795, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 223, 116, -742, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 226, 117, -742, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 229, 118, -742, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 232, 119, -1049, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 235, 120, -970, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 239, 121, -918, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 240, 122, -918, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 245, 123, -918, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 246, 124, -1225, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 251, 125, -1146, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 253, 126, -1093, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 255, 127, -1093, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 256, 128, -1093, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 257, 129, -1400, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 260, 130, -1321, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 264, 131, -1265, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 265, 132, -1266, -1040, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 269, 133, -1269, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 271, 134, -1576, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 275, 135, -1497, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 278, 136, -1444, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 280, 137, -1444, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 284, 138, -1444, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 286, 139, -1752, 947, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 290, 140, -1673, 1000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 293, 141, -1620, 995, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 295, 142, -1620, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 299, 143, -1620, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 604, -1, 1400, -1472, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 0, 145, 2096, -4000, 880, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 146, 2096, -4007, 880, -2880, 2880, -2880, 824, 824, 4096 },
    { 3, 147, 2096, -4000, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 4, 148, 1624, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 7, 149, 1703, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 11, 150, 1756, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 12, 151, 1756, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 17, 152, 1756, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 18, 153, 1448, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 23, 154, 1527, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 25, 155, 1580, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 26, 156, 1580, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 31, 157, 1580, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 32, 158, 1273, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 37, 159, 1352, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 41, 160, 1404, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 42, 161, 1404, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 46, 162, 1404, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 48, 163, 1097, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 52, 164, 1176, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 55, 165, 1229, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 56, 166, 1229, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 61, 167, 1229, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 62, 168, 921, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 67, 169, 1000, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 70, 170, 1053, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 72, 171, 1053, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 76, 172, 1053, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 78, 173, 746, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 82, 174, 825, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 85, 175, 878, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 86, 176, 878, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 91, 177, 878, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 92, 178, 570, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 97, 179, 649, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 100, 180, 702, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 101, 181, 702, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 106, 182, 702, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 107, 183, 395, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 112, 184, 474, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 115, 185, 526, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 116, 186, 526, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 120, 187, 526, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 122, 188, 219, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 126, 189, 298, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 130, 190, 354, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 131, 191, 354, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 136, 192, 351, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 137, 193, 43, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 142, 194, 122, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 144, 195, 175, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 146, 196, 175, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 150, 197, 175, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 152, 198, -131, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 156, 199, -52, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 160, 200, 0, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 161, 201, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 166, 202, 0, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 167, 203, -307, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 172, 204, -228, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 174, 205, -175, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 175, 206, -175, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 180, 207, -175, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 181, 208, -482, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 186, 209, -403, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 190, 210, -351, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 191, 211, -351, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 194, 212, -351, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 197, 213, -658, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 200, 214, -579, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 204, 215, -526, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 205, 216, -526, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 210, 217, -526, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 211, 218, -834, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 216, 219, -755, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 218, 220, -702, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 221, 221, -702, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 224, 222, -702, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 227, 223, -1009, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 230, 224, -930, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 234, 225, -878, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 235, 226, -878, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 240, 227, -878, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 241, 228, -1185, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 246, 229, -1106, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 248, 230, -1053, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 250, 231, -1053, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 254, 232, -1053, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 256, 233, -1360, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 260, 234, -1281, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 264, 235, -1225, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 265, 236, -1226, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 269, 237, -1229, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 271, 238, -1536, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 275, 239, -1457, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 278, 240, -1404, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 280, 241, -1404, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 284, 242, -1404, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 286, 243, -1712, 856, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 290, 244, -1633, 900, 880, -2880, 2880, -2880, 819, 819, 4096 },
    { 293, 245, -1580, 896, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 295, 246, -1580, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 299, 247, -1580, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 604, -1, 1353, -4000, 880, -2880, 2880, -2880, 409, 409, 4096 },
    { 0, 249, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 250, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 113, 251, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 114, 252, 1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 119, 253, 1425, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 124, 254, 1370, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 129, 255, 1315, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 134, 256, 1260, 704, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 139, 257, 1205, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 144, 258, 1151, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 149, 259, 1096, 744, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 154, 260, 1041, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 159, 261, 986, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 164, 262, 931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 169, 263, 877, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 174, 264, 822, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 179, 265, 767, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 184, 266, 712, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 189, 267, 657, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 194, 268, 602, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 199, 269, 548, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 204, 270, 493, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 209, 271, 438, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 214, 272, 383, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 219, 273, 328, 744, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 224, 274, 274, 704, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 229, 275, 219, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 234, 276, 164, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 239, 277, 109, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 244, 278, 54, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 249, 279, 0, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 254, 280, -54, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 259, 281, -109, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 264, 282, -164, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 269, 283, -219, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 274, 284, -274, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 279, 285, -328, 744, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 284, 286, -383, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 289, 287, -438, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 294, 288, -493, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 299, 289, -548, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 304, 290, -602, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 309, 291, -657, 728, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 314, 292, -712, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 319, 293, -767, 720, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 324, 294, -822, 688, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 329, 295, -877, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 334, 296, -931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 339, 297, -986, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 344, 298, -1041, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 349, 299, -1096, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 354, 300, -1151, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 359, 301, -1205, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 364, 302, -1260, 696, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 369, 303, -1315, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 374, 304, -1370, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 379, 305, -1425, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 384, 306, -1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 385, 307, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 603, 308, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 310, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 311, 1499, -4573, 400, -2880, 2880, -2693, 4096, 4096, 4096 },
    { 130, 312, 1480, -4000, 400, -2880, 2880, -2655, 4096, 4096, 4096 },
    { 131, 313, 1480, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 136, 314, 1425, 1033, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 141, 315, 1370, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 146, 316, 1315, 1024, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 151, 317, 1260, 998, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 156, 318, 1205, 1033, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 161, 319, 1151, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 166, 320, 1096, 1042, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 171, 321, 1041, 980, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 176, 322, 986, 1033, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 181, 323, 931, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 186, 324, 877, 1051, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 191, 325, 822, 998, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 196, 326, 767, 1024, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 201, 327, 712, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 206, 328, 657, 1033, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 211, 329, 602, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 216, 330, 548, 1024, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 221, 331, 493, 980, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 226, 332, 438, 1033, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 231, 333, 383, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 236, 334, 328, 1042, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 241, 335, 274, 998, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 246, 336, 219, 1024, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 251, 337, 164, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 256, 338, 109, 1051, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 261, 339, 54, 980, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 266, 340, 0, 1024, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 271, 341, -54, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 276, 342, -109, 1033, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 281, 343, -164, 998, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 286, 344, -219, 1024, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 291, 345, -274, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 296, 346, -328, 1042, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 301, 347, -383, 980, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 306, 348, -438, 1024, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 311, 349, -493, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 316, 350, -548, 1033, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 321, 351, -602, 998, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 326, 352, -657, 1024, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 331, 353, -712, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 336, 354, -767, 1016, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 341, 355, -822, 980, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 346, 356, -877, 1042, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 351, 357, -931, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 356, 358, -986, 1033, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 361, 359, -1041, 989, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 366, 360, -1096, 1024, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 371, 361, -1151, 980, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 376, 362, -1205, 1042, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 381, 363, -1260, 989, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 386, 364, -1315, 1033, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 391, 365, -1370, 998, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 396, 366, -1425, 1024, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 401, 367, -1480, 989, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 402, 368, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 370, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 371, 1501, -4561, 400, -2880, 2880, -2632, 4096, 4096, 4096 },
    { 141, 372, 1480, -4000, 400, -2880, 2880, -2647, 4096, 4096, 4096 },
    { 142, 373, 1480, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 147, 374, 1425, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 152, 375, 1370, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 157, 376, 1315, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 162, 377, 1260, 704, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 167, 378, 1205, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 172, 379, 1151, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 177, 380, 1096, 744, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 182, 381, 1041, 688, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 187, 382, 986, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 192, 383, 931, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 197, 384, 877, 752, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 202, 385, 822, 704, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 207, 386, 767, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 212, 387, 712, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 217, 388, 657, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 222, 389, 602, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 227, 390, 548, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 232, 391, 493, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 237, 392, 438, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 242, 393, 383, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 247, 394, 328, 744, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 252, 395, 274, 704, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 257, 396, 219, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 262, 397, 164, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 267, 398, 109, 752, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 272, 399, 54, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 277, 400, 0, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 282, 401, -54, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 287, 402, -109, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 292, 403, -164, 704, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 297, 404, -219, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 302, 405, -274, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 307, 406, -328, 744, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 312, 407, -383, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 317, 408, -438, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 322, 409, -493, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 327, 410, -548, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 332, 411, -602, 704, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 337, 412, -657, 728, 400, -2880, 2880, -2624, 4096, 4096, 4096 },
    { 342, 413, -712, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 347, 414, -767, 720, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 352, 415, -822, 688, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 357, 416, -877, 744, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 362, 417, -931, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 367, 418, -986, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 372, 419, -1041, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 377, 420, -1096, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 382, 421, -1151, 688, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 387, 422, -1205, 744, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 392, 423, -1260, 696, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 397, 424, -1315, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 402, 425, -1370, 704, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 407, 426, -1425, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 412, 427, -1480, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 413, 428, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 601, 429, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 431, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 432, 1503, -4621, 400, -2880, 2880, -2700, 4096, 4096, 4096 },
    { 158, 433, 1480, -4000, 400, -2880, 2880, -2655, 4096, 4096, 4096 },
    { 159, 434, 1480, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 164, 435, 1425, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 169, 436, 1370, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 174, 437, 1315, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 179, 438, 1260, 944, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 184, 439, 1205, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 189, 440, 1151, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 194, 441, 1096, 984, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 199, 442, 1041, 928, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 204, 443, 986, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 209, 444, 931, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 214, 445, 877, 992, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 219, 446, 822, 944, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 224, 447, 767, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 229, 448, 712, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 234, 449, 657, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 239, 450, 602, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 244, 451, 548, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 249, 452, 493, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 254, 453, 438, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 259, 454, 383, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 264, 455, 328, 984, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 269, 456, 274, 944, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 274, 457, 219, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 279, 458, 164, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 284, 459, 109, 992, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 289, 460, 54, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 294, 461, 0, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 299, 462, -54, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 304, 463, -109, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 309, 464, -164, 944, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 314, 465, -219, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 319, 466, -274, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 324, 467, -328, 984, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 329, 468, -383, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 334, 469, -438, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 339, 470, -493, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 344, 471, -548, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 349, 472, -602, 944, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 354, 473, -657, 968, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 359, 474, -712, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 364, 475, -767, 960, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 369, 476, -822, 928, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 374, 477, -877, 984, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 379, 478, -931, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 384, 479, -986, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 389, 480, -1041, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 394, 481, -1096, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 399, 482, -1151, 928, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 404, 483, -1205, 984, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 409, 484, -1260, 936, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 414, 485, -1315, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 419, 486, -1370, 944, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 424, 487, -1425, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 429, 488, -1480, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 430, 489, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 603, 490, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 492, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 493, 1505, -4615, 400, -2880, 2880, -2697, 4096, 4096, 4096 },
    { 175, 494, 1480, -4000, 400, -2880, 2880, -2647, 4096, 4096, 4096 },
    { 176, 495, 1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 181, 496, 1425, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 186, 497, 1370, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 191, 498, 1315, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 196, 499, 1260, 704, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 201, 500, 1205, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 206, 501, 1151, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 211, 502, 1096, 744, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 216, 503, 1041, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 221, 504, 986, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 226, 505, 931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 231, 506, 877, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 236, 507, 822, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 241, 508, 767, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 246, 509, 712, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 251, 510, 657, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 256, 511, 602, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 261, 512, 548, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 266, 513, 493, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 271, 514, 438, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 276, 515, 383, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 281, 516, 328, 744, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 286, 517, 274, 704, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 291, 518, 219, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 296, 519, 164, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 301, 520, 109, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 306, 521, 54, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 311, 522, 0, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 316, 523, -54, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 321, 524, -109, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 326, 525, -164, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 331, 526, -219, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 336, 527, -274, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 341, 528, -328, 744, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 346, 529, -383, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 351, 530, -438, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 356, 531, -493, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 361, 532, -548, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 366, 533, -602, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 371, 534, -657, 728, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 376, 535, -712, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 381, 536, -767, 720, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 386, 537, -822, 688, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 391, 538, -877, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 396, 539, -931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 401, 540, -986, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 406, 541, -1041, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 411, 542, -1096, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 416, 543, -1151, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 421, 544, -1205, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 426, 545, -1260, 696, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 431, 546, -1315, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 436, 547, -1370, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 441, 548, -1425, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 446, 549, -1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 447, 550, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 552, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 553, 1506, -4670, 400, -2880, 2880, -2642, 4096, 4096, 4096 },
    { 186, 554, 1480, -4000, 400, -2880, 2880, -2655, 4096, 4096, 4096 },
    { 187, 555, 1480, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 192, 556, 1425, 1051, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 197, 557, 1370, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 202, 558, 1315, 1041, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 207, 559, 1260, 1012, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 212, 560, 1205, 1051, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 217, 561, 1151, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 222, 562, 1096, 1060, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 227, 563, 1041, 993, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 232, 564, 986, 1051, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 237, 565, 931, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 242, 566, 877, 1070, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 247, 567, 822, 1012, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 252, 568, 767, 1041, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 257, 569, 712, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 262, 570, 657, 1051, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 267, 571, 602, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 272, 572, 548, 1041, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 277, 573, 493, 993, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 282, 574, 438, 1051, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 287, 575, 383, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 292, 576, 328, 1060, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 297, 577, 274, 1012, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 302, 578, 219, 1041, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 307, 579, 164, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 312, 580, 109, 1070, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 317, 581, 54, 993, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 322, 582, 0, 1041, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 327, 583, -54, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 332, 584, -109, 1051, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 337, 585, -164, 1012, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 342, 586, -219, 1041, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 347, 587, -274, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 352, 588, -328, 1060, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 357, 589, -383, 993, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 362, 590, -438, 1041, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 367, 591, -493, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 372, 592, -548, 1051, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 377, 593, -602, 1012, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 382, 594, -657, 1041, 400, -2880, 2880, -2624, 4096, 4096, 4096 },
    { 387, 595, -712, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 392, 596, -767, 1032, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 397, 597, -822, 993, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 402, 598, -877, 1060, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 407, 599, -931, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 412, 600, -986, 1051, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 417, 601, -1041, 1003, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 422, 602, -1096, 1041, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 427, 603, -1151, 993, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 432, 604, -1205, 1060, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 437, 605, -1260, 1003, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 442, 606, -1315, 1051, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 447, 607, -1370, 1012, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 452, 608, -1425, 1041, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 457, 609, -1480, 1003, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 458, 610, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 601, 611, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 602, 612, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 614, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 615, 1508, -4646, 400, -2880, 2880, -2703, 4096, 4096, 4096 },
    { 203, 616, 1480, -4000, 400, -2880, 2880, -2647, 4096, 4096, 4096 },
    { 204, 617, 1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 209, 618, 1425, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 214, 619, 1370, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 219, 620, 1315, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 224, 621, 1260, 704, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 229, 622, 1205, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 234, 623, 1151, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 239, 624, 1096, 744, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 244, 625, 1041, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 249, 626, 986, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 254, 627, 931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 259, 628, 877, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 264, 629, 822, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 269, 630, 767, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 274, 631, 712, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 279, 632, 657, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 284, 633, 602, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 289, 634, 548, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 294, 635, 493, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 299, 636, 438, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 304, 637, 383, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 309, 638, 328, 744, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 314, 639, 274, 704, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 319, 640, 219, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 324, 641, 164, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 329, 642, 109, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 334, 643, 54, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 339, 644, 0, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 344, 645, -54, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 349, 646, -109, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 354, 647, -164, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 359, 648, -219, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 364, 649, -274, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 369, 650, -328, 744, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 374, 651, -383, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 379, 652, -438, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 384, 653, -493, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 389, 654, -548, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 394, 655, -602, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 399, 656, -657, 728, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 404, 657, -712, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 409, 658, -767, 720, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 414, 659, -822, 688, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 419, 660, -877, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 424, 661, -931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 429, 662, -986, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 434, 663, -1041, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 439, 664, -1096, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 444, 665, -1151, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 449, 666, -1205, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 454, 667, -1260, 696, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 459, 668, -1315, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 464, 669, -1370, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 469, 670, -1425, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 474, 671, -1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 475, 672, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 603, 673, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 675, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 676, 1509, -4692, 400, -2880, 2880, -2713, 4096, 4096, 4096 },
    { 217, 677, 1480, -4000, 400, -2880, 2880, -2655, 4096, 4096, 4096 },
    { 218, 678, 1480, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 223, 679, 1425, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 228, 680, 1370, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 233, 681, 1315, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 238, 682, 1260, 944, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 243, 683, 1205, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 248, 684, 1151, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 253, 685, 1096, 984, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 258, 686, 1041, 928, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 263, 687, 986, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 268, 688, 931, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 273, 689, 877, 992, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 278, 690, 822, 944, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 283, 691, 767, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 288, 692, 712, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 293, 693, 657, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 298, 694, 602, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 303, 695, 548, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 308, 696, 493, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 313, 697, 438, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 318, 698, 383, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 323, 699, 328, 984, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 328, 700, 274, 944, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 333, 701, 219, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 338, 702, 164, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 343, 703, 109, 992, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 348, 704, 54, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 353, 705, 0, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 358, 706, -54, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 363, 707, -109, 976, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 368, 708, -164, 944, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 373, 709, -219, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 378, 710, -274, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 383, 711, -328, 984, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 388, 712, -383, 928, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 393, 713, -438, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 398, 714, -493, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 403, 715, -548, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 408, 716, -602, 944, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 413, 717, -657, 968, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 418, 718, -712, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 423, 719, -767, 960, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 428, 720, -822, 928, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 433, 721, -877, 984, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 438, 722, -931, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 443, 723, -986, 976, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 448, 724, -1041, 936, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 453, 725, -1096, 968, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 458, 726, -1151, 928, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 463, 727, -1205, 984, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 468, 728, -1260, 936, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 473, 729, -1315, 976, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 478, 730, -1370, 944, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 483, 731, -1425, 968, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 488, 732, -1480, 936, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 489, 733, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 602, 734, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 736, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 737, 1511, -4669, 400, -2880, 2880, -2641, 4096, 4096, 4096 },
    { 232, 738, 1480, -4000, 400, -2880, 2880, -2647, 4096, 4096, 4096 },
    { 233, 739, 1480, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 238, 740, 1425, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 243, 741, 1370, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 248, 742, 1315, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 253, 743, 1260, 704, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 258, 744, 1205, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 263, 745, 1151, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 268, 746, 1096, 744, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 273, 747, 1041, 688, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 278, 748, 986, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 283, 749, 931, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 288, 750, 877, 752, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 293, 751, 822, 704, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 298, 752, 767, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 303, 753, 712, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 308, 754, 657, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 313, 755, 602, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 318, 756, 548, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 323, 757, 493, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 328, 758, 438, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 333, 759, 383, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 338, 760, 328, 744, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 343, 761, 274, 704, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 348, 762, 219, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 353, 763, 164, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 358, 764, 109, 752, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 363, 765, 54, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 368, 766, 0, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 373, 767, -54, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 378, 768, -109, 736, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 383, 769, -164, 704, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 388, 770, -219, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 393, 771, -274, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 398, 772, -328, 744, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 403, 773, -383, 688, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 408, 774, -438, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 413, 775, -493, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 418, 776, -548, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 423, 777, -602, 704, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 428, 778, -657, 728, 400, -2880, 2880, -2624, 4096, 4096, 4096 },
    { 433, 779, -712, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 438, 780, -767, 720, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 443, 781, -822, 688, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 448, 782, -877, 744, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 453, 783, -931, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 458, 784, -986, 736, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 463, 785, -1041, 696, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 468, 786, -1096, 728, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 473, 787, -1151, 688, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 478, 788, -1205, 744, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 483, 789, -1260, 696, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 488, 790, -1315, 736, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 493, 791, -1370, 704, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 498, 792, -1425, 728, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 503, 793, -1480, 696, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 504, 794, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 602, 795, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 797, 1600, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 2, 798, 1517, -4692, 400, -2880, 2880, -2720, 4096, 4096, 4096 },
    { 293, 799, 1480, -4000, 400, -2880, 2880, -2647, 4096, 4096, 4096 },
    { 294, 800, 1480, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 299, 801, 1425, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 305, 802, 1370, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 311, 803, 1315, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 316, 804, 1260, 704, 400, -2880, 2880, -2688, 4096, 4096, 4096 },
    { 322, 805, 1205, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 328, 806, 1151, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 334, 807, 1096, 744, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 339, 808, 1041, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 345, 809, 986, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 351, 810, 931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 357, 811, 877, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 362, 812, 822, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 368, 813, 767, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 374, 814, 712, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 380, 815, 657, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 385, 816, 602, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 391, 817, 548, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 397, 818, 493, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 403, 819, 438, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 408, 820, 383, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 414, 821, 328, 744, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 420, 822, 274, 704, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 426, 823, 219, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 431, 824, 164, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 437, 825, 109, 752, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 443, 826, 54, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 449, 827, 0, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 454, 828, -54, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 460, 829, -109, 736, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 466, 830, -164, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 472, 831, -219, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 477, 832, -274, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 483, 833, -328, 744, 400, -2880, 2880, -3072, 4096, 4096, 4096 },
    { 489, 834, -383, 688, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 495, 835, -438, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 500, 836, -493, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 506, 837, -548, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 512, 838, -602, 704, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 518, 839, -657, 728, 400, -2880, 2880, -3136, 4096, 4096, 4096 },
    { 523, 840, -712, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 529, 841, -767, 720, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 535, 842, -822, 688, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 541, 843, -877, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 546, 844, -931, 696, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 552, 845, -986, 736, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 558, 846, -1041, 696, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 564, 847, -1096, 728, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 569, 848, -1151, 688, 400, -2880, 2880, -2640, 4096, 4096, 4096 },
    { 575, 849, -1205, 744, 400, -2880, 2880, -3104, 4096, 4096, 4096 },
    { 581, 850, -1260, 696, 400, -2880, 2880, -2672, 4096, 4096, 4096 },
    { 587, 851, -1315, 736, 400, -2880, 2880, -3120, 4096, 4096, 4096 },
    { 592, 852, -1370, 704, 400, -2880, 2880, -2656, 4096, 4096, 4096 },
    { 598, 853, -1425, 728, 400, -2880, 2880, -3088, 4096, 4096, 4096 },
    { 603, 854, -1470, 701, 400, -2880, 2880, -2714, 4096, 4096, 4096 },
    { 604, -1, -1480, -4000, 400, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 coffee01_D_050200AC[] = {
    0x00000000, 0x00000358, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000002, 0x00000359,
    0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000004, 0x0000035A, 0x00000044, 0x3C00F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x0000025B, 0x0000035B, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x0000025C, 0xFFFFFFFF, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws coffee01_D_05020138 = {
    0, 562, 60, coffee01_D_05020138_COUNT, coffee01_D_05020150, coffee01_D_05020270,
};

Lws_unk_10 coffee01_D_05020150[] = {
    { coffee01_D_050147B8, -1, 50, 0, 0, 0 },   { coffee01_D_05014C10, -1, 47, 50, 0, 0 },
    { coffee01_D_050149D8, -1, 51, 97, 0, 0 },  { coffee01_D_050147B8, -1, 49, 148, 0, 0 },
    { coffee01_D_05014C10, -1, 48, 197, 0, 0 }, { coffee01_D_05014C10, -1, 49, 245, 0, 0 },
    { coffee01_D_050147B8, -1, 50, 294, 0, 0 }, { coffee01_D_050149D8, -1, 49, 344, 0, 0 },
    { coffee01_D_05014C10, -1, 50, 393, 0, 0 }, { coffee01_D_050149D8, -1, 51, 443, 0, 0 },
    { coffee01_D_05011760, -1, 46, 494, 0, 0 }, { coffee01_D_05013160, -1, 42, 540, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_05020150) == coffee01_D_05020138_COUNT, "");

Lws_unk_14 coffee01_D_05020270[] = {
    { 0, 1, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 2, 2, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 7, 3, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 12, 4, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 17, 5, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 22, 6, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 27, 7, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 32, 8, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 37, 9, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 42, 10, -1028, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 47, 11, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 52, 12, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 57, 13, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 62, 14, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 67, 15, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 77, 16, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 82, 17, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 87, 18, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 92, 19, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 97, 20, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 102, 21, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 107, 22, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 112, 23, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 117, 24, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 122, 25, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 127, 26, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 132, 27, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 137, 28, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 142, 29, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 147, 30, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 152, 31, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 157, 32, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 162, 33, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 167, 34, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 172, 35, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 177, 36, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 182, 37, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 187, 38, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 192, 39, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 197, 40, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 202, 41, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 207, 42, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 212, 43, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 217, 44, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 222, 45, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 227, 46, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 232, 47, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 237, 48, 1486, 736, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 238, 49, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 562, -1, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 51, 200, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 33, 52, 200, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 34, 53, -1280, 936, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 39, 54, -1244, 976, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 44, 55, -1208, 928, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 49, 56, -1146, 960, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 54, 57, -1084, 944, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 59, 58, -1020, 984, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 64, 59, -956, 936, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 69, 60, -892, 968, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 79, 61, -763, 960, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 84, 62, -699, 928, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 89, 63, -635, 992, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 94, 64, -571, 936, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 99, 65, -506, 976, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 104, 66, -442, 944, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 109, 67, -378, 968, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 114, 68, -314, 936, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 119, 69, -249, 984, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 124, 70, -185, 936, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 129, 71, -121, 960, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 134, 72, -57, 928, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 139, 73, 7, 976, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 144, 74, 71, 944, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 149, 75, 135, 968, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 154, 76, 200, 936, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 159, 77, 271, 984, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 164, 78, 342, 936, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 169, 79, 404, 960, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 174, 80, 466, 944, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 179, 81, 530, 976, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 184, 82, 594, 936, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 189, 83, 658, 984, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 194, 84, 722, 920, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 199, 85, 787, 960, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 204, 86, 851, 928, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 209, 87, 915, 984, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 214, 88, 980, 936, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 219, 89, 1044, 968, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 224, 90, 1108, 928, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 229, 91, 1172, 976, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 234, 92, 1237, 944, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 239, 93, 1301, 968, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 244, 94, 1365, 936, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 249, 95, 1429, 960, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 250, 96, 1442, -8000, 400, -2880, 0, -2864, 4096, 4096, 4096 },
    { 562, -1, 1686, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 98, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 31, 99, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 32, 100, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 37, 101, -1444, 736, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 42, 102, -1408, 688, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 47, 103, -1346, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 52, 104, -1284, 704, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 57, 105, -1220, 744, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 62, 106, -1156, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 67, 107, -1092, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 72, 108, -1028, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 77, 109, -963, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 82, 110, -899, 688, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 87, 111, -835, 752, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 92, 112, -771, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 97, 113, -706, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 107, 114, -578, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 112, 115, -514, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 117, 116, -449, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 122, 117, -385, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 127, 118, -321, 720, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 132, 119, -257, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 137, 120, -192, 736, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 142, 121, -128, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 147, 122, -64, 728, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 152, 123, 0, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 157, 124, 71, 744, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 162, 125, 142, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 167, 126, 204, 720, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 172, 127, 266, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 177, 128, 330, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 182, 129, 394, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 187, 130, 458, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 192, 131, 522, 680, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 197, 132, 587, 720, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 202, 133, 651, 688, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 207, 134, 715, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 212, 135, 779, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 217, 136, 844, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 222, 137, 908, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 227, 138, 972, 736, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 232, 139, 1037, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 237, 140, 1101, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 242, 141, 1165, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 247, 142, 1229, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 252, 143, 1294, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 257, 144, 1358, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 262, 145, 1422, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 267, 146, 1486, 736, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 268, 147, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 562, -1, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 149, 200, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 56, 150, -1398, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 57, 151, -1380, 982, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 62, 152, -1280, 989, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 67, 153, -1244, 1033, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 72, 154, -1208, 980, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 77, 155, -1146, 1016, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 82, 156, -1084, 998, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 87, 157, -1020, 1042, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 92, 158, -956, 989, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 97, 159, -892, 1024, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 107, 160, -763, 1016, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 112, 161, -699, 980, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 117, 162, -635, 1051, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 122, 163, -571, 989, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 127, 164, -506, 1033, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 132, 165, -442, 998, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 137, 166, -378, 1024, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 142, 167, -314, 989, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 147, 168, -249, 1042, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 152, 169, -185, 989, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 157, 170, -121, 1016, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 162, 171, -57, 980, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 167, 172, 7, 1033, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 172, 173, 71, 998, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 177, 174, 135, 1024, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 182, 175, 200, 989, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 187, 176, 271, 1042, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 192, 177, 342, 989, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 197, 178, 404, 1016, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 202, 179, 466, 998, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 207, 180, 530, 1033, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 212, 181, 594, 989, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 217, 182, 658, 1042, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 222, 183, 722, 972, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 227, 184, 787, 1016, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 232, 185, 851, 980, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 237, 186, 915, 1042, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 242, 187, 980, 989, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 247, 188, 1044, 1024, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 252, 189, 1108, 980, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 257, 190, 1172, 1033, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 262, 191, 1237, 998, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 267, 192, 1301, 1024, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 272, 193, 1365, 989, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 277, 194, 1429, 1016, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 278, 195, 1442, -8000, 400, -2880, 0, -2864, 4096, 4096, 4096 },
    { 298, 196, 1686, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 562, -1, 1686, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 198, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 65, 199, -1444, -8000, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 70, 200, -1408, 688, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 75, 201, -1346, 720, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 80, 202, -1284, 704, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 85, 203, -1220, 744, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 90, 204, -1156, 696, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 95, 205, -1092, 728, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 100, 206, -1028, 696, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 105, 207, -963, 720, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 110, 208, -899, 688, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 115, 209, -835, 752, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 120, 210, -771, 696, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 125, 211, -706, 736, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 135, 212, -578, 728, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 140, 213, -514, 696, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 145, 214, -449, 744, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 150, 215, -385, 696, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 155, 216, -321, 720, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 160, 217, -257, 688, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 165, 218, -192, 736, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 170, 219, -128, 704, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 175, 220, -64, 728, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 180, 221, 0, 696, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 185, 222, 71, 744, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 190, 223, 142, 696, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 195, 224, 204, 720, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 200, 225, 266, 704, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 205, 226, 330, 736, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 210, 227, 394, 696, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 215, 228, 458, 744, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 220, 229, 522, 680, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 225, 230, 587, 720, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 230, 231, 651, 688, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 235, 232, 715, 744, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 240, 233, 779, 696, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 245, 234, 844, 728, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 250, 235, 908, 688, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 255, 236, 972, 736, 400, -2880, 0, -2400, 4096, 4096, 4096 },
    { 260, 237, 1037, 704, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 265, 238, 1101, 728, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 270, 239, 1165, 696, 400, -2880, 0, -3360, 4096, 4096, 4096 },
    { 275, 240, 1229, 720, 400, -2880, 0, -2784, 4096, 4096, 4096 },
    { 280, 241, 1294, 688, 400, -2880, 0, -3168, 4096, 4096, 4096 },
    { 285, 242, 1358, 736, 400, -2880, 0, -2592, 4096, 4096, 4096 },
    { 290, 243, 1422, 696, 400, -2880, 0, -2976, 4096, 4096, 4096 },
    { 291, 244, 1435, -8000, 400, -2880, 0, -2956, 4096, 4096, 4096 },
    { 562, -1, 1435, -8000, 400, -2880, 0, -2956, 4096, 4096, 4096 },
    { 0, 246, 200, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 86, 247, -1373, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 87, 248, -1374, 963, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 92, 249, -1280, 936, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 97, 250, -1244, 976, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 102, 251, -1208, 928, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 107, 252, -1146, 960, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 112, 253, -1084, 944, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 117, 254, -1020, 984, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 122, 255, -956, 936, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 127, 256, -892, 968, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 137, 257, -763, 960, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 142, 258, -699, 928, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 147, 259, -635, 992, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 152, 260, -571, 936, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 157, 261, -506, 976, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 162, 262, -442, 944, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 167, 263, -378, 968, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 172, 264, -314, 936, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 177, 265, -249, 984, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 182, 266, -185, 936, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 187, 267, -121, 960, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 192, 268, -57, 928, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 197, 269, 7, 976, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 202, 270, 71, 944, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 207, 271, 135, 968, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 212, 272, 200, 936, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 217, 273, 271, 984, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 222, 274, 342, 936, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 227, 275, 404, 960, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 232, 276, 466, 944, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 237, 277, 530, 976, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 242, 278, 594, 936, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 247, 279, 658, 984, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 252, 280, 722, 920, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 257, 281, 787, 960, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 262, 282, 851, 928, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 267, 283, 915, 984, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 272, 284, 980, 936, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 277, 285, 1044, 968, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 282, 286, 1108, 928, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 287, 287, 1172, 976, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 292, 288, 1237, 944, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 297, 289, 1301, 968, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 302, 290, 1365, 936, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 307, 291, 1429, 960, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 311, 292, 1481, 934, 400, -2880, 0, -3108, 4096, 4096, 4096 },
    { 312, 293, 1494, -8000, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 562, -1, 1552, -9308, 400, -2880, 0, -3071, 4096, 4096, 4096 },
    { 0, 295, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 98, 296, -1451, -8000, 400, -2880, 0, -2560, 4096, 4096, 4096 },
    { 99, 297, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 104, 298, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 109, 299, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 114, 300, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 119, 301, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 124, 302, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 129, 303, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 134, 304, -1028, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 139, 305, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 144, 306, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 149, 307, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 154, 308, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 159, 309, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 169, 310, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 174, 311, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 179, 312, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 184, 313, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 189, 314, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 194, 315, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 199, 316, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 204, 317, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 209, 318, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 214, 319, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 219, 320, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 224, 321, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 229, 322, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 234, 323, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 239, 324, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 244, 325, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 249, 326, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 254, 327, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 259, 328, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 264, 329, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 269, 330, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 274, 331, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 279, 332, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 284, 333, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 289, 334, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 294, 335, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 299, 336, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 304, 337, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 309, 338, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 314, 339, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 319, 340, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 324, 341, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 327, 342, 1461, 720, 400, -2880, 0, -2912, 4096, 4096, 4096 },
    { 328, 343, 1473, -8000, 400, -2880, 0, -2896, 4096, 4096, 4096 },
    { 562, -1, 1473, -8000, 400, -2880, 0, -2896, 4096, 4096, 4096 },
    { 0, 345, 200, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 114, 346, -1373, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 115, 347, -1374, 1011, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 120, 348, -1280, 1003, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 125, 349, -1244, 1051, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 130, 350, -1208, 993, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 135, 351, -1146, 1032, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 140, 352, -1084, 1012, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 145, 353, -1020, 1060, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 150, 354, -956, 1003, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 155, 355, -892, 1041, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 165, 356, -763, 1032, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 170, 357, -699, 993, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 175, 358, -635, 1070, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 180, 359, -571, 1003, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 185, 360, -506, 1051, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 190, 361, -442, 1012, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 195, 362, -378, 1041, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 200, 363, -314, 1003, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 205, 364, -249, 1060, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 210, 365, -185, 1003, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 215, 366, -121, 1032, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 220, 367, -57, 993, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 225, 368, 7, 1051, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 230, 369, 71, 1012, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 235, 370, 135, 1041, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 240, 371, 200, 1003, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 245, 372, 271, 1060, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 250, 373, 342, 1003, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 255, 374, 404, 1032, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 260, 375, 466, 1012, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 265, 376, 530, 1051, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 270, 377, 594, 1003, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 275, 378, 658, 1060, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 280, 379, 722, 984, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 285, 380, 787, 1032, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 290, 381, 851, 993, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 295, 382, 915, 1060, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 300, 383, 980, 1003, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 305, 384, 1044, 1041, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 310, 385, 1108, 993, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 315, 386, 1172, 1051, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 320, 387, 1237, 1012, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 325, 388, 1301, 1041, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 330, 389, 1365, 1003, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 335, 390, 1429, 1032, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 336, 391, 1442, 1024, 400, -2880, 0, -2864, 4096, 4096, 4096 },
    { 337, 392, 1455, -8000, 400, -2880, 0, -2928, 4096, 4096, 4096 },
    { 562, -1, 1455, -8000, 400, -2880, 0, -2928, 4096, 4096, 4096 },
    { 0, 394, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 126, 395, -1451, -8000, 400, -2880, 0, -2528, 4096, 4096, 4096 },
    { 127, 396, -1444, 736, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 132, 397, -1408, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 137, 398, -1346, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 142, 399, -1284, 704, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 147, 400, -1220, 744, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 152, 401, -1156, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 157, 402, -1092, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 162, 403, -1028, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 167, 404, -963, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 172, 405, -899, 688, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 177, 406, -835, 752, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 182, 407, -771, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 187, 408, -706, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 197, 409, -578, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 202, 410, -514, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 207, 411, -449, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 212, 412, -385, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 217, 413, -321, 720, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 222, 414, -257, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 227, 415, -192, 736, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 232, 416, -128, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 237, 417, -64, 728, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 242, 418, 0, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 247, 419, 71, 744, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 252, 420, 142, 696, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 257, 421, 204, 720, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 262, 422, 266, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 267, 423, 330, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 272, 424, 394, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 277, 425, 458, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 282, 426, 522, 680, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 287, 427, 587, 720, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 292, 428, 651, 688, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 297, 429, 715, 744, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 302, 430, 779, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 307, 431, 844, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 312, 432, 908, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 317, 433, 972, 736, 400, -2880, 0, -3320, 4096, 4096, 4096 },
    { 322, 434, 1037, 704, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 327, 435, 1101, 728, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 332, 436, 1165, 696, 400, -2880, 0, -2440, 4096, 4096, 4096 },
    { 337, 437, 1229, 720, 400, -2880, 0, -2968, 4096, 4096, 4096 },
    { 342, 438, 1294, 688, 400, -2880, 0, -2616, 4096, 4096, 4096 },
    { 347, 439, 1358, 736, 400, -2880, 0, -3144, 4096, 4096, 4096 },
    { 352, 440, 1422, 696, 400, -2880, 0, -2792, 4096, 4096, 4096 },
    { 357, 441, 1486, 736, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 358, 442, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 562, -1, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 444, 0, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 181, 445, -1478, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 182, 446, -1480, 696, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 188, 447, -1444, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 194, 448, -1408, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 200, 449, -1346, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 206, 450, -1284, 704, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 212, 451, -1220, 744, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 218, 452, -1156, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 224, 453, -1092, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 230, 454, -1028, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 236, 455, -963, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 242, 456, -899, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 248, 457, -835, 752, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 254, 458, -771, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 260, 459, -706, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 272, 460, -578, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 278, 461, -514, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 284, 462, -449, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 290, 463, -385, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 296, 464, -321, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 302, 465, -257, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 308, 466, -192, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 314, 467, -128, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 320, 468, -64, 728, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 326, 469, 0, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 332, 470, 71, 744, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 338, 471, 142, 696, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 344, 472, 204, 720, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 350, 473, 266, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 356, 474, 330, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 362, 475, 394, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 368, 476, 458, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 374, 477, 522, 680, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 380, 478, 587, 720, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 386, 479, 651, 688, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 392, 480, 715, 744, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 398, 481, 779, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 404, 482, 844, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 410, 483, 908, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 416, 484, 972, 736, 400, -2880, 0, -2480, 4096, 4096, 4096 },
    { 422, 485, 1037, 704, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 428, 486, 1101, 728, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 434, 487, 1165, 696, 400, -2880, 0, -3280, 4096, 4096, 4096 },
    { 440, 488, 1229, 720, 400, -2880, 0, -2800, 4096, 4096, 4096 },
    { 446, 489, 1294, 688, 400, -2880, 0, -3120, 4096, 4096, 4096 },
    { 452, 490, 1358, 736, 400, -2880, 0, -2640, 4096, 4096, 4096 },
    { 458, 491, 1422, 696, 400, -2880, 0, -2960, 4096, 4096, 4096 },
    { 464, 492, 1486, 736, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 465, 493, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 562, -1, 1486, -8000, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 495, -1870, -8000, 320, -2880, 8, -2753, 4096, 4096, 4096 },
    { 233, 496, -1830, -8000, 320, -2880, 9, -2753, 4096, 4096, 4096 },
    { 234, 497, -1830, 1232, 320, -2880, 8, -2753, 4096, 4096, 4096 },
    { 239, 498, -1710, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 247, 499, -1560, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 255, 500, -1520, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 263, 501, -1440, 1192, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 271, 502, -1310, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 279, 503, -1270, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 287, 504, -1210, 1192, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 295, 505, -1060, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 303, 506, -1020, 1200, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 311, 507, -940, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 319, 508, -810, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 327, 509, -770, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 335, 510, -670, 1204, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 343, 511, -540, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 351, 512, -510, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 359, 513, -420, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 367, 514, -280, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 375, 515, -250, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 383, 516, -160, 1180, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 391, 517, -50, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 399, 518, 0, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 407, 519, 80, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 415, 520, 170, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 416, 521, 170, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 424, 522, 210, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 432, 523, 300, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 440, 524, 420, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 448, 525, 460, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 456, 526, 540, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 464, 527, 670, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 472, 528, 710, 1188, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 480, 529, 790, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 488, 530, 920, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 496, 531, 960, 1200, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 504, 532, 1060, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 512, 533, 1190, 1244, 320, -2880, 0, -3041, 4096, 4096, 4096 },
    { 520, 534, 1220, 1204, 320, -2880, 0, -2880, 4096, 4096, 4096 },
    { 527, 535, 1330, 1188, 320, -2880, 0, -2753, 4096, 4096, 4096 },
    { 535, 536, 1440, 1244, 320, -2880, 0, -3056, 4096, 4096, 4096 },
    { 543, 537, 1550, 1204, 320, -2880, 0, -2740, 4096, 4096, 4096 },
    { 560, 538, 1810, 1204, 320, -2880, 0, -2894, 4096, 4096, 4096 },
    { 561, 539, 1809, -8000, 320, -2880, 0, -2894, 4096, 4096, 4096 },
    { 562, -1, 1808, -8000, 320, -2880, 0, -2893, 4096, 4096, 4096 },
    { 0, 541, -1870, -8000, 400, -2880, 8, -2753, 4096, 4096, 4096 },
    { 254, 542, -1525, -8000, 400, -2880, 0, -2900, 4096, 4096, 4096 },
    { 255, 543, -1520, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 263, 544, -1440, 592, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 271, 545, -1310, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 279, 546, -1270, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 287, 547, -1210, 592, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 295, 548, -1060, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 303, 549, -1020, 600, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 311, 550, -940, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 319, 551, -810, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 327, 552, -770, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 335, 553, -670, 604, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 343, 554, -540, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 351, 555, -510, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 359, 556, -420, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 367, 557, -280, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 375, 558, -250, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 383, 559, -160, 580, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 391, 560, -50, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 399, 561, 0, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 407, 562, 80, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 415, 563, 170, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 416, 564, 170, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 424, 565, 210, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 432, 566, 300, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 440, 567, 420, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 448, 568, 460, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 456, 569, 540, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 464, 570, 670, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 472, 571, 710, 588, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 480, 572, 790, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 488, 573, 920, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 496, 574, 960, 600, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 504, 575, 1060, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 512, 576, 1190, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 520, 577, 1220, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 527, 578, 1330, 588, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 535, 579, 1500, 644, 400, -2880, 0, -3041, 4096, 4096, 4096 },
    { 543, 580, 1590, 604, 400, -2880, 0, -2880, 4096, 4096, 4096 },
    { 544, 581, 2590, -8000, 400, -2880, 0, -2753, 4096, 4096, 4096 },
    { 562, -1, 2579, -8000, 400, -2880, 0, -2749, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 coffee01_D_05024218[] = {
    0x00000000, 0x00000247, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x0000022A, 0x00000248, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000231, 0x00000249, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000232, 0xFFFFFFFF, 0x00000044, 0x3C00F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws coffee01_D_05024288 = {
    350, 1249, 60, coffee01_D_05024288_COUNT, coffee01_D_050242B8, coffee01_D_050245E8,
};

Lws coffee01_D_050242A0 = {
    350, 1249, 60, coffee01_D_050242A0_COUNT, coffee01_D_05024450, coffee01_D_050245E8,
};

Lws_unk_10 coffee01_D_050242B8[] = {
    { coffee01_D_05011FE0, -1, 15, 0, 0, 0 },   { coffee01_D_05013BE8, -1, 15, 15, 0, 0 },
    { coffee01_D_05013A98, -1, 15, 30, 0, 0 },  { coffee01_D_05012670, -1, 15, 45, 0, 0 },
    { coffee01_D_05013D38, -1, 15, 60, 0, 0 },  { coffee01_D_05012DC0, -1, 15, 75, 0, 0 },
    { coffee01_D_05014108, -1, 15, 90, 0, 0 },  { coffee01_D_050145A8, -1, 15, 105, 0, 0 },
    { coffee01_D_05012F10, -1, 15, 120, 0, 0 }, { coffee01_D_05012DC0, -1, 15, 135, 0, 0 },
    { coffee01_D_05014108, -1, 15, 150, 0, 0 }, { coffee01_D_05011480, -1, 15, 165, 0, 0 },
    { coffee01_D_05013BE8, -1, 15, 180, 0, 0 }, { coffee01_D_05013A98, -1, 15, 195, 0, 0 },
    { coffee01_D_05013E88, -1, 15, 210, 0, 0 }, { coffee01_D_05012520, -1, 15, 225, 0, 0 },
    { coffee01_D_050119E0, -1, 4, 245, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_050242B8) == coffee01_D_05024288_COUNT, "");

Lws_unk_10 coffee01_D_05024450[] = {
    { coffee01_D_05011FE0, -1, 15, 0, 0, 0 },   { coffee01_D_05013BE8, -1, 15, 15, 0, 0 },
    { coffee01_D_05013A98, -1, 15, 30, 0, 0 },  { coffee01_D_05012670, -1, 15, 45, 0, 0 },
    { coffee01_D_05013D38, -1, 15, 60, 0, 0 },  { coffee01_D_05012DC0, -1, 15, 75, 0, 0 },
    { coffee01_D_05014108, -1, 15, 90, 0, 0 },  { coffee01_D_050145A8, -1, 15, 105, 0, 0 },
    { coffee01_D_05012F10, -1, 15, 120, 0, 0 }, { coffee01_D_05012DC0, -1, 15, 135, 0, 0 },
    { coffee01_D_05014108, -1, 15, 150, 0, 0 }, { coffee01_D_05011480, -1, 15, 165, 0, 0 },
    { coffee01_D_05013BE8, -1, 15, 180, 0, 0 }, { coffee01_D_05013A98, -1, 15, 195, 0, 0 },
    { coffee01_D_05013E88, -1, 15, 210, 0, 0 }, { coffee01_D_05012520, -1, 15, 225, 0, 0 },
    { coffee01_D_05011D40, -1, 4, 245, 0, 0 },
};
static_assert(ARRAY_COUNT(coffee01_D_05024450) == coffee01_D_050242A0_COUNT, "");

Lws_unk_14 coffee01_D_050245E8[] = {
    { 0, 1, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 2, -4160, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 3, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 4, -960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 5, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 6, -960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 7, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 8, -960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 9, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 10, -960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 11, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 12, -960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 13, -960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 14, -960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, -960, 1359, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 16, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 17, -4032, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 18, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 19, -832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 20, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 21, -832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 22, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 23, -832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 24, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 25, -832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 26, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 27, -832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 28, -832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 29, -832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, -832, 1360, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 31, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 32, -3904, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 33, -704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 34, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 35, -704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 36, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 37, -704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 38, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 39, -704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 40, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 41, -704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 42, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 43, -704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 44, -704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, -704, 1399, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 46, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 47, -3776, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 48, -576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 49, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 50, -576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 51, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 52, -576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 53, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 54, -576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 55, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 56, -576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 57, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 58, -576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 59, -576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, -576, 1320, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 61, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 62, -3648, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 63, -448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 64, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 65, -448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 66, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 67, -448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 68, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 69, -448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 70, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 71, -448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 72, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 73, -448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 74, -448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, -448, 1399, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 76, -8000, 1360, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 77, -3520, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 78, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 79, -320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 80, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 81, -320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 82, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 83, -320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 84, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 85, -320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 86, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 87, -320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 88, -320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 89, -320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, -320, 1359, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 91, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 92, -3392, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 93, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 94, -192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 95, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 96, -192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 97, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 98, -192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 99, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 100, -192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 101, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 102, -192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 103, -192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 104, -192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, -192, 1360, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 106, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 107, -3264, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 108, -64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 109, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 110, -64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 111, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 112, -64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 113, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 114, -64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 115, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 116, -64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 117, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 118, -64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 119, -64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, -64, 1320, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 121, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 122, -3136, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 123, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 124, 64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 125, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 126, 64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 127, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 128, 64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 129, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 130, 64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 131, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 132, 64, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 133, 64, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 134, 64, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, 64, 1359, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 136, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 137, -3008, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 138, 192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 139, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 140, 192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 141, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 142, 192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 143, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 144, 192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 145, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 146, 192, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 147, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 148, 192, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 149, 192, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, 192, 1320, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 151, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 152, -2880, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 153, 320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 154, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 155, 320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 156, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 157, 320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 158, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 159, 320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 160, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 161, 320, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 162, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 163, 320, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 164, 320, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, 320, 1399, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 166, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 167, -2752, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 168, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 169, 448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 170, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 171, 448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 172, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 173, 448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 174, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 175, 448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 176, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 177, 448, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 178, 448, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 179, 448, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, 448, 1360, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 181, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 182, -2624, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 183, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 184, 576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 185, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 186, 576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 187, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 188, 576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 189, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 190, 576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 191, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 192, 576, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 193, 576, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 194, 576, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, 576, 1359, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 196, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 197, -2496, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 198, 704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 199, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 200, 704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 201, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 202, 704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 203, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 204, 704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 205, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 206, 704, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 207, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 208, 704, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 209, 704, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, 704, 1320, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 211, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 212, -2368, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 650, 213, 832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 700, 214, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 750, 215, 832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 800, 216, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 850, 217, 832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 900, 218, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 950, 219, 832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1000, 220, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1050, 221, 832, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1100, 222, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1150, 223, 832, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1200, 224, 832, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1249, -1, 832, 1399, 800, -2880, 2880, -2649, 4915, 4915, 4096 },
    { 0, 226, -8000, 1400, 800, -2880, 2880, -2880, 4915, 4915, 4096 },
    { 350, 227, -2240, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 650, 228, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 700, 229, 960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 750, 230, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 800, 231, 960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 850, 232, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 900, 233, 960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 950, 234, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1000, 235, 960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1050, 236, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1100, 237, 960, 1320, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1150, 238, 960, 1360, 800, -2880, 2880, -3120, 4915, 4915, 4096 },
    { 1200, 239, 960, 1400, 800, -2880, 2880, -2640, 4915, 4915, 4096 },
    { 1249, -1, 960, 1360, 800, -2880, 2880, -3110, 4915, 4915, 4096 },
    { 0, 241, 0, -800, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 10, 242, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 50, 243, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 650, 244, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 1249, -1, 0, 424, 480, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 246, -8000, 880, 800, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 350, 247, -3200, 880, 800, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 650, 248, 0, 880, 800, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 1249, -1, 0, 880, 800, -2880, 2880, -2880, 4096, 4096, 4096 },
};
