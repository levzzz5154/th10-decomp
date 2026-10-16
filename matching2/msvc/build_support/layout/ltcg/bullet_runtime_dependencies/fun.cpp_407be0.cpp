// 0x00407BE0: reflect bullets at enabled playfield edges and limit rebounds.
#include "th10/platform/sound_queue.hpp"
#include "th10/game/bullet_runtime_deceleration.hpp"
#include "th10/math/angle.hpp"
extern "C" float flt_neg192, flt_192, flt_0, flt_448;
extern "C" float flt_pi, flt_neg384, flt_384, flt_neg990;
#pragma code_seg(".text$01jbounce")
void BulletRuntimeDeceleration::Bounce() {
    if (position_x <= flt_neg192 || position_x >= flt_192 || position_y <= flt_0 ||
        position_y >= flt_448) {
        int bounced = 0;
        if (sound_id >= 0)
            g_sound_manager.Queue(sound_id, 0);
        if (position_x < flt_neg192 || position_x >= flt_192) {
            angle = Angle_NormalizeSum(-angle - flt_pi, 0.0f);
            bounced = 1;
            position_x = (position_x < flt_neg192 ? flt_neg384 : flt_384) - position_x;
        }
        if (!(flags & 0x08000000u) &&
            (position_y < flt_0 || (position_y >= flt_448 && (flags & 0x400)))) {
            bounced = 1;
            angle = -angle;
            position_y = position_y < flt_0 ? -position_y
                                                    : flt_448 - position_y + flt_448;
        }
        if (rebound_speed > flt_neg990)
            speed = rebound_speed;
        // This caller passes the stored binary32 value directly to the polar helper.
        velocity.SetPolar(angle, const_cast<const float&>(speed));
        if (bounced)
            ++bounce_count;
        if (bounce_count >= bounce_limit)
            flags &= 0xF7FFF3FFu;
    }
}
#pragma code_seg()
