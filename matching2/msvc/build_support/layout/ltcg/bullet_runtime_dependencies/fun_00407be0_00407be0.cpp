// 0x00407BE0: reflect bullets at enabled playfield edges and limit rebounds.
#include "th10/platform/sound_queue.hpp"
#include "th10/game/bullet_runtime_deceleration.hpp"
#include "th10/math/angle.hpp"
extern "C" float data_00470b40, data_00470b3c, data_00470b04, data_00470b38;
extern "C" float data_00470b18, data_00470b58, data_00470b54, data_00470b50;
#pragma code_seg(".text$01jbounce")
void BulletRuntimeDeceleration::Bounce() {
    if (position_x <= data_00470b40 || position_x >= data_00470b3c || position_y <= data_00470b04 ||
        position_y >= data_00470b38) {
        int bounced = 0;
        if (sound_id >= 0)
            g_sound_manager.Queue(sound_id, 0);
        if (position_x < data_00470b40 || position_x >= data_00470b3c) {
            angle = Angle_NormalizeSum(-angle - data_00470b18, 0.0f);
            bounced = 1;
            position_x = (position_x < data_00470b40 ? data_00470b58 : data_00470b54) - position_x;
        }
        if (!(flags & 0x08000000u) &&
            (position_y < data_00470b04 || (position_y >= data_00470b38 && (flags & 0x400)))) {
            bounced = 1;
            angle = -angle;
            position_y = position_y < data_00470b04 ? -position_y
                                                    : data_00470b38 - position_y + data_00470b38;
        }
        if (rebound_speed > data_00470b50)
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
