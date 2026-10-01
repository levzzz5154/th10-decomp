#pragma once

struct EffectPoolState {
    int unknown_00[4];
    int vtable;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    unsigned char pad_024[0x18];
    int field_3C;
    unsigned char pad_040[4];
    int field_44;
    unsigned char pad_048[0x80];
    int field_0C8;
    unsigned char pad_0CC[0x40];
    int field_10C;
    int field_110;
    int field_114;
    unsigned char pad_118[4];
    int field_11C;
    unsigned char pad_120[0x80];
    int field_1A0;
    unsigned char pad_1A4[0x40];
    int field_1E4;
    int field_1E8;
    int field_1EC;
    unsigned char pad_1F0[4];
    int field_1F4;
    unsigned char pad_1F8[0x80];
    int field_278;
    unsigned char pad_27C[0x40];
    int field_2BC;
    int field_2C0;
    unsigned char tail_2C4[0x20];
};

typedef char EffectPoolState_size_must_be_2E4[
    sizeof(EffectPoolState) == 0x2E4 ? 1 : -1];
