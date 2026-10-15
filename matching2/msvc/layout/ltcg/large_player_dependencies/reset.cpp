#include "th10/game/large_player_native.hpp"
#pragma code_seg(".text$a05body")
PlayerResetBlock::PlayerResetBlock() {
    PlayerResetSlot* embedded = &slot;
    PlayerReset_ClearFlag(&embedded->field_06C);
    PlayerReset_ClearFlag(&embedded->field_0B0);
    PlayerReset_ClearFlag(&embedded->field_0FC);
    PlayerReset_ClearFlag(&embedded->field_128);
    PlayerReset_ClearFlag(&embedded->field_174);
    PlayerReset_ClearFlag(&embedded->field_1B0);
    PlayerReset_ClearFlag(&embedded->field_1FC);
    PlayerReset_ClearFlag(&embedded->field_228);
    PlayerReset_ClearFlag(&embedded->field_378);
    memset(embedded, 0, sizeof(*embedded));
    embedded->field_384 = 0xffff;
    PlayerReset_ClearFlag(&timers[0].flags);
    PlayerReset_ClearFlag(&timers[1].flags);
    PlayerReset_ClearFlag(&timers[2].flags);
    PlayerPickupRecord5c* projectile = pickups;
    int count = 128;
    do { PlayerReset_ClearFlag(&projectile->timer.flags); ++projectile; } while (--count);
    unsigned int flags = animations[0].flags;
    PlayerAnimationRecord98* animation = animations;
    _ReadWriteBarrier();
    animation->flags = flags & ~1u;
    flags = (animation+1)->flags;
    ++animation;
    _ReadWriteBarrier();
    animation->flags = flags & ~1u;
    flags = (animation+1)->flags;
    ++animation;
    _ReadWriteBarrier();
    animation->flags = flags & ~1u;
    PlayerReset_ClearFlag(&(animation+1)->flags);
    PlayerIndicatorRecord6c* effect = indicators;
    count = 33;
    do { PlayerReset_ClearFlag(&effect->timer.flags); ++effect; } while (--count);
    PlayerReset_ClearFlag(&final_timer.flags);
    memset(this, 0, sizeof(*this));
    g_player = this;
}
#pragma code_seg()
