#pragma once
#include "runtime.hpp"
#include "collision.hpp"
extern "C" int data_00474c6c;
#include "movement_input.hpp"
extern "C" const float data_00470b00;
extern "C" const float data_00470b4c, data_00470b48;
// Actual complete animation operations, called only by the real movement body.
__declspec(noinline) void __fastcall MovementStopFrame_00449210(
 unsigned short frame, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall MovementSetPosition_004492f0(
 const Vector3* position, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall MovementSetTranslatedPosition_00449350(
 PickupAnimationLists* context, const Vector3* position, AnimationRef id);
