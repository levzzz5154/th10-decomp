#pragma once
#include "runtime.hpp"
#include "collision.hpp"
extern "C" int g_globals_shot_type;
#include "movement_input.hpp"
extern "C" const float flt_0_01;
extern "C" const float flt_224, flt_16;
// Actual complete animation operations, called only by the real movement body.
__declspec(noinline) void __fastcall Animation_SetStopFrame(
 unsigned short frame, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall Animation_SetPosition(
 const Vector3* position, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall Animation_SetTranslatedPosition(
 PickupAnimationLists* context, const Vector3* position, AnimationRef id);
