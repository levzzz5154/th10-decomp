// 0x004076A0: BulletExCurve::StepCurve — enemy-bullet Ex-transform curve &
// acceleration (flags +0x43C bit 0x20): turns angle_3E4 and scales speed until
// the deadline, then clears bit 0x20 and ticks the embedded timer.
#include "th10/game/player_motion_helpers.hpp"
extern "C" float flt_1;
extern "C" float flt_1_01;
extern "C" float flt_0_99;
extern "C" float flt_5;
extern "C" float flt_0_3125;
extern "C" float g_game_speed;
// Native LTCG passes the bullet in ESI; writing heading through a pointer
// ensures velocity.SetPolar re-reads the stored field, matching retail.
#pragma code_seg(".text$01acdeath")
void BulletExCurve::StepCurve() {
    if (death_timer.current >= death_deadline_6A4) {
        flags_43C &= ~0x20u;
    } else {
        float* heading = &angle_3E4;
        *heading = Angle_NormalizeSum(*heading, g_game_speed * angle_rate_694);
        scalar_3D8 = g_game_speed * fall_rate_690 + scalar_3D8;
        velocity.SetPolar(angle_3E4, scalar_3D8);
    }

    death_timer.previous = death_timer.current;
    if (*death_timer.speed > flt_0_99 && *death_timer.speed < flt_1_01) {
        ++death_timer.current;
        death_timer.elapsed += 1.0f;
    } else {
        death_timer.current = int(death_timer.elapsed = *(const volatile float*)death_timer.speed + death_timer.elapsed);
    }
}

#pragma code_seg()
