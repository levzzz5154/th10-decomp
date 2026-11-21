#pragma once
#include "th10/render/animation_script_id.hpp"
#include <stddef.h>
#include "th10/platform/worker.hpp"
#include "th10/platform/archive_callers.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/ending_text_dispatcher.hpp"
#include "th10/game/ending_script/script_executor_ascii_anchors.hpp"
struct EndingScriptCommand {
    unsigned short frame;
    unsigned char opcode;
    unsigned char argument_bytes;
    int arguments[3];
};
struct GameFrameTimer {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __declspec(noinline) void Set(int value);
    __declspec(noinline) void Advance(float delta);
};
struct AnmScriptHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) void MarkForRemoval();
};
struct AnmLookupNode {
    AnmLookupNode* object;
    AnmLookupNode* next;
    unsigned char reserved_008[0x0C];
    AnmLookupNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x340];
    unsigned int flags;
};
struct AnmLookupContext {
    unsigned char reserved_000[0x72DAD4];
    AnmLookupNode* primary;
    int reserved_72dad8;
    AnmLookupNode* secondary;
};
struct AnmLookup {
    __declspec(noinline) void* __fastcall Find(AnmLookupContext* context, AnimationScriptId id);
    __declspec(noinline) void* __fastcall SetFlag(AnmLookupContext* context, int id);
    __declspec(noinline) void* __cdecl Validate(AnmScriptHandle* handle);
};
struct GameThreadResourceView {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;
    unsigned char reserved_8998[0x89A4 - 0x8998];
    void* animation_handle;
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};
struct AnmSlotManager {
    unsigned char pad_000[0x3AD06C];
    struct AnimationResource6* slots_3ad06c[0x21];
    __declspec(noinline) void ClearResourceSlot(int index);
};
struct EndingOwner {
    unsigned char reserved_000[0x20];
    unsigned char flags_020;
};
struct EndingScriptState {
    unsigned int reserved_000;
    GameFrameTimer outer_timer;
    GameFrameTimer command_timer;
    GameFrameTimer wait_timer;
    AnmScriptHandle text_handles[5];
    EndingScriptCommand* command;
    unsigned char reserved_058[0x18];
    const unsigned char* background_data;
    unsigned int flags;
    int text_ring_position;
    unsigned int color;
    void* resources[4];
    unsigned int animation_handles[16];
    PlatformWorker worker;
};
typedef char RecoveryScriptSizeCheck[(sizeof(EndingScriptState)==0xEC)?1:-1];
typedef char RecoveryScriptCommandOffsetCheck[(offsetof(EndingScriptState,command)==0x54)?1:-1];
typedef char RecoveryScriptFlagsOffsetCheck[(offsetof(EndingScriptState,flags)==0x74)?1:-1];
typedef char RecoveryScriptHandlesOffsetCheck[(offsetof(EndingScriptState,animation_handles)==0x90)?1:-1];
typedef char RecoveryScriptWorkerOffsetCheck[(offsetof(EndingScriptState,worker)==0xD0)?1:-1];
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack(void* resource, void** out, int index, int render_bucket);
extern "C" __declspec(noinline) int __stdcall EndingScript_Execute(EndingScriptState* state);

typedef char RecoveryScriptArgumentOffsetCheck[(offsetof(EndingScriptCommand,arguments)==4)?1:-1];
