#include "th10/source_views/playfield_bounds_7c91ed_0.hpp"
#include "th10/source_views/playfield_bounds_7c91ed_1.hpp"
#include "th10/source_views/playfield_bounds_7c91ed_2.hpp"
int SmollScorePosition::OutsideViewport(float horizontal_margin,
                                        float vertical_margin) const {
    if (!(x + horizontal_margin <= g_playfield_min_x) &&
        !(x - horizontal_margin >= g_playfield_max_x) &&
        !(y + vertical_margin <= g_playfield_min_y) &&
        !(y - vertical_margin >= g_playfield_max_y))
        return 0;
    return 1;
}
