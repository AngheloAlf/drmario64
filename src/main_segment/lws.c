/**
 * Original filename: lws.c
 */

#include "lws.h"

#include "libc/stdint.h"
#include "macros_defines.h"

#include "calc.h"
#include "main_story.h"
#include "calcsub.h"

static Mtx AnimProc[0x40];

s32 lws_anim(Gfx **gfxP, Mtx *mtx, Lws *pSceneData, s32 frame, void *baseAddr) {
    Gfx *gfx = *gfxP;
    s32 i;
    s32 ret;

    if (frame >= pSceneData->last_frame) {
        ret = 1;
        frame = pSceneData->last_frame - 1;
    } else {
        ret = 0;
    }

    for (i = 0; i < pSceneData->obj_count; i++) {
        s32 key;
        Mtx m;
        Mtx sp68;
        Mtx spA8;
        f32 lx;
        f32 ly;
        f32 lz;
        f32 rx;
        f32 ry;
        f32 rz;
        f32 sx;
        f32 sy;
        f32 sz;
        f32 step;
        s16 irx;
        s16 iry;
        s16 irz;
        LwsKey *pKey1;
        LwsKey *pKey2;
        LwsKey *pKey;
        LwsObj *pObj;
        s32 ilx;
        s32 ily;
        s32 ilz;

#if 0
        long ms[4][4]; // r1+0x5C
        long mt[4][4]; // r1+0x1C
#endif

        pObj = RELOCATE_SEGMENTED(pSceneData->obj, baseAddr);
        pObj = &pObj[i];

        pKey = RELOCATE_SEGMENTED(pSceneData->key, baseAddr);
        pKey = &pKey[pObj->key_index];

        pKey1 = pKey2 = pKey;

        for (key = 1; key < pObj->key_count; key++) {
            pKey1 = &pKey[key - 1];
            pKey2 = &pKey[key];
            if (pKey2->key_no > frame) {
                break;
            }
        }

        if (frame >= pKey2->key_no) {
            step = 0.0f;
            pKey1 = pKey2;
        } else if (pKey1 == pKey2) {
            step = 0.0f;
        } else {
            step = frame - pKey1->key_no;
        }

        lx = pKey1->lx;
        ly = pKey1->ly;
        lz = pKey1->lz;
        rx = pKey1->rx;
        ry = pKey1->ry;
        rz = pKey1->rz;
        sx = pKey1->sx;
        sy = pKey1->sy;
        sz = pKey1->sz;
        if (step > 0.0f) {
            step /= (pKey2->key_no - pKey1->key_no);

            lx += (pKey2->lx - lx) * step;
            ly += (pKey2->ly - ly) * step;
            lz += (pKey2->lz - lz) * step;
            rx += (pKey2->rx - rx) * step;
            ry += (pKey2->ry - ry) * step;
            rz += (pKey2->rz - rz) * step;
            sx += (pKey2->sx - sx) * step;
            sy += (pKey2->sy - sy) * step;
            sz += (pKey2->sz - sz) * step;
        }

        makeScaleMatrix(&sp68, 0x8000);

        sp68.m[0][0] = sx * DOUBLE_LITERAL(8) + DOUBLE_LITERAL(0.5);
        sp68.m[1][1] = sy * DOUBLE_LITERAL(8) + DOUBLE_LITERAL(0.5);
        sp68.m[2][2] = sz * DOUBLE_LITERAL(8) + DOUBLE_LITERAL(0.5);

        ilx = lx * DOUBLE_LITERAL(0x1000);
        ily = ly * DOUBLE_LITERAL(0x1000);
        ilz = lz * DOUBLE_LITERAL(0x1000);

        irx = angleF2S(rx / DOUBLE_LITERAL(16));
        iry = angleF2S(ry / DOUBLE_LITERAL(16));
        irz = angleF2S(rz / DOUBLE_LITERAL(16));

        makeMatrix(&spA8, irx, iry, irz, ilx, ily, ilz);
        matrixMulL(&sp68, &spA8, &m);

        if (pObj->parent == -1) {
            matrixMulL(&m, mtx, &AnimProc[i]);
        } else {
            matrixMulL(&m, &AnimProc[pObj->parent], &AnimProc[i]);
        }

        if (pObj->dl != NULL) {
            matrixConv(&AnimProc[i], pObjectMtx, 0);

            gSPMatrix(gfx++, pObjectMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            pObjectMtx++;

            gSPDisplayList(gfx++, pObj->dl);
        }
    }

    *gfxP = gfx;

    return ret;
}
