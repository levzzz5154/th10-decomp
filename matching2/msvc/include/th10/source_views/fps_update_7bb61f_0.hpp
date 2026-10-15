#pragma once
// Complete frame-rate update0x004134B0, with its real FPS draw and scheduler callback.
// Native LTCG preserves the original ESI receiver in Update, EDI receiver in Draw,
// and ECX scheduler boundary. The original variadic formatter and queue writer
// are part of this same genuine caller/callee closure.

extern "C" double __cdecl FrameTimer_GetDelta(void);   // 0x00439540

// Frame timer state the counter resets (see src/core/main/frame_clock.cpp for the
// routines that own it).
extern "C" long long data_00492508;   // 0x00492508  QPC ticks per second
extern "C" double data_00492528;      // 0x00492528
extern "C" double data_00492530;      // 0x00492530
extern "C" double data_00492538;      // 0x00492538
extern "C" double data_00492540;      // 0x00492540

// The slot owner whose flags gate the accounting below; the same object
// src/game/bullet/fun_004065c0_004065c0.cpp names GameBulletView.
struct GameFpsView {
    unsigned char pad_00[0x58];
    unsigned int field_58;  // +0x58
};
extern "C" GameFpsView* g_game;  // 0x00477810

// 4-byte packing is what puts the two doubles at +0x24/+0x2C: their retail
// offsets are 4 mod 8.
#include "th10/game/fps_runtime.hpp"

#pragma code_seg(".text$05update")
