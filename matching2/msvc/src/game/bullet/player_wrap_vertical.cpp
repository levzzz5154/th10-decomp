// 0x00407E40: wrap an object that left the playfield through the top or the
// bottom to the opposite edge.
//
// The vertical twin of 0x00407DA0, with its own timer and flag. The object
// arrives in EBX.
#include "th10/game/player_wrap.hpp"

#pragma code_seg(".text$01mvertical")
void PlayerWrapHorizontalState::WrapVertical() {
    if (!position_3B4.OutsidePlayfieldInclusive(bounds_39C->extent_34, bounds_39C->extent_30))
        return;

    if (position_3B4.y < 0.0) {
        position_3B4.y = bounds_39C->extent_30 + position_3B4.y + 448.0f;
        vertical_timer_780.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            g_sound_manager.Queue(effect_slot_458, 0);
    } else if (position_3B4.y > 448.0f) {
        position_3B4.y = position_3B4.y - (bounds_39C->extent_30 + 448.0f);
        vertical_timer_780.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            g_sound_manager.Queue(effect_slot_458, 0);
    }
    if (vertical_timer_780.current <= 0)
        flags_43C ^= 0x00200000u;
}
#pragma code_seg()
