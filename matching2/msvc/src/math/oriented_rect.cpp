#include <math.h>

struct Point3_0041E4D0 {
    float x;
    float y;
    float z;
};

struct OrientedRect_0041E4D0 {
    unsigned char unknown_000[0x24];
    Point3_0041E4D0 center_024;
    unsigned char unknown_030[0x0C];
    float rotation_03c;
    float extent_x_040;
    float extent_y_044;

    __declspec(noinline) int IntersectsCircle(
        const Point3_0041E4D0* point,
        float radius) const;
};

// 0x0041E4D0 is referenced by data at 0x0046DA80, consistent with a
// vtable-style method entry. The target takes the receiver in ECX, the point
// and radius on the stack, and returns with RET 8.
int OrientedRect_0041E4D0::IntersectsCircle(
    const Point3_0041E4D0* point,
    float radius) const {
    const Point3_0041E4D0 offset = {
        point->x - center_024.x,
        point->y - center_024.y,
        point->z - center_024.z
    };
    Point3_0041E4D0 local = offset;

    // Keep the trigonometric calls as expressions sharing -rotation: this
    // source shape historically retained the target's FSIN/FCOS x87 block.
    local.x = offset.x * cos(-rotation_03c) -
              sin(-rotation_03c) * offset.y;
    local.y = sin(-rotation_03c) * offset.x +
              cos(-rotation_03c) * offset.y;

    if (local.x - radius <= extent_x_040 &&
        local.y - radius <= extent_y_044 * 0.5f &&
        0.0f <= local.x + radius &&
        extent_y_044 * -0.5f <= local.y + radius) {
        return 2;
    }
    return 0;
}
