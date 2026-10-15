#pragma once
#include <stddef.h>
#include "th10/game/anm_vm.hpp"

struct Loading {
    unsigned int flags;
    unsigned char unknown_004[0xC];
    GameTimer timer;
    unsigned char unknown_024[0xC];
    AnmVm vm;
    unsigned char unknown_3dc[0x14];

    Loading();
};
extern "C" Loading* g_loading;

typedef char Loading_size_check[sizeof(Loading)==0x3f0?1:-1];
