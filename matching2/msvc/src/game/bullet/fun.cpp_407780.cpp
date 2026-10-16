// 0x00407780: turn by a fixed angle and decelerate between speed resets.
#include "th10/platform/sound_queue.hpp"
extern "C" float flt_0_99, flt_1_01, g_game_speed;
#include "th10/game/bullet_deceleration.hpp"
#pragma code_seg(".text$01bullet")
void BulletDeceleration::TurnStep() {
    int length = duration;
    float magnitude;
    if (current >= length) {
        if (sound_id >= 0)
            g_sound_manager.Queue(sound_id, 0);
        if (++iteration >= limit)
            flags &= ~0x40u;
        angle = angle_step + angle;
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
        float step = *time_scale;
        current = int(elapsed = step + elapsed);
    }
}
#pragma code_seg()
