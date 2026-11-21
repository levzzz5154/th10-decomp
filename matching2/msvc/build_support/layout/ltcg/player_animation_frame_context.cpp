#include "../../../src/game/bullet/bullet_ex_speedup.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall PlayerAnimationFrameContext(BulletExSpeedup** players,int count) {
 while(count--) (*players++)->StepSpeedup();
}
#pragma code_seg()
