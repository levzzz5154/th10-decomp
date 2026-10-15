#pragma once
#include "th10/game/anm_vm.hpp"

struct Effect_0042b430 {
    unsigned char unknown_00[0x2C];
    unsigned int active : 1;
    unsigned int other_flags : 31;
    unsigned char unknown_30[0x10];

    __forceinline Effect_0042b430() { active = 0; }
};

struct SmollScore {
    unsigned int flags;
    unsigned char unknown_004[0x14];
    AnmVm vm;
    Effect_0042b430 effects[0x2D3];

    SmollScore();
};
extern "C" SmollScore* g_smoll_score;

typedef char SmollScore_size_check[sizeof(SmollScore)==0xb884?1:-1];
