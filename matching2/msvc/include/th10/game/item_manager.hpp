#pragma once

#include "th10/game/item.hpp"

struct ItemPoolManager {
    enum { ITEM_COUNT = 0x896 };

    unsigned char reserved_00[0x14];
    Item2 items[ITEM_COUNT];

    __declspec(noinline) int Draw();
};

struct ItemPauseState {
    unsigned char reserved_00[0x58];
    unsigned char flags;                               // +0x58
};

struct StageAnmManagerView;

extern "C" ItemPauseState* g_game;
extern "C" StageAnmManagerView* g_sprt_ctrl;

// 0x004451C0: entity in EAX, manager in ECX.
extern "C" __declspec(noinline) int __cdecl AnmVm_DrawDispatch(
        SpriteDimensionsView* entity, StageAnmManagerView* manager);

int __fastcall ItemManager_OnDraw2(ItemPoolManager* manager);
