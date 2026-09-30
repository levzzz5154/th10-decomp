#pragma once
#include <stddef.h>
#include "th10/platform/worker.hpp"
#include "th10/platform/archive_callers.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/recovery_script_executor_text_anchors.hpp"
#include "th10/game/recovery_script_executor_ascii_anchors.hpp"
struct RecoveryCommand_0040bd80 {
    unsigned short frame;
    unsigned char opcode;
    unsigned char argument_bytes;
    int arguments[3];
};
struct RecoveryTimer_0040bd80 {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __declspec(noinline) void Set(int value);
    __declspec(noinline) void Advance(float delta);
};
struct RecoveryHandle_0040bd80 {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) void MarkForRemoval();
};
struct RecoveryLookupNode_0040bd80 {
    RecoveryLookupNode_0040bd80* object;
    RecoveryLookupNode_0040bd80* next;
    unsigned char reserved_008[0x0C];
    RecoveryLookupNode_0040bd80* children;
    int children_flagged;
    unsigned char reserved_01c[0x340];
    unsigned int flags;
};
struct RecoveryLookupContext_0040bd80 {
    unsigned char reserved_000[0x72DAD4];
    RecoveryLookupNode_0040bd80* primary;
    int reserved_72dad8;
    RecoveryLookupNode_0040bd80* secondary;
};
struct RecoveryScriptId_0040bd80 { int value; };
struct RecoveryLookup_0040bd80 {
    __declspec(noinline) void* __fastcall Find(RecoveryLookupContext_0040bd80* context, RecoveryScriptId_0040bd80 id);
    __declspec(noinline) void* __fastcall SetFlag(RecoveryLookupContext_0040bd80* context, int id);
    __declspec(noinline) void* __cdecl Validate(RecoveryHandle_0040bd80* handle);
};
struct GameThread_0040c540 {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;
    unsigned char reserved_8998[0x89A4 - 0x8998];
    void* animation_handle;
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};
struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    struct AnimationResource_00447810* slots_3ad06c[0x21];
    __declspec(noinline) void ClearResourceSlot(int index);
};
struct RecoveryScriptOwner_0040bd80 {
    unsigned char reserved_000[0x20];
    unsigned char flags_020;
};
struct RecoveryScriptState_0040bd80 {
    unsigned int reserved_000;
    RecoveryTimer_0040bd80 outer_timer;
    RecoveryTimer_0040bd80 command_timer;
    RecoveryTimer_0040bd80 wait_timer;
    RecoveryHandle_0040bd80 text_handles[5];
    RecoveryCommand_0040bd80* command;
    unsigned char reserved_058[0x18];
    const unsigned char* background_data;
    unsigned int flags;
    int text_ring_position;
    unsigned int color;
    void* resources[4];
    unsigned int animation_handles[16];
    PlatformWorker worker;
};
typedef char RecoveryScriptSizeCheck[(sizeof(RecoveryScriptState_0040bd80)==0xEC)?1:-1];
typedef char RecoveryScriptCommandOffsetCheck[(offsetof(RecoveryScriptState_0040bd80,command)==0x54)?1:-1];
typedef char RecoveryScriptFlagsOffsetCheck[(offsetof(RecoveryScriptState_0040bd80,flags)==0x74)?1:-1];
typedef char RecoveryScriptHandlesOffsetCheck[(offsetof(RecoveryScriptState_0040bd80,animation_handles)==0x90)?1:-1];
typedef char RecoveryScriptWorkerOffsetCheck[(offsetof(RecoveryScriptState_0040bd80,worker)==0xD0)?1:-1];
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack_00448d00(void* resource, void** out, int index, int render_bucket);
extern "C" __declspec(noinline) int __stdcall RecoveryScript_Execute_0040bd80(RecoveryScriptState_0040bd80* state);

typedef char RecoveryScriptArgumentOffsetCheck[(offsetof(RecoveryCommand_0040bd80,arguments)==4)?1:-1];
