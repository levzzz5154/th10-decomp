#include "th10/source_views/entity_cacea2_0.hpp"
int32_t PlayfieldPoint::OutsidePlayfield(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= -64.0f || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}


#include "th10/source_views/entity_cacea2_0.hpp"
int32_t PlayfieldPoint::OutsidePlayfieldInclusive(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= g_playfield_min_y || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

