#pragma once

#pragma code_seg()
























// 0x004491C0..0x00449208: ?AnimationManager_Find@@ (recovered below)



// 0x004492A0..0x004492E1: ?AnimationManager_SetFlag@@ (recovered below)















// Recovered semantic C++ definitions.

// The animation manager methods take the animation context in EDX (the second
// fastcall register) and the script id on the stack; ECX carries the manager
// object and is forwarded unchanged along the call chain.

// One node of an animation lookup bucket (also the object returned by the
// lookup: the first word of a registered object is its script id).
struct AnimationLookupEntry {
    AnimationLookupEntry* object;       // +0x00: object registered by this node
    AnimationLookupEntry* next;         // +0x04: next node of the bucket list
    unsigned char reserved_08[0x0C];
    AnimationLookupEntry* children;     // +0x14: head of the child node list
    int children_flagged;               // +0x18: children already flagged
    unsigned char reserved_1c[0x340];
    unsigned int flags;                  // +0x35C
};

// The lookup buckets live far inside the animation context, the large runtime
// structure the manager receives in EDX.
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationLookupEntry* primary_bucket;      // +0x72DAD4
    int reserved_2;                            // +0x72DAD8
    AnimationLookupEntry* secondary_bucket;    // +0x72DADC
};

class SprtCtrl {
public:
    __declspec(noinline) void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

// 0x004492A0: AnimationManager_SetFlag - mark the object registered under a
// script id, and its not-yet-flagged children, as script owned.
typedef void* (__fastcall* AnimationFindFn)(SprtCtrl*, AnimationLookupContext*, int);

#pragma code_seg(".text$03setflag")
