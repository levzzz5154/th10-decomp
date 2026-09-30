#pragma once

#include <math.h>

struct Point3_OrientedRect {
    float x;
    float y;
    float z;

    Point3_OrientedRect() {}
    Point3_OrientedRect(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {}

    __forceinline Point3_OrientedRect operator-(const Point3_OrientedRect& other) const {
        return Point3_OrientedRect(x - other.x, y - other.y, z - other.z);
    }

    __forceinline Point3_OrientedRect operator+(const Point3_OrientedRect& other) const {
        return Point3_OrientedRect(x + other.x, y + other.y, z + other.z);
    }
};

// The cached value converts to float at each use. Keeping that conversion
// preserves retail's shared x87 sine/cosine calculation and the float type
// at each sine use.
struct OrientedRectSine {
    float value;

    OrientedRectSine(float angle) : value(sin(angle)) {}
    __forceinline operator float() const { return value; }
};

__forceinline Point3_OrientedRect RotateOrientedRectOffset(
    Point3_OrientedRect offset, float angle) {
    OrientedRectSine sine(angle);
    return Point3_OrientedRect(
        offset.x * cos(angle) - sine * offset.y,
        sine * offset.x + cos(angle) * offset.y,
        offset.z);
}
