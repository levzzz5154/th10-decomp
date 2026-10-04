#pragma once
#include <stddef.h>

// The application state block at 0x00491C00. Only the members that recovered
// code reaches through this view are named; the rest is still addressed by
// individual data symbols.
//
// The block's address is handed to many routines, so the compiler has to
// assume that a store into it may alias anything read through a pointer. Code
// that writes one of these members next to pointer loads keeps its source
// order only when the member is declared here rather than as a lone global.
struct Supervisor {
    unsigned char reserved_000[0x70];
    void* window;                            // +0x070 (0x00491C70)
    unsigned char reserved_074[0x163 - 0x74];
    unsigned char music_mode;                // +0x163 (0x00491D63)
    unsigned char effect_mode;               // +0x164 (0x00491D64)
    unsigned char reserved_165[3];
    signed char music_volume;                // +0x168 (0x00491D68)
    signed char effect_volume;               // +0x169 (0x00491D69)
    unsigned char reserved_16a[0x178 - 0x16a];
    unsigned int flags;                      // +0x178 (0x00491D78)
    unsigned char reserved_17c[0x3b8 - 0x17c];
    int next_state;                          // +0x3b8 (0x00491FB8)
};

extern "C" Supervisor g_supervisor;

typedef char Supervisor_music_volume_offset[
    offsetof(Supervisor, music_volume) == 0x168 ? 1 : -1];
typedef char Supervisor_next_state_offset[
    offsetof(Supervisor, next_state) == 0x3b8 ? 1 : -1];
