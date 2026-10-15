#pragma once
#include "th10/core/func_ctrl.hpp"

extern "C" void __cdecl crt_free(void* memory);

// The ASCII manager (g_ascii_manager) as its constructor and destructor see it:
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
    char pad_22C[0x12C];
    void* resource;               // +0x358, heap block owned by the slot
    char pad_35C[0x1C];
    unsigned field_378;
    char pad_37C[8];
    unsigned short field_384;
    char pad_386[0x26];

    // 0x00401FF0 when not expanded in place.
    // The destructor cluster keeps this helper at its public thiscall ABI.
    // The export belongs only to the compiler context, not the final image.
#ifdef TH10_GAME_THREAD_SLOT_EXPORTED_ABI
    __declspec(dllexport)
#endif
    ~GameThreadSlot() {
        if (resource)
            crt_free(resource);
        resource = 0;
    }
};

struct GameThread {
    virtual int ObjectSize();     // 0x00401C90
    unsigned flags;
    char pad_008[4];
    SchedulerTask* update_task;   // +0x0C
    SchedulerTask* draw_task;     // +0x10
    GameThreadSlot slots_0014;
    GameThreadSlot slots_03c0;
    char pad_76C[0x8974 - 0x76C];
    int field_8974;
    float field_8978;
    float field_897C;
    char pad_8980[4];
    int field_8984;
    char pad_8988[4];
    int field_898C;
    char pad_8990[0x89A8 - 0x8990];
    SchedulerTask* late_draw_task; // +0x89A8

    __declspec(noinline) GameThread();
    __declspec(noinline) ~GameThread();
};

typedef char GameThread_size_must_be_0x89ac[sizeof(GameThread) == 0x89AC ? 1 : -1];
