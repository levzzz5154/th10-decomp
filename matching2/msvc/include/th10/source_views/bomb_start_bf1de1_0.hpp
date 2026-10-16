#pragma once
// 0x00405860: start a bomb: its animation, sound and the power display.
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" void* g_sprt_ctrl;
extern "C" const float flt_224;
extern "C" const float flt_16;
extern "C" const float flt_5_2083335;
extern "C" const float flt_02;
#include "../../../build_support/layout/ltcg/player_initialize_dependencies/entity_init.cpp"
#include "../../../src/core/sprtlib/animation_pool_allocate.cpp"
#include "../../../build_support/layout/ltcg/player_initialize_dependencies/load_script.cpp"
#include "../../../build_support/layout/ltcg/player_initialize_dependencies/configure.cpp"
#include "th10/game/power_display.hpp"
#include "../../../build_support/layout/ltcg/player_initialize_dependencies/clear_flags.cpp"
#include "../../../build_support/layout/ltcg/player_initialize_dependencies/sound_pan.cpp"
#include "th10/game/bomb.hpp"

struct PrimaryListNode {
    Entity* owner;
    PrimaryListNode* next;
    PrimaryListNode* previous;
};
struct AnimationPrimaryLists {
    unsigned char pad_000000[0x72DAD4];
    PrimaryListNode* head;
    PrimaryListNode* tail;
    unsigned char pad_72dadc[0x732454-0x72DADC];
    int serial;
    __declspec(noinline) int* RegisterPrimaryBack(int* out, Entity* entity);
};
#pragma code_seg(".text$a08register")
