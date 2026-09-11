#include "asm_encoding.hpp"
#include "asm_symbols.hpp"








// 0x0043EC70..0x0043ECD7: ?AnimationObject_ReadIntegerVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ReadIntegerVariable_0043ec70() {
    __asm {
    L_0043ec70:
        lea edx,[eax-2710h]
    L_0043ec76:
        cmp edx,9
    L_0043ec79:
        ja short L_0043ecd7
    L_0043ec7b:
        jmp dword ptr [edx*4+43ECD8h]
    L_0043ec82:
        mov eax,dword ptr [ecx+30Ch]
    L_0043ec88:
        ret
    L_0043ec89:
        mov eax,dword ptr [ecx+310h]
    L_0043ec8f:
        ret
    L_0043ec90:
        mov eax,dword ptr [ecx+314h]
    L_0043ec96:
        ret
    L_0043ec97:
        mov eax,dword ptr [ecx+318h]
    L_0043ec9d:
        ret
    L_0043ec9e:
        fld dword ptr [ecx+31Ch]
    L_0043eca4:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043eca9:
        fld dword ptr [ecx+320h]
    L_0043ecaf:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecb4:
        fld dword ptr [ecx+324h]
    L_0043ecba:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecbf:
        fld dword ptr [ecx+328h]
    L_0043ecc5:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecca:
        mov eax,dword ptr [ecx+32Ch]
    L_0043ecd0:
        ret
    L_0043ecd1:
        mov eax,dword ptr [ecx+330h]
    L_0043ecd7:
        ret
        _emit 0x82
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0x89
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0x90
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0x97
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0x9e
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0xa9
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0xb4
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0xbf
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0xca
        _emit 0xec
        _emit 0x43
        _emit 0x00
        _emit 0xd1
        _emit 0xec
        _emit 0x43
        _emit 0x00
    }
}
























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

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, int id);
    void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

// 0x004491C0: AnimationManager_Find - look a script id up in the primary and
// then the secondary bucket, returning the registered object.
void* __fastcall AnimationManager::Find(AnimationLookupContext* context, int id) {
    if (!id)
        return 0;
    for (AnimationLookupEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id)
            return node->object;
    for (AnimationLookupEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id)
            return node->object;
    return 0;
}

// 0x004492A0: AnimationManager_SetFlag - mark the object registered under a
// script id, and its not-yet-flagged children, as script owned.
typedef void* (__fastcall* AnimationFindFn)(AnimationManager*, AnimationLookupContext*, int);

void* __fastcall AnimationManager::SetFlag(AnimationLookupContext* context, int id) {
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
