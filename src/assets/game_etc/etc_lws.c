#include "libc/assert.h"

#include "alignment.h"
#include "lws.h"
#include "macros_defines.h"

#define D_0500563C_COUNT (3)
#define D_0500685C_COUNT (3)
#define D_0500197C_COUNT (4)
#define D_05000038_COUNT (4)
#define D_05004414_COUNT (4)
#define D_05003444_COUNT (4)
#define D_050077AC_COUNT (6)
#define D_0500A0AC_COUNT (1)
#define D_050142A0_COUNT (4)
#define D_0500AAAC_COUNT (3)
#define D_0500C544_COUNT (20)
#define D_05013954_COUNT (1)
#define D_05016158_COUNT (4)
#define D_05017400_COUNT (16)

extern Lws *D_05000000[];
extern Lws D_05000038;
extern u32 D_05000050[];
extern Vtx D_05000070[];
extern u16 D_050000B0[];
extern u8 D_050000D0[];
extern Gfx D_050002B0[];
extern u32 D_050003A0[];
extern Vtx D_050003C0[];
extern u16 D_05000400[];
extern u8 D_05000420[];
extern Gfx D_050005D0[];
extern u32 D_050006C0[];
extern Vtx D_050006E0[];
extern u16 D_05000720[];
extern u8 D_05000740[];
extern Gfx D_05000900[];
extern u32 D_050009F0[];
extern Vtx D_05000A10[];
extern u16 D_05000A50[];
extern u8 D_05000A70[];
extern Gfx D_05000C40[];
extern Lws_unk_10 D_05000D30[];
extern Lws_unk_14 D_05000D90[];
extern u32 D_0500189C[];
extern Lws D_0500197C;
extern u32 D_05001994[];
extern Vtx D_050019B8[];
extern u16 D_050019F8[];
extern u8 D_05001A18[];
extern Gfx D_05001C48[];
extern u32 D_05001D38[];
extern Vtx D_05001D58[];
extern u16 D_05001D98[];
extern u8 D_05001DB8[];
extern Gfx D_05001FB8[];
extern u32 D_050020A8[];
extern Vtx D_050020C8[];
extern u16 D_05002108[];
extern u8 D_05002128[];
extern Gfx D_05002358[];
extern u32 D_05002448[];
extern Vtx D_05002468[];
extern u16 D_050024A8[];
extern u8 D_050024C8[];
extern Gfx D_05002708[];
extern Lws_unk_10 D_050027F8[];
extern Lws_unk_14 D_05002858[];
extern u32 D_05003364[];
extern Lws D_05003444;
extern u32 D_0500345C[];
extern Vtx D_05003480[];
extern u16 D_050034C0[];
extern u8 D_050034E0[];
extern Gfx D_050036A0[];
extern u32 D_05003790[];
extern Vtx D_050037B0[];
extern u16 D_050037F0[];
extern u8 D_05003810[];
extern Gfx D_050039D0[];
extern u32 D_05003AC0[];
extern Vtx D_05003AE0[];
extern u16 D_05003B20[];
extern u8 D_05003B40[];
extern Gfx D_05003D10[];
extern u32 D_05003E00[];
extern Vtx D_05003E20[];
extern u16 D_05003E60[];
extern u8 D_05003E80[];
extern Gfx D_05004040[];
extern Lws_unk_10 D_05004130[];
extern Lws_unk_14 D_05004190[];
extern u32 D_050043DC[];
extern Lws D_05004414;
extern u32 D_0500442C[];
extern Vtx D_05004450[];
extern u16 D_05004490[];
extern u8 D_050044B0[];
extern Gfx D_050046C0[];
extern u32 D_050047B0[];
extern Vtx D_050047D0[];
extern u16 D_05004810[];
extern u8 D_05004830[];
extern Gfx D_05004A40[];
extern u32 D_05004B30[];
extern Vtx D_05004B50[];
extern u16 D_05004B90[];
extern u8 D_05004BB0[];
extern Gfx D_05004DD0[];
extern u32 D_05004EC0[];
extern Vtx D_05004EE0[];
extern u16 D_05004F20[];
extern u8 D_05004F40[];
extern Gfx D_05005150[];
extern Lws_unk_10 D_05005240[];
extern Lws_unk_14 D_050052A0[];
extern u32 D_050055CC[];
extern Lws D_0500563C;
extern u32 D_05005654[];
extern Vtx D_05005678[];
extern u16 D_050056B8[];
extern u8 D_050056D8[];
extern Gfx D_05005A80[];
extern u32 D_05005B70[];
extern Vtx D_05005B90[];
extern u16 D_05005BD0[];
extern u8 D_05005BF0[];
extern Gfx D_05005D20[];
extern u32 D_05005E10[];
extern Vtx D_05005E30[];
extern u16 D_05005E70[];
extern u8 D_05005E90[];
extern Gfx D_05006238[];
extern Lws_unk_10 D_05006328[];
extern Lws_unk_14 D_05006370[];
extern u32 D_050067EC[];
extern Lws D_0500685C;
extern u32 D_05006874[];
extern Vtx D_05006898[];
extern u16 D_050068D8[];
extern u8 D_050068F8[];
extern Gfx D_05006BE0[];
extern u32 D_05006CD0[];
extern Vtx D_05006CF0[];
extern u16 D_05006D30[];
extern u8 D_05006D50[];
extern Gfx D_05006E50[];
extern u32 D_05006F40[];
extern Vtx D_05006F60[];
extern u16 D_05006FA0[];
extern u8 D_05006FC0[];
extern Gfx D_050071C0[];
extern Lws_unk_10 D_050072B0[];
extern Lws_unk_14 D_050072F8[];
extern u32 D_05007774[];
extern Lws D_050077AC;
extern u32 D_050077C4[];
extern Vtx D_050077E8[];
extern u16 D_05007828[];
extern u8 D_05007A28[];
extern Gfx D_05007C80[];
extern u32 D_05007D70[];
extern Vtx D_05007D90[];
extern u16 D_05007DD0[];
extern u8 D_05007FD0[];
extern Gfx D_050080F0[];
extern u32 D_050081E0[];
extern Vtx D_05008200[];
extern u16 D_05008240[];
extern u8 D_05008440[];
extern Gfx D_050086B0[];
extern u32 D_050087A0[];
extern Vtx D_050087C0[];
extern u16 D_05008800[];
extern u8 D_05008A00[];
extern Gfx D_05008B30[];
extern u32 D_05008C20[];
extern Vtx D_05008C40[];
extern u16 D_05008C80[];
extern u8 D_05008E80[];
extern Gfx D_05009010[];
extern u32 D_05009100[];
extern Vtx D_05009120[];
extern u16 D_05009160[];
extern u8 D_05009360[];
extern Gfx D_05009490[];
extern Lws_unk_10 D_05009580[];
extern Lws_unk_14 D_05009610[];
extern u32 D_0500A020[];
extern Lws D_0500A0AC;
extern u32 D_0500A0C4[];
extern Vtx D_0500A0E8[];
extern u16 D_0500A128[];
extern u8 D_0500A328[];
extern Gfx D_0500A8A8[];
extern Lws_unk_10 D_0500A998[];
extern Lws_unk_14 D_0500A9B0[];
extern u32 D_0500AA90[];
extern Lws D_0500AAAC;
extern u32 D_0500AAC4[];
extern Vtx D_0500AAE8[];
extern u16 D_0500AB28[];
extern u8 D_0500AD28[];
extern Gfx D_0500B128[];
extern u32 D_0500B218[];
extern Vtx D_0500B238[];
extern u16 D_0500B278[];
extern u8 D_0500B478[];
extern Gfx D_0500B878[];
extern u32 D_0500B968[];
extern Vtx D_0500B988[];
extern u16 D_0500B9C8[];
extern u8 D_0500BBC8[];
extern Gfx D_0500BFC8[];
extern Lws_unk_10 D_0500C0B8[];
extern Lws_unk_14 D_0500C100[];
extern u32 D_0500C448[];
extern Lws D_0500C544;
extern u32 D_0500C55C[];
extern Vtx D_0500C580[];
extern u8 D_0500C5E0[];
extern Gfx D_0500C7F0[];
extern u32 D_0500C8B0[];
extern Vtx D_0500C8D0[];
extern u16 D_0500C910[];
extern u8 D_0500CB10[];
extern Gfx D_0500CF30[];
extern u32 D_0500D020[];
extern Vtx D_0500D040[];
extern u8 D_0500D0A0[];
extern Gfx D_0500D2F8[];
extern u32 D_0500D3B8[];
extern Vtx D_0500D3D8[];
extern u16 D_0500D418[];
extern u8 D_0500D618[];
extern Gfx D_0500DA00[];
extern u32 D_0500DAF0[];
extern Vtx D_0500DB10[];
extern u8 D_0500DB70[];
extern Gfx D_0500DDA0[];
extern u32 D_0500DE60[];
extern Vtx D_0500DE80[];
extern u16 D_0500DEC0[];
extern u8 D_0500E0C0[];
extern Gfx D_0500E520[];
extern u32 D_0500E610[];
extern Vtx D_0500E630[];
extern u8 D_0500E690[];
extern Gfx D_0500E850[];
extern u32 D_0500E910[];
extern Vtx D_0500E930[];
extern u16 D_0500E970[];
extern u8 D_0500EB70[];
extern Gfx D_0500EE10[];
extern u32 D_0500EF00[];
extern Vtx D_0500EF20[];
extern u8 D_0500EF80[];
extern Gfx D_0500F1A0[];
extern u32 D_0500F260[];
extern Vtx D_0500F280[];
extern u16 D_0500F2C0[];
extern u8 D_0500F4C0[];
extern Gfx D_0500F900[];
extern u32 D_0500F9F0[];
extern Vtx D_0500FA10[];
extern u8 D_0500FA70[];
extern Gfx D_0500FC80[];
extern u32 D_0500FD40[];
extern Vtx D_0500FD60[];
extern u16 D_0500FDA0[];
extern u8 D_0500FFA0[];
extern Gfx D_050103C0[];
extern u32 D_050104B0[];
extern Vtx D_050104D0[];
extern u8 D_05010530[];
extern Gfx D_05010740[];
extern u32 D_05010800[];
extern Vtx D_05010820[];
extern u16 D_05010860[];
extern u8 D_05010A60[];
extern Gfx D_05010E80[];
extern u32 D_05010F70[];
extern Vtx D_05010F90[];
extern u8 D_05010FF0[];
extern Gfx D_05011180[];
extern u32 D_05011240[];
extern Vtx D_05011260[];
extern u16 D_050112A0[];
extern u8 D_050114A0[];
extern Gfx D_050117C0[];
extern u32 D_050118B0[];
extern Vtx D_050118D0[];
extern u8 D_05011930[];
extern Gfx D_05011AD0[];
extern u32 D_05011B90[];
extern Vtx D_05011BB0[];
extern u16 D_05011BF0[];
extern u8 D_05011DF0[];
extern Gfx D_05012060[];
extern u32 D_05012150[];
extern Vtx D_05012170[];
extern u8 D_050121D0[];
extern Gfx D_05012410[];
extern u32 D_050124D0[];
extern Vtx D_050124F0[];
extern u16 D_05012530[];
extern u8 D_05012730[];
extern Gfx D_05012BB0[];
extern Lws_unk_10 D_05012CA0[];
extern Lws_unk_14 D_05012E80[];
extern u32 D_05013938[];
extern Lws D_05013954;
extern u32 D_0501396C[];
extern Vtx D_05013990[];
extern u16 D_050139D0[];
extern u8 D_05013BD0[];
extern Gfx D_05014080[];
extern Lws_unk_10 D_05014170[];
extern Lws_unk_14 D_05014188[];
extern u32 D_05014284[];
extern Lws D_050142A0;
extern u32 D_050142B8[];
extern Vtx D_050142D8[];
extern u8 D_05014338[];
extern Gfx D_050147E8[];
extern u32 D_050148A8[];
extern Vtx D_050148C8[];
extern u8 D_05014928[];
extern Gfx D_05014DD8[];
extern u32 D_05014E98[];
extern Vtx D_05014EB8[];
extern u16 D_05014EF8[];
extern u8 D_05014F18[];
extern Gfx D_050153C8[];
extern u32 D_050154B8[];
extern Vtx D_050154D8[];
extern u16 D_05015518[];
extern u8 D_05015538[];
extern Gfx D_050159E8[];
extern Lws_unk_10 D_05015AD8[];
extern Lws_unk_14 D_05015B38[];
extern Lws D_05016158;
extern Vtx D_05016190[];
extern u8 D_050161F0[];
extern Gfx D_050166A0[];
extern Vtx D_05016780[];
extern u16 D_050167C0[];
extern u8 D_050167E0[];
extern Gfx D_05016C90[];
extern Lws_unk_10 D_05016D80[];
extern Lws_unk_14 D_05016DE0[];
extern Lws D_05017400;
extern u32 D_05017418[];
extern Vtx D_05017438[];
extern u8 D_05017498[];
extern Gfx D_05017658[];
extern u32 D_05017718[];
extern Vtx D_05017738[];
extern u16 D_05017778[];
extern u8 D_05017798[];
extern Gfx D_05017958[];
extern u32 D_05017A48[];
extern Vtx D_05017A68[];
extern u8 D_05017AC8[];
extern Gfx D_05017C88[];
extern u32 D_05017D48[];
extern Vtx D_05017D68[];
extern u16 D_05017DA8[];
extern u8 D_05017DC8[];
extern Gfx D_05017F88[];
extern u32 D_05018078[];
extern Vtx D_05018098[];
extern u8 D_050180F8[];
extern Gfx D_05018350[];
extern u32 D_05018410[];
extern Vtx D_05018430[];
extern u16 D_05018470[];
extern u8 D_05018490[];
extern Gfx D_050186E8[];
extern Lws_unk_10 D_050187D8[];
extern Lws_unk_14 D_05018958[];
extern u32 D_05019218[];

