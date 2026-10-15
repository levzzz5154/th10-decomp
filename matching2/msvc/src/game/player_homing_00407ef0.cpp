#include "th10/game/player_homing_00407ef0.hpp"
#include "th10/math/angle.hpp"
#include <math.h>
#include "th10/game/player.hpp"

extern "C" float data_00470b04, data_00470b64, data_00470b68, data_00476f78;

// Steer toward the target with an angular offset and scaled turn rate until
// the deadline, then clear the homing flag. The homing timer always advances.
#pragma code_seg(".text$01homing")
void PlayerHomingState_00407EF0::HomeTowardTarget() {
    if (homing_timer.current >= homing_deadline_7DC) {
        flags_43C &= ~0x04000000u;
    } else {
        const double dx =
            (double)g_player->position.x -
            (double)position_x;
        const double dy =
            (double)g_player->position.y -
            (double)position_y;
        float target_angle;
        if (dy == data_00470b04 && dx == data_00470b04) {
            // Retail uses a quarter turn for a zero-length direction.
            target_angle = 1.57079637f;
        } else {
            target_angle = (float)atan2(dy, dx);
        }

        angle_3E4 = Angle_NormalizeSum(angle_3E4,
            WrappedAngleDifference(Angle_NormalizeSum(heading_offset_7CC, target_angle),
                angle_3E4) * turn_rate_7C8 * data_00476f78);
        velocity.SetPolar(angle_3E4, scalar_3D8);
    }

    homing_timer.previous = homing_timer.current;
    if (*homing_timer.speed > data_00470b68 && *homing_timer.speed < data_00470b64) {
        ++homing_timer.current;
        homing_timer.elapsed += 1.0f;
    } else {
        // Preserve the pointed-clock read as the left operand of the x87 sum.
        homing_timer.current = int(homing_timer.elapsed =
            *reinterpret_cast<const volatile float*>(homing_timer.speed) +
            homing_timer.elapsed);
    }
}
#pragma code_seg()
