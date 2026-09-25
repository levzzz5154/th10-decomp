#include "th10/game/entity.hpp"

// 0x00421B90..0x00421BDC: computes right cross left.
// Retail receives destination in EAX, left in ECX, and right in EDX.
// The current image has no incoming references to this private ABI entry.
extern "C" void __cdecl asm_Vector3_Cross_00421b90(
    Vector3* destination, const Vector3* left, const Vector3* right) {
    // Stage every component before writing: destination may alias an input.
    const float x = left->z * right->y - right->z * left->y;
    const float y = right->z * left->x - left->z * right->x;
    const float z = right->x * left->y - left->x * right->y;
    destination->x = x;
    destination->y = y;
    destination->z = z;
}
