#include "th10/render/anm_distance_color.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>

int main() {
    const float position[3] = {0.0f, 0.0f, 10.0f};
    const float camera[3] = {0.0f, 0.0f, 0.0f};
    const unsigned char tint[4] = {128, 128, 128, 128};
    uint32_t output = 0;
    assert(AnmDistanceColor_Apply(
               0xFF804020u, position, camera, 0, tint,
               20.0f, 40.0f, 0xFF000000u, &output) == 0);
    assert(output == 0xFF804020u);

    const float far_position[3] = {0.0f, 0.0f, 30.0f};
    assert(AnmDistanceColor_Apply(
               0xFF804020u, far_position, camera, 0, tint,
               20.0f, 40.0f, 0xFF000000u, &output) == 0);
    assert((output & 0xFF000000u) == 0x7F000000u);
    assert((output & 0x00FFFFFFu) == 0x402010u);

    assert(AnmDistanceColor_Apply(
               0xFF804020u, position, camera, 1, tint,
               20.0f, 40.0f, 0xFF000000u, &output) == 0);
    assert(output == 0xFF804020u);

    const float beyond[3] = {0.0f, 0.0f, 50.0f};
    assert(AnmDistanceColor_Apply(
               0xFF804020u, beyond, camera, 0, tint,
               20.0f, 40.0f, 0xFF000000u, &output) != 0);
    std::puts("ANM_DISTANCE_COLOR_PASS");
    return 0;
}
