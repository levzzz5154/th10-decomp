#pragma once
#include <stddef.h>
#include "th10/game/anm_vm.hpp"
#include "th10/game/counter_block.hpp"

extern "C" const void* const data_0046ecf0[];

// The vtable pointer, set before any member is constructed.
struct TitleBase {
    const void* const* vtable;

    __forceinline TitleBase() { vtable = data_0046ecf0; }
};

// A state word whose low bit is cleared on construction.
struct TitleBusyFlag {
    unsigned int busy : 1;
    unsigned int other_flags : 31;

    __forceinline TitleBusyFlag() { busy = 0; }
};

struct Title : TitleBase {
    unsigned int flags;
    unsigned char unknown_008[0x1C];
    CounterBlock first_counter;
    CounterBlock second_counter;
    CounterBlock third_counter;
    unsigned char unknown_2ac[0x14];
    TitleBusyFlag state;
    unsigned char unknown_2c4[0x5630];
    CounterBlock total_counter;
    unsigned char unknown_59cc[0xE4];
    GameTimer timer;
    unsigned char unknown_5ac4[8];

    Title();
};
extern "C" Title* g_title;

typedef char TitleSizeCheck[sizeof(Title)==0x5acc?1:-1];
typedef char TitleWorkerOffsetCheck[offsetof(Title,timer)==0x5ab0?1:-1];
