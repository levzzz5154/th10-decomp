#pragma once
#include <stddef.h>

struct GameConfig {
    int version_marker;            // +0x00
    char version_prefix[0x12];     // +0x04 .. +0x15
    unsigned short window_width;   // +0x16
    unsigned short window_height;  // +0x18
    unsigned char field_1a;        // +0x1A
    unsigned char field_1b;        // +0x1B
    unsigned char field_1c;        // +0x1C
    unsigned char field_1d;        // +0x1D
    unsigned char field_1e;        // +0x1E
    unsigned char field_1f;        // +0x1F
    unsigned char field_20;        // +0x20
    unsigned char field_21;        // +0x21
    unsigned char field_22;        // +0x22
    char unknown_23[0x0D];         // +0x23 .. +0x2F
    int flags;                     // +0x30
};

struct LargeStateTimer {
    const void* const* vtable;
    unsigned int previous;
    unsigned int current;
    unsigned int elapsed;
    unsigned int control;
};
struct LargeInitializationState {
    unsigned char before_config[0x120];
    GameConfig config;
    unsigned char before_flags[0x3cc-0x154];
    unsigned int flags;
    unsigned char before_timer[0x62c-0x3d0];
    LargeStateTimer timer;
    unsigned char tail[0x784-0x640];
};
typedef char InitState_size_check[sizeof(LargeInitializationState)==0x784?1:-1];
typedef char InitState_config_check[offsetof(LargeInitializationState,config)==0x120?1:-1];
typedef char InitState_flags_check[offsetof(LargeInitializationState,flags)==0x3cc?1:-1];
typedef char InitState_timer_check[offsetof(LargeInitializationState,timer)==0x62c?1:-1];
__declspec(noinline) char __fastcall GameConfig_InitializeDefaults(int, GameConfig*);
extern "C" __declspec(noinline) LargeInitializationState* __stdcall Init_00421f00(LargeInitializationState*);
