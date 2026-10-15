// 0x00422C30: resume the pause-menu owner and restore the saved speed.
#include "../../core/sprtanim/animation_manager_register_resource_0043e460.cpp"
struct AnimationLookupContext;
struct AnimationScriptId { int value; };
void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext*, AnimationScriptId);
extern "C" AnimationLookupContext* data_00491c10;
struct PauseFlags_00422c30 { unsigned char reserved[0x58]; unsigned flags; };
extern PauseFlags_00422c30* g_pause_flags;
extern AnimationManager_0043e460 g_music_requests;
extern float g_game_speed;
struct PauseOwner_00422c30 {
 unsigned char reserved[0x1DC];
 AnimationScriptId animation;
 unsigned char reserved_1e0[0x2C0-0x1E0];
 float saved_speed;
 __declspec(noinline) void Unpause();
};
#pragma code_seg(".text$00fn")
void PauseOwner_00422c30::Unpause() {
 g_pause_flags->flags &= ~0x10u;
 g_music_requests.RegisterResource("", 7, 0);
 AnimationManager_SetFlag_004492a0(data_00491c10, animation);
 // Publish the cleared pause animation before restoring game timing.
 *(volatile int*)&animation.value = 0;
 g_game_speed = *(volatile float*)&saved_speed;
}
#pragma code_seg()
