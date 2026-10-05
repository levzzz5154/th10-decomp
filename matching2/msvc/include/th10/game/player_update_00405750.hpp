#ifndef TH10_PLAYER_UPDATE_00405750_HPP
#define TH10_PLAYER_UPDATE_00405750_HPP
#include "th10/math/timer.hpp"
#include "th10/render/position_setter_pair.hpp"
#include "th10/game/player_update_score.hpp"
#include "th10/game/player_update_collision.hpp"
struct PlayerUpdateState_00405750 {
    unsigned char reserved_000[0x14];
    FrameTimer timer;
    int active_state;
    PositionScriptId_004492f0 animation;
    PositionVector_004492f0 position;
    float collision_radius;
    __declspec(noinline) int Update();
    __declspec(noinline) int Draw();
    void Step();
};
struct PlayerMotionGlobals_00405750 {
    unsigned char reserved_000[0x3788];
    int input_state;
    unsigned int flags;
};
struct PlayerAnimationValue_00405750 {
    unsigned char reserved_000[0x40];
    float collision_radius;
};
extern "C" PlayerMotionGlobals_00405750* data_004776f4;
extern "C" CollisionEngine_00408100* data_004776f0;
extern "C" ScoreRecords_0041c800* data_0047781c;
extern "C" int data_00474c68;
extern "C" float data_00470b0c, data_00470afc, data_00470d34, data_00470b4c, data_00470b48;
typedef char PlayerUpdateTimerOffset[offsetof(PlayerUpdateState_00405750,timer)==0x14 ? 1:-1];
typedef char PlayerUpdateStateOffset[offsetof(PlayerUpdateState_00405750,active_state)==0x28 ? 1:-1];
typedef char PlayerUpdatePositionOffset[offsetof(PlayerUpdateState_00405750,position)==0x30 ? 1:-1];
typedef char PlayerUpdateRadiusOffset[offsetof(PlayerUpdateState_00405750,collision_radius)==0x3C ? 1:-1];
#endif
