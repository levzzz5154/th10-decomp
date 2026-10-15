// 0x0041F670: GrowLaser::HitTestCircle (vtable 0x0046DA10 slot 0x20): does a circle touch the
// laser's oriented rectangle.
#include "th10/math/oriented_rect_contact.hpp"

struct GrowLaser {
    unsigned char unknown_000[0x24];
    Point3_OrientedRect center_024;
    unsigned char unknown_030[0x0C];
    float rotation_03c;
    float extent_x_040;
    float extent_y_044;

    __declspec(noinline) int HitTestCircle(
        const Point3_OrientedRect* point, float radius) const;
};

// 0x0041F670..0x0041F751. The receiver is in ECX; point and radius are on
// the stack. Return 2 for an overlap and 0 otherwise, with RET 8.
int GrowLaser::HitTestCircle(
    const Point3_OrientedRect* point, float radius) const {
    Point3_OrientedRect offset = *point - center_024;
    Point3_OrientedRect local = RotateOrientedRectOffset(offset, -rotation_03c);
    Point3_OrientedRect lower = local - Point3_OrientedRect(radius, radius, 0.0f);
    Point3_OrientedRect upper = local + Point3_OrientedRect(radius, radius, 0.0f);

    // Use negated rejection tests so unordered comparisons retain retail's
    // behavior: a NaN does not by itself reject the overlap.
    if (!(lower.x > extent_x_040) &&
        !(extent_y_044 * 0.5f < lower.y) &&
        !(upper.x < 0.0f) &&
        !(extent_y_044 * -0.5f > upper.y)) {
        return 2;
    }
    return 0;
}
