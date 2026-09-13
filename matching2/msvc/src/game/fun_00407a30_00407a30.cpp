// 0x00407A30: aim toward the player and decelerate between speed resets.
#include <math.h>
#include "th10/math/angle.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" float data_00470b68, data_00470b64, data_00476f78;
#include "th10/game/bullet_deceleration.hpp"
struct AimTarget {
    char reserved[0x3C0];
    float x, y;
};
extern "C" AimTarget* data_00477834;
extern "C" float data_00470b04;
#pragma code_seg(".text$01haim")
void BulletDeceleration::AimStep() {
    int length = duration;
    float magnitude;
    if (current >= length) {
        if (sound_id >= 0)
            data_00492590.Queue(sound_id, 0);
        if (++iteration >= limit)
            flags &= ~0x80u;
        double dx = data_00477834->x - position_x;
        double dy = data_00477834->y - position_y;
        float heading;
        if (dy == data_00470b04 && dx == data_00470b04)
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
            time_scale = &data_00476f78;
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
    if (*time_scale > data_00470b68 && *time_scale < data_00470b64) {
        ++current;
        elapsed += 1.0f;
    } else {
        const volatile float& old_elapsed = elapsed;
        current = int(elapsed = old_elapsed + *(const float*)time_scale);
    }
}
#pragma code_seg()
