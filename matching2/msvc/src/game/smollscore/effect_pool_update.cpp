// 0x0042B9A0: the effect pool's update task (registered by 0x0042B4D0).
#include "th10/game/effect_pool_0042b6f0.hpp"

#pragma code_seg(".text$02wrapper")
int EffectPool_0042b6f0::Update() {
    return UpdateDrops();
}
#pragma code_seg()
