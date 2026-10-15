#pragma once
#include "th10/game/entity.hpp"
struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};

struct AnimationEntry {
    AnimationEntry* object;             // +0x00: object registered by this node
    AnimationEntry* next;               // +0x04: next node of the bucket list
    unsigned char reserved_08[0x0C];
    AnimationEntry* children;           // +0x14: head of the child node list
    int children_flagged;               // +0x18: children already flagged
    unsigned char reserved_1c[0x340];
    unsigned int flags;                  // +0x35C
};

// The lookup buckets live far inside the animation context, the large runtime
// structure this lookup receives in EDX.
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationEntry* primary_bucket;     // +0x72DAD4
    int reserved_2;                     // +0x72DAD8
    AnimationEntry* secondary_bucket;   // +0x72DADC
};

struct AnimationScriptId {
    int value;
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};


struct AnimationResource_00449870 {
    void __declspec(noinline) InitializeObject(Entity* object, int index);
};
struct AnimationPosition_00448d50 {
    float x, y, z;
    AnimationPosition_00448d50(float px, float py, float pz) : x(px), y(py), z(pz) {}
};
extern "C" void* g_sprt_ctrl;
extern "C" void* g_ascii_manager;
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);
__declspec(noinline) void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
    void* resource, void** out, int index, const AnimationPosition_00448d50* position);
typedef void (__fastcall *AnimationInitializer_0040b1b0)(Entity* object, void* context);
typedef void (*AnimationCallback_0040b1b0)(Entity* object);
extern "C" __declspec(noinline) AnimationScriptId* __stdcall AnimationCreateWithCallbacks_0040b1b0(
    AnimationScriptId* out, AnimationResource_00449870* resource, AnimationScriptId script,
    void* context, AnimationInitializer_0040b1b0 initialize,
    AnimationCallback_0040b1b0 update, AnimationCallback_0040b1b0 draw);
struct TitleEffectState_0041fdd0;
extern "C" __declspec(noinline) int __stdcall TitleEffectsAdvance_0041fdd0(TitleEffectState_0041fdd0* state);
