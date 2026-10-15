#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00470c68;
extern "C" float data_00470c6c;
extern "C" float g_game_speed;
// 0x004076A0. While the death clock runs, turn the heading and grow the
// speed by the frame scale and refresh the velocity; at the deadline clear the
// shrink flag. Either way advance the embedded frame clock. The object arrives
// in ESI. The heading is written through a pointer so that the velocity
// refresh reads the stored field again, as retail does.
#pragma code_seg(".text$01acdeath")
void PlayerDeathShrinkState_004076A0::AdvanceDeathShrink() {
    if (death_timer.current >= death_deadline_6A4) {
        flags_43C &= ~0x20u;
    } else {
        float* heading = &angle_3E4;
        *heading = Angle_NormalizeSum(*heading, g_game_speed * angle_rate_694);
        scalar_3D8 = g_game_speed * fall_rate_690 + scalar_3D8;
        velocity.SetPolar(angle_3E4, scalar_3D8);
    }

    death_timer.previous = death_timer.current;
    if (*death_timer.speed > data_00470b68 && *death_timer.speed < data_00470b64) {
        ++death_timer.current;
        death_timer.elapsed += 1.0f;
    } else {
        death_timer.current = int(death_timer.elapsed = *(const volatile float*)death_timer.speed + death_timer.elapsed);
    }
}

#pragma code_seg()
