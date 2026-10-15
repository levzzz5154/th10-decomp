// 0x00407DA0: wrap an object that left the playfield sideways to the opposite
// edge.
//
// Each wrap spends one count of the wrap timer and plays the object's sound;
// once the timer has run out the horizontal wrap flag is toggled. The object
// arrives in EBX.
#include "th10/game/player_wrap.hpp"

#pragma code_seg(".text$01lwrap")
void PlayerWrapHorizontalState_00407DA0::WrapHorizontal() {
    if (!position_3B4.OutsidePlayfieldInclusive(bounds_39C->extent_34, bounds_39C->extent_30))
        return;

    if (position_3B4.x < -192.0f) {
        position_3B4.x = bounds_39C->extent_34 + position_3B4.x + 384.0f;
        wrap_timer_74C.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            data_00492590.Queue(effect_slot_458, 0);
    } else if (position_3B4.x > 192.0f) {
        position_3B4.x = position_3B4.x - (bounds_39C->extent_34 + 384.0f);
        wrap_timer_74C.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            data_00492590.Queue(effect_slot_458, 0);
    }
    if (wrap_timer_74C.current <= 0)
        flags_43C ^= 0x00100000u;
}
#pragma code_seg()
