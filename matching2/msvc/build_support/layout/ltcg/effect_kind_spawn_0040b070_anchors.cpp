// Compiler context only: models of the callees, so the pass derives their
// register arguments.
#include "th10/game/effect_kind_spawn.hpp"

extern "C" void* __cdecl operator_new2(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

#pragma code_seg(".text$00449950_fn")
AnimationNode2* AnimationPool2::Allocate() {
    unsigned char* bytes = (unsigned char*)this;
    unsigned int index = *(unsigned int*)(bytes + 0x3AD068);
    if (bytes[0x3AC068 + index] != 0) {
        index = NextPoolIndex_00449950(index);
        *(unsigned int*)(bytes + 0x3AD068) = index;
        if (bytes[0x3AC068 + index] != 0) {
            unsigned char* allocated = (unsigned char*)operator_new2(0x3AC);
            if (allocated == 0) return 0;
            Entity_Constructor_00402050(allocated);
            Entity_Init_00401de0(0, allocated);
            *(unsigned int*)(bytes + 0x3AD068) =
                NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
            return (AnimationNode2*)allocated;
        }
    }
    unsigned char* slot = bytes + 0x68 + index * 0x3AC;
    bytes[0x3AC068 + index] = 1;
    *(unsigned int*)(bytes + 0x3AD068) =
        NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
    return (AnimationNode2*)slot;
}

#pragma code_seg(".text$004489d0_fn")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    unsigned char* node = e + 0x04;
    *(void**)(node + 0) = e;
    *(void**)(node + 4) = 0;
    *(void**)(node + 8) = 0;
    if (*(void**)(m + 0x72DAD4) == 0) {
        *(void**)(m + 0x72DAD4) = node;
    } else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        if (*(unsigned char**)(tail + 0x04) != 0) {
            *(unsigned char**)(node + 4) = *(unsigned char**)(tail + 0x04);
            *(unsigned char**)(*(unsigned char**)(tail + 0x04) + 0x08) = node;
        }
        *(unsigned char**)(tail + 0x04) = node;
        *(unsigned char**)(node + 8) = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    int id = *(int*)(m + 0x732454) + 1;
    *(int*)(m + 0x732454) = id;
    if (id == 0)
        *(int*)(m + 0x732454) = id + 1;
    *(int*)e = *(int*)(m + 0x732454);
    *(int*)out = *(int*)(m + 0x732454);
    return out;
}

#pragma code_seg(".text$004491c0_fn")
AnimationNode2* AnimationLists2::Find(AnimationHandle2 handle) {
    if (!handle.value)
        return 0;
    for (AnimationNode2* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (AnimationNode2* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg()
