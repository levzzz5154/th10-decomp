#pragma once
#include <stddef.h>
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

void __cdecl operator delete(void* block);

struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};
// 0x004492A0: let the animation with this id, and its children, be removed.
void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler* scheduler, SchedulerTask* task);

extern "C" AnimationLookupContext* data_00491c10;
extern "C" void* data_00491be4;

// An animation the manager owns, named by its id.
struct PlayerManagerAnimation_00408af0 {
    AnimationScriptId id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(AnimationLookupContext* animations) {
        AnimationManager_SetFlag_004492a0(animations, id);
        id.value = 0;
    }
};

// One 0x3AC-byte sprite of the player manager's pools, destroyed by
// 0x00401FF0.
struct PlayerManagerSprite_00408af0 {
    unsigned char storage[0x3AC];

    __declspec(noinline) ~PlayerManagerSprite_00408af0();
};

// The 0x37B0-byte player manager, as its destructor sees it.
struct PlayerManager_00408af0 {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    PlayerManagerSprite_00408af0 sprites_0010[2];
    PlayerManagerAnimation_00408af0 effects[3]; // +0x768
    unsigned char reserved_0774[0x778 - 0x774];
    PlayerManagerSprite_00408af0 sprites_0778[8];
    PlayerManagerSprite_00408af0 sprites_24d8[5];
    unsigned char reserved_3734[0x37AC - 0x3734];
    SchedulerTask* trailing_task;               // +0x37AC

    __declspec(noinline) ~PlayerManager_00408af0();    // 0x00408AF0
};
typedef char PlayerManagerSize_00408af0[sizeof(PlayerManager_00408af0) == 0x37B0 ? 1 : -1];
typedef char PlayerManagerEffects_00408af0[offsetof(PlayerManager_00408af0, effects) == 0x768 ? 1 : -1];

extern "C" PlayerManager_00408af0* data_004776f4;
