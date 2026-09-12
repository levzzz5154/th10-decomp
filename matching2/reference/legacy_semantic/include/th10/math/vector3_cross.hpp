// 0x00421B90 FUN_00421b90
// Readable reconstruction of retail helper FUN_00421b90.
//
// FUN_00421b90 computes the 3-float cross product ``out = left x right``
// in place.  The retail ABI has the destination pointer carried in the
// preserved-EAX register across the call, so the readable signature
// reifies it as the first parameter.
//
// The retail drops the intermediate float copies straight into the
// destination slot, so the readable body mirrors Ghidra's variable
// capture exactly; both compute the canonical
//   out = (left.y * right.z - left.z * right.y,
//          left.z * right.x - left.x * right.z,
//          left.x * right.y - left.y * right.x)
// edge ordering.

#ifndef TH10_MATH_VECTOR3_CROSS_HPP
#define TH10_MATH_VECTOR3_CROSS_HPP

struct Vector3 {
    float x;
    float y;
    float z;
};

// Cross product of two 3-float vectors into ``out``.  Safe to call with
// any of out/left/right overlapping (the retail captures scalars first).
void Vector3_Cross(Vector3* out, const Vector3* left, const Vector3* right);

#endif  // TH10_MATH_VECTOR3_CROSS_HPP