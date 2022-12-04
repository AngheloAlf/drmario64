extern s32 B_800EFCD0;
extern s8 D_80088410;
extern u32 D_800A7390;
extern s32 D_800A7394;
extern s32 D_800A7398;
extern ? D_800B3240;

u32 func_80075F98(struct_800EB670 *arg0) {
    OSMesgQueue sp10;
    void *sp28;
    struct_800FAF98_unk_64 sp48;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s1;
    s32 var_v0_2;
    u32 var_s0;
    u32 var_v0;

    var_s0 = 0;
    var_s1 = -(B_800EB4F0 == 6) & 0x63;
    osCreateMesgQueue(&sp10, &sp28, 8);
    func_8002A184(arg0, &sp48, &sp10);
    func_8002E830(osGetCount());
    func_80075F30();
    B_800F1CE0 = func_8002A954();
    osRecvMesg(&sp10, NULL, 1);
    D_80088124 = 2;
    do {
        func_8002A700();
        osRecvMesg(&sp10, NULL, 1);
        temp_v1 = B_800E59A4 + B_800E59A8;
        if (temp_v1 >= 0) {
            var_a0 = 0xFF;
            if (temp_v1 < 0x100) {
                var_a0 = temp_v1;
            }
        } else {
            var_a0 = 0;
        }
        B_800E59A4 = var_a0;
        if (B_800E59A0 != 0) {
            if ((B_800E59A0 >= 0) && (B_800E59A0 < 8)) {
                if (B_800E59A0 < 6) {

                } else {
                    B_800E59A8 = -B_800E59A8;
                    if (B_800E59A0 == 6) {
                        var_s0 = 1;
                    } else if (B_800E59A0 == 7) {
                        var_s0 = 2;
                    }
                }
            }
        } else {
            var_s1 += 1;
            if (D_800A739C == -1) {
                B_800E59A0 = 7;
            } else {
                if (var_s1 == 0x64) {
                    func_8002AFC4(0xB);
                }
                if (D_800A739C == 1) {
                    B_800E59A0 = 6;
                }
            }
        }
        func_8002AE58();
    } while (var_s0 == 0);
    func_8002B0E4();
loop_22:
    if (func_8002AFA4() == 0) {
block_24:
        osRecvMesg(&sp10, NULL, 1);
        func_8002AE58();
        temp_v1_2 = B_800E59A4 + B_800E59A8;
        if (temp_v1_2 >= 0) {
            var_a0_2 = 0xFF;
            if (temp_v1_2 < 0x100) {
                var_a0_2 = temp_v1_2;
            }
        } else {
            var_a0_2 = 0;
        }
        B_800E59A4 = var_a0_2;
        goto loop_22;
    }
    if (B_800E59A4 < 0xFF) {
        goto block_24;
    }
    D_80088124 = 0;
    if (D_80088128 != 0) {
        do {
            osRecvMesg(&sp10, NULL, 1);
            func_8002AE58();
        } while (D_80088128 != 0);
    }
    func_8002A1DC(arg0, &sp48);
    var_v0 = 2;
    if (var_s0 == 1) {
        return 6U;
    }
    if (var_s0 == 2) {
        var_v0 = D_800A7390;
        if (var_v0 == 0) {
            D_800AACEC = (s32) *(&D_800B3240 + (rand() % 18));
            var_v0_2 = 4;
            if ((D_800A7394 == 0) || (var_v0_2 = 5, (D_800A7394 == (s32) 1U)) || (var_v0_2 = 6, (D_800A7394 == var_s0))) {
                B_800EFCD0 = var_v0_2;
            }
            *B_801236F0 = 0;
            temp_v0 = D_800A7394 + 1;
            D_800A7394 = temp_v0;
            if (temp_v0 >= 3) {
                D_800A7394 = 0;
            }
            D_800A7390 ^= 1;
            return 1U;
        }
        if (var_v0 == 1) {
            D_80088410 = (s8) D_800A7398;
            temp_v0_2 = D_800A7398 + 1;
            D_800A7398 = temp_v0_2;
            if (temp_v0_2 >= 4) {
                D_800A7398 = 0;
            }
            D_800A7390 = 0;
            var_v0 = 4;
        }
        /* Duplicate return node #48. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
