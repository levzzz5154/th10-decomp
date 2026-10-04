#pragma once

// The two-component motion vector used by the bullet trajectory interpolator.
struct TrajectoryVec2 {
    float x, y;

    TrajectoryVec2() {}
    TrajectoryVec2(float fx, float fy) { x = fx; y = fy; }

    TrajectoryVec2 operator+(const TrajectoryVec2& v) const { return TrajectoryVec2(x + v.x, y + v.y); }
    TrajectoryVec2 operator-(const TrajectoryVec2& v) const { return TrajectoryVec2(x - v.x, y - v.y); }
    TrajectoryVec2 operator*(float f) const { return TrajectoryVec2(x * f, y * f); }
};
