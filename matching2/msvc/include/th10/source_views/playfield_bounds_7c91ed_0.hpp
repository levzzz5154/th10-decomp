#pragma once
struct PlayfieldPoint {
    float x;
    float y;

    int OutsideBounds(float horizontal_margin, float vertical_margin) const;
};

struct ViewportPosition {
    float x;
    float y;

    int IsPartiallyOutside(float horizontal_margin,
                           float vertical_margin) const;
};

struct SmollScorePosition {
    float x;
    float y;

    int OutsideViewport(float horizontal_margin, float vertical_margin) const;
};

extern float g_playfield_min_x;
extern float g_playfield_max_x;
extern float g_playfield_min_y;
extern float g_playfield_max_y;

// 0x004086B0: report whether a point touches or crosses the playfield limits
// after expanding them by the supplied margins. The negated comparisons
// preserve retail's unordered behavior: a NaN coordinate or margin is inside.
