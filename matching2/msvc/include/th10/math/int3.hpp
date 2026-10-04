#ifndef TH10_MATH_INT3_HPP
#define TH10_MATH_INT3_HPP

// Integer colour vector. Each scaled component truncates separately.
struct Int3 {
    int x, y, z;
    Int3() {}
    Int3(int ix, int iy, int iz) { x = ix; y = iy; z = iz; }
    Int3 operator+(const Int3& v) const {
        int rx = x + v.x; int ry = y + v.y; int rz = z + v.z;
        return Int3(rx, ry, rz);
    }
    Int3 operator-(const Int3& v) const {
        int rx = x - v.x; int ry = y - v.y; int rz = z - v.z;
        return Int3(rx, ry, rz);
    }
    __forceinline Int3 Scale(float f) const {
        int rx = int(x * f); int ry = int(y * f); int rz = int(z * f);
        return Int3(rx, ry, rz);
    }
    __declspec(noinline) Int3 operator*(float f) const;
};

#pragma code_seg(".text$00441e50_fn")
inline Int3 Int3::operator*(float f) const { return Scale(f); }
#pragma code_seg()


#endif
