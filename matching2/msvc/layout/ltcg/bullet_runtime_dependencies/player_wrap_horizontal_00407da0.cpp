#include "th10/game/player_wrap.hpp"

// 0x00407DA0. Test the player position against its current bounds, wrap x
// across the playfield edge, advance the wrap timer, queue the wrap effect, and
// toggle the horizontal pose bit at a nonpositive timer count. Retail caller
// 0x00406533 supplies the object in EBX; whole-cluster/LTCG work is required
// to connect this ordinary member to that private call edge.
#pragma code_seg(".text$01lwrap")
void PlayerWrapHorizontalState_00407DA0::WrapHorizontal() {
    if (!position_3B4.OutsidePlayfieldInclusive(bounds_39C->extent_34, bounds_39C->extent_30)) {
        return;
    }

    if (position_3B4.x < data_00470b40) {
        position_3B4.x = bounds_39C->extent_34 + position_3B4.x + data_00470b54;
    } else if (position_3B4.x > data_00470b3c) {
        position_3B4.x = position_3B4.x - (bounds_39C->extent_34 + data_00470b54);
    } else {
        goto check_timer;
    }

    {
        wrap_timer_74C.Advance(-1.0f);
        if (effect_slot_458 >= 0)
            data_00492590.Queue(effect_slot_458, 0);
    }

check_timer:
    if (wrap_timer_74C.current <= 0)
        flags_43C ^= 0x00100000u;
}

#pragma code_seg()
