// 0x00407A30: aim toward the player and decelerate between speed resets.
#include <math.h>
#include "th10/math/angle.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" float flt_0_99, flt_1_01, g_game_speed;
#include "th10/game/bullet_deceleration.hpp"
#include "th10/game/player.hpp"
extern "C" float flt_0;
#pragma code_seg(".text$01haim")
void BulletDeceleration::AimStep() {
    int length = duration;
    float magnitude;
    if (current >= length) {
        if (sound_id >= 0)
            g_sound_manager.Queue(sound_id, 0);
        if (++iteration >= limit)
            flags &= ~0x80u;
        double dx = g_player->position.x - position_x;
        double dy = g_player->position.y - position_y;
        float heading;
        if (dy == flt_0 && dx == flt_0)
            heading = 1.57079637f;
        else
            heading = (float)atan2(dy, dx);
        angle = Angle_NormalizeSum(heading, angle_step);
        magnitude = speed = next_speed;
        unsigned int initial_flags = timer_flags;
        if (!(initial_flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0;
            time_scale = &g_game_speed;
            timer_flags = initial_flags | 1;
        }
        current = 0;
        elapsed = 0;
        previous = -1;
    } else {
        float initial_speed = speed;
        magnitude = initial_speed - initial_speed * elapsed / length;
    }
    velocity.SetPolar(angle, magnitude);
    previous = current;
    if (*time_scale > flt_0_99 && *time_scale < flt_1_01) {
        ++current;
        elapsed += 1.0f;
    } else {
        const volatile float& old_elapsed = elapsed;
        current = int(elapsed = old_elapsed + *(const float*)time_scale);
    }
}
#pragma code_seg()
