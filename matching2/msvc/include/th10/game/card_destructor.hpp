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
void* __fastcall AnimationManager_SetFlag2(AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl* scheduler, SchedulerTask* task);

extern "C" AnimationLookupContext* g_sprt_ctrl;
extern "C" void* g_func_ctrl;

// An animation the manager owns, named by its id.
struct CardAnimation {
    AnimationScriptId id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(AnimationLookupContext* animations) {
        AnimationManager_SetFlag2(animations, id);
        id.value = 0;
    }
};

// One 0x3AC-byte sprite of the spell-card manager's pools, destroyed by
// 0x00401FF0.
struct CardSprite2 {
    unsigned char storage[0x3AC];

    __declspec(noinline) ~CardSprite2();
};

// The 0x37B0-byte spell-card manager, as its destructor sees it.
struct Card2 {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    CardSprite2 sprites_0010[2];
    CardAnimation effects[3]; // +0x768
    unsigned char reserved_0774[0x778 - 0x774];
    CardSprite2 sprites_0778[8];
    CardSprite2 sprites_24d8[5];
    unsigned char reserved_3734[0x37AC - 0x3734];
    SchedulerTask* trailing_task;               // +0x37AC

    __declspec(noinline) ~Card2();    // 0x00408AF0
};
typedef char CardSize2[sizeof(Card2) == 0x37B0 ? 1 : -1];
typedef char CardEffects[offsetof(Card2, effects) == 0x768 ? 1 : -1];

extern "C" Card2* g_card;
