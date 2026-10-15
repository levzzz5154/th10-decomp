// Interfaces and accessed fields for the stop-frame/run family.
#pragma once
#include <stddef.h>

struct AnimationLookupContext;
struct AnimationScriptId { int value; };

struct AnimationTreeNode {
    AnimationTreeNode* object;
    AnimationTreeNode* next;
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children; // +0x014
    int children_flagged;       // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;  // +0x304
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

// The complete state/table extent is not needed by these slot callers. The
// retail address calculation identifies its ID table at +0x2C4, stride four.
struct Title;
inline AnimationScriptId* AnimationSlots(Title* state) {
    return reinterpret_cast<AnimationScriptId*>(
        reinterpret_cast<unsigned char*>(state) + 0x2C4);
}

struct AnimationRunHandle {
    AnimationScriptId value;
    __declspec(noinline) void SetStopFrameAndRun(unsigned short frame);
};

extern "C" AnimationLookupContext* data_00491c10;
// RunAnimationVm is the real stack-pointer / RET4 interpreter at 0x0043EE30.
extern "C" int __stdcall RunAnimationVm(AnimationTreeNode* node);

// Native LTCG retains frame in DI, context in EDX, and the record ID on stack.
void __fastcall AnimationManager_SetStopFrameAndRun(
    unsigned short frame, AnimationLookupContext* context, AnimationScriptId id);
// The private entry takes state in EAX and slot in ECX; plain RET.
void __fastcall Title_DispatchAnimationSlot(int slot, Title* state);
void __fastcall Title_DispatchAnimationSlotSecondary(int slot, Title* state);

typedef char AnimationRunIdSize[sizeof(AnimationScriptId) == 4 ? 1 : -1];
typedef char AnimationRunHandleSize[sizeof(AnimationRunHandle) == 4 ? 1 : -1];
typedef char AnimationRunChildrenOffset[offsetof(AnimationTreeNode, children) == 0x14 ? 1 : -1];
typedef char AnimationRunChildFlagOffset[offsetof(AnimationTreeNode, children_flagged) == 0x18 ? 1 : -1];
typedef char AnimationRunStopFrameOffset[offsetof(AnimationTreeNode, stop_frame) == 0x304 ? 1 : -1];
