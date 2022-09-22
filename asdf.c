s32 func_80001EB4();                                /* extern */
s32 func_80002148(u8 *arg0, s32 arg1);              /* static */
u8 func_800021CC(s32 arg0);                         /* static */
extern u8 B_8001B640;
extern s32 B_8001D7F8;
extern s32 B_8001D7FC;
extern u32 B_8001F98C;
extern s32 B_8001F990;
extern s32 B_8001FAFC;
extern s32 B_8001FB00;
extern u8 B_80021BE0;
extern u32 B_80029BE0;
extern ? D_8000E338;
extern u32 D_8000E738;

s32 func_80001F90(u32 segmentRom, s32 arg1, u32 segmentSize) {
    B_80029C00 = segmentRom;
    B_80029C04 = segmentSize;
    B_8001D7F8 = arg1;
    B_8001D7FC = 0;
    func_800021A0();
    func_800020A0();
    return B_8001D7FC;
}

u32 func_80001FD8(u32 *arg0, u8 *arg1, u32 arg2) {
    u32 temp_s1;
    u32 temp_v1;
    u32 var_s2;

    temp_v1 = arg0->unk_4;
    var_s2 = arg2;
    if (temp_v1 < var_s2) {
        var_s2 = temp_v1;
    }
    temp_s1 = (var_s2 + 7) & ~7;
    if (temp_s1 != 0) {
        func_80000620(arg0->unk_0, arg1, temp_s1);
    }
    arg0->unk_4 = (u32) (arg0->unk_4 - temp_s1);
    arg0->unk_0 += temp_s1;
    if ((s32) arg0->unk_4 < 0) {
        arg0->unk_4 = 0U;
    }
    return var_s2;
}

s32 func_80002064(s32 *arg0, u8 *arg1, s32 arg2) {
    u32 temp_a3;
    u8 *var_a1;
    u8 *var_v1;
    u8 temp_v0;

    var_a1 = arg1;
    var_v1 = arg0->unk_0;
    if (arg2 != 0) {
        temp_a3 = arg2 + var_a1;
        do {
            temp_v0 = *var_a1;
            var_a1 += 1;
            *var_v1 = temp_v0;
            var_v1 += 1;
        } while ((u32) var_a1 < temp_a3);
    }
    arg0->unk_0 = var_v1;
    arg0->unk_4 = (s32) (arg0->unk_4 + arg2);
    return arg2;
}

s32 func_800020A0(void) {
    u8 sp10;
    ? sp18;
    s32 temp_v0;
    s32 var_v0;
    u32 temp_v1;
    u8 *var_s0;

    func_80002148(NULL, 0);
    temp_v0 = func_80001EB4();
    var_v0 = -1;
    if (temp_v0 != 3) {
        var_s0 = &sp10;
        if (temp_v0 == 0) {
            do {
                temp_v1 = B_80029BE0;
                if (temp_v1 < (u32) B_8001F98C) {
                    B_80029BE0 = temp_v1 + 1;
                    *var_s0 = (&B_8001B640)[temp_v1];
                } else {
                    *var_s0 = func_800021CC(0);
                }
                var_s0 += 1;
                var_v0 = 0;
            } while ((s32) var_s0 < (s32) &sp18);
        }
    }
    return var_v0;
}

s32 func_80002148(u8 *arg0, s32 arg1) {
    s32 var_a1;
    u32 var_a2;
    u8 *var_a0;
    u8 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = -1U;
    if (var_a0 != NULL) {
        var_a2 = D_8000E738;
        if (var_a1 != 0) {
            do {
                temp_v0 = *var_a0;
                var_a0 += 1;
                var_a1 -= 1;
                var_a2 = *((((var_a2 ^ temp_v0) & 0xFF) * 4) + &D_8000E338) ^ (var_a2 >> 8);
            } while (var_a1 != 0);
        }
    }
    D_8000E738 = var_a2;
    return ~var_a2;
}

void func_800021A0(void) {
    B_8001F990 = 0;
    B_80029BE0 = 0;
    B_8001F98C = 0;
    B_8001FB00 = 0;
    B_8001FAFC = 0;
}

u8 func_800021CC(s32 arg0) {
    u32 temp_a2;
    u32 temp_v0;
    u32 temp_v0_2;
    u8 var_v0;

    B_8001F98C = 0;
loop_1:
    temp_a2 = B_8001F98C;
    temp_v0 = func_80001FD8(&B_80029C00, &(&B_8001B640)[temp_a2], 0x2000 - temp_a2);
    if ((u32) (temp_v0 + 1) >= 2U) {
        temp_v0_2 = B_8001F98C + temp_v0;
        B_8001F98C = temp_v0_2;
        if (temp_v0_2 < 0x2000U) {
            goto loop_1;
        }
    }
    if ((B_8001F98C != 0) || (var_v0 = -1U, (arg0 == 0))) {
        var_v0 = B_8001B640;
        B_80029BE0 = 1;
        B_8001FAFC += B_8001F98C;
    }
    return var_v0;
}

void func_800022A8(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;
    u8 *var_s1;

    var_s1 = arg1;
    var_s0 = arg2;
loop_1:
    temp_v0 = func_80002064(arg0, var_s1, var_s0);
    var_s0 -= temp_v0;
    if (temp_v0 != var_s0) {
        var_s1 = &var_s1[temp_v0];
        goto loop_1;
    }
}

void func_80002300(void) {
    s32 temp_a1;
    s32 temp_v1;

    temp_a1 = B_8001F990;
    if (temp_a1 != 0) {
        func_80002148(&B_80021BE0, temp_a1);
        func_800022A8(&B_8001D7F8, &B_80021BE0, B_8001F990);
        temp_v1 = B_8001F990;
        B_8001F990 = 0;
        B_8001FB00 += temp_v1;
    }
}
