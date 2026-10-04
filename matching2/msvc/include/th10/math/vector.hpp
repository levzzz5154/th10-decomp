#ifndef TH10_MATH_VECTOR_HPP
#define TH10_MATH_VECTOR_HPP

// Float vectors with the arithmetic the interpolators use.

struct Vec2 {
    float x, y;

    Vec2() {}
    Vec2(float fx, float fy) { x = fx; y = fy; }

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(float f) const { return Vec2(x * f, y * f); }
};

struct Vec3 {
    float x, y, z;

    Vec3() {}
    Vec3(float fx, float fy, float fz) { x = fx; y = fy; z = fz; }

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float f) const { return Vec3(x * f, y * f, z * f); }
    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
};

#endif
