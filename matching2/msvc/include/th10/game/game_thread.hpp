#pragma once

// 0x89AC-byte object built by 0x00401000 and created by 0x00401440; the
// global pointer at 0x004776E0 refers to it.

// +0x14 and +0x3C0: the two per-player state blocks.
struct GameThreadSlot {
    char pad_000[0x6C];
    unsigned field_06C;
    char pad_070[0x40];
    unsigned field_0B0;
    char pad_0B4[0x48];
    unsigned field_0FC;
    char pad_100[0x28];
    unsigned field_128;
    char pad_12C[0x48];
    unsigned field_174;
    char pad_178[0x38];
    unsigned field_1B0;
    char pad_1B4[0x48];
    unsigned field_1FC;
    char pad_200[0x28];
    unsigned field_228;
    char pad_22C[0x14C];
    unsigned field_378;
    char pad_37C[8];
    unsigned short field_384;
    char pad_386[0x26];
};

struct GameThread {
    const void* type;
    unsigned flags;
    char pad_008[0x0C];
    GameThreadSlot slots[2];
    char pad_76C[0x8974 - 0x76C];
    int field_8974;
    float field_8978;
    float field_897C;
    char pad_8980[4];
    int field_8984;
    char pad_8988[4];
    int field_898C;
    char pad_8990[0x89AC - 0x8990];

    __declspec(noinline) GameThread();
};

typedef char GameThread_size_must_be_0x89ac[sizeof(GameThread) == 0x89AC ? 1 : -1];
