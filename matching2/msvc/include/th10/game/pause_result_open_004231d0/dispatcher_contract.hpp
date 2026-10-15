#pragma once
#include <stddef.h>
#include "th10/game/pause_result_open_004231d0/open_state.hpp"
#include "th10/math/timer.hpp"
#include "th10/game/player.hpp"
#include "th10/game/score.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/render/screen_effect_controller.hpp"
#include "th10/game/recovery_mark_text_and_dispatcher_004479d0.hpp"

// Genuine source inputs recovered from the retail body. All private register
// choices require these helpers' complete ordinary bodies in the native graph.
struct DispatcherVec3 { float x, y, z; };
struct DispatcherRef {
    int value;
    DispatcherRef(int value) : value(value) {}
    __declspec(noinline) void SelectCurrentSprite(int index);
    __declspec(noinline) void SelectResourceSprite(AnimationResource_00449870*, int index);
};
// The animation manager's primary list tail registration (0x004489D0). The
// returned four-byte reference has a genuine compiler-generated return home.
struct DispatcherPrimaryLists {
    unsigned char reserved_000[0x72DAD4];
    AnimationManagerNodeOpen* primary_head;
    AnimationManagerNodeOpen* primary_tail;
    unsigned char reserved_72dadc[0x732454 - 0x72DADC];
    int next_id;
    __declspec(noinline) DispatcherRef RegisterPrimaryBack(Entity* object);
};
typedef char DispatcherPrimaryHeadOffset[
    offsetof(DispatcherPrimaryLists, primary_head)==0x72DAD4?1:-1];
typedef char DispatcherPrimaryIdOffset[
    offsetof(DispatcherPrimaryLists, next_id)==0x732454?1:-1];

struct DispatcherHandle {
    AnimationScriptId id;
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) void SetStopFrame(short frame);
    __declspec(noinline) DispatcherRef FindChildRef(int script_id);
};
__declspec(noinline) DispatcherRef __stdcall DispatcherCreateAnimation(
    AnimationResource_00449870* resource, int script_index, int render_bucket);
typedef RecoveryTextVm_00447a50 DispatcherObject;
struct AnimationLookupContext;
static __forceinline DispatcherObject* DispatcherFindAnimation(
        AnimationLookupContext* context, AnimationScriptId id) {
    return reinterpret_cast<DispatcherObject*>(AnimationManager_Find_004491c0(context, id));
}
__declspec(noinline) void* __fastcall DispatcherRemoveAnimation(
    AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void DispatcherSetPosition(const DispatcherVec3*,
    AnimationLookupContext*, AnimationScriptId);
__declspec(noinline) char* Path_DecodeXor(const char* encoded);

struct DispatcherInputState {
    unsigned char reserved_000[0x390];
    int mode;
    unsigned char reserved_394[0x3CC - 0x394];
    unsigned flags;
};
__declspec(noinline) void SetInputMode(DispatcherInputState*, int);
struct DispatcherRankState {
    unsigned char reserved_000[0x3C];
    int level;
    __declspec(noinline) void AdvanceLevel();
};
struct DispatcherWaitTimer {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned flags;
    __declspec(noinline) void SetSchedulerValue(int value);
};

#pragma pack(push, 1)
struct DispatcherCommand {
    unsigned short frame;
    unsigned char opcode;
    unsigned char operand_size;
    int first_operand;
};
#pragma pack(pop)

struct ResultDispatcherState {
    int variant;                         // +00
    DispatcherVec3 position;             // +04
    const float* position_step;          // +10
    int reserved_14;
    FrameTimer timer;                    // +18
    DispatcherWaitTimer wait;            // +2C
    DispatcherHandle left_portrait;      // +40
    DispatcherHandle right_portrait;     // +44
    DispatcherHandle background;         // +48
    DispatcherHandle first_text;         // +4C
    DispatcherHandle second_text;        // +50
    DispatcherHandle stage_title;        // +54
    int reserved_58;
    DispatcherCommand* command;          // +5C
    DispatcherVec3 text_positions[2];     // +60
    int countdown;                       // +78
    unsigned flags;                      // +7C
    int alternate_text;                  // +80
    int text_side;                       // +84
    int text_parameters[2];              // +88
};
typedef char DispatcherTimerOffset[offsetof(ResultDispatcherState,timer)==0x18?1:-1];
typedef char DispatcherWaitOffset[offsetof(ResultDispatcherState,wait)==0x2C?1:-1];
typedef char DispatcherPortraitOffset[offsetof(ResultDispatcherState,left_portrait)==0x40?1:-1];
typedef char DispatcherCommandOffset[offsetof(ResultDispatcherState,command)==0x5C?1:-1];
typedef char DispatcherPositionsOffset[offsetof(ResultDispatcherState,text_positions)==0x60?1:-1];
typedef char DispatcherParametersOffset[offsetof(ResultDispatcherState,text_parameters)==0x88?1:-1];
typedef char DispatcherStateExtent[sizeof(ResultDispatcherState)==0x90?1:-1];

struct DispatcherStageResourceOwner {
    unsigned char reserved_00[0x38];
    AnimationResource_00449870* resource;
};
struct DispatcherStageState {
    unsigned char reserved_000[0x9E14];
    AnimationScriptId transition_animation;
    unsigned char reserved_9e18[0x9E80-0x9E18];
    AnimationResource_00449870* effect_resource;
    unsigned char reserved_9e84[0x9EB4-0x9E84];
    unsigned flags;
    unsigned char reserved_9eb8[0x9EC8-0x9EB8];
    AnimationResource_00449870* resource;
    int result_phase;
};
typedef char DispatcherStageFlagsOffset[offsetof(DispatcherStageState,flags)==0x9EB4?1:-1];
typedef char DispatcherStageResourceOffset[offsetof(DispatcherStageState,resource)==0x9EC8?1:-1];

struct DispatcherProgress {
    unsigned char reserved_000[0x4D0];
    int first_clear_count;
};
struct DispatcherReplayOwner {
    unsigned char reserved_00[0x10];
    int replay_mode;
};
struct DispatcherMusicRecord {
    int values[10];
    int music_slot;
};

extern "C" DispatcherStageResourceOwner* data_00477704;
extern "C" DispatcherReplayOwner* data_00477838;
extern "C" void* data_00491c10;
extern "C" DispatcherInputState data_00491c28;
extern "C" ScoreState data_00474c40;
extern "C" short data_00474c48;
extern "C" int data_00474c4c;
extern "C" int data_00474c68;
extern "C" int data_00474c6c;
extern "C" int data_00474c70;
extern "C" int data_00474c74;
extern "C" int data_00474c7c;
extern "C" int data_00474c84;
extern "C" int data_00474c8c;
extern "C" unsigned data_00474ca0;
extern "C" unsigned g_input;
extern "C" unsigned data_00474e62;

// Real public stack interfaces: Music_Play has two inputs and RET8,
// RandomVoice has one float and RET4. Incoming ECX is unused in both.
extern "C" int __stdcall asm_Sound_PlayDummyRetail_00420b10(int slot, int heard_index);
extern "C" int __stdcall asm_Sound_PlayRandomVoiceRetail_00420c30(float amount);

