#pragma once
#include <stddef.h>

#pragma pack(push, 4)
struct FPS {
    unsigned char pad_0000[0x14];
    double time_last;          // +0x14  clamped timer sample
    int frame_events;          // +0x1C  consecutive high-rate frames
    unsigned int frame_count;  // +0x20  game frames inside the interval
    double measured;           // +0x24
    double budget;             // +0x2C
    float fps;                 // +0x34
    __declspec(noinline) int Update();
    __declspec(noinline) int Draw();
};
#pragma pack(pop)

typedef char FPS_count_offset_is_20[offsetof(FPS, frame_count) == 0x20 ? 1 : -1];
typedef char FPS_rate_offset_is_34[offsetof(FPS, fps) == 0x34 ? 1 : -1];
