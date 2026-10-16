#pragma once
#include <stddef.h>
#include "th10/platform/worker.hpp"
#include "th10/platform/archive_callers.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/recovery_script_executor_cluster/recovery_script_executor_text_anchors.hpp"
#include "th10/game/recovery_script_executor_ascii_anchors.hpp"
struct RecoveryCommand {
    unsigned short frame;
    unsigned char opcode;
    unsigned char argument_bytes;
    int arguments[3];
};
struct RecoveryTimer2 {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __declspec(noinline) void Set(int value);
    __declspec(noinline) void Advance(float delta);
};
struct RecoveryHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) void MarkForRemoval();
};
struct RecoveryLookupNode {
    RecoveryLookupNode* object;
    RecoveryLookupNode* next;
    unsigned char reserved_008[0x0C];
    RecoveryLookupNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x340];
    unsigned int flags;
};
struct RecoveryLookupContext {
    unsigned char reserved_000[0x72DAD4];
    RecoveryLookupNode* primary;
    int reserved_72dad8;
    RecoveryLookupNode* secondary;
};
struct RecoveryScriptId { int value; };
struct RecoveryLookup {
    __declspec(noinline) void* __fastcall Find(RecoveryLookupContext* context, RecoveryScriptId id);
    __declspec(noinline) void* __fastcall SetFlag(RecoveryLookupContext* context, int id);
    __declspec(noinline) void* __cdecl Validate(RecoveryHandle* handle);
};
struct GameThread6 {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;
    unsigned int reserved_8998;
    void* text_resource;                // +0x899C
    unsigned int reserved_89a0;
    void* animation_handle;
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};
struct AnimationManager13 {
    unsigned char pad_000[0x3AD06C];
    struct AnimationResource6* slots_3ad06c[0x21];
    __declspec(noinline) void ClearResourceSlot(int index);
};
struct RecoveryScriptOwner {
    unsigned char reserved_000[0x20];
    unsigned char flags_020;
};
struct RecoveryScriptState {
    unsigned int reserved_000;
    RecoveryTimer2 outer_timer;
    RecoveryTimer2 command_timer;
    RecoveryTimer2 wait_timer;
    RecoveryHandle text_handles[5];
    RecoveryCommand* command;
    unsigned char reserved_058[0x18];
    const unsigned char* background_data;
    unsigned int flags;
    int text_ring_position;
    unsigned int color;
    void* resources[4];
    unsigned int animation_handles[16];
    PlatformWorker worker;
};
typedef char RecoveryScriptSizeCheck[(sizeof(RecoveryScriptState)==0xEC)?1:-1];
typedef char RecoveryScriptCommandOffsetCheck[(offsetof(RecoveryScriptState,command)==0x54)?1:-1];
typedef char RecoveryScriptFlagsOffsetCheck[(offsetof(RecoveryScriptState,flags)==0x74)?1:-1];
typedef char RecoveryScriptHandlesOffsetCheck[(offsetof(RecoveryScriptState,animation_handles)==0x90)?1:-1];
typedef char RecoveryScriptWorkerOffsetCheck[(offsetof(RecoveryScriptState,worker)==0xD0)?1:-1];
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack(void* resource, void** out, int index, int render_bucket);
extern "C" __declspec(noinline) int __stdcall RecoveryScript_Execute2(RecoveryScriptState* state);

typedef char RecoveryScriptArgumentOffsetCheck[(offsetof(RecoveryCommand,arguments)==4)?1:-1];
