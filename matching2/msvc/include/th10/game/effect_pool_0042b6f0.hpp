#pragma once
struct EffectTimer_0042b6f0 {
    volatile int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __forceinline void Tick();
};

struct EffectDrop_0042b6f0 {
    float position;
    unsigned char pad_004[8];
    EffectTimer_0042b6f0 timer;
    unsigned char pad_020[8];
    unsigned char active;
    unsigned char pad_029[0x17];
};
typedef char EffectDrop_0042b6f0_size[sizeof(EffectDrop_0042b6f0) == 0x40 ? 1 : -1];

struct EffectPool_0042b6f0 {
    unsigned char pad_000[0x3D4];
    EffectDrop_0042b6f0 drops[0x2D3];
    __declspec(noinline) int UpdateDrops();
    __declspec(noinline) int Update();
};
