#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00470c68;
extern "C" float data_00470c6c;
extern "C" float data_00476f78;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// 0x004076A0. Ease the angle and scalar while the death clock is active, clear
// the shrink flag at its deadline, and advance the embedded frame clock. The
// retail 0x004063AF edge supplies this object in ESI; whole-cluster/LTCG work
// is still needed before this ordinary member can replace that private entry.
#pragma code_seg(".text$01acdeath")
void PlayerDeathShrinkState_004076A0::AdvanceDeathShrink() {
    if (death_timer.current >= death_deadline_6A4) {
        flags_43C &= ~0x20u;
    } else {
        angle_3E4 = Angle_NormalizeSum(angle_3E4, data_00476f78 * angle_rate_694);
        _ReadWriteBarrier();
        scalar_3D8 = data_00476f78 * fall_rate_690 + scalar_3D8;
        velocity.SetPolar(angle_3E4, scalar_3D8);
    }

    death_timer.previous = death_timer.current;
    if (*death_timer.speed > data_00470b68 && *death_timer.speed < data_00470b64) {
        ++death_timer.current;
        death_timer.elapsed += 1.0f;
    } else {
        death_timer.current = int(death_timer.elapsed += *death_timer.speed);
    }
}

#pragma code_seg()
