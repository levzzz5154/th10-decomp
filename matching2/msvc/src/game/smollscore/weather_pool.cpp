#include "th10/game/effect_pool_0042b6f0.hpp"

extern "C" float data_00476f78;
extern "C" float data_00470b0c;
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;

__forceinline void EffectTimer_0042b6f0::Tick() {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        current++;
        elapsed += 1.0f;
    } else {
        float sum = elapsed;
        sum += *speed;
        elapsed = sum;
        current = int(sum);
    }
}

#pragma code_seg(".text$01drops")
int EffectPool_0042b6f0::UpdateDrops() {
    for (int index = 0; index < 0x2D3; index++) {
        EffectDrop_0042b6f0* drop = &drops[index];
        if (!drop->active) continue;
        drop->position -= data_00470b0c * data_00476f78;
        drop->timer.Tick();
        if (drop->timer.current > 60) drop->active = 0;
    }
    return 1;
}
#pragma code_seg()
