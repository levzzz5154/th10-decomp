// 0x004188A0: add lives to the stock, capped at nine.
//
// An extend that fits plays the extend sound and restarts the extend banner;
// either way the side panel then shows the new number of life icons. The
// counters arrive in EAX and the amount in ECX.
#include "th10/game/life_stock_add_004188a0.hpp"

#pragma code_seg(".text$004188a0_fn")
void RunCounters_004188a0::AddLives(int amount) {
    lives += amount;
    if (lives > 9) {
        lives = 9;
    } else {
        data_00492590.Queue(44, 0);
        AnimationHandle_004188a0* banner = &data_0047770c->extend_banner;
        data_00491c10->MarkForRemoval(*banner);
        banner->value = 0;
        AnimationHandle_004188a0 created;
        *banner = *reinterpret_cast<AnimationHandle_004188a0*>(
            AnimationManager_CreatePrimaryBack_00448d00(
                data_0047770c->animation_resource, reinterpret_cast<void**>(&created), 75, 15));
    }
    data_0047770c->SetActiveCount(data_00474c40.lives);
}

// 0x00418930: add power, capped at 100.
//
// Reaching the cap restarts the banner with the full power script. The result
// tells whether the power level, a step of 20, changed. The counters arrive
// in EAX and the amount on the stack.
#pragma code_seg(".text$00418930_fn")
int RunCounters_004188a0::AddPower(int amount) {
    if (power >= 100)
        return 0;
    power += amount;
    if (power > 100) {
        power = 100;
        AnimationHandle_004188a0* banner = &data_0047770c->extend_banner;
        data_00491c10->MarkForRemoval(*banner);
        banner->value = 0;
        AnimationHandle_004188a0 created;
        *banner = *reinterpret_cast<AnimationHandle_004188a0*>(
            AnimationManager_CreatePrimaryBack_00448d00(
                data_0047770c->animation_resource, reinterpret_cast<void**>(&created), 73, 15));
    }
    return (power - (short)amount) / 20 != power / 20;
}
#pragma code_seg()
