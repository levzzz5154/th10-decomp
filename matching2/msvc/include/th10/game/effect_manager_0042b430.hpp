#pragma once
#include "th10/game/anm_vm.hpp"

struct Effect_0042b430 {
    unsigned char unknown_00[0x2C];
    unsigned int active : 1;
    unsigned int other_flags : 31;
    unsigned char unknown_30[0x10];

    __forceinline Effect_0042b430() { active = 0; }
};

struct EffectManager_0042b430 {
    unsigned int flags;
    unsigned char unknown_004[0x14];
    AnmVm vm;
    Effect_0042b430 effects[0x2D3];

    EffectManager_0042b430();
};
extern "C" EffectManager_0042b430* data_00477840;

typedef char EffectManager_size_check[sizeof(EffectManager_0042b430)==0xb884?1:-1];
