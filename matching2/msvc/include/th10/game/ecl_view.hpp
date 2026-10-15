#pragma once
#include <stddef.h>
#include "th10/game/anm_vm.hpp"
#include "th10/game/counter_block.hpp"

struct EclViewState {
    unsigned int flags;
    unsigned char unknown_004[0xC];
    GameTimer timer;
    unsigned char unknown_024[0x18];
    CounterBlock first_counter;
    CounterBlock second_counter;
    CounterBlock third_counter;
    unsigned char unknown_2c4[4];
    AnmVm vm;
    unsigned char unknown_674[0x14];

    EclViewState();
};
extern "C" EclViewState* g_ecl_view;

typedef char CounterState_size_check[sizeof(EclViewState) == 0x688 ? 1 : -1];
typedef char CounterState_timer_check[offsetof(EclViewState, timer) == 0x10 ? 1 : -1];
typedef char CounterState_vm_check[offsetof(EclViewState, vm) == 0x2c8 ? 1 : -1];
