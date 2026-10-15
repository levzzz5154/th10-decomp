#ifndef TH10_PLATFORM_DERIVED_TIMER_STATE_0043A750_HPP
#define TH10_PLATFORM_DERIVED_TIMER_STATE_0043A750_HPP
#include <stddef.h>

#include "th10/platform/win32_timer.hpp"

struct PauseVtable;

// Two contiguous sets of 32 values are initialized separately in retail.
struct TimerChannelValues {
    unsigned int values[32];
    __forceinline void Initialize() {
        for (unsigned int index = 0; index < 32; ++index) {
            values[index] = 0;
        }
    }
};

// This is the observed 0x2e4-byte prefix, not a full allocation-size claim.
// Later sequencer code also uses fields beyond this prefix.
// Only observed fields are named; reserved ranges are untouched by this body.
// The two dispatch tables are data objects already present in the image.
struct DerivedTimerState {
    PauseVtable* vtable;            // +0x000
    unsigned int timer_id;              // +0x004
    Win32TimerCaps caps;                // +0x008
    int sentinel;                      // +0x010
    TimerChannelValues first_values;    // +0x014
    unsigned int first_tail;            // +0x094
    TimerChannelValues second_values;   // +0x098
    unsigned int value118;              // +0x118
    unsigned char reserved11c[4];
    unsigned int value120;              // +0x120
    unsigned int value124;              // +0x124
    unsigned char reserved128[0x10];
    unsigned int value138;              // +0x138
    unsigned int value13c;              // +0x13c
    unsigned int value140;              // +0x140
    unsigned char reserved144[0x180];
    unsigned char flag2c4;              // +0x2c4
    unsigned char reserved2c5[3];
    unsigned int tail_values[7];        // +0x2c8
    __declspec(noinline) DerivedTimerState();
};
typedef char TimerChannelValues_size[sizeof(TimerChannelValues) == 0x80 ? 1 : -1];
typedef char DerivedTimerState_size[sizeof(DerivedTimerState) == 0x2e4 ? 1 : -1];
typedef char DerivedTimerState_caps_offset[offsetof(DerivedTimerState, caps) == 8 ? 1 : -1];
typedef char DerivedTimerState_sentinel_offset[offsetof(DerivedTimerState, sentinel) == 0x10 ? 1 : -1];
typedef char DerivedTimerState_first_offset[offsetof(DerivedTimerState, first_values) == 0x14 ? 1 : -1];
typedef char DerivedTimerState_first_tail_offset[offsetof(DerivedTimerState, first_tail) == 0x94 ? 1 : -1];
typedef char DerivedTimerState_second_offset[offsetof(DerivedTimerState, second_values) == 0x98 ? 1 : -1];
typedef char DerivedTimerState_value118_offset[offsetof(DerivedTimerState, value118) == 0x118 ? 1 : -1];
typedef char DerivedTimerState_value120_offset[offsetof(DerivedTimerState, value120) == 0x120 ? 1 : -1];
typedef char DerivedTimerState_value124_offset[offsetof(DerivedTimerState, value124) == 0x124 ? 1 : -1];
typedef char DerivedTimerState_value138_offset[offsetof(DerivedTimerState, value138) == 0x138 ? 1 : -1];
typedef char DerivedTimerState_value13c_offset[offsetof(DerivedTimerState, value13c) == 0x13c ? 1 : -1];
typedef char DerivedTimerState_value140_offset[offsetof(DerivedTimerState, value140) == 0x140 ? 1 : -1];
typedef char DerivedTimerState_flag_offset[offsetof(DerivedTimerState, flag2c4) == 0x2c4 ? 1 : -1];
typedef char DerivedTimerState_tail_offset[offsetof(DerivedTimerState, tail_values) == 0x2c8 ? 1 : -1];

#endif
