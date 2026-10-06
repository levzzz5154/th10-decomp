#pragma once
#include "runtime.hpp"
// Both callers use the same complete player, record and descriptor declarations.
typedef PickupAnimation AnimationObject;
typedef PickupAnimationNode AnimationNode;
typedef PickupAnimationLists AnimationContext;
typedef PickupRecord EffectEntry;
typedef PickupDescriptor EffectDescriptor;
struct FrontScript { unsigned char reserved[0x9eb8]; void* script;
    __declspec(noinline) void SetPowerDigits(int whole, int fraction); };
extern "C" {
extern FrontScript* data_0047770c;
float __stdcall NormalizeAngle(float value);
}
