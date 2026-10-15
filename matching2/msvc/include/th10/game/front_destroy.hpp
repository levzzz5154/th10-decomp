#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/render/animation_resource_removal.hpp"

void __cdecl operator delete(void* block);
extern "C" void __cdecl crt_free(void* block);

struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};
// 0x004492A0: let the animation with this id, and its children, be removed.
void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl* scheduler, SchedulerTask* task);

extern "C" AnimationLookupContext* g_sprt_ctrl;
extern "C" void* g_func_ctrl;

// The same manager object, seen by the resource-removal marker.
inline SprtCtrl* AnimationRemoval(AnimationLookupContext* animations) {
    return reinterpret_cast<SprtCtrl*>(animations);
}

// The animation manager's two lists of live animations, as the lookup at
// 0x004491C0 walks them.
struct AnimationListEntry {
    AnimationListEntry* object;
    AnimationListEntry* next;
    unsigned char reserved_08[0x0C];
    AnimationListEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};
struct AnimationLists_004145f0 {
    unsigned char reserved[0x72DAD4];
    AnimationListEntry* primary;
    int reserved_2;
    AnimationListEntry* secondary;
};

// The lookup and the flag setter again, written out so that they can be
// expanded in place: the destructor's loop holds a copy of both.
__forceinline AnimationListEntry* AnimationLists_Find(AnimationLookupContext* context, AnimationScriptId id) {
    AnimationLists_004145f0* lists = reinterpret_cast<AnimationLists_004145f0*>(context);
    AnimationListEntry* node;
    int* object;
    if (!id.value)
        return 0;
    for (node = lists->primary; node != 0; node = node->next) {
        object = (int*)node->object;
        if (*object == id.value)
            return node->object;
    }
    for (node = lists->secondary; node != 0; node = node->next) {
        object = (int*)node->object;
        if (*object == id.value)
            return node->object;
    }
    return 0;
}
__forceinline void AnimationLists_SetFlag(AnimationLookupContext* context, AnimationScriptId id) {
    AnimationListEntry* entry = AnimationLists_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
}

// An animation the manager owns, named by its id.
struct HudAnimation {
    AnimationScriptId id;

    // Let the animation manager dispose of the animation and forget it.
    void Release(AnimationLookupContext* animations) {
        AnimationManager_SetFlag_004492a0(animations, id);
        id.value = 0;
    }
    // The same, with the setter expanded in place.
    __forceinline void ReleaseInPlace(AnimationLookupContext* animations) {
        AnimationLists_SetFlag(animations, id);
        id.value = 0;
    }
};

// One sprite of the item manager: an Entity whose destructor is 0x00401FF0.
struct FrontSprite : Entity {
    ~FrontSprite();
};

// The 0x9ED0-byte item manager, as its destructor sees it.
struct Front {
    unsigned int flags;
    unsigned int reserved_0004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    FrontSprite sprites_0010[10];
    FrontSprite sprites_24c8[10];
    FrontSprite sprites_4980[9];
    FrontSprite sprites_6a8c[4];
    FrontSprite sprites_793c[2];
    FrontSprite sprites_8094[7];
    FrontSprite sprite_9a48;
    HudAnimation effects[8];      // +0x9DF4
    unsigned char reserved_9e14[0x9E50 - 0x9E14];
    HudAnimation banner;          // +0x9E50
    unsigned char reserved_9e54[0x9EC8 - 0x9E54];
    void* captions;                                // +0x9EC8, animation file
    unsigned int reserved_9ecc;

    __declspec(noinline) ~Front();    // 0x004145F0
};
typedef char ItemManagerSize_004145f0[sizeof(Front) == 0x9ED0 ? 1 : -1];
typedef char ItemManagerEffects[offsetof(Front, effects) == 0x9DF4 ? 1 : -1];

// 0x00414370: release everything the manager's items and score texts hold.
void __stdcall Front_ReleaseContents(Front* manager);

extern "C" Front* g_front;
