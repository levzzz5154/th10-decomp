#pragma once
#include "th10/render/animation_resource_removal.hpp"

// One entry's animation interface.  Retail calls its third virtual slot (+0x8)
// with the interface itself pushed, i.e. a __stdcall member.
struct AnimationHandle_00447810 {
    virtual void slot0();
    virtual void slot1();
    virtual void __stdcall slot2();
};

struct AnimationResourceEntry_00447810 {
    AnimationHandle_00447810* handle;   // +0x00
    void* allocation;                   // +0x04
    unsigned char pad_008[8];
};

struct AnimationResource_00447810 {
    unsigned char pad_000[0x108];
    void* resource_108;                            // +0x108: the record's own interface
    int entry_count_10c;                           // +0x10C
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;                           // +0x118
    void* auxiliary_11c;                           // +0x11C
    AnimationResourceEntry_00447810* entries_120;  // +0x120
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;                           // +0x12C

    __declspec(noinline) void Release();
};


struct BulletEntity_0040d680 {
    unsigned int vtable;
    unsigned char reserved_004[0x88];
    void* owned_resource;

    __declspec(noinline) void ReleaseResource();
};
