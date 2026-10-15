#pragma once
#include <stddef.h>
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"

void __cdecl operator delete(void* block);

struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};
// 0x004492A0: let the animation with this id, and its children, be removed.
void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl* scheduler, SchedulerTask* task);

extern "C" AnimationLookupContext* g_sprt_ctrl;
extern "C" void* g_func_ctrl;

// An animation the manager owns, named by its id.
struct CardAnimation_00408af0 {
    AnimationScriptId id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(AnimationLookupContext* animations) {
        AnimationManager_SetFlag_004492a0(animations, id);
        id.value = 0;
    }
};

// One 0x3AC-byte sprite of the spell-card manager's pools, destroyed by
// 0x00401FF0.
struct CardSprite_00408af0 {
    unsigned char storage[0x3AC];

    __declspec(noinline) ~CardSprite_00408af0();
};

// The 0x37B0-byte spell-card manager, as its destructor sees it.
struct Card_00408af0 {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    CardSprite_00408af0 sprites_0010[2];
    CardAnimation_00408af0 effects[3]; // +0x768
    unsigned char reserved_0774[0x778 - 0x774];
    CardSprite_00408af0 sprites_0778[8];
    CardSprite_00408af0 sprites_24d8[5];
    unsigned char reserved_3734[0x37AC - 0x3734];
    SchedulerTask* trailing_task;               // +0x37AC

    __declspec(noinline) ~Card_00408af0();    // 0x00408AF0
};
typedef char CardSize_00408af0[sizeof(Card_00408af0) == 0x37B0 ? 1 : -1];
typedef char CardEffects[offsetof(Card_00408af0, effects) == 0x768 ? 1 : -1];

extern "C" Card_00408af0* g_card;
