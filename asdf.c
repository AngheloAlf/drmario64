extern OSContPad B_800EB4D8;
extern u16 B_800EBCF8;
extern u16 B_800EF554;
extern u16 B_800F1E20;
extern void *B_800F3E60;
extern u16 B_800F3E64;
extern s16 B_800F48B8;
extern u16 B_800F48C4;
extern OSContStatus B_800F5358;
extern u16 B_800F6CD8;
extern ? B_800FAD31;
extern ? B_80113670;

s32 func_8002A5B0(s32 arg0) {
    OSMesgQueue sp10;
    void *sp28;
    u8 sp2C;
    ? *var_a1_2;
    s16 *var_a3_2;
    s16 *var_v0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v1_2;
    u16 *var_a1;
    u16 *var_a2;
    u16 *var_a2_2;
    u16 *var_a3;
    u16 *var_v1;

    osCreateMesgQueue(&sp10, &sp28, 1);
    osSetEventMesg(5U, &sp10, NULL);
    osContSetCh(4U);
    osContInit(&sp10, &sp2C, &B_800F5358);
    osCreateMesgQueue(&B_800F3E38, &B_800F3E60, 1);
    osSetEventMesg(5U, &B_800F3E38, NULL);
    var_a0 = 0;
    var_a3 = &B_800EBCF8;
    var_a2 = &B_800F3E64;
    var_a1 = B_800FAF88;
    var_v1 = &B_800F48C4;
    do {
        *var_v1 = 0;
        *var_a1 = 0;
        *var_a2 = 0;
        *var_a3 = 0;
        var_a3 += 2;
        var_a2 += 2;
        var_a1 += 2;
        var_a0 += 1;
        var_v1 += 2;
    } while (var_a0 < 5);
    var_a0_2 = 0;
    var_a3_2 = &B_800F48B8;
    var_a2_2 = &B_800F6CD8;
    var_a1_2 = &B_80113670;
    do {
        var_v1_2 = 0xF;
        var_v0 = var_a1_2 + 0x1E;
loop_4:
        *var_v0 = 0;
        var_v1_2 -= 1;
        var_v0 -= 2;
        if (var_v1_2 >= 0) {
            goto loop_4;
        }
        *var_a2_2 = 0;
        *var_a3_2 = 0;
        var_a3_2 += 2;
        var_a2_2 += 2;
        *(&B_800FAD31 + var_a0_2) = 0;
        var_a0_2 += 1;
        var_a1_2 += 0x20;
    } while (var_a0_2 < 4);
    B_800EF554 = 0x14;
    B_800F1E20 = 4;
    return 4;
}

void func_8002A700(void) {
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a3;
    s32 var_t3;
    u16 *temp_v0;
    u16 *temp_v0_2;
    u16 *temp_v0_4;
    u16 temp_a1;
    u16 temp_t5;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u32 temp_v1_3;
    u32 var_a2;
    void *temp_t2;

    osContStartReadData(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, 1);
    osContGetReadData(&B_800EB4D8);
    var_t3 = 0;
    temp_t5 = B_800EF554;
    var_a3 = 0;
    do {
        var_a2 = 0x8000;
        temp_v1 = var_t3 & 0xFFFF;
        temp_v0 = &(&B_800EBCF8)[temp_v1];
        temp_a1 = (&B_800EB4D8)[temp_v1].button;
        temp_t2 = (temp_v1 << 5) + &B_80113670;
        *temp_v0 = temp_a1;
        temp_v0_2 = &(&B_800F48C4)[temp_v1];
        B_800FAF88[temp_v1] = ~(&B_800F3E64)[temp_v1] & temp_a1;
        *temp_v0_2 = 0;
loop_2:
        if ((&B_800F6CD8)[temp_v1] & var_a2) {
            temp_v0_3 = var_a3 & 0xFFFF;
            if (var_a2 & *temp_v0) {
                temp_v0_4 = (temp_v0_3 * 2) + temp_t2;
                temp_v1_2 = *temp_v0_4 + 1;
                *temp_v0_4 = temp_v1_2;
                temp_v1_3 = temp_v1_2 & 0xFFFF;
                if ((temp_v1_3 == 1) || ((temp_v1_3 >= temp_t5) && (((s32) (temp_v1_3 - temp_t5) % (s32) (B_800F1E20 & 0xFFFF)) == 0))) {
                    *temp_v0_2 |= var_a2;
                }
            } else {
                *((temp_v0_3 * 2) + temp_t2) = 0;
            }
        }
        var_a3 += 1;
        var_a2 = var_a2 >> 1;
        if ((u32) (var_a3 & 0xFFFF) < 0x10U) {
            goto loop_2;
        }
        temp_v1_4 = var_t3 & 0xFFFF;
        temp_v1_5 = temp_v1_4 * 2;
        temp_v0_5 = (&B_800EBCF8)[temp_v1_4];
        var_t3 += 1;
        *(temp_v1_5 + &B_800F3E64) = temp_v0_5;
        var_a3 = 0;
    } while ((u32) (var_t3 & 0xFFFF) < 4U);
}

void func_8002A8F8(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v1;

    var_a0 = arg0 & 0xFFFF;
    var_v1 = 0xF;
loop_1:
    if (!(var_a0 & 1)) {
        var_v1 -= 1;
        var_a0 = var_a0 >> 1;
        if (var_v1 >= 0) {
            goto loop_1;
        }
    }
    *((var_v1 * 2) + (((arg1 & 0xFF) << 5) + &B_80113670)) = (B_800EF554 + B_800F1E20) - 1;
}

s32 func_8002A954(void) {
    OSContStatus sp10;
    OSContStatus *temp_v1;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 var_a2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_v0;
    s8 var_a1;
    u8 var_a1_2;
    u8 var_v0_3;

    var_s1 = 0;
    osContStartQuery(&B_800F3E38);
    osRecvMesg(&B_800F3E38, NULL, 1);
    osContGetQuery(&sp10);
    var_a1 = 0;
    var_v0 = 0 << 0x18;
    do {
        B_800EBD16[var_v0 >> 0x18] = 4;
        temp_v0 = var_a1 + 1;
        var_a1 = temp_v0;
        var_v0 = var_a1 << 0x18;
    } while (temp_v0 < 4);
    var_a2 = 0;
    var_a1_2 = 0;
    var_v0_2 = 0U << 0x18;
    do {
        temp_a0 = var_v0_2 >> 0x18;
        temp_v1 = &(&sp10)[temp_a0];
        B_800F3E78[temp_a0] = 0;
        var_v0_3 = var_a1_2 + 1;
        if (temp_v1->errno != 8) {
            var_v0_3 = var_a1_2 + 1;
            if ((temp_v1->type & 0x1F07) == 5) {
                var_s1 += 1;
                temp_v0_2 = var_a2 << 0x18;
                var_a2 += 1;
                B_800F3E78[temp_a0] = 1;
                B_800EBD16[temp_v0_2 >> 0x18] = var_a1_2;
                var_v0_3 = var_a1_2 + 1;
            }
        }
        var_a1_2 = var_v0_3;
        var_v0_2 = var_a1_2 << 0x18;
    } while ((s8) var_v0_3 < 4);
    return var_s1;
}
