#pragma once
#include "runtime.hpp"
#include "collision.hpp"
extern "C" int data_00474c6c;
#include "movement_input.hpp"
extern "C" const float data_00470b00;
extern "C" const float data_00470b4c, data_00470b48;
// Actual complete animation operations, called only by the real movement body.
__declspec(noinline) void __fastcall Animation_SetStopFrame(
 unsigned short frame, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall Animation_SetPosition(
 const Vector3* position, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall Animation_SetTranslatedPosition(
 PickupAnimationLists* context, const Vector3* position, AnimationRef id);
