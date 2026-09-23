#include <math.h>
#include "th10/math/angle.hpp"
#include "th10/math/timer.hpp"

extern "C" float data_00470afc;
extern "C" float data_00470b04;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00476f78;
extern "C" double __cdecl atan2(double, double);

struct PolarVector2_00408750 {
    float x;
    float y;
    __declspec(noinline) void SetPolar(float angle, float scale);
};

struct PlayerAimTarget_00407EF0 {
    unsigned char reserved_000[0x3C0];
    float target_x;
    float target_y;
};
extern "C" PlayerAimTarget_00407EF0* data_00477834;

struct PlayerHomingState_00407EF0 {
    unsigned char reserved_000[0x3B4];
    float position_x;
    float position_y;
    float position_z;
    PolarVector2_00408750 velocity;
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
    float turn_limit_7CC;
    unsigned char reserved_7D0[0x0C];
    int homing_deadline_7DC;

    __declspec(noinline) void HomeTowardTarget();
};

// 0x00407EF0. Aim at the global player target, limit the per-frame turn, write
// the resulting velocity vector, and advance the embedded homing clock. The
// retail 0x00406408 edge supplies this object in ESI; whole-cluster/LTCG work
// is still needed before this ordinary member can replace that private entry.
void PlayerHomingState_00407EF0::HomeTowardTarget() {
    if (homing_timer.current < homing_deadline_7DC) {
        const double dx = (double)data_00477834->target_x - (double)position_x;
        const double dy = (double)data_00477834->target_y - (double)position_y;
        float target_angle;
        if (dy == data_00470b04 && dx == data_00470b04) {
            target_angle = 1.57079637f;
        } else {
            target_angle = (float)atan2(dy, dx);
        }

        target_angle = Angle_NormalizeSum(turn_limit_7CC, target_angle);
        const float turn_delta =
            WrappedAngleDifference(target_angle, angle_3E4) * turn_rate_7C8 *
            data_00476f78;
        angle_3E4 = Angle_NormalizeSum(angle_3E4, turn_delta);
        velocity.SetPolar(angle_3E4, scalar_3D8);
    } else {
        flags_43C &= ~0x04000000u;
    }

    homing_timer.previous = homing_timer.current;
    const float frame_scale = *homing_timer.speed;
    if (data_00470b68 < frame_scale && frame_scale < data_00470b64) {
        ++homing_timer.current;
        homing_timer.elapsed += data_00470afc;
    } else {
        homing_timer.elapsed = homing_timer.elapsed + frame_scale;
        homing_timer.current = (int)homing_timer.elapsed;
    }
}
