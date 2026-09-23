#include "th10/math/angle.hpp"
#include "th10/math/timer.hpp"

extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00476f78;

struct PolarVector2_00408750 {
    float x;
    float y;
    __declspec(noinline) void SetPolar(float angle, float scale);
};

struct PlayerDeathShrinkState_004076A0 {
    unsigned char reserved_000[0x3C0];
    PolarVector2_00408750 velocity;
    unsigned char reserved_3C8[0x10];
    float scalar_3D8;
    unsigned char reserved_3DC[8];
    float angle_3E4;
    unsigned char reserved_3E8[0x54];
    unsigned int flags_43C;
    unsigned char reserved_440[0x23C];
    FrameTimer death_timer;
    float fall_rate_690;
    float angle_rate_694;
    unsigned char reserved_698[0x0C];
    int death_deadline_6A4;

    __declspec(noinline) void AdvanceDeathShrink();
};

// 0x004076A0. Ease the angle and scalar while the death clock is active, clear
// the shrink flag at its deadline, and advance the embedded frame clock. The
// retail 0x004063AF edge supplies this object in ESI; whole-cluster/LTCG work
// is still needed before this ordinary member can replace that private entry.
void PlayerDeathShrinkState_004076A0::AdvanceDeathShrink() {
    if (death_timer.current < death_deadline_6A4) {
        angle_3E4 = Angle_NormalizeSum(
            angle_3E4, data_00476f78 * angle_rate_694);
        scalar_3D8 = data_00476f78 * fall_rate_690 + scalar_3D8;
        velocity.SetPolar(angle_3E4, scalar_3D8);
    } else {
        flags_43C &= ~0x20u;
    }

    death_timer.previous = death_timer.current;
    const float frame_scale = *death_timer.speed;
    if (data_00470b68 < frame_scale && frame_scale < data_00470b64) {
        ++death_timer.current;
        death_timer.elapsed += data_00470afc;
    } else {
        death_timer.elapsed = death_timer.elapsed + frame_scale;
        death_timer.current = (int)death_timer.elapsed;
    }
}
