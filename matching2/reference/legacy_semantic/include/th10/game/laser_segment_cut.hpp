#pragma once

#include <cstdint>

// Logical view shared by the two infinite-laser cut paths at 0x0041EB00 and
// 0x0041EFA0. Retail samples the ray at 6 + 12*n units and preserves every
// uncut run as either the shortened original or a cloned segment.
struct LaserCutState {
    float origin[3];
    float angle;
    float length;
    float width;
    float distance_budget;
    int type;
    int16_t kind;
    int16_t colour;
    bool retired;
    float traveled;
    float length_limit;
};

struct LaserCutRegion {
    float center[3];
    float size[3];
};

struct LaserCutOps {
    void* context;
    void (*spawn_spark)(void*, const float position[3], int script);
    void (*spawn_item)(void*, const float position[3], int kind, int id,
                       float angle, float speed);
    int (*outside_viewport)(void*, const float position[3], float radius_x,
                            float radius_y);
    void (*clone_segment)(void*, const LaserCutState* segment);
};

// 0x0041EFA0: cut samples inside a circle.
int LaserCut_Circle(LaserCutState* laser, const float center[3], float radius,
                    int spawn_items, const LaserCutOps* ops);

// 0x0041EB00: cut samples inside the axis-aligned rectangle centered at
// region.center with full dimensions region.size.
int LaserCut_Rectangle(LaserCutState* laser, const LaserCutRegion* region,
                       int spawn_items, const LaserCutOps* ops);

int LaserTrim_Circle(LaserCutState* laser, const float center[3], float radius,
                     int spawn_items, const LaserCutOps* ops);
int LaserTrim_Rectangle(LaserCutState* laser, const LaserCutRegion* region,
                        int spawn_items, const LaserCutOps* ops);
