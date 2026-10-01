#include "th10/game/player_wrap.hpp"
extern "C" double data_00470b70;
extern "C" float data_00470b38;
#pragma code_seg(".text$01mvertical")
void PlayerWrapHorizontalState_00407DA0::WrapVertical() {
    if (!position_3B4.OutsidePlayfieldInclusive(bounds_39C->extent_34, bounds_39C->extent_30))
        return;
    if (position_3B4.y < data_00470b70) {
        position_3B4.y = bounds_39C->extent_30 + position_3B4.y + data_00470b38;
    } else if (position_3B4.y > data_00470b38) {
        position_3B4.y = position_3B4.y - (bounds_39C->extent_30 + data_00470b38);
    } else {
        goto check_timer;
    }
    vertical_timer_780.Advance(-1.0f);
    if (effect_slot_458 >= 0)
        data_00492590.Queue(effect_slot_458, 0);
check_timer:
    if (vertical_timer_780.current <= 0)
        flags_43C ^= 0x00200000u;
}
#pragma code_seg()
