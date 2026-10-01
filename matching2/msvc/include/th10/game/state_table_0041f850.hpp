#pragma once
#include <stddef.h>
#include "th10/game/anm_vm.hpp"

struct StateTable_0041f850 {
    unsigned int flags;
    unsigned char unknown_004[0xC];
    GameTimer timer;
    unsigned char unknown_024[0xC];
    AnmVm vm;
    unsigned char unknown_3dc[0x14];

    StateTable_0041f850();
};
extern "C" StateTable_0041f850* data_00477820;

typedef char StateTable_size_check[sizeof(StateTable_0041f850)==0x3f0?1:-1];
