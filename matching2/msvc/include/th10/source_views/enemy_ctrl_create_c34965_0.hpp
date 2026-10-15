#pragma once
// 0x0040D6B0..0x0040D70E: create and publish an enemy manager.
// Native LTCG keeps the manager in EBX for initialization, and teardown receives
// it in EAX. The initializer still runs when allocation returned null.
#include <string.h>
#include "th10/game/enemy_ctrl.hpp"

void *__cdecl operator new(unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" void *g_enemy_ctrl;

#pragma code_seg(".text$04b")
