#pragma once
#include "runtime.hpp"
// Both callers use the same complete player, record and descriptor declarations.
typedef PickupAnimation AnimationObject;
typedef PickupAnimationNode AnimationNode;
typedef PickupAnimationLists AnimationContext;
typedef PickupRecord EffectEntry;
typedef PickupDescriptor EffectDescriptor;
struct Resource_0043e5a0;
struct FrontScript {
    unsigned char storage[0x9eb8];
    void* script;
    unsigned char reserved_9ebc[0x9ec8-0x9ebc];
    Resource_0043e5a0* animation_resource;
    AnimationRef& ExtendBanner() { return *reinterpret_cast<AnimationRef*>(storage+0x9e18); }
    Resource_0043e5a0*& AnimationResource() { return animation_resource; }
    __declspec(noinline) void SetPowerDigits(int whole,int fraction);
    __declspec(noinline) void SetActiveCount(int count);
};
extern "C" {
extern FrontScript* data_0047770c;
float __stdcall NormalizeAngle(float value);
}
