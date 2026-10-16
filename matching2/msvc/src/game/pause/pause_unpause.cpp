// 0x00422C30: resume the pause-menu owner and restore the saved speed.
#include "../../core/sprtanim/animation_manager_register_resource.cpp"
struct AnimationLookupContext;
struct AnimationScriptId { int value; };
void* __fastcall AnimationManager_SetFlag2(AnimationLookupContext*, AnimationScriptId);
extern "C" AnimationLookupContext* g_sprt_ctrl;
struct PauseFlags { unsigned char reserved[0x58]; unsigned flags; };
extern PauseFlags* g_pause_flags;
extern AnimationManager9 g_music_requests;
extern float g_game_speed;
struct PauseOwner {
 unsigned char reserved[0x1DC];
 AnimationScriptId animation;
 unsigned char reserved_1e0[0x2C0-0x1E0];
 float saved_speed;
 __declspec(noinline) void Unpause();
};
#pragma code_seg(".text$00fn")
void PauseOwner::Unpause() {
 g_pause_flags->flags &= ~0x10u;
 g_music_requests.RegisterResource("", 7, 0);
 AnimationManager_SetFlag2(g_sprt_ctrl, animation);
 // Publish the cleared pause animation before restoring game timing.
 *(volatile int*)&animation.value = 0;
 g_game_speed = *(volatile float*)&saved_speed;
}
#pragma code_seg()
