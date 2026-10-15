#pragma once

#include "th10/game/item_0041b8e0.hpp"

struct ItemManager_0041b8e0 {
    enum { ITEM_COUNT = 0x896 };

    unsigned char reserved_00[0x14];
    Item_0041b8e0 items[ITEM_COUNT];

    __declspec(noinline) int Draw();
};

struct ItemPauseState {
    unsigned char reserved_00[0x58];
    unsigned char flags;                               // +0x58
};

struct AnimationManager_0041b8e0;

extern "C" ItemPauseState* g_game;
extern "C" AnimationManager_0041b8e0* g_sprt_ctrl;

// 0x004451C0: entity in EAX, manager in ECX.
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        AnimationObject_0043e5a0* entity, AnimationManager_0041b8e0* manager);

int __fastcall ItemManager_OnDraw_0041ba30(ItemManager_0041b8e0* manager);
