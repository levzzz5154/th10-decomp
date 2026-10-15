#ifndef TH10_OPEN_ANIMATION_HPP
#define TH10_OPEN_ANIMATION_HPP
#include <stddef.h>
#include "th10/game/entity.hpp"

struct AnimationScriptId {
    int value;
    AnimationScriptId() {}
    AnimationScriptId(int value) : value(value) {}
};
struct AnimationLookupContext;
__declspec(noinline) void* __fastcall AnimationManager_Find(
    AnimationLookupContext* context, AnimationScriptId id);
extern "C" void* g_sprt_ctrl;
extern "C" float g_game_speed;
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);
Entity* __fastcall Entity_Constructor(Entity* self);
void* __cdecl operator new(unsigned int size);
extern "C" int __stdcall RunAnimationVm_0043ee30(Entity* object);

struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};
struct AnimationBank {
    unsigned short id;
    unsigned char reserved_002[0x11C - 2];
    void** scripts;
    unsigned char reserved_120[4];
    int loading;
    __declspec(noinline) void InitializeObject(Entity* object, int index);
};
__declspec(noinline) void __stdcall LoadScriptPreservingState(
    AnimationBank* resource, Entity* object, int index);

struct AnimationManagerNodeOpen {
    Entity* animation;
    AnimationManagerNodeOpen* next;
    AnimationManagerNodeOpen* previous;
};
struct AnimationListsOpen {
    unsigned char reserved[0x72DADC];
    AnimationManagerNodeOpen* secondary_head;
    AnimationManagerNodeOpen* secondary_tail;
    unsigned char reserved_72dae4[0x732454 - 0x72DAE4];
    int next_id;
    __declspec(noinline) AnimationScriptId RegisterSecondaryBack(Entity* object);
};
typedef char PoolObjectOffsetCheck[offsetof(AnimationPool, objects) == 0x68 ? 1 : -1];
typedef char PoolBusyOffsetCheck[offsetof(AnimationPool, occupied) == 0x3AC068 ? 1 : -1];
typedef char PoolCursorOffsetCheck[offsetof(AnimationPool, next_slot) == 0x3AD068 ? 1 : -1];
typedef char ResourceScriptsOffsetCheck[offsetof(AnimationBank, scripts) == 0x11C ? 1 : -1];
typedef char ResourceLoadingOffsetCheck[offsetof(AnimationBank, loading) == 0x124 ? 1 : -1];
typedef char SecondaryIdOffsetCheck[offsetof(AnimationListsOpen, next_id) == 0x732454 ? 1 : -1];

// The VM word at +0x35C is shared with the low-word end marker.
struct AnimationOpenFlags {
    unsigned low_flags : 30;
    unsigned render_enabled : 1;
    unsigned high_flag : 1;
};
#endif
