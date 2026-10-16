#include "../../../src/game/bullet/player_animation_advance_frame.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall PlayerAnimationFrameContext(PlayerAnimationState** players,int count) {
 while(count--) (*players++)->AdvanceAnimationFrame();
}
#pragma code_seg()