Lws *D_05000000[] = {
    &D_0500563C, &D_0500685C, &D_0500197C, &D_05000038, &D_05004414, &D_05003444, &D_050077AC,
    &D_0500A0AC, &D_050142A0, &D_0500AAAC, &D_0500C544, &D_05013954, &D_05016158, &D_05017400,
};

Lws D_05000038 = {
    0, 137, 60, D_05000038_COUNT, D_05000D30, D_05000D90,
};

/* unreferenced data */
u32 D_05000050[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05000070[] = {
#include "assets/game_etc/lws/D_05000070.vtx.inc.c"
};

u16 D_050000B0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050000D0.palette.inc"
};

u8 D_050000D0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050000D0.ci4.inc"
};

Gfx D_050002B0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050000B0),
    gsDPLoadTextureBlock_4b(D_050000D0, G_IM_FMT_CI, 32, 30, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05000070, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050003A0[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF2, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_050003C0[] = {
#include "assets/game_etc/lws/D_050003C0.vtx.inc.c"
};

u16 D_05000400[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000420.palette.inc"
};

u8 D_05000420[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000420.ci4.inc"
};

Gfx D_050005D0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05000400),
    gsDPLoadTextureBlock_4b(D_05000420, G_IM_FMT_CI, 32, 27, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050003C0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050006C0[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF1, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_050006E0[] = {
#include "assets/game_etc/lws/D_050006E0.vtx.inc.c"
};

u16 D_05000720[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000740.palette.inc"
};

u8 D_05000740[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000740.ci4.inc"
};

Gfx D_05000900[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05000720),
    gsDPLoadTextureBlock_4b(D_05000740, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050006E0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050009F0[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF1, 0x0000000E, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05000A10[] = {
#include "assets/game_etc/lws/D_05000A10.vtx.inc.c"
};

u16 D_05000A50[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000A70.palette.inc"
};

u8 D_05000A70[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05000A70.ci4.inc"
};

Gfx D_05000C40[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05000A50),
    gsDPLoadTextureBlock_4b(D_05000A70, G_IM_FMT_CI, 32, 29, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05000A10, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05000D30[] = {
    { D_050002B0, -1, 23, 0, 0, 0 },
    { D_050005D0, -1, 28, 23, 0, 0 },
    { D_05000900, -1, 23, 51, 0, 0 },
    { D_05000C40, -1, 27, 74, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05000D30) == D_05000038_COUNT, "");

Lws_unk_14 D_05000D90[] = {
    { 0, 1, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 2, 0, 184, 0, -2880, 2880, -3420, 4096, 4096, 4096 },
    { 16, 3, -178, 184, 0, -2880, 2880, -2403, 4096, 4096, 4096 },
    { 28, 4, -138, 158, 0, -2880, 2880, -3166, 4096, 4096, 4096 },
    { 32, 5, -186, 158, 0, -2880, 2880, -2727, 4096, 4096, 4096 },
    { 36, 6, -192, 158, 0, -2880, 2880, -3065, 4096, 4096, 4096 },
    { 40, 7, -192, 140, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 8, -192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 9, -192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 80, 10, -192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 11, -186, 142, 0, -2880, 2880, -2936, 4096, 4096, 4096 },
    { 90, 12, -190, 108, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 94, 13, -186, 94, 0, -2880, 2880, -2804, 4096, 4096, 4096 },
    { 98, 14, -184, -2, 0, -2880, 2880, -2964, 4096, 4096, 4096 },
    { 104, 15, -182, -16, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 108, 16, -186, -60, 0, -2880, 2880, -2916, 4096, 4096, 4096 },
    { 112, 17, -186, -72, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 116, 18, -184, -92, 0, -2880, 2880, -2956, 4096, 4096, 4096 },
    { 120, 19, -182, -102, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 122, 20, -186, -28, 0, -2880, 2880, -2905, 4096, 4096, 4096 },
    { 127, 21, -180, 78, 0, -2880, 2880, -2972, 4096, 4096, 4096 },
    { 129, 22, -176, 202, 0, -2880, 2880, -2744, 4096, 4096, 4096 },
    { 137, -1, -192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 24, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 4, 25, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 26, -34, 168, 0, -2880, 2880, -2267, 4096, 4096, 4096 },
    { 20, 27, -38, 166, 0, -2880, 2880, -3275, 4096, 4096, 4096 },
    { 28, 28, -82, 158, 0, -2880, 2880, -2561, 4096, 4096, 4096 },
    { 36, 29, -46, 158, 0, -2880, 2880, -3142, 4096, 4096, 4096 },
    { 40, 30, -64, 140, 0, -2880, 2880, -2769, 4096, 4096, 4096 },
    { 44, 31, -58, 140, 0, -2880, 2880, -2988, 4096, 4096, 4096 },
    { 48, 32, -84, 138, 0, -2880, 2880, -2796, 4096, 4096, 4096 },
    { 52, 33, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 34, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 35, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 36, -66, 126, 0, -2880, 2880, -3097, 4096, 4096, 4096 },
    { 72, 37, -64, 130, 0, -2880, 2880, -2756, 4096, 4096, 4096 },
    { 76, 38, -56, 124, 0, -2880, 2880, -2776, 4096, 4096, 4096 },
    { 80, 39, -48, 100, 0, -2880, 2880, -2976, 4096, 4096, 4096 },
    { 84, 40, -48, 100, 0, -2880, 2880, -2944, 4096, 4096, 4096 },
    { 88, 41, -48, 52, 0, -2880, 2880, -2766, 4096, 4096, 4096 },
    { 92, 42, -22, -8, 0, -2880, 2880, -3036, 4096, 4096, 4096 },
    { 98, 43, -16, -86, 0, -2880, 2880, -2800, 4096, 4096, 4096 },
    { 102, 44, -6, -112, 0, -2880, 2880, -2923, 4096, 4096, 4096 },
    { 106, 45, -6, -200, 0, -2880, 2880, -2804, 4096, 4096, 4096 },
    { 110, 46, -6, -220, 0, -2880, 2880, -2963, 4096, 4096, 4096 },
    { 114, 47, -6, -240, 0, -2880, 2880, -2784, 4096, 4096, 4096 },
    { 118, 48, -8, -264, 0, -2880, 2880, -2923, 4096, 4096, 4096 },
    { 122, 49, -24, 2, 0, -2880, 2880, -3024, 4096, 4096, 4096 },
    { 129, 50, -64, 174, 0, -2880, 2880, -2838, 4096, 4096, 4096 },
    { 137, -1, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 52, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 53, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 54, 114, 180, 0, -2880, 2880, -3499, 4096, 4096, 4096 },
    { 24, 55, 28, 166, 0, -2880, 2880, -2644, 4096, 4096, 4096 },
    { 32, 56, 74, 152, 0, -2880, 2880, -3016, 4096, 4096, 4096 },
    { 40, 57, 74, 152, 0, -2880, 2880, -2736, 4096, 4096, 4096 },
    { 44, 58, 74, 142, 0, -2880, 2880, -2937, 4096, 4096, 4096 },
    { 48, 59, 74, 144, 0, -2880, 2880, -2838, 4096, 4096, 4096 },
    { 52, 60, 74, 142, 0, -2880, 2880, -2936, 4096, 4096, 4096 },
    { 56, 61, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 62, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 63, 74, 134, 0, -2880, 2880, -2721, 4096, 4096, 4096 },
    { 92, 64, 76, 105, 0, -2880, 2880, -2840, 4096, 4096, 4096 },
    { 96, 65, 78, 111, 0, -2880, 2880, -2972, 4096, 4096, 4096 },
    { 100, 66, 76, 71, 0, -2880, 2880, -2697, 4096, 4096, 4096 },
    { 106, 67, 76, 61, 0, -2880, 2880, -2947, 4096, 4096, 4096 },
    { 110, 68, 76, 39, 0, -2880, 2880, -2782, 4096, 4096, 4096 },
    { 114, 69, 78, 21, 0, -2880, 2880, -2947, 4096, 4096, 4096 },
    { 118, 70, 82, 1, 0, -2880, 2880, -2825, 4096, 4096, 4096 },
    { 122, 71, 90, -38, 0, -2880, 2880, -2947, 4096, 4096, 4096 },
    { 127, 72, 74, 80, 0, -2880, 2880, -2815, 4096, 4096, 4096 },
    { 129, 73, 78, 196, 0, -2880, 2880, -2945, 4096, 4096, 4096 },
    { 137, -1, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 75, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 76, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 77, 140, 182, 0, -2880, 2880, -2225, 4096, 4096, 4096 },
    { 28, 78, 232, 182, 0, -2880, 2880, -3198, 4096, 4096, 4096 },
    { 36, 79, 160, 180, 0, -2880, 2880, -2468, 4096, 4096, 4096 },
    { 40, 80, 182, 164, 0, -2880, 2880, -3080, 4096, 4096, 4096 },
    { 44, 81, 178, 150, 0, -2880, 2880, -2779, 4096, 4096, 4096 },
    { 48, 82, 188, 156, 0, -2880, 2880, -2924, 4096, 4096, 4096 },
    { 52, 83, 190, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 84, 192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 85, 192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 86, 200, 136, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 72, 87, 194, 122, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 76, 88, 176, 122, 0, -2880, 2880, -2648, 4096, 4096, 4096 },
    { 80, 89, 180, 118, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 84, 90, 188, 106, 0, -2880, 2880, -2840, 4096, 4096, 4096 },
    { 92, 91, 184, 68, 0, -2880, 2880, -3030, 4096, 4096, 4096 },
    { 96, 92, 184, 52, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 102, 93, 182, 12, 0, -2880, 2880, -3004, 4096, 4096, 4096 },
    { 106, 94, 190, -28, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 110, 95, 186, -54, 0, -2880, 2880, -2809, 4096, 4096, 4096 },
    { 114, 96, 186, -90, 0, -2880, 2880, -2939, 4096, 4096, 4096 },
    { 118, 97, 182, -122, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 122, 98, 182, -150, 0, -2880, 2880, -2966, 4096, 4096, 4096 },
    { 125, 99, 176, -32, 0, -2880, 2880, -2712, 4096, 4096, 4096 },
    { 129, 100, 194, 184, 0, -2880, 2880, -3006, 4096, 4096, 4096 },
    { 137, -1, 192, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_0500189C[] = {
    0x00000000, 0x00000066, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000038,
    0x00000067, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000040, 0x00000068,
    0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000054, 0x00000069, 0x00000000,
    0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000005C, 0x0000006A, 0x00000000, 0x0960F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x0000007A, 0x0000006B, 0x00000000, 0x0960F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x00000081, 0x0000006C, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x00000089, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500197C = {
    0, 137, 60, D_0500197C_COUNT, D_050027F8, D_05002858,
};

/* unreferenced data */
u32 D_05001994[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEE, 0x00000011, 0x00000000, 0x00000000, 0x00000012, 0x00000000, 0x00000000,
};

Vtx D_050019B8[] = {
#include "assets/game_etc/lws/D_050019B8.vtx.inc.c"
};

u16 D_050019F8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05001A18.palette.inc"
};

u8 D_05001A18[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05001A18.ci4.inc"
};

Gfx D_05001C48[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050019F8),
    gsDPLoadTextureBlock_4b(D_05001A18, G_IM_FMT_CI, 32, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050019B8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05001D38[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05001D58[] = {
#include "assets/game_etc/lws/D_05001D58.vtx.inc.c"
};

u16 D_05001D98[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05001DB8.palette.inc"
};

u8 D_05001DB8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05001DB8.ci4.inc"
};

Gfx D_05001FB8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05001D98),
    gsDPLoadTextureBlock_4b(D_05001DB8, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05001D58, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050020A8[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEE, 0x00000011, 0x00000000, 0x00000000, 0x00000012, 0x00000000,
};

Vtx D_050020C8[] = {
#include "assets/game_etc/lws/D_050020C8.vtx.inc.c"
};

u16 D_05002108[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05002128.palette.inc"
};

u8 D_05002128[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05002128.ci4.inc"
};

Gfx D_05002358[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05002108),
    gsDPLoadTextureBlock_4b(D_05002128, G_IM_FMT_CI, 32, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050020C8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05002448[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEE, 0x00000012, 0x00000000, 0x00000000, 0x00000012, 0x00000000,
};

Vtx D_05002468[] = {
#include "assets/game_etc/lws/D_05002468.vtx.inc.c"
};

u16 D_050024A8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050024C8.palette.inc"
};

u8 D_050024C8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050024C8.ci4.inc"
};

Gfx D_05002708[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050024A8),
    gsDPLoadTextureBlock_4b(D_050024C8, G_IM_FMT_CI, 32, 36, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05002468, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_050027F8[] = {
    { D_05001C48, -1, 23, 0, 0, 0 },
    { D_05001FB8, -1, 28, 23, 0, 0 },
    { D_05002358, -1, 23, 51, 0, 0 },
    { D_05002708, -1, 27, 74, 0, 0 },
};
static_assert(ARRAY_COUNT(D_050027F8) == D_0500197C_COUNT, "");

Lws_unk_14 D_05002858[] = {
    { 0, 1, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 2, 0, 184, 0, -2880, 2880, -3420, 4096, 4096, 4096 },
    { 16, 3, -178, 184, 0, -2880, 2880, -2403, 4096, 4096, 4096 },
    { 28, 4, -138, 158, 0, -2880, 2880, -3166, 4096, 4096, 4096 },
    { 32, 5, -186, 158, 0, -2880, 2880, -2727, 4096, 4096, 4096 },
    { 36, 6, -192, 158, 0, -2880, 2880, -3065, 4096, 4096, 4096 },
    { 40, 7, -206, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 8, -206, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 9, -206, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 80, 10, -206, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 11, -206, 142, 0, -2880, 2880, -2936, 4096, 4096, 4096 },
    { 90, 12, -206, 110, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 94, 13, -194, 94, 0, -2880, 2880, -2804, 4096, 4096, 4096 },
    { 98, 14, -198, -2, 0, -2880, 2880, -2964, 4096, 4096, 4096 },
    { 104, 15, -194, -16, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 108, 16, -194, -62, 0, -2880, 2880, -2916, 4096, 4096, 4096 },
    { 112, 17, -194, -72, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 116, 18, -192, -92, 0, -2880, 2880, -2956, 4096, 4096, 4096 },
    { 120, 19, -194, -102, 0, -2880, 2880, -2801, 4096, 4096, 4096 },
    { 122, 20, -192, -28, 0, -2880, 2880, -2905, 4096, 4096, 4096 },
    { 127, 21, -192, 78, 0, -2880, 2880, -2972, 4096, 4096, 4096 },
    { 129, 22, -206, 202, 0, -2880, 2880, -2744, 4096, 4096, 4096 },
    { 137, -1, -206, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 24, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 4, 25, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 26, -34, 168, 0, -2880, 2880, -2267, 4096, 4096, 4096 },
    { 20, 27, -38, 166, 0, -2880, 2880, -3275, 4096, 4096, 4096 },
    { 28, 28, -82, 158, 0, -2880, 2880, -2561, 4096, 4096, 4096 },
    { 36, 29, -46, 158, 0, -2880, 2880, -3142, 4096, 4096, 4096 },
    { 40, 30, -64, 140, 0, -2880, 2880, -2769, 4096, 4096, 4096 },
    { 44, 31, -58, 140, 0, -2880, 2880, -2988, 4096, 4096, 4096 },
    { 48, 32, -84, 138, 0, -2880, 2880, -2796, 4096, 4096, 4096 },
    { 52, 33, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 34, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 35, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 36, -66, 126, 0, -2880, 2880, -3097, 4096, 4096, 4096 },
    { 72, 37, -64, 130, 0, -2880, 2880, -2756, 4096, 4096, 4096 },
    { 76, 38, -56, 124, 0, -2880, 2880, -2776, 4096, 4096, 4096 },
    { 80, 39, -48, 100, 0, -2880, 2880, -2976, 4096, 4096, 4096 },
    { 84, 40, -48, 100, 0, -2880, 2880, -2944, 4096, 4096, 4096 },
    { 88, 41, -48, 52, 0, -2880, 2880, -2766, 4096, 4096, 4096 },
    { 92, 42, -22, -8, 0, -2880, 2880, -3036, 4096, 4096, 4096 },
    { 98, 43, -16, -86, 0, -2880, 2880, -2800, 4096, 4096, 4096 },
    { 102, 44, -6, -112, 0, -2880, 2880, -2923, 4096, 4096, 4096 },
    { 106, 45, -6, -200, 0, -2880, 2880, -2804, 4096, 4096, 4096 },
    { 110, 46, -6, -220, 0, -2880, 2880, -2963, 4096, 4096, 4096 },
    { 114, 47, -6, -240, 0, -2880, 2880, -2784, 4096, 4096, 4096 },
    { 118, 48, -8, -264, 0, -2880, 2880, -2923, 4096, 4096, 4096 },
    { 122, 49, -24, 2, 0, -2880, 2880, -3024, 4096, 4096, 4096 },
    { 129, 50, -64, 174, 0, -2880, 2880, -2838, 4096, 4096, 4096 },
    { 137, -1, -66, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 52, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 53, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 54, 114, 180, 0, -2880, 2880, -3499, 4096, 4096, 4096 },
    { 24, 55, 28, 166, 0, -2880, 2880, -2644, 4096, 4096, 4096 },
    { 32, 56, 74, 152, 0, -2880, 2880, -3016, 4096, 4096, 4096 },
    { 40, 57, 74, 152, 0, -2880, 2880, -2736, 4096, 4096, 4096 },
    { 44, 58, 74, 142, 0, -2880, 2880, -2937, 4096, 4096, 4096 },
    { 48, 59, 74, 144, 0, -2880, 2880, -2838, 4096, 4096, 4096 },
    { 52, 60, 74, 142, 0, -2880, 2880, -2936, 4096, 4096, 4096 },
    { 56, 61, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 62, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 63, 74, 134, 0, -2880, 2880, -2841, 4096, 4096, 4096 },
    { 92, 64, 74, 133, 0, -2880, 2880, -2840, 4096, 4096, 4096 },
    { 96, 65, 76, 113, 0, -2880, 2880, -2998, 4096, 4096, 4096 },
    { 100, 66, 78, 73, 0, -2880, 2880, -2697, 4096, 4096, 4096 },
    { 106, 67, 80, 63, 0, -2880, 2880, -2947, 4096, 4096, 4096 },
    { 110, 68, 80, 43, 0, -2880, 2880, -2782, 4096, 4096, 4096 },
    { 114, 69, 82, 25, 0, -2880, 2880, -3131, 4096, 4096, 4096 },
    { 118, 70, 84, -2, 0, -2880, 2880, -2828, 4096, 4096, 4096 },
    { 122, 71, 82, -26, 0, -2880, 2880, -3054, 4096, 4096, 4096 },
    { 127, 72, 84, -69, 0, -2880, 2880, -2815, 4096, 4096, 4096 },
    { 129, 73, 78, 196, 0, -2880, 2880, -2945, 4096, 4096, 4096 },
    { 137, -1, 74, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 75, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 76, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 77, 140, 182, 0, -2880, 2880, -2225, 4096, 4096, 4096 },
    { 28, 78, 232, 182, 0, -2880, 2880, -3198, 4096, 4096, 4096 },
    { 36, 79, 166, 180, 0, -2880, 2880, -2468, 4096, 4096, 4096 },
    { 40, 80, 202, 166, 0, -2880, 2880, -3080, 4096, 4096, 4096 },
    { 44, 81, 192, 150, 0, -2880, 2880, -2779, 4096, 4096, 4096 },
    { 48, 82, 214, 156, 0, -2880, 2880, -2924, 4096, 4096, 4096 },
    { 52, 83, 218, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 56, 84, 218, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 85, 218, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 86, 200, 136, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 72, 87, 194, 122, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 76, 88, 186, 120, 0, -2880, 2880, -2648, 4096, 4096, 4096 },
    { 80, 89, 180, 118, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 84, 90, 188, 106, 0, -2880, 2880, -2840, 4096, 4096, 4096 },
    { 92, 91, 184, 68, 0, -2880, 2880, -3030, 4096, 4096, 4096 },
    { 96, 92, 184, 52, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 102, 93, 190, 12, 0, -2880, 2880, -3004, 4096, 4096, 4096 },
    { 106, 94, 190, -28, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 110, 95, 186, -56, 0, -2880, 2880, -2809, 4096, 4096, 4096 },
    { 114, 96, 188, -90, 0, -2880, 2880, -2939, 4096, 4096, 4096 },
    { 118, 97, 190, -124, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 122, 98, 192, -150, 0, -2880, 2880, -2966, 4096, 4096, 4096 },
    { 125, 99, 184, -32, 0, -2880, 2880, -2712, 4096, 4096, 4096 },
    { 129, 100, 230, 184, 0, -2880, 2880, -3006, 4096, 4096, 4096 },
    { 137, -1, 218, 142, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_05003364[] = {
    0x00000000, 0x00000066, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000038,
    0x00000067, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000040, 0x00000068,
    0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000054, 0x00000069, 0x00000000,
    0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000005C, 0x0000006A, 0x00000000, 0x0960F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x0000007A, 0x0000006B, 0x00000000, 0x0960F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x00000081, 0x0000006C, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x00000089, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_05003444 = {
    0, 110, 60, D_05003444_COUNT, D_05004130, D_05004190,
};

/* unreferenced data */
u32 D_0500345C[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF2, 0x0000000E, 0x00000000, 0x00000000, 0x00000014, 0x00000000, 0x00000000,
};

Vtx D_05003480[] = {
#include "assets/game_etc/lws/D_05003480.vtx.inc.c"
};

u16 D_050034C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050034E0.palette.inc"
};

u8 D_050034E0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050034E0.ci4.inc"
};

Gfx D_050036A0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050034C0),
    gsDPLoadTextureBlock_4b(D_050034E0, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05003480, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05003790[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF2, 0x0000000E, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_050037B0[] = {
#include "assets/game_etc/lws/D_050037B0.vtx.inc.c"
};

u16 D_050037F0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003810.palette.inc"
};

u8 D_05003810[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003810.ci4.inc"
};

Gfx D_050039D0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050037F0),
    gsDPLoadTextureBlock_4b(D_05003810, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050037B0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05003AC0[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF1, 0x0000000E, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05003AE0[] = {
#include "assets/game_etc/lws/D_05003AE0.vtx.inc.c"
};

u16 D_05003B20[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003B40.palette.inc"
};

u8 D_05003B40[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003B40.ci4.inc"
};

Gfx D_05003D10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05003B20),
    gsDPLoadTextureBlock_4b(D_05003B40, G_IM_FMT_CI, 32, 29, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05003AE0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05003E00[] = {
    0xFFFFFFF1, 0x00000011, 0xFFFFFFF2, 0x0000000E, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_05003E20[] = {
#include "assets/game_etc/lws/D_05003E20.vtx.inc.c"
};

u16 D_05003E60[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003E80.palette.inc"
};

u8 D_05003E80[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05003E80.ci4.inc"
};

Gfx D_05004040[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05003E60),
    gsDPLoadTextureBlock_4b(D_05003E80, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05003E20, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05004130[] = {
    { D_050036A0, -1, 5, 0, 0, 0 },
    { D_050039D0, -1, 5, 5, 0, 0 },
    { D_05003D10, -1, 6, 10, 0, 0 },
    { D_05004040, -1, 5, 16, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05004130) == D_05003444_COUNT, "");

Lws_unk_14 D_05004190[] = {
    { 0, 1, -182, 94, 0, -2880, 1440, -2880, 3686, 3686, 4096 },
    { 16, 2, -182, 94, 0, -2880, 2880, -2880, 3686, 3686, 4096 },
    { 48, 3, -192, 67, 0, -2880, 2880, -2943, 3686, 3686, 4096 },
    { 80, 4, -209, 108, 0, -2880, 2880, -2745, 3686, 3686, 4096 },
    { 110, -1, -183, 94, 0, -2880, 2880, -2875, 3686, 3686, 4096 },
    { 0, 6, -75, 101, 0, -2880, 1440, -2880, 3686, 3686, 4096 },
    { 16, 7, -75, 101, 0, -2880, 2880, -2880, 3686, 3686, 4096 },
    { 52, 8, -103, 120, 0, -2880, 2880, -2794, 3686, 3686, 4096 },
    { 84, 9, -100, 94, 0, -2880, 2880, -2928, 3686, 3686, 4096 },
    { 110, -1, -79, 99, 0, -2880, 2880, -2890, 3686, 3686, 4096 },
    { 0, 11, 26, 102, 0, -2880, 1440, -2880, 3686, 3686, 4096 },
    { 16, 12, 26, 102, 0, -2880, 2880, -2880, 3686, 3686, 4096 },
    { 44, 13, 9, 91, 0, -2880, 2880, -2667, 3686, 3686, 4096 },
    { 72, 14, 9, 122, 0, -2880, 2880, -2943, 3686, 3686, 4096 },
    { 100, 15, 40, 95, 0, -2880, 2880, -2972, 3686, 3686, 4096 },
    { 110, -1, 29, 100, 0, -2880, 2880, -2860, 3686, 3686, 4096 },
    { 0, 17, 178, 101, 0, -2880, 1440, -2880, 3686, 3686, 4096 },
    { 16, 18, 178, 101, 0, -2880, 2880, -2880, 3686, 3686, 4096 },
    { 48, 19, 193, 113, 0, -2880, 2880, -2951, 3686, 3686, 4096 },
    { 80, 20, 191, 88, 0, -2880, 2880, -2818, 3686, 3686, 4096 },
    { 110, -1, 179, 100, 0, -2880, 2880, -2875, 3686, 3686, 4096 },
};

/* unreferenced data */
u32 D_050043DC[] = {
    0x00000000, 0x00000016, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x0000006E, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_05004414 = {
    0, 110, 60, D_05004414_COUNT, D_05005240, D_050052A0,
};

/* unreferenced data */
u32 D_0500442C[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000010, 0x00000000, 0x00000000, 0x00000011, 0x00000000, 0x00000000,
};

Vtx D_05004450[] = {
#include "assets/game_etc/lws/D_05004450.vtx.inc.c"
};

u16 D_05004490[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050044B0.palette.inc"
};

u8 D_050044B0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050044B0.ci4.inc"
};

Gfx D_050046C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05004490),
    gsDPLoadTextureBlock_4b(D_050044B0, G_IM_FMT_CI, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05004450, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050047B0[] = {
    0xFFFFFFF0, 0x00000011, 0xFFFFFFEF, 0x00000010, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_050047D0[] = {
#include "assets/game_etc/lws/D_050047D0.vtx.inc.c"
};

u16 D_05004810[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004830.palette.inc"
};

u8 D_05004830[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004830.ci4.inc"
};

Gfx D_05004A40[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05004810),
    gsDPLoadTextureBlock_4b(D_05004830, G_IM_FMT_CI, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050047D0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05004B30[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000011, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_05004B50[] = {
#include "assets/game_etc/lws/D_05004B50.vtx.inc.c"
};

u16 D_05004B90[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004BB0.palette.inc"
};

u8 D_05004BB0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004BB0.ci4.inc"
};

Gfx D_05004DD0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05004B90),
    gsDPLoadTextureBlock_4b(D_05004BB0, G_IM_FMT_CI, 32, 34, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05004B50, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05004EC0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05004EE0[] = {
#include "assets/game_etc/lws/D_05004EE0.vtx.inc.c"
};

u16 D_05004F20[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004F40.palette.inc"
};

u8 D_05004F40[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05004F40.ci4.inc"
};

Gfx D_05005150[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05004F20),
    gsDPLoadTextureBlock_4b(D_05004F40, G_IM_FMT_CI, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05004EE0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05005240[] = {
    { D_050046C0, -1, 7, 0, 0, 0 },
    { D_05004A40, -1, 7, 7, 0, 0 },
    { D_05004DD0, -1, 8, 14, 0, 0 },
    { D_05005150, -1, 7, 22, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05005240) == D_05004414_COUNT, "");

Lws_unk_14 D_050052A0[] = {
    { 0, 1, -244, 134, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 2, -244, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 12, 3, -244, 134, 0, -2880, 2880, -2880, 4505, 4096, 4096 },
    { 16, 4, -244, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 48, 5, -262, 94, 0, -2880, 2880, -2971, 4505, 3686, 4096 },
    { 80, 6, -282, 150, 0, -2880, 2880, -2688, 3276, 4505, 4096 },
    { 110, -1, -245, 135, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
    { 0, 8, -68, 126, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 9, -68, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 12, 10, -68, 126, 0, -2880, 2880, -2880, 4505, 4096, 4096 },
    { 16, 11, -68, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 52, 12, -106, 164, 0, -2880, 2880, -2758, 3276, 4096, 4096 },
    { 84, 13, -104, 116, 0, -2880, 2880, -2948, 4505, 4096, 4096 },
    { 110, -1, -75, 121, 0, -2880, 2880, -2895, 4096, 4096, 4096 },
    { 0, 15, 74, 128, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 16, 74, 128, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 12, 17, 74, 128, 0, -2880, 2880, -2880, 4505, 4096, 4096 },
    { 16, 18, 74, 128, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 44, 19, 50, 116, 0, -2880, 2880, -2576, 4505, 3686, 4096 },
    { 72, 20, 50, 160, 0, -2880, 2880, -2971, 3276, 4096, 4096 },
    { 100, 21, 94, 110, 0, -2880, 2880, -3012, 4096, 4096, 4096 },
    { 110, -1, 77, 124, 0, -2880, 2880, -2852, 4096, 4096, 4096 },
    { 0, 23, 248, 126, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 24, 248, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 12, 25, 248, 126, 0, -2880, 2880, -2880, 4505, 4096, 4096 },
    { 16, 26, 248, 126, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 48, 27, 270, 156, 0, -2880, 2880, -2982, 3276, 4096, 4096 },
    { 80, 28, 266, 94, 0, -2880, 2880, -2792, 4505, 4096, 4096 },
    { 110, -1, 249, 123, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_050055CC[] = {
    0x00000000, 0x0000001E, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000008, 0x0000001F, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x0000000C, 0x00000020, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x0000006E, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500563C = {
    0, 104, 60, D_0500563C_COUNT, D_05006328, D_05006370,
};

/* unreferenced data */
u32 D_05005654[] = {
    0xFFFFFFEC, 0x0000001C, 0xFFFFFFED, 0x00000014, 0x00000000, 0x00000000, 0x0000001C, 0x00000000, 0x00000000,
};

Vtx D_05005678[] = {
#include "assets/game_etc/lws/D_05005678.vtx.inc.c"
};

u16 D_050056B8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050056D8.palette.inc"
};

u8 D_050056D8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050056D8.ci4.inc"
};

Gfx D_05005A80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050056B8),
    gsDPLoadTextureBlock_4b(D_050056D8, G_IM_FMT_CI, 48, 39, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05005678, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05005B70[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFED, 0x00000013, 0x00000000, 0x00000000, 0x00000013, 0x00000000,
};

Vtx D_05005B90[] = {
#include "assets/game_etc/lws/D_05005B90.vtx.inc.c"
};

u16 D_05005BD0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05005BF0.palette.inc"
};

u8 D_05005BF0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05005BF0.ci4.inc"
};

Gfx D_05005D20[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05005BD0),
    gsDPLoadTextureBlock_4b(D_05005BF0, G_IM_FMT_CI, 16, 38, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05005B90, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05005E10[] = {
    0xFFFFFFEC, 0x0000001C, 0xFFFFFFEC, 0x00000013, 0x00000000, 0x00000000, 0x0000001C, 0x00000000,
};

Vtx D_05005E30[] = {
#include "assets/game_etc/lws/D_05005E30.vtx.inc.c"
};

u16 D_05005E70[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05005E90.palette.inc"
};

u8 D_05005E90[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05005E90.ci4.inc"
};

Gfx D_05006238[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05005E70),
    gsDPLoadTextureBlock_4b(D_05005E90, G_IM_FMT_CI, 48, 39, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05005E30, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05006328[] = {
    { D_05005A80, -1, 14, 0, 0, 0 },
    { D_05005D20, -1, 14, 14, 0, 0 },
    { D_05006238, -1, 13, 28, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05006328) == D_0500563C_COUNT, "");

Lws_unk_14 D_05006370[] = {
    { 0, 1, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 2, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 3, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 24, 4, 0, 120, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 32, 5, -108, 264, 0, -2880, 2880, -2728, 3276, 4915, 4096 },
    { 40, 6, -190, 196, 0, -2880, 2880, -2987, 3276, 4915, 4096 },
    { 48, 7, -190, 120, 0, -2880, 2880, -2880, 4096, 3276, 4096 },
    { 56, 8, -196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 9, -196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 72, 10, -196, 72, 0, -2880, 2880, -2790, 4915, 3276, 4096 },
    { 80, 11, -196, 234, 0, -2880, 2880, -2790, 3276, 4915, 4096 },
    { 88, 12, -196, 112, 0, -2880, 2880, -2884, 4915, 3276, 4096 },
    { 96, 13, -196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 104, -1, -196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 15, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 16, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 17, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 28, 18, 0, 88, 0, -2880, 2880, -2880, 4915, 2457, 4096 },
    { 36, 19, -2, 232, 0, -2880, 2880, -2880, 3276, 4915, 4096 },
    { 44, 20, -2, 120, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 52, 21, -2, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 22, -1, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 23, -1, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 76, 24, -1, 36, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 84, 25, -1, 280, 0, -2880, 2880, -2880, 3276, 4915, 4096 },
    { 92, 26, -1, 36, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 100, 27, 0, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 104, -1, 0, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 0, 29, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 30, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 24, 31, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 32, 32, 0, 118, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 40, 33, 108, 246, 0, -2880, 2880, -3072, 3276, 4915, 4096 },
    { 48, 34, 158, 200, 0, -2880, 2880, -2713, 3276, 4915, 4096 },
    { 56, 35, 196, 118, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 64, 36, 196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 72, 37, 196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 80, 38, 196, 52, 0, -2880, 2880, -2974, 4915, 3276, 4096 },
    { 88, 39, 196, 250, 0, -2880, 2880, -2979, 3276, 4915, 4096 },
    { 96, 40, 196, 52, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 104, -1, 196, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_050067EC[] = {
    0x00000000, 0x0000002A, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000038, 0x0000002B, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000040, 0x0000002C, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000068, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500685C = {
    0, 104, 60, D_0500685C_COUNT, D_050072B0, D_050072F8,
};

/* unreferenced data */
u32 D_05006874[] = {
    0xFFFFFFEC, 0x0000001C, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x0000001C, 0x00000000, 0x00000000,
};

Vtx D_05006898[] = {
#include "assets/game_etc/lws/D_05006898.vtx.inc.c"
};

u16 D_050068D8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050068F8.palette.inc"
};

u8 D_050068F8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050068F8.ci4.inc"
};

Gfx D_05006BE0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050068D8),
    gsDPLoadTextureBlock_4b(D_050068F8, G_IM_FMT_CI, 48, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05006898, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05006CD0[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05006CF0[] = {
#include "assets/game_etc/lws/D_05006CF0.vtx.inc.c"
};

u16 D_05006D30[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05006D50.palette.inc"
};

u8 D_05006D50[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05006D50.ci4.inc"
};

Gfx D_05006E50[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05006D30),
    gsDPLoadTextureBlock_4b(D_05006D50, G_IM_FMT_CI, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05006CF0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05006F40[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05006F60[] = {
#include "assets/game_etc/lws/D_05006F60.vtx.inc.c"
};

u16 D_05006FA0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05006FC0.palette.inc"
};

u8 D_05006FC0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05006FC0.ci4.inc"
};

Gfx D_050071C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05006FA0),
    gsDPLoadTextureBlock_4b(D_05006FC0, G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05006F60, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_050072B0[] = {
    { D_05006BE0, -1, 14, 0, 0, 0 },
    { D_05006E50, -1, 14, 14, 0, 0 },
    { D_050071C0, -1, 13, 28, 0, 0 },
};
static_assert(ARRAY_COUNT(D_050072B0) == D_0500685C_COUNT, "");

Lws_unk_14 D_050072F8[] = {
    { 0, 1, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 8, 2, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 3, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 24, 4, 0, 120, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 32, 5, -98, 264, 0, -2880, 2880, -2728, 3276, 4915, 4096 },
    { 40, 6, -146, 196, 0, -2880, 2880, -2987, 3276, 4915, 4096 },
    { 48, 7, -128, 120, 0, -2880, 2880, -2880, 4096, 3276, 4096 },
    { 56, 8, -134, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 9, -120, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 72, 10, -106, 72, 0, -2880, 2880, -2790, 4915, 3276, 4096 },
    { 80, 11, -132, 234, 0, -2880, 2880, -2790, 3276, 4915, 4096 },
    { 88, 12, -84, 116, 0, -2880, 2880, -2884, 4915, 3276, 4096 },
    { 96, 13, -108, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 104, -1, -117, 150, 0, -2880, 2880, -2879, 4081, 4110, 4096 },
    { 0, 15, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 16, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 17, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 28, 18, 0, 88, 0, -2880, 2880, -2880, 4915, 2457, 4096 },
    { 36, 19, -2, 232, 0, -2880, 2880, -2880, 3276, 4915, 4096 },
    { 44, 20, -2, 120, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 52, 21, -2, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 64, 22, -1, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 23, -1, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 76, 24, -1, 36, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 84, 25, -1, 280, 0, -2880, 2880, -2880, 3276, 4915, 4096 },
    { 92, 26, -1, 36, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 100, 27, 0, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 104, -1, 0, 153, 0, -2880, 2880, -2880, 4069, 4122, 4096 },
    { 0, 29, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 30, 0, 712, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 24, 31, 0, 182, 0, -2880, 2880, -2880, 2457, 4915, 4096 },
    { 32, 32, 0, 118, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 40, 33, 108, 246, 0, -2880, 2880, -3072, 3276, 4915, 4096 },
    { 48, 34, 132, 200, 0, -2880, 2880, -2713, 3276, 4915, 4096 },
    { 56, 35, 136, 118, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 64, 36, 142, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 72, 37, 142, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 80, 38, 116, 52, 0, -2880, 2880, -2974, 4915, 3276, 4096 },
    { 88, 39, 160, 250, 0, -2880, 2880, -2979, 3276, 4915, 4096 },
    { 96, 40, 126, 52, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 104, -1, 137, 125, 0, -2880, 2880, -2878, 4300, 3891, 4096 },
};

/* unreferenced data */
u32 D_05007774[] = {
    0x00000000, 0x0000002A, 0x00000000, 0x03F4F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
    0x00000068, 0xFFFFFFFF, 0x00000000, 0x03F4F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_050077AC = {
    0, 202, 60, D_050077AC_COUNT, D_05009580, D_05009610,
};

/* unreferenced data */
u32 D_050077C4[] = {
    0xFFFFFFF6, 0x0000000A, 0xFFFFFFF3, 0x0000000C, 0x00000000, 0x00000000, 0x0000000D, 0x00000000, 0x00000000,
};

Vtx D_050077E8[] = {
#include "assets/game_etc/lws/D_050077E8.vtx.inc.c"
};

u16 D_05007828[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05007A28.palette.inc"
};

u8 D_05007A28[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05007A28.ci8.inc"
};

Gfx D_05007C80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05007828),
    gsDPLoadTextureBlock(D_05007A28, G_IM_FMT_CI, G_IM_SIZ_8b, 24, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050077E8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05007D70[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF7, 0x00000009, 0x00000000, 0x00000000, 0x00000009, 0x00000000,
};

Vtx D_05007D90[] = {
#include "assets/game_etc/lws/D_05007D90.vtx.inc.c"
};

u16 D_05007DD0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05007FD0.palette.inc"
};

u8 D_05007FD0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05007FD0.ci8.inc"
};

Gfx D_050080F0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05007DD0),
    gsDPLoadTextureBlock(D_05007FD0, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05007D90, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050081E0[] = {
    0xFFFFFFF4, 0x0000000C, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x0000000D, 0x00000000,
};

Vtx D_05008200[] = {
#include "assets/game_etc/lws/D_05008200.vtx.inc.c"
};

u16 D_05008240[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008440.palette.inc"
};

u8 D_05008440[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008440.ci8.inc"
};

Gfx D_050086B0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05008240),
    gsDPLoadTextureBlock(D_05008440, G_IM_FMT_CI, G_IM_SIZ_8b, 24, 26, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05008200, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050087A0[] = {
    0xFFFFFFFA, 0x00000006, 0xFFFFFFF6, 0x00000009, 0x00000000, 0x00000000, 0x0000000A, 0x00000000,
};

Vtx D_050087C0[] = {
#include "assets/game_etc/lws/D_050087C0.vtx.inc.c"
};

u16 D_05008800[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008A00.palette.inc"
};

u8 D_05008A00[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008A00.ci8.inc"
};

Gfx D_05008B30[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05008800),
    gsDPLoadTextureBlock(D_05008A00, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 19, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050087C0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05008C20[] = {
    0xFFFFFFF6, 0x0000000A, 0xFFFFFFF3, 0x0000000C, 0x00000000, 0x00000000, 0x0000000D, 0x00000000,
};

Vtx D_05008C40[] = {
#include "assets/game_etc/lws/D_05008C40.vtx.inc.c"
};

u16 D_05008C80[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008E80.palette.inc"
};

u8 D_05008E80[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05008E80.ci8.inc"
};

Gfx D_05009010[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05008C80),
    gsDPLoadTextureBlock(D_05008E80, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05008C40, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05009100[] = {
    0xFFFFFFF8, 0x00000008, 0xFFFFFFF6, 0x00000009, 0x00000000, 0x00000000, 0x0000000A, 0x00000000,
};

Vtx D_05009120[] = {
#include "assets/game_etc/lws/D_05009120.vtx.inc.c"
};

u16 D_05009160[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05009360.palette.inc"
};

u8 D_05009360[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05009360.ci8.inc"
};

Gfx D_05009490[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05009160),
    gsDPLoadTextureBlock(D_05009360, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 19, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05009120, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05009580[] = {
    { D_05007C80, -1, 16, 0, 0, 0 },  { D_050080F0, -1, 17, 16, 0, 0 }, { D_050086B0, -1, 15, 33, 0, 0 },
    { D_05008B30, -1, 14, 48, 0, 0 }, { D_05009010, -1, 15, 62, 0, 0 }, { D_05009490, -1, 15, 77, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05009580) == D_050077AC_COUNT, "");

Lws_unk_14 D_05009610[] = {
    { 0, 1, 24, 666, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 16, 2, 8, 119, 0, -2880, 2880, -3408, 4096, 4096, 4096 },
    { 22, 3, -69, 119, 0, -2880, 2880, -2518, 4096, 4096, 4096 },
    { 28, 4, -127, 159, 0, -2880, 2880, -3069, 4096, 4096, 4096 },
    { 40, 5, -144, 138, 0, -2880, 2880, -3056, 4096, 4096, 4096 },
    { 48, 6, -172, 132, 0, -2880, 2880, -2808, 4096, 4096, 4096 },
    { 56, 7, -168, 140, 0, -2880, 2880, -2924, 4096, 4096, 4096 },
    { 60, 8, -174, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 80, 9, -174, 94, 0, -2880, 2880, -2976, 4096, 4096, 4096 },
    { 100, 10, -174, 134, 0, -2880, 2880, -2772, 4096, 4096, 4096 },
    { 120, 11, -174, 182, 0, -2880, 2880, -2899, 4096, 4096, 4096 },
    { 140, 12, -174, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 156, 13, -174, 104, 0, -2880, 2880, -2996, 4096, 4096, 4096 },
    { 172, 14, -174, 134, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 188, 15, -174, 170, 0, -2880, 2880, -2760, 4096, 4096, 4096 },
    { 202, -1, -174, 138, 0, -2880, 2880, -2863, 4096, 4096, 4096 },
    { 0, 17, 24, 634, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 4, 18, 24, 634, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 24, 19, 10, 91, 0, -2880, 2880, -3281, 4096, 4096, 4096 },
    { 32, 20, -39, 103, 0, -2880, 2880, -2603, 4096, 4096, 4096 },
    { 40, 21, -69, 129, 0, -2880, 2880, -3236, 4096, 4096, 4096 },
    { 48, 22, -119, 117, 0, -2880, 2880, -2515, 4096, 4096, 4096 },
    { 56, 23, -73, 105, 0, -2880, 2880, -3038, 4096, 4096, 4096 },
    { 64, 24, -88, 100, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 84, 25, -88, 144, 0, -2880, 2880, -2820, 4096, 4096, 4096 },
    { 104, 26, -88, 100, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 124, 27, -88, 68, 0, -2880, 2880, -2814, 4096, 4096, 4096 },
    { 140, 28, -88, 93, 0, -2880, 2880, -2866, 4096, 4096, 4096 },
    { 144, 29, -88, 100, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 160, 30, -88, 120, 0, -2880, 2880, -2752, 4096, 4096, 4096 },
    { 176, 31, -88, 90, 0, -2880, 2880, -3017, 4096, 4096, 4096 },
    { 192, 32, -88, 62, 0, -2880, 2880, -3214, 4096, 4096, 4096 },
    { 202, -1, -88, 87, 0, -2880, 2880, -2931, 4096, 4096, 4096 },
    { 0, 34, 24, 666, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 35, 24, 666, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 36, 36, 15, 189, 0, -2880, 2880, -3425, 4096, 4096, 4096 },
    { 44, 37, -38, 167, 0, -2880, 2880, -2648, 4096, 4096, 4096 },
    { 52, 38, -20, 189, 0, -2880, 2880, -3036, 4096, 4096, 4096 },
    { 60, 39, -22, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 72, 40, -22, 62, 0, -2880, 2880, -3014, 4096, 4096, 4096 },
    { 92, 41, -22, 200, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 112, 42, -22, 184, 0, -2880, 2880, -2806, 4096, 4096, 4096 },
    { 132, 43, -22, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 140, 44, -22, 127, 0, -2880, 2880, -2915, 4096, 4096, 4096 },
    { 148, 45, -22, 112, 0, -2880, 2880, -2936, 4096, 4096, 4096 },
    { 176, 46, -22, 150, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 192, 47, -22, 178, 0, -2880, 2880, -2990, 4096, 4096, 4096 },
    { 202, -1, -22, 136, 0, -2880, 2880, -2929, 4096, 4096, 4096 },
    { 0, 49, 24, 642, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 36, 50, 24, 642, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 48, 51, 28, 119, 0, -2880, 2880, -2544, 4096, 4096, 4096 },
    { 56, 52, 72, 121, 0, -2880, 2880, -3176, 4096, 4096, 4096 },
    { 64, 53, 34, 113, 0, -2880, 2880, -2736, 4096, 4096, 4096 },
    { 72, 54, 44, 106, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 88, 55, 44, 68, 0, -2880, 2880, -3064, 4096, 4096, 4096 },
    { 104, 56, 44, 106, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 120, 57, 44, 134, 0, -2880, 2880, -2731, 4096, 4096, 4096 },
    { 140, 58, 44, 106, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 160, 59, 44, 88, 0, -2880, 2880, -2489, 4096, 4096, 4096 },
    { 176, 60, 30, 126, 0, -2880, 2880, -2686, 4096, 4096, 4096 },
    { 192, 61, 44, 130, 0, -2880, 2880, -2860, 4096, 4096, 4096 },
    { 202, -1, 44, 108, 0, -2880, 2880, -2878, 4096, 4096, 4096 },
    { 0, 63, 24, 666, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 44, 64, 24, 666, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 60, 65, 52, 166, 0, -2880, 2880, -2510, 4096, 4096, 4096 },
    { 68, 66, 124, 166, 0, -2880, 2880, -3182, 4096, 4096, 4096 },
    { 76, 67, 94, 162, 0, -2880, 2880, -2678, 4096, 4096, 4096 },
    { 80, 68, 118, 148, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 92, 69, 118, 110, 0, -2880, 2880, -2760, 4096, 4096, 4096 },
    { 104, 70, 118, 148, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 116, 71, 118, 176, 0, -2880, 2880, -2961, 4096, 4096, 4096 },
    { 128, 72, 118, 148, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 140, 73, 118, 114, 0, -2880, 2880, -2881, 4096, 4096, 4096 },
    { 156, 74, 118, 88, 0, -2880, 2880, -2750, 4096, 4096, 4096 },
    { 172, 75, 118, 122, 0, -2880, 2880, -2955, 4096, 4096, 4096 },
    { 188, 76, 118, 144, 0, -2880, 2880, -2952, 4096, 4096, 4096 },
    { 202, -1, 118, 114, 0, -2880, 2880, -2891, 4096, 4096, 4096 },
    { 0, 78, 24, 642, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 56, 79, 24, 642, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 68, 80, 75, 100, 0, -2880, 2880, -2566, 4096, 4096, 4096 },
    { 76, 81, 75, 100, 0, -2880, 2880, -3073, 4096, 4096, 4096 },
    { 80, 82, 95, 128, 0, -2880, 2880, -2641, 4096, 4096, 4096 },
    { 82, 83, 129, 146, 0, -2880, 2880, -2588, 4096, 4096, 4096 },
    { 88, 84, 171, 120, 0, -2880, 2880, -2641, 4096, 4096, 4096 },
    { 94, 85, 208, 108, 0, -2880, 2880, -3049, 4096, 4096, 4096 },
    { 98, 86, 194, 98, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 110, 87, 194, 62, 0, -2880, 2880, -2712, 4096, 4096, 4096 },
    { 122, 88, 194, 98, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 138, 89, 194, 134, 0, -2880, 2880, -3004, 4096, 4096, 4096 },
    { 140, 90, 194, 129, 0, -2880, 2880, -2989, 4096, 4096, 4096 },
    { 154, 91, 194, 98, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 202, -1, 194, 128, 0, -2880, 2880, -2984, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_0500A020[] = {
    0x00000000, 0x0000005D, 0x00000000, 0x0A1AF4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000062, 0x0000005E,
    0x00000000, 0x0A1AF4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000008C, 0x0000005F, 0x00000000, 0x0A1AF4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x0000009A, 0x00000060, 0x00000000, 0x0A1AF4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x000000CA, 0xFFFFFFFF, 0x00000000, 0x0A1AF4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500A0AC = {
    0, 88, 60, D_0500A0AC_COUNT, D_0500A998, D_0500A9B0,
};

/* unreferenced data */
u32 D_0500A0C4[] = {
    0xFFFFFFE0, 0x00000020, 0xFFFFFFF5, 0x0000000B, 0x00000000, 0x00000000, 0x00000020, 0x00000000, 0x00000000,
};

Vtx D_0500A0E8[] = {
#include "assets/game_etc/lws/D_0500A0E8.vtx.inc.c"
};

u16 D_0500A128[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500A328.palette.inc"
};

u8 D_0500A328[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500A328.ci8.inc"
};

Gfx D_0500A8A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500A128),
    gsDPLoadTextureBlock(D_0500A328, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 22, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500A0E8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_0500A998[] = {
    { D_0500A8A8, -1, 8, 0, 0, 0 },
};
static_assert(ARRAY_COUNT(D_0500A998) == D_0500A0AC_COUNT, "");

Lws_unk_14 D_0500A9B0[] = {
    { 0, 1, 0, 0, 80, -2880, 2880, -2880, 40, 4096, 4096 },
    { 12, 2, 0, 0, 80, -2880, 2880, -2880, 4505, 3686, 4096 },
    { 20, 3, 0, 0, 80, -2880, 2880, -2880, 3686, 4505, 4096 },
    { 26, 4, 0, 0, 80, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 42, 5, 0, 0, 80, -2880, 2880, -2937, 3686, 4505, 4096 },
    { 58, 6, 0, 0, 80, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 74, 7, 0, 0, 80, -2880, 2880, -2792, 4505, 3686, 4096 },
    { 88, -1, 0, 0, 80, -2880, 2880, -2867, 4152, 4039, 4096 },
};

/* unreferenced data */
u32 D_0500AA90[] = {
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500AAAC = {
    0, 159, 75, D_0500AAAC_COUNT, D_0500C0B8, D_0500C100,
};

/* unreferenced data */
u32 D_0500AAC4[] = {
    0xFFFFFFF2, 0x0000000E, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000, 0x00000000,
};

Vtx D_0500AAE8[] = {
#include "assets/game_etc/lws/D_0500AAE8.vtx.inc.c"
};

u16 D_0500AB28[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500AD28.palette.inc"
};

u8 D_0500AD28[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500AD28.ci8.inc"
};

Gfx D_0500B128[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500AB28),
    gsDPLoadTextureBlock(D_0500AD28, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500AAE8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500B218[] = {
    0xFFFFFFF2, 0x0000000E, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500B238[] = {
#include "assets/game_etc/lws/D_0500B238.vtx.inc.c"
};

u16 D_0500B278[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500B478.palette.inc"
};

u8 D_0500B478[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500B478.ci8.inc"
};

Gfx D_0500B878[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500B278),
    gsDPLoadTextureBlock(D_0500B478, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500B238, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500B968[] = {
    0xFFFFFFF2, 0x0000000E, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500B988[] = {
#include "assets/game_etc/lws/D_0500B988.vtx.inc.c"
};

u16 D_0500B9C8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500BBC8.palette.inc"
};

u8 D_0500BBC8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500BBC8.ci8.inc"
};

Gfx D_0500BFC8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500B9C8),
    gsDPLoadTextureBlock(D_0500BBC8, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500B988, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_0500C0B8[] = {
    { D_0500B128, -1, 10, 6, 0, 0 },
    { D_0500B878, -1, 8, 16, 0, 0 },
    { D_0500BFC8, -1, 6, 24, 0, 0 },
};
static_assert(ARRAY_COUNT(D_0500C0B8) == D_0500AAAC_COUNT, "");

Lws_unk_14 D_0500C100[] = {
    { 0, 1, 0, 162, 0, -2880, 2880, -2880, 4096, 40, 4096 },
    { 8, 2, 0, 162, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 149, 3, 0, 162, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 152, 4, 0, 182, 0, -2880, 2880, -2880, 4096, 4915, 4096 },
    { 156, 5, -2, 54, 0, -2880, 2880, -2880, 2457, 8192, 4096 },
    { 159, -1, 0, -614, 0, -2880, 2880, -2880, 40, 12288, 4096 },
    { 0, 7, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
    { 96, 8, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
    { 96, 9, 0, 0, 0, -2880, 0, -2880, 40, 40, 4096 },
    { 104, 10, 0, 122, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 123, 11, 0, -30, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 126, 12, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 149, 13, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 152, 14, 0, 28, 0, -2880, 2880, -2880, 4096, 4915, 4096 },
    { 156, 15, 0, -192, 0, -2880, 2880, -2880, 2457, 8192, 4096 },
    { 159, -1, 0, -844, 0, -2880, 2880, -2880, 40, 12288, 4096 },
    { 0, 17, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
    { 48, 18, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
    { 48, 19, 0, 0, 0, -2880, 2880, -2880, 40, 40, 4096 },
    { 56, 20, 0, 122, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 75, 21, -2, -28, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 78, 22, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 92, 23, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 96, -1, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
    { 0, 25, 0, -144, 0, -2880, 2880, -2880, 40, 40, 4096 },
    { 8, 26, 0, 118, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 20, 27, 0, -32, 0, -2880, 2880, -2880, 4915, 3276, 4096 },
    { 24, 28, 0, 0, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 44, 29, 0, 0, 0, -2880, 2880, -2880, 4084, 4107, 4096 },
    { 48, -1, 0, 0, 0, -2880, 0, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_0500C448[] = {
    0x00000000, 0x0000001F, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000030, 0x00000020,
    0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000003C, 0x00000021, 0x00000000, 0x0960F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x00000060, 0x00000022, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x0000007E, 0x00000023, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000095,
    0x00000024, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000098, 0x00000025, 0x00000000,
    0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000009C, 0x00000026, 0x00000000, 0x0960F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x0000009F, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_0500C544 = {
    1, 136, 60, D_0500C544_COUNT, D_05012CA0, D_05012E80,
};

/* unreferenced data */
u32 D_0500C55C[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000, 0x00000000,
};

Vtx D_0500C580[] = {
#include "assets/game_etc/lws/D_0500C580.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500C5C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500C5C0.rgba16.inc"
};

u8 D_0500C5E0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500C5E0.i4.inc"
};

Gfx D_0500C7F0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500C5E0, G_IM_FMT_I, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500C580, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500C8B0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500C8D0[] = {
#include "assets/game_etc/lws/D_0500C8D0.vtx.inc.c"
};

u16 D_0500C910[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500CB10.palette.inc"
};

u8 D_0500CB10[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500CB10.ci8.inc"
};

Gfx D_0500CF30[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500C910),
    gsDPLoadTextureBlock(D_0500CB10, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500C8D0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500D020[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_0500D040[] = {
#include "assets/game_etc/lws/D_0500D040.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500D080[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500D080.rgba16.inc"
};

u8 D_0500D0A0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500D0A0.i4.inc"
};

Gfx D_0500D2F8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500D0A0, G_IM_FMT_I, 48, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500D040, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500D3B8[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_0500D3D8[] = {
#include "assets/game_etc/lws/D_0500D3D8.vtx.inc.c"
};

u16 D_0500D418[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500D618.palette.inc"
};

u8 D_0500D618[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500D618.ci8.inc"
};

Gfx D_0500DA00[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500D418),
    gsDPLoadTextureBlock(D_0500D618, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500D3D8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500DAF0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000011, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_0500DB10[] = {
#include "assets/game_etc/lws/D_0500DB10.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500DB50[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500DB50.rgba16.inc"
};

u8 D_0500DB70[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500DB70.i4.inc"
};

Gfx D_0500DDA0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500DB70, G_IM_FMT_I, 32, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500DB10, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500DE60[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000011, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_0500DE80[] = {
#include "assets/game_etc/lws/D_0500DE80.vtx.inc.c"
};

u16 D_0500DEC0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500E0C0.palette.inc"
};

u8 D_0500E0C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500E0C0.ci8.inc"
};

Gfx D_0500E520[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500DEC0),
    gsDPLoadTextureBlock(D_0500E0C0, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 35, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500DE80, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500E610[] = {
    0xFFFFFFF4, 0x0000000C, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x0000000D, 0x00000000,
};

Vtx D_0500E630[] = {
#include "assets/game_etc/lws/D_0500E630.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500E670[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500E670.rgba16.inc"
};

u8 D_0500E690[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500E690.i4.inc"
};

Gfx D_0500E850[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500E690, G_IM_FMT_I, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500E630, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500E910[] = {
    0xFFFFFFF4, 0x0000000C, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x0000000D, 0x00000000,
};

Vtx D_0500E930[] = {
#include "assets/game_etc/lws/D_0500E930.vtx.inc.c"
};

u16 D_0500E970[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500EB70.palette.inc"
};

u8 D_0500EB70[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500EB70.ci8.inc"
};

Gfx D_0500EE10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500E970),
    gsDPLoadTextureBlock(D_0500EB70, G_IM_FMT_CI, G_IM_SIZ_8b, 24, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500E930, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500EF00[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500EF20[] = {
#include "assets/game_etc/lws/D_0500EF20.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500EF60[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500EF60.rgba16.inc"
};

u8 D_0500EF80[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500EF80.i4.inc"
};

Gfx D_0500F1A0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500EF80, G_IM_FMT_I, 32, 34, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500EF20, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500F260[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x00000010, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500F280[] = {
#include "assets/game_etc/lws/D_0500F280.vtx.inc.c"
};

u16 D_0500F2C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500F4C0.palette.inc"
};

u8 D_0500F4C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500F4C0.ci8.inc"
};

Gfx D_0500F900[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500F2C0),
    gsDPLoadTextureBlock(D_0500F4C0, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 34, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500F280, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500F9F0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500FA10[] = {
#include "assets/game_etc/lws/D_0500FA10.vtx.inc.c"
};

/* unreferenced data */
u16 D_0500FA50[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500FA50.rgba16.inc"
};

u8 D_0500FA70[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500FA70.i4.inc"
};

Gfx D_0500FC80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_0500FA70, G_IM_FMT_I, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500FA10, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_0500FD40[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_0500FD60[] = {
#include "assets/game_etc/lws/D_0500FD60.vtx.inc.c"
};

u16 D_0500FDA0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500FFA0.palette.inc"
};

u8 D_0500FFA0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_0500FFA0.ci8.inc"
};

Gfx D_050103C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_0500FDA0),
    gsDPLoadTextureBlock(D_0500FFA0, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_0500FD60, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050104B0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_050104D0[] = {
#include "assets/game_etc/lws/D_050104D0.vtx.inc.c"
};

/* unreferenced data */
u16 D_05010510[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010510.rgba16.inc"
};

u8 D_05010530[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010530.i4.inc"
};

Gfx D_05010740[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05010530, G_IM_FMT_I, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050104D0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05010800[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF0, 0x0000000F, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05010820[] = {
#include "assets/game_etc/lws/D_05010820.vtx.inc.c"
};

u16 D_05010860[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010A60.palette.inc"
};

u8 D_05010A60[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010A60.ci8.inc"
};

Gfx D_05010E80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05010860),
    gsDPLoadTextureBlock(D_05010A60, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 33, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05010820, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05010F70[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05010F90[] = {
#include "assets/game_etc/lws/D_05010F90.vtx.inc.c"
};

/* unreferenced data */
u16 D_05010FD0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010FD0.rgba16.inc"
};

u8 D_05010FF0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05010FF0.i4.inc"
};

Gfx D_05011180[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05010FF0, G_IM_FMT_I, 32, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05010F90, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05011240[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000010, 0x00000000,
};

Vtx D_05011260[] = {
#include "assets/game_etc/lws/D_05011260.vtx.inc.c"
};

u16 D_050112A0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050114A0.palette.inc"
};

u8 D_050114A0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050114A0.ci8.inc"
};

Gfx D_050117C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_050112A0),
    gsDPLoadTextureBlock(D_050114A0, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 25, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05011260, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050118B0[] = {
    0xFFFFFFF4, 0x0000000C, 0xFFFFFFF4, 0x0000000C, 0x00000000, 0x00000000, 0x0000000C, 0x00000000,
};

Vtx D_050118D0[] = {
#include "assets/game_etc/lws/D_050118D0.vtx.inc.c"
};

/* unreferenced data */
u16 D_05011910[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05011910.rgba16.inc"
};

u8 D_05011930[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05011930.i4.inc"
};

Gfx D_05011AD0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05011930, G_IM_FMT_I, 32, 26, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050118D0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05011B90[] = {
    0xFFFFFFF4, 0x0000000C, 0xFFFFFFF4, 0x0000000C, 0x00000000, 0x00000000, 0x0000000C, 0x00000000,
};

Vtx D_05011BB0[] = {
#include "assets/game_etc/lws/D_05011BB0.vtx.inc.c"
};

u16 D_05011BF0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05011DF0.palette.inc"
};

u8 D_05011DF0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05011DF0.ci8.inc"
};

Gfx D_05012060[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05011BF0),
    gsDPLoadTextureBlock(D_05011DF0, G_IM_FMT_CI, G_IM_SIZ_8b, 24, 26, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05011BB0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05012150[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000011, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_05012170[] = {
#include "assets/game_etc/lws/D_05012170.vtx.inc.c"
};

/* unreferenced data */
u16 D_050121B0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050121B0.rgba16.inc"
};

u8 D_050121D0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050121D0.i4.inc"
};

Gfx D_05012410[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_050121D0, G_IM_FMT_I, 32, 36, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05012170, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050124D0[] = {
    0xFFFFFFF0, 0x00000010, 0xFFFFFFEF, 0x00000011, 0x00000000, 0x00000000, 0x00000011, 0x00000000,
};

Vtx D_050124F0[] = {
#include "assets/game_etc/lws/D_050124F0.vtx.inc.c"
};

u16 D_05012530[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05012730.palette.inc"
};

u8 D_05012730[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05012730.ci8.inc"
};

Gfx D_05012BB0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_05012530),
    gsDPLoadTextureBlock(D_05012730, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 36, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050124F0, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05012CA0[] = {
    { D_0500C7F0, -1, 5, 0, 0, 0 },  { D_0500CF30, -1, 5, 5, 0, 0 },  { D_0500D2F8, -1, 5, 10, 0, 0 },
    { D_0500DA00, -1, 5, 15, 0, 0 }, { D_0500DDA0, -1, 5, 20, 0, 0 }, { D_0500E520, -1, 5, 25, 0, 0 },
    { D_0500E850, -1, 5, 30, 0, 0 }, { D_0500EE10, -1, 5, 35, 0, 0 }, { D_0500F1A0, -1, 5, 40, 0, 0 },
    { D_0500F900, -1, 5, 45, 0, 0 }, { D_0500FC80, -1, 5, 50, 0, 0 }, { D_050103C0, -1, 5, 55, 0, 0 },
    { D_05010740, -1, 5, 60, 0, 0 }, { D_05010E80, -1, 5, 65, 0, 0 }, { D_05011180, -1, 5, 70, 0, 0 },
    { D_050117C0, -1, 5, 75, 0, 0 }, { D_05011AD0, -1, 5, 80, 0, 0 }, { D_05012060, -1, 5, 85, 0, 0 },
    { D_05012410, -1, 4, 90, 0, 0 }, { D_05012BB0, -1, 4, 94, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05012CA0) == D_0500C544_COUNT, "");

Lws_unk_14 D_05012E80[] = {
    { 0, 1, 302, -106, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 2, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 76, 3, 302, -106, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 4, 302, -106, 0, -2880, 2880, 8751, 3276, 3276, 4096 },
    { 136, -1, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 6, 302, -106, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 7, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 76, 8, 302, -106, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 9, 302, -106, 0, -2880, 2880, 8751, 3276, 3276, 4096 },
    { 136, -1, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 11, 162, -134, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 12, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 68, 13, 162, -134, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 14, 162, -134, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 0, 16, 162, -134, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 17, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 68, 18, 162, -134, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 19, 162, -134, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 0, 21, 16, -114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 22, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 60, 23, 16, -114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 24, 16, -114, 0, -2880, 2880, 8791, 3276, 3276, 4096 },
    { 136, -1, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 26, 16, -114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 27, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 60, 28, 16, -114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 29, 16, -114, 0, -2880, 2880, 8791, 3276, 3276, 4096 },
    { 136, -1, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 31, -130, -146, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 32, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 52, 33, -130, -146, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 100, 34, -130, -146, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 0, 36, -130, -146, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 37, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 52, 38, -130, -146, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 100, 39, -130, -146, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 0, 41, -276, -130, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 42, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 44, 43, -276, -130, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 92, 44, -276, -130, 0, -2880, 2880, 8737, 3276, 3276, 4096 },
    { 136, -1, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 0, 46, -276, -130, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 47, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 44, 48, -276, -130, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 92, 49, -276, -130, 0, -2880, 2880, 8737, 3276, 3276, 4096 },
    { 136, -1, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 0, 51, 298, 82, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 52, 298, 82, 0, -2880, 2880, 8640, 3481, 3481, 4096 },
    { 72, 53, 298, 82, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 120, 54, 298, 62, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 298, 82, 0, -2880, 2880, 8640, 3481, 3481, 4096 },
    { 0, 56, 298, 82, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 57, 298, 82, 0, -2880, 2880, 8640, 3481, 3481, 4096 },
    { 72, 58, 298, 82, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 120, 59, 298, 62, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 298, 82, 0, -2880, 2880, 8640, 3481, 3481, 4096 },
    { 0, 61, 136, 114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 62, 136, 114, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 64, 63, 136, 114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 64, 136, 94, 0, -2880, 2880, 8771, 3276, 3276, 4096 },
    { 136, -1, 136, 114, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 0, 66, 136, 114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 67, 136, 114, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 64, 68, 136, 114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 69, 136, 94, 0, -2880, 2880, 8771, 3276, 3276, 4096 },
    { 136, -1, 136, 114, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 0, 71, -12, 88, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 72, -12, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 56, 73, -12, 88, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 104, 74, -12, 68, 0, -2880, 2880, 8457, 3276, 3276, 4096 },
    { 136, -1, -12, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 0, 76, -12, 88, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 77, -12, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 56, 78, -12, 88, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 104, 79, -12, 68, 0, -2880, 2880, 8457, 3276, 3276, 4096 },
    { 136, -1, -12, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 0, 81, -150, 86, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 82, -150, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 48, 83, -150, 86, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 96, 84, -150, 62, 0, -2880, 2880, 8745, 3276, 3276, 4096 },
    { 136, -1, -150, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 0, 86, -150, 86, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 87, -150, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 48, 88, -150, 86, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 96, 89, -150, 62, 0, -2880, 2880, 8745, 3276, 3276, 4096 },
    { 136, -1, -150, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 0, 91, -272, 96, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 92, -272, 96, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 88, 93, -272, 64, 0, -2880, 2880, 8467, 3276, 3276, 4096 },
    { 136, -1, -272, 96, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 0, 95, -272, 96, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 96, -272, 96, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 88, 97, -272, 64, 0, -2880, 2880, 8467, 3276, 3276, 4096 },
    { 136, -1, -272, 96, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_05013938[] = {
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x0AC8F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_05013954 = {
    1, 160, 60, D_05013954_COUNT, D_05014170, D_05014188,
};

/* unreferenced data */
u32 D_0501396C[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF8, 0x00000007, 0x00000000, 0x00000000, 0x00000028, 0x00000000, 0x00000000,
};

Vtx D_05013990[] = {
#include "assets/game_etc/lws/D_05013990.vtx.inc.c"
};

u16 D_050139D0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05013BD0.palette.inc"
};

u8 D_05013BD0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05013BD0.ci8.inc"
};

Gfx D_05014080[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal256(D_050139D0),
    gsDPLoadTextureBlock(D_05013BD0, G_IM_FMT_CI, G_IM_SIZ_8b, 80, 15, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05013990, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05014170[] = {
    { D_05014080, -1, 9, 0, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05014170) == D_05013954_COUNT, "");

Lws_unk_14 D_05014188[] = {
    { 0, 1, 0, -414, 0, -2880, 2880, -2880, 4096, 40, 4096 },
    { 40, 2, 0, -414, 0, -2880, 2880, -2880, 4096, 40, 4096 },
    { 50, 3, 0, -340, 0, -2880, 2880, -2880, 4096, 4915, 4096 },
    { 56, 4, 0, -362, 0, -2880, 2880, -2880, 4096, 3686, 4096 },
    { 60, 5, 0, -356, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 85, 6, -50, -355, 0, -2880, 2880, -2828, 3276, 4505, 4096 },
    { 110, 7, 0, -356, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 135, 8, 58, -356, 0, -2880, 2880, -2926, 3276, 4505, 4096 },
    { 160, -1, 0, -356, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_05014284[] = {
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x0AC8F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_050142A0 = {
    0, 104, 60, D_050142A0_COUNT, D_05015AD8, D_05015B38,
};

/* unreferenced data */
u32 D_050142B8[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_050142D8[] = {
#include "assets/game_etc/lws/D_050142D8.vtx.inc.c"
};

/* unreferenced data */
u16 D_05014318[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014318.rgba16.inc"
};

u8 D_05014338[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014338.i4.inc"
};

Gfx D_050147E8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05014338, G_IM_FMT_I, 80, 30, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050142D8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050148A8[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_050148C8[] = {
#include "assets/game_etc/lws/D_050148C8.vtx.inc.c"
};

/* unreferenced data */
u16 D_05014908[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014908.rgba16.inc"
};

u8 D_05014928[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014928.i4.inc"
};

Gfx D_05014DD8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05014928, G_IM_FMT_I, 80, 30, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050148C8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05014E98[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_05014EB8[] = {
#include "assets/game_etc/lws/D_05014EB8.vtx.inc.c"
};

u16 D_05014EF8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014F18.palette.inc"
};

u8 D_05014F18[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05014F18.ci4.inc"
};

Gfx D_050153C8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05014EF8),
    gsDPLoadTextureBlock_4b(D_05014F18, G_IM_FMT_CI, 80, 30, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05014EB8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_050154B8[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_050154D8[] = {
#include "assets/game_etc/lws/D_050154D8.vtx.inc.c"
};

u16 D_05015518[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05015538.palette.inc"
};

u8 D_05015538[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05015538.ci4.inc"
};

Gfx D_050159E8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05015518),
    gsDPLoadTextureBlock_4b(D_05015538, G_IM_FMT_CI, 80, 30, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_050154D8, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05015AD8[] = {
    { D_050147E8, -1, 12, 0, 0, 0 },
    { D_05014DD8, -1, 12, 12, 0, 0 },
    { D_050153C8, -1, 12, 24, 0, 0 },
    { D_050159E8, -1, 12, 36, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05015AD8) == D_050142A0_COUNT, "");

Lws_unk_14 D_05015B38[] = {
    { 0, 1, -8, 118, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 2, -8, 216, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 3, -8, 229, 0, -2880, 2880, -2649, 2648, 4409, 4096 },
    { 20, 4, -8, 214, 0, -2880, 2880, -3051, 4096, 4096, 4096 },
    { 28, 5, -8, 209, 0, -2880, 2880, -2688, 4160, 4081, 4096 },
    { 36, 6, -8, 161, 0, -2880, 2880, -2979, 4160, 4081, 4096 },
    { 48, 7, -8, 113, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 8, -8, 118, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 9, -8, 98, 0, -2880, 2880, -2940, 4096, 4096, 4096 },
    { 76, 10, -8, 138, 0, -2880, 2880, -2817, 4096, 4096, 4096 },
    { 84, 11, -8, 172, 0, -2880, 2880, -2948, 4096, 4096, 4096 },
    { 104, -1, -8, 120, 0, -2880, 2880, -2883, 4096, 4096, 4096 },
    { 0, 13, -8, -68, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 14, -8, -154, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 15, -8, -117, 0, -2880, 2880, -3132, 2648, 4409, 4096 },
    { 20, 16, -8, -132, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 28, 17, -8, -135, 0, -2880, 2880, -3054, 4160, 4081, 4096 },
    { 36, 18, -8, -83, 0, -2880, 2880, -2838, 4160, 4081, 4096 },
    { 48, 19, -8, -66, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 20, -8, -68, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 70, 21, -8, -112, 0, -2880, 2880, -2761, 4096, 4096, 4096 },
    { 82, 22, -8, -132, 0, -2880, 2880, -2952, 4096, 4096, 4096 },
    { 94, 23, -8, -88, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 104, -1, -8, -69, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
    { 0, 25, -8, 118, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 26, -8, 216, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 27, -8, 229, 0, -2880, 2880, -2649, 2648, 4409, 4096 },
    { 20, 28, -8, 214, 0, -2880, 2880, -3051, 4096, 4096, 4096 },
    { 28, 29, -8, 209, 0, -2880, 2880, -2688, 4160, 4081, 4096 },
    { 36, 30, -8, 161, 0, -2880, 2880, -2979, 4160, 4081, 4096 },
    { 48, 31, -8, 113, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 32, -8, 118, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 33, -8, 98, 0, -2880, 2880, -2940, 4096, 4096, 4096 },
    { 76, 34, -8, 138, 0, -2880, 2880, -2817, 4096, 4096, 4096 },
    { 84, 35, -8, 172, 0, -2880, 2880, -2948, 4096, 4096, 4096 },
    { 104, -1, -8, 120, 0, -2880, 2880, -2883, 4096, 4096, 4096 },
    { 0, 37, -8, -68, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 38, -8, -154, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 39, -8, -117, 0, -2880, 2880, -3132, 2648, 4409, 4096 },
    { 20, 40, -8, -132, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 28, 41, -8, -135, 0, -2880, 2880, -3054, 4160, 4081, 4096 },
    { 36, 42, -8, -83, 0, -2880, 2880, -2838, 4160, 4081, 4096 },
    { 48, 43, -8, -66, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 44, -8, -68, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 70, 45, -8, -112, 0, -2880, 2880, -2761, 4096, 4096, 4096 },
    { 82, 46, -8, -132, 0, -2880, 2880, -2952, 4096, 4096, 4096 },
    { 94, 47, -8, -88, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 104, -1, -8, -69, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_05016078[] = {
    0x00000000, 0x00000031, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000006,
    0x00000032, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000000C, 0x00000033,
    0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000001C, 0x00000034, 0x00000000,
    0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000024, 0x00000035, 0x00000000, 0x0960F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x00000030, 0x00000036, 0x00000000, 0x0960F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x0000003A, 0x00000037, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x00000068, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_05016158 = {
    0, 104, 60, D_05016158_COUNT, D_05016D80, D_05016DE0,
};

/* unreferenced data */
u32 D_05016170[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_05016190[] = {
#include "assets/game_etc/lws/D_05016190.vtx.inc.c"
};

/* unreferenced data */
u16 D_050161D0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050161D0.rgba16.inc"
};

u8 D_050161F0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050161F0.i4.inc"
};

Gfx D_050166A0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_050161F0, G_IM_FMT_I, 80, 30, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05016190, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05016760[] = {
    0xFFFFFFD8, 0x00000028, 0xFFFFFFF1, 0x0000000F, 0x00000000, 0x00000000, 0x00000028, 0x00000000,
};

Vtx D_05016780[] = {
#include "assets/game_etc/lws/D_05016780.vtx.inc.c"
};

u16 D_050167C0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050167E0.palette.inc"
};

u8 D_050167E0[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050167E0.ci4.inc"
};

Gfx D_05016C90[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_050167C0),
    gsDPLoadTextureBlock_4b(D_050167E0, G_IM_FMT_CI, 80, 30, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05016780, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_05016D80[] = {
    { D_050166A0, -1, 12, 0, 0, 0 },
    { D_05014DD8, -1, 12, 12, 0, 0 },
    { D_05016C90, -1, 12, 24, 0, 0 },
    { D_050159E8, -1, 12, 36, 0, 0 },
};
static_assert(ARRAY_COUNT(D_05016D80) == D_05016158_COUNT, "");

Lws_unk_14 D_05016DE0[] = {
    { 0, 1, -8, 118, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 2, -8, 216, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 3, -8, 229, 0, -2880, 2880, -2649, 2648, 4409, 4096 },
    { 20, 4, -8, 214, 0, -2880, 2880, -3051, 4096, 4096, 4096 },
    { 28, 5, -8, 209, 0, -2880, 2880, -2688, 4160, 4081, 4096 },
    { 36, 6, -8, 161, 0, -2880, 2880, -2979, 4160, 4081, 4096 },
    { 48, 7, -8, 113, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 8, -8, 118, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 9, -8, 98, 0, -2880, 2880, -2940, 4096, 4096, 4096 },
    { 76, 10, -8, 138, 0, -2880, 2880, -2817, 4096, 4096, 4096 },
    { 84, 11, -8, 172, 0, -2880, 2880, -2948, 4096, 4096, 4096 },
    { 104, -1, -8, 120, 0, -2880, 2880, -2883, 4096, 4096, 4096 },
    { 0, 13, -8, -68, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 14, -8, -154, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 15, -8, -117, 0, -2880, 2880, -3132, 2648, 4409, 4096 },
    { 20, 16, -8, -132, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 28, 17, -8, -135, 0, -2880, 2880, -3054, 4160, 4081, 4096 },
    { 36, 18, -8, -83, 0, -2880, 2880, -2838, 4160, 4081, 4096 },
    { 48, 19, -8, -66, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 20, -8, -68, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 70, 21, -8, -112, 0, -2880, 2880, -2761, 4096, 4096, 4096 },
    { 82, 22, -8, -132, 0, -2880, 2880, -2952, 4096, 4096, 4096 },
    { 94, 23, -8, -88, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 104, -1, -8, -69, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
    { 0, 25, -8, 118, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 26, -8, 216, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 27, -8, 229, 0, -2880, 2880, -2649, 2648, 4409, 4096 },
    { 20, 28, -8, 214, 0, -2880, 2880, -3051, 4096, 4096, 4096 },
    { 28, 29, -8, 209, 0, -2880, 2880, -2688, 4160, 4081, 4096 },
    { 36, 30, -8, 161, 0, -2880, 2880, -2979, 4160, 4081, 4096 },
    { 48, 31, -8, 113, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 32, -8, 118, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 68, 33, -8, 98, 0, -2880, 2880, -2940, 4096, 4096, 4096 },
    { 76, 34, -8, 138, 0, -2880, 2880, -2817, 4096, 4096, 4096 },
    { 84, 35, -8, 172, 0, -2880, 2880, -2948, 4096, 4096, 4096 },
    { 104, -1, -8, 120, 0, -2880, 2880, -2883, 4096, 4096, 4096 },
    { 0, 37, -8, -68, 0, -2880, 2880, -2880, 40, 4096, 4096 },
    { 6, 38, -8, -154, 0, -2880, 2880, -2880, 311, 4915, 4096 },
    { 12, 39, -8, -117, 0, -2880, 2880, -3132, 2648, 4409, 4096 },
    { 20, 40, -8, -132, 0, -2880, 2880, -2683, 4096, 4096, 4096 },
    { 28, 41, -8, -135, 0, -2880, 2880, -3054, 4160, 4081, 4096 },
    { 36, 42, -8, -83, 0, -2880, 2880, -2838, 4160, 4081, 4096 },
    { 48, 43, -8, -66, 0, -2880, 2880, -2880, 4420, 4025, 4096 },
    { 58, 44, -8, -68, 0, -2880, 2880, -2880, 4096, 4096, 4096 },
    { 70, 45, -8, -112, 0, -2880, 2880, -2761, 4096, 4096, 4096 },
    { 82, 46, -8, -132, 0, -2880, 2880, -2952, 4096, 4096, 4096 },
    { 94, 47, -8, -88, 0, -2880, 2880, -2812, 4096, 4096, 4096 },
    { 104, -1, -8, -69, 0, -2880, 2880, -2873, 4096, 4096, 4096 },
};

/* unreferenced data */
u32 D_05017320[] = {
    0x00000000, 0x00000031, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000006,
    0x00000032, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000000C, 0x00000033,
    0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x0000001C, 0x00000034, 0x00000000,
    0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000, 0x00000024, 0x00000035, 0x00000000, 0x0960F4C0,
    0x0B40F4C0, 0x10001000, 0x10000000, 0x00000030, 0x00000036, 0x00000000, 0x0960F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x0000003A, 0x00000037, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000,
    0x10000000, 0x00000068, 0xFFFFFFFF, 0x00000000, 0x0960F4C0, 0x0B40F4C0, 0x10001000, 0x10000000,
};

Lws D_05017400 = {
    1, 136, 60, D_05017400_COUNT, D_050187D8, D_05018958,
};

/* unreferenced data */
u32 D_05017418[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05017438[] = {
#include "assets/game_etc/lws/D_05017438.vtx.inc.c"
};

/* unreferenced data */
u16 D_05017478[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017478.rgba16.inc"
};

u8 D_05017498[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017498.i4.inc"
};

Gfx D_05017658[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05017498, G_IM_FMT_I, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05017438, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05017718[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05017738[] = {
#include "assets/game_etc/lws/D_05017738.vtx.inc.c"
};

u16 D_05017778[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017798.palette.inc"
};

u8 D_05017798[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017798.ci4.inc"
};

Gfx D_05017958[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05017778),
    gsDPLoadTextureBlock_4b(D_05017798, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05017738, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05017A48[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05017A68[] = {
#include "assets/game_etc/lws/D_05017A68.vtx.inc.c"
};

/* unreferenced data */
u16 D_05017AA8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017AA8.rgba16.inc"
};

u8 D_05017AC8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017AC8.i4.inc"
};

Gfx D_05017C88[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_05017AC8, G_IM_FMT_I, 32, 28, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05017A68, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05017D48[] = {
    0xFFFFFFF4, 0x00000014, 0xFFFFFFF3, 0x0000000D, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05017D68[] = {
#include "assets/game_etc/lws/D_05017D68.vtx.inc.c"
};

u16 D_05017DA8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017DC8.palette.inc"
};

u8 D_05017DC8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05017DC8.ci4.inc"
};

Gfx D_05017F88[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05017DA8),
    gsDPLoadTextureBlock_4b(D_05017DC8, G_IM_FMT_CI, 32, 28, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05017D68, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05018078[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05018098[] = {
#include "assets/game_etc/lws/D_05018098.vtx.inc.c"
};

/* unreferenced data */
u16 D_050180D8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050180D8.rgba16.inc"
};

u8 D_050180F8[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_050180F8.i4.inc"
};

Gfx D_05018350[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_SHADEDECALA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTextureBlock_4b(D_050180F8, G_IM_FMT_I, 48, 25, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05018098, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

/* unreferenced data */
u32 D_05018410[] = {
    0xFFFFFFEC, 0x00000014, 0xFFFFFFF4, 0x0000000B, 0x00000000, 0x00000000, 0x00000014, 0x00000000,
};

Vtx D_05018430[] = {
#include "assets/game_etc/lws/D_05018430.vtx.inc.c"
};

u16 D_05018470[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05018490.palette.inc"
};

u8 D_05018490[] ALIGNED(8) = {
#include "assets/game_etc/lws/D_05018490.ci4.inc"
};

Gfx D_050186E8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_FRONT | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH | G_CLIPPING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPLoadTLUT_pal16(0, D_05018470),
    gsDPLoadTextureBlock_4b(D_05018490, G_IM_FMT_CI, 48, 25, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsSPVertex(D_05018430, 4, 0),
    gsSP2Triangles(2, 0, 1, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Lws_unk_10 D_050187D8[] = {
    { D_0500C7F0, -1, 5, 0, 0, 0 },  { D_0500CF30, -1, 5, 5, 0, 0 },  { D_0500D2F8, -1, 5, 10, 0, 0 },
    { D_0500DA00, -1, 5, 15, 0, 0 }, { D_0500DDA0, -1, 5, 20, 0, 0 }, { D_0500E520, -1, 5, 25, 0, 0 },
    { D_0500E850, -1, 5, 30, 0, 0 }, { D_0500EE10, -1, 5, 35, 0, 0 }, { D_0500F1A0, -1, 5, 40, 0, 0 },
    { D_0500F900, -1, 5, 45, 0, 0 }, { D_05017658, -1, 5, 50, 0, 0 }, { D_05017958, -1, 5, 55, 0, 0 },
    { D_05017C88, -1, 5, 60, 0, 0 }, { D_05017F88, -1, 5, 65, 0, 0 }, { D_05018350, -1, 5, 70, 0, 0 },
    { D_050186E8, -1, 5, 75, 0, 0 },
};
static_assert(ARRAY_COUNT(D_050187D8) == D_05017400_COUNT, "");

Lws_unk_14 D_05018958[] = {
    { 0, 1, 302, -106, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 2, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 76, 3, 302, -106, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 4, 302, -106, 0, -2880, 2880, 8751, 3276, 3276, 4096 },
    { 136, -1, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 6, 302, -106, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 7, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 76, 8, 302, -106, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 9, 302, -106, 0, -2880, 2880, 8751, 3276, 3276, 4096 },
    { 136, -1, 302, -106, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 11, 162, -134, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 12, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 68, 13, 162, -134, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 14, 162, -134, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 0, 16, 162, -134, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 17, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 68, 18, 162, -134, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 19, 162, -134, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, 162, -134, 0, -2880, 2880, 8640, 3829, 3829, 4096 },
    { 0, 21, 16, -114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 22, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 60, 23, 16, -114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 24, 16, -114, 0, -2880, 2880, 8791, 3276, 3276, 4096 },
    { 136, -1, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 26, 16, -114, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 27, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 60, 28, 16, -114, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 108, 29, 16, -114, 0, -2880, 2880, 8791, 3276, 3276, 4096 },
    { 136, -1, 16, -114, 0, -2880, 2880, 8640, 3788, 3788, 4096 },
    { 0, 31, -130, -146, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 32, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 52, 33, -130, -146, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 100, 34, -130, -146, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 0, 36, -130, -146, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 37, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 52, 38, -130, -146, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 100, 39, -130, -146, 0, -2880, 2880, 8523, 3276, 3276, 4096 },
    { 136, -1, -130, -146, 0, -2880, 2880, 8640, 3870, 3870, 4096 },
    { 0, 41, -276, -130, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 42, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 44, 43, -276, -130, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 92, 44, -276, -130, 0, -2880, 2880, 8737, 3276, 3276, 4096 },
    { 136, -1, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 0, 46, -276, -130, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 47, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 44, 48, -276, -130, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 92, 49, -276, -130, 0, -2880, 2880, 8737, 3276, 3276, 4096 },
    { 136, -1, -276, -130, 0, -2880, 2880, 8640, 3993, 3993, 4096 },
    { 0, 51, 176, 74, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 52, 176, 74, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 64, 53, 176, 74, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 54, 176, 54, 0, -2880, 2880, 8771, 3276, 3276, 4096 },
    { 136, -1, 176, 74, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 0, 56, 176, 74, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 57, 176, 74, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 64, 58, 176, 74, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 112, 59, 176, 54, 0, -2880, 2880, 8771, 3276, 3276, 4096 },
    { 136, -1, 176, 74, 0, -2880, 2880, 8640, 3686, 3686, 4096 },
    { 0, 61, 20, 88, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 62, 20, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 56, 63, 20, 88, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 104, 64, 20, 68, 0, -2880, 2880, 8457, 3276, 3276, 4096 },
    { 136, -1, 20, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 0, 66, 20, 88, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 67, 20, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 56, 68, 20, 88, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 104, 69, 20, 68, 0, -2880, 2880, 8457, 3276, 3276, 4096 },
    { 136, -1, 20, 88, 0, -2880, 2880, 8640, 3891, 3891, 4096 },
    { 0, 71, -126, 86, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 72, -126, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 48, 73, -126, 86, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 96, 74, -126, 62, 0, -2880, 2880, 8745, 3276, 3276, 4096 },
    { 136, -1, -126, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 0, 76, -126, 86, 0, -2880, 2880, -2880, 8192, 8192, 4096 },
    { 40, 77, -126, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
    { 48, 78, -126, 86, 0, -2880, 2880, 8640, 4096, 4096, 4096 },
    { 96, 79, -126, 62, 0, -2880, 2880, 8745, 3276, 3276, 4096 },
    { 136, -1, -126, 86, 0, -2880, 2880, 8678, 3973, 3973, 4096 },
};

/* unreferenced data */
u32 D_05019218[] = {
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x0AC8F4C0, 0x0B40F4C0,
    0x10001000, 0x10000000, 0x00000000, 0x00000000, 0x00000000,
};
