#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043EC70..0x0043ECFF: read an integer-valued animation variable.
struct AnimationObjectVariables_0043ec70 {
    unsigned char reserved_000[0x30c];
    int integer_0;
    int integer_1;
    int integer_2;
    int integer_3;
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    int integer_8;
    int integer_9;

    __declspec(noinline) int ReadIntegerVariable(int variable) const;
};

#pragma code_seg(".text$01readvar")
int AnimationObjectVariables_0043ec70::ReadIntegerVariable(int variable) const {
    switch (variable - 10000) {
    case 0: return integer_0;
    case 1: return integer_1;
    case 2: return integer_2;
    case 3: return integer_3;
    case 4: return (int)float_0;
    case 5: return (int)float_1;
    case 6: return (int)float_2;
    case 7: return (int)float_3;
    case 8: return integer_8;
    case 9: return integer_9;
    default: return variable;
    }
}
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
void* __fastcall SprtCtrl::SetFlag(AnimationLookupContext* context, int id) {
    // The lookup is the sibling entry point; the retail call keeps the manager
    // object in ECX and the context in EDX, so it goes through its fixed address.
    AnimationLookupEntry* entry = (AnimationLookupEntry*)
        ((AnimationFindFn)asm_AnimationManager_Find_004491c0)(this, context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()
