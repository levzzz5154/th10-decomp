#ifndef TH10_BOMB_STATE_HPP
#define TH10_BOMB_STATE_HPP
#include "th10/math/timer.hpp"
#include "th10/render/position_setter_pair.hpp"
#include "th10/game/player_update_score.hpp"
#include "th10/game/player_update_collision.hpp"
// The bomb (g_bomb, 0x004776EC) as its update and bullet-cancel pass
// see it: the animation and position use the position-setter types the
// update cluster needs. The full layout is Bomb in th10/game/bomb.hpp.
struct BombState {
    unsigned char reserved_000[0x14];
    FrameTimer timer;
    int active_state;
    PositionScriptId_004492f0 animation;
    PositionVector_004492f0 position;
    float collision_radius;
    __declspec(noinline) int Update();
    __declspec(noinline) int CancelBullets();
    void Step();
};
struct BombPlayerInput {
    unsigned char reserved_000[0x3788];
    int input_state;
    unsigned int flags;
};
struct BombAnimationValue {
    unsigned char reserved_000[0x40];
    float collision_radius;
};
extern "C" BombPlayerInput* g_card;
extern "C" CollisionEngine_00408100* data_004776f0;
extern "C" LaserManager_0041c800* g_laser_manager;
extern "C" int data_00474c68;
extern "C" float data_00470b0c, data_00470afc, data_00470d34, data_00470b4c, data_00470b48;
typedef char BombStateTimerOffset[offsetof(BombState,timer)==0x14 ? 1:-1];
typedef char BombStateStateOffset[offsetof(BombState,active_state)==0x28 ? 1:-1];
typedef char BombStatePositionOffset[offsetof(BombState,position)==0x30 ? 1:-1];
typedef char BombStateRadiusOffset[offsetof(BombState,collision_radius)==0x3C ? 1:-1];
#endif
