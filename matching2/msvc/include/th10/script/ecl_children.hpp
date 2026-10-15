// ECL owner and intrusive child-list fields used by 0x0044FD10.
#pragma once
#include <stddef.h>

// The interpreter's internals are not accessed by this traversal. The reset
// model at 0x0040C730 identifies its 0x1024-byte extent and the following
// script pointer at owner +0x102C.
struct EclChildState {
    unsigned char state[0x1024];
};

struct EclChildNode {
    EclChildState* state;
    EclChildNode* next;
    EclChildNode* previous;

    void Unlink() {
        if (next) next->previous = previous;
        if (previous) previous->next = next;
        next = 0;
        previous = 0;
    }
};

struct EclChildOwner {
    void* vtable;
    EclChildState* active; // +0x0004
    EclChildState root;   // +0x0008
    void* script;         // +0x102C
    EclChildNode children; // +0x1030; first node represents the root
};

typedef char EclChildStateSize[sizeof(EclChildState) == 0x1024 ? 1 : -1];
typedef char EclChildNodeSize[sizeof(EclChildNode) == 12 ? 1 : -1];
typedef char EclChildActiveOffset[offsetof(EclChildOwner, active) == 4 ? 1 : -1];
typedef char EclChildRootOffset[offsetof(EclChildOwner, root) == 8 ? 1 : -1];
typedef char EclChildScriptOffset[offsetof(EclChildOwner, script) == 0x102C ? 1 : -1];
typedef char EclChildrenOffset[offsetof(EclChildOwner, children) == 0x1030 ? 1 : -1];

// Native LTCG supplies the observed private conventions: the interpreter
// enters 0x0044E1A0 in EAX; the owner enters 0x0044FD10 in EDI. Both take delta
// on the stack and remove one word. See build_support/layout/ltcg/ecl_tick_children.json.
extern "C" __declspec(noinline) int __stdcall
EclVm_RunInterpreter(EclChildState* state, float delta);
extern "C" __declspec(noinline) int __stdcall
EclVm_TickChildren(EclChildOwner* owner, float delta);
