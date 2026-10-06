// 0x004267F0..0x004269C7: classify an object against a rotated rectangle.
//
// The object's position is taken relative to the rectangle's origin and
// rotated by -angle, so that the rectangle runs along +x. With the object's
// half size added on both sides:
//   * inside [0, length] along the rectangle and within half a width of the
//     centre line: the object is activated (unless a dialogue is running, the
//     object is in mode 2..4 or its countdown is still positive) -> 1;
//   * otherwise inside [0, length] and within 1.5 widths of the centre line
//     -> 2;
//   * otherwise -> 0.
//
// The object arrives in ECX and the origin in EAX.
//
// `lower` first holds the unrotated offset and is then reused for the lower
// corner; the rotation is written back into `rotated`. That sharing is what
// orders the two vectors in the frame (the compiler sorts stack slots by
// reference count).
#include "th10/game/trigger_region_004267f0.hpp"

#pragma code_seg(".text$30classifier")
int TriggerField_004267f0::ClassifyRotatedRegion(const Point3_OrientedRect* origin, float angle, float width,
                                                 float length) {
    Point3_OrientedRect rotated = position - *origin;
    Point3_OrientedRect lower = rotated;
    OrientedRectSine sine(-angle);
    rotated.x = lower.x * cos(-angle) - sine * lower.y;
    rotated.y = sine * lower.x + cos(-angle) * lower.y;

    lower = rotated - half_size;
    Point3_OrientedRect upper;
    upper = rotated + half_size;

    // Negated rejection tests, so that an unordered comparison does not
    // reject by itself.
    if (!(lower.x > length) && !(width * 0.5f < lower.y) && !(upper.x < 0.0f) && !(width * -0.5f > upper.y)) {
        if (data_0047770c != 0 && data_0047770c->active != 0)
            return 0;
        if (mode == 2 || mode == 4 || mode == 3)
            return 0;
        if (activation_countdown > 0)
            return 0;
        ActivateField_00426cf0(this);
        return 1;
    }
    if (!(lower.x > length) && !(upper.x < 0.0f) && !(width * 1.5f < lower.y) && !(width * -1.5f > lower.y))
        return 2;
    return 0;
}
#pragma code_seg()
