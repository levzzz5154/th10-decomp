#include "th10/math/timer.hpp"

extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00470c68;
extern "C" float data_00470c6c;

struct PolarVector2_00408750 {
    float x;
    float y;
    __declspec(noinline) void SetPolar(float angle, float scale);
};

// Offset model for the animation-clock leaf. The player arrives in ESI at the
// retail call edge; the whole-cluster LTCG route must bind that private entry.
struct PlayerAnimationState_004074B0 {
    unsigned char reserved_000[0x3C0];
    PolarVector2_00408750 velocity;
    float velocity_z;
    unsigned char reserved_3CC[0x0C];
    float speed_3D8;
    unsigned char reserved_3DC[8];
    float angle_3E4;
    unsigned char reserved_3E8[0x54];
    unsigned int flags_43C;
    unsigned char reserved_440[0x1D4];
    FrameTimer animation_timer;

    __declspec(noinline) void AdvanceAnimationFrame();
};

// 0x004074B0. Advance the animation timer and update the player's trail
// velocity while its frame counter is below the trail cutoff.
void PlayerAnimationState_004074B0::AdvanceAnimationFrame() {
    if (animation_timer.current <= 16) {
        const float trail_speed =
            data_00470c68 - animation_timer.elapsed * data_00470c6c + speed_3D8;
        velocity.SetPolar(angle_3E4, trail_speed);
    } else {
        flags_43C ^= 1u;
    }

    animation_timer.previous = animation_timer.current;
    const float frame_scale = *animation_timer.speed;
    if (data_00470b68 < frame_scale && frame_scale < data_00470b64) {
        ++animation_timer.current;
        animation_timer.elapsed += data_00470afc;
    } else {
        animation_timer.elapsed = animation_timer.elapsed + frame_scale;
        animation_timer.current = (int)animation_timer.elapsed;
    }
}
