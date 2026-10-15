#ifndef TH10_PLAYER_HOMING_00407EF0_HPP
#define TH10_PLAYER_HOMING_00407EF0_HPP
#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
#include "th10/game/player.hpp"

struct PlayerHomingState {
    unsigned char reserved_000[0x3B4];
    float position_x;
    float position_y;
    float position_z;
    PolarVector2 velocity;
    float velocity_z;
    unsigned char reserved_3CC[0x0C];
    float scalar_3D8;
    unsigned char reserved_3DC[8];
    float angle_3E4;
    unsigned char reserved_3E8[0x54];
    unsigned int flags_43C;
    unsigned char reserved_440[0x374];
    FrameTimer homing_timer;
    float turn_rate_7C8;
    float heading_offset_7CC;
    unsigned char reserved_7D0[0x0C];
    int homing_deadline_7DC;

    __declspec(noinline) void HomeTowardTarget();
};

typedef char PlayerHoming_position_offset[offsetof(PlayerHomingState,position_x)==0x3B4 ? 1 : -1];
typedef char PlayerHoming_timer_offset[offsetof(PlayerHomingState,homing_timer)==0x7B4 ? 1 : -1];
typedef char PlayerHoming_deadline_offset[offsetof(PlayerHomingState,homing_deadline_7DC)==0x7DC ? 1 : -1];
typedef char PlayerHoming_size_check[sizeof(PlayerHomingState)==0x7E0 ? 1 : -1];
#endif
