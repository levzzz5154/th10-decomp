#include <cassert>
#include <limits>

#define __declspec(attribute)
#define __stdcall
#define __cdecl
#define __fastcall
#include "../msvc/src/game/playfield_bounds.cpp"

float g_playfield_min_x = -10.0f;
float g_playfield_max_x = 10.0f;
float g_playfield_min_y = -8.0f;
float g_playfield_max_y = 8.0f;

static void expect(float x, float y, float half_width, float half_height,
                   int expected) {
    PlayfieldPoint point = {x, y};
    assert(point.OutsideBounds(half_width, half_height) == expected);
}

int main() {
    expect(0.0f, 0.0f, 1.0f, 1.0f, 0);

    // Touching any boundary is outside; one representable step inward is not.
    expect(-11.0f, 0.0f, 1.0f, 1.0f, 1);
    expect(11.0f, 0.0f, 1.0f, 1.0f, 1);
    expect(0.0f, -9.0f, 1.0f, 1.0f, 1);
    expect(0.0f, 9.0f, 1.0f, 1.0f, 1);
    expect(-10.999f, 0.0f, 1.0f, 1.0f, 0);
    expect(10.999f, 0.0f, 1.0f, 1.0f, 0);
    expect(0.0f, -8.999f, 1.0f, 1.0f, 0);
    expect(0.0f, 8.999f, 1.0f, 1.0f, 0);
    expect(-11.001f, 0.0f, 1.0f, 1.0f, 1);
    expect(11.001f, 0.0f, 1.0f, 1.0f, 1);

    const float nan = std::numeric_limits<float>::quiet_NaN();
    expect(nan, 0.0f, 1.0f, 1.0f, 0);
    expect(0.0f, nan, 1.0f, 1.0f, 0);
    expect(0.0f, 0.0f, nan, 1.0f, 0);
    expect(0.0f, 0.0f, 1.0f, nan, 0);
}
