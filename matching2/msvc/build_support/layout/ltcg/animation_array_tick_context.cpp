#include "../../../src/core/sprtanim/animation_array_tick.cpp"
#pragma code_seg(".text$03context")
__declspec(noinline) void __fastcall TickAnimationArrayContext(BatchAnimation* animations, int count) {
 TickAnimationArray(animations,count);
}
#pragma code_seg()
