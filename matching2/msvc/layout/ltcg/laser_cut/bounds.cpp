#include "types.hpp"
extern float g_playfield_min_x,g_playfield_max_x,g_playfield_min_y,g_playfield_max_y;
#pragma code_seg(".text$f0041f7a0F")
int CutVector::IsPartiallyOutside(float horizontal,float vertical) const {
    if (!(x+horizontal<=g_playfield_min_x) && !(x-horizontal>=g_playfield_max_x) &&
        !(y+vertical<=g_playfield_min_y) && !(y-vertical>=g_playfield_max_y)) return 0;
    return 1;
}
#pragma code_seg()
