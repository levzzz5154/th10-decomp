#pragma once
#include "runtime.hpp"
// Both callers use the same complete player, record and descriptor declarations.
typedef PickupAnimation AnimationObject;
typedef PickupAnimationNode AnimationNode;
typedef PickupAnimationLists AnimationContext;
struct FrontScript { unsigned char reserved[0x9eb8]; void* script;
    __declspec(noinline) void SetPowerDigits(int whole, int fraction); };
extern "C" {
extern FrontScript* g_front;
float __stdcall NormalizeAngle(float value);
}
