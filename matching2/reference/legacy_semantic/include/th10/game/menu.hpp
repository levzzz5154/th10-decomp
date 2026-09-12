#pragma once

// MSVC 7.1 is pre-C++11 — use manual typedefs instead of <cstdint>
typedef int int32_t;

// Bounded menu-selection cursor shared by the title, pause, and practice
// menu handlers. The retail leaf at 0x0044BEA0 receives the cursor through
// EAX; the clean form takes it as a normal argument.
struct MenuCursor {
    int32_t value;           // +0x00 current position
    int32_t reserved_04;     // +0x04
    int32_t itemCount;       // +0x08 number of selectable items
    int32_t reserved_0C[33]; // +0x0C .. +0x8F
    int32_t skipValues[16];  // +0x90 positions that must be bypassed
    int32_t wrap;            // +0xD0 nonzero wraps, zero clamps at the edges
    int32_t skipCount;       // +0xD4 populated skipValues entries
};

int MenuCursor_Advance(MenuCursor* cursor, int delta);
