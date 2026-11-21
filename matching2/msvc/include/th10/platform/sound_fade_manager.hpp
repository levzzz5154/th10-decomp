#pragma once
#include <stddef.h>
#include "th10/platform/sound_fade.hpp"
struct SoundFadeManager {
    unsigned char reserved_0000[0x5208];
    PlatformInterfaceState2* stream;
    __declspec(noinline) void TickFades();
};
struct MainTaskState {
    unsigned char reserved_000[0x38C];
    int current_mode;
    int next_mode;
    int previous_mode;
    unsigned char reserved_398[4];
    int ui_mode;
    unsigned char reserved_3A0[0x2C];
    unsigned char flags_3CC;
    unsigned char reserved_3CD[0x63C-0x3CD];
    int state_63C;
    unsigned char reserved_640[8];
    int request_648;
    unsigned char critical_sections[6][0x18];
    unsigned char reserved_6DC[0x18];
    unsigned char lock_depth[6];
    unsigned char reserved_6FA[0x768-0x6FA];
    void* created_state;
    unsigned char reserved_76C[0x14];
    unsigned int overlay_color;
    __declspec(noinline) void LeaveSlot(int index);
    __declspec(noinline) int UpdateMode();
};
typedef char FadeStreamOffset[offsetof(SoundFadeManager, stream)==0x5208?1:-1];
typedef char MainFlagsOffset[offsetof(MainTaskState, flags_3CC)==0x3CC?1:-1];
typedef char MainStateOffset[offsetof(MainTaskState, state_63C)==0x63C?1:-1];
typedef char MainRequestOffset[offsetof(MainTaskState, request_648)==0x648?1:-1];
extern "C" SoundFadeManager g_sound_manager;
extern "C" int g_main_state;
extern "C" void* g_sprt_ctrl;
extern "C" unsigned short __fastcall Input_Poll(unsigned int binding_index);
extern "C" int __stdcall SprtCtrl_HasPendingLoads(void* pending);
typedef char ModeCurrentOffset[offsetof(MainTaskState,current_mode)==0x38C?1:-1];
typedef char ModeCriticalOffset[offsetof(MainTaskState,critical_sections)==0x64C?1:-1];
typedef char ModeDepthOffset[offsetof(MainTaskState,lock_depth)==0x6F4?1:-1];
typedef char ModeCreatedOffset[offsetof(MainTaskState,created_state)==0x768?1:-1];
typedef char ModeOverlayOffset[offsetof(MainTaskState,overlay_color)==0x780?1:-1];
