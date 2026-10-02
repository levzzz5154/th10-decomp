// 0x004078E0: decelerate a bullet until its step runs out, then load the
// next speed and heading and restart the step timer.
#include <math.h>
#include "th10/math/angle.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" float data_00470b68, data_00470b64, data_00476f78;
#include "th10/game/bullet_runtime_deceleration.hpp"
extern "C" float data_00470b04;
#pragma code_seg(".text$01gease")
void BulletRuntimeDeceleration::EaseStep() {
    int length = duration;
    float magnitude;
    if (current >= length) {
        if (sound_id >= 0)
            data_00492590.Queue(sound_id, 0);
        if (++iteration >= limit)
            flags &= ~0x100u;
        angle = angle_step;
        float reset_speed = next_speed;
        speed = reset_speed;
        unsigned int initial_flags = timer_flags;
        magnitude = reset_speed;
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
        current = int(elapsed = *(const volatile float*)time_scale + elapsed);
    }
}
#pragma code_seg()
