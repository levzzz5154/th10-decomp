#include "th10/game/pause_result_open_004231d0/player/item_collision/item_collision.hpp"
extern float g_playfield_min_x, g_playfield_max_x;
extern float g_playfield_min_y, g_playfield_max_y;
#pragma code_seg(".text$004086b0_fn")
int PlayfieldPoint::OutsideBounds(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= g_playfield_min_x) &&
        !(x - horizontal_margin >= g_playfield_max_x) &&
        !(y + vertical_margin <= g_playfield_min_y) &&
        !(y - vertical_margin >= g_playfield_max_y)) return 0;
    return 1;
}
#pragma code_seg()
