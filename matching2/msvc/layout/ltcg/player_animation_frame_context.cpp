#include "../../src/game/bullet/player_animation_advance_frame_004074b0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall PlayerAnimationFrameContext(PlayerAnimationState_004074B0** players,int count) {
 while(count--) (*players++)->AdvanceAnimationFrame();
}
#pragma code_seg()
