#pragma once
#include <stddef.h>
#include "th10/game/pause_result_open_004231d0/open_state.hpp"
#include "th10/game/entity.hpp"
#include "th10/game/polar_motion.hpp"
#include "th10/game/pause_result_open_004231d0/player/player_collision.hpp"
#include "th10/game/player_update_score.hpp"
#include "th10/game/power_display_004054b0.hpp"
#include "th10/game/score.hpp"

// These are physical record views, with one pointer for each real object.
// The source graph must supply the ordinary definitions of private methods.
struct PlayerSchedulerRecord {
    int field_00, field_04;
    float field_08;
    const float* field_0C;
    int flags_10;
    __declspec(noinline) void SetSchedulerValue(int value);
};
struct PlayerParticle_00425730 {
    float horizontal_extent, horizontal_growth;
    float vertical_extent, vertical_growth;
    unsigned char reserved_10[8];
    PolarMotion motion;
    FrameTimer timer;
    unsigned mode;
    unsigned counter;
    int limit;
    int phase;
    unsigned flags;
};
struct HistoryPoint_00425730 { int x, y; };
struct PlayerState_00425730 {
    unsigned char reserved_0000[0x14];
    Entity animation;
    PolarVec3 position;
    int fixed_x, fixed_y;
    unsigned char reserved_03d4[0x404-0x3D4];
    PolarVec3 collision_min, collision_max, collision_extent;
    PolarVec3 secondary_size, secondary_extent, entry_position;
    unsigned char reserved_044c[0x458-0x44C];
    int phase;
    void* stage_schedule;
    FrameTimer stage_timer;
    FrameTimer state_timer;
    FrameTimer auxiliary_timer;
    unsigned char reserved_049c[0x332C-0x49C];
    int familiar_0_state;
    unsigned char reserved_3330[0x33C4-0x3330];
    int familiar_1_state;
    unsigned char reserved_33c8[0x345C-0x33C8];
    int familiar_2_state;
    unsigned char reserved_3460[0x34F4-0x3460];
    int familiar_3_state;
    unsigned char reserved_34f8[8];
    int familiar_level;
    int pending_stage;
    char pending_stage_name;
    unsigned char reserved_3509[3];
    PlayerParticle_00425730 particles[32];
    unsigned char reserved_428c[0x430C-0x428C];
    FrameTimer invulnerability_timer;
    unsigned reserved_4320;
    PolarVec3 secondary_half_min, secondary_half_max;
    PolarVec3 secondary_min, secondary_max;
    PolarVec3 size_min, size_max;
    HistoryPoint_00425730 history[33];
    int alternate;
};
typedef char PlayerAnimationOffset[offsetof(PlayerState_00425730,animation)==0x14?1:-1];
typedef char PlayerPositionOffset[offsetof(PlayerState_00425730,position)==0x3C0?1:-1];
typedef char PlayerPhaseOffset[offsetof(PlayerState_00425730,phase)==0x458?1:-1];
typedef char PlayerStateTimerOffset[offsetof(PlayerState_00425730,state_timer)==0x474?1:-1];
typedef char PlayerAuxiliaryTimerOffset[offsetof(PlayerState_00425730,auxiliary_timer)==0x488?1:-1];
typedef char PlayerParticleExtent[sizeof(PlayerParticle_00425730)==0x6C?1:-1];
typedef char PlayerParticleMotionOffset[offsetof(PlayerParticle_00425730,motion)==0x18?1:-1];
typedef char PlayerParticleTimerOffset[offsetof(PlayerParticle_00425730,timer)==0x44?1:-1];
typedef char PlayerParticlesOffset[offsetof(PlayerState_00425730,particles)==0x350C?1:-1];
typedef char PlayerInvulnerabilityOffset[offsetof(PlayerState_00425730,invulnerability_timer)==0x430C?1:-1];
typedef char PlayerHistoryOffset[offsetof(PlayerState_00425730,history)==0x436C?1:-1];
typedef char PlayerAlternateOffset[offsetof(PlayerState_00425730,alternate)==0x4474?1:-1];

struct PlayerInitialization_00425730 {
    unsigned char reserved_00[0x28];
    int initialized;
};
struct ReplayState_00425730 {
    unsigned char reserved_00[0x10];
    int mode;
};
struct ActiveStage_00425730 {
    unsigned char reserved_00[0x60];
    int active;
};
struct FrontScript_00425730 {
    unsigned char reserved_0000[0x9EB8];
    void* script;
};
struct EntityAngleTarget_00426610 {
    unsigned char reserved_000[0x3C0];
    float x,y;
};
__declspec(noinline) double Entity_AngleToPoint(
    const EntityAngleTarget_00426610* entity, const float* point);
struct MovementState;
__declspec(noinline) int PlayerMovement_004250b0(MovementState* player);
struct StageSequence;

extern "C" {
extern PlayerInitialization_00425730* data_004776ec;
extern ScoreRecords_0041c800* data_0047781c;
extern ReplayState_00425730* data_00477838;
extern ActiveStage_00425730* data_00477704;
extern short data_00474c48;
extern int data_00474c70, data_00474c98;
extern unsigned int data_00474e5c;
extern ScoreState data_00474c40;
extern float data_00470afc, data_00470b00, data_00470b04;
extern float data_00470b0c, data_00470b4c, data_00470b64, data_00470b68;
extern float data_00470bc8, data_00470d38, data_00470d3c;
extern float data_00470d40, data_00470d44;
// Each imported body consumes exactly this one stack pointer and RET4.
int __stdcall PlayerInitialize_00405860(PlayerInitialization_00425730* state);
void __stdcall PlayerFamiliarRefresh_00426f70(PlayerState_00425730* state);
void __stdcall PlayerSpellTimeout_004269d0(PlayerState_00425730* state);
int __stdcall PlayerEffectPoolUpdate_00428280(PlayerState_00425730* state);
int __stdcall PlayerAnimationVmTick_0043ee30(Entity* animation);
}
struct InputState_00425730 {
    unsigned char reserved_000[0x390];
    int mode;
    unsigned char reserved_394[0x3CC-0x394];
    unsigned flags;
};
extern "C" InputState_00425730 data_00491c28;
__declspec(noinline) void PlayerSetInputMode_0040ac90(InputState_00425730* state,int mode);

extern "C" __declspec(noinline) int __stdcall PlayerStateUpdate_00425730(
    PlayerState_00425730* player);
