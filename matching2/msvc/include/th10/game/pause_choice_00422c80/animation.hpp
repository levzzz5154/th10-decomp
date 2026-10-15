#ifndef TH10_CHOICE_ANIMATION_HPP
#define TH10_CHOICE_ANIMATION_HPP
#include <stddef.h>
#include "th10/render/resource_registrar_0043e460.hpp"

struct AnimationScriptId { int value; };
struct AnimationLookupContext;
__declspec(noinline) void* __fastcall AnimationManager_Find(
    AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void* __fastcall AnimationManager_SetFlag_004492a0(
    AnimationLookupContext* context, AnimationScriptId id);
extern "C" AnimationLookupContext* g_sprt_ctrl;

struct Ref4 {
    int value;
    Ref4(int value) : value(value) {}
    __declspec(noinline) void StopAtFrame6();
};
struct Handle4 {
    unsigned int value;
    __declspec(noinline) void SetStopFrame(short frame);
    __declspec(noinline) Ref4 FindChildRef(int script_id);
    __declspec(noinline) void StopAtFrame1();
};
struct PauseOwner_00422c30 {
    unsigned char reserved[0x1DC];
    AnimationScriptId animation;
    unsigned char reserved_1e0[0x2C0 - 0x1E0];
    float saved_speed;
    __declspec(noinline) void Unpause();
};
struct PauseFlags_00422c30 { unsigned char reserved[0x58]; unsigned flags; };
extern PauseFlags_00422c30* g_pause_flags;
extern AnimationManager_0043e460 g_music_requests;
extern float g_game_speed;

typedef char HandleSizeCheck[(sizeof(Handle4) == 4) ? 1 : -1];
typedef char RefSizeCheck[(sizeof(Ref4) == 4) ? 1 : -1];
typedef char PauseOwnerAnimationOffsetCheck[(offsetof(PauseOwner_00422c30, animation) == 0x1DC) ? 1 : -1];
typedef char PauseOwnerSpeedOffsetCheck[(offsetof(PauseOwner_00422c30, saved_speed) == 0x2C0) ? 1 : -1];
#endif
