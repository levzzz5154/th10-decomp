// 0x00421B90 FUN_00421b90
// Readable reconstruction of retail helper FUN_00421b90.
//
// See the header for the destination ABI note.  The readable body mirrors
// Ghidra's variable capture exactly so out, left, right may alias.

#include "th10/math/vector3_cross.hpp"

#ifdef _MSC_VER
__declspec(naked) void Vector3_Cross(
        Vector3* out, const Vector3* left, const Vector3* right) {
    __asm {
        sub esp, 0Ch
        fld dword ptr [ecx+8]
        fmul dword ptr [edx+4]
        fld dword ptr [edx+8]
        fmul dword ptr [ecx+4]
        fsubp st(1), st
        fstp dword ptr [esp]
        fld dword ptr [edx+8]
        fmul dword ptr [ecx]
        fld dword ptr [ecx+8]
        fmul dword ptr [edx]
        fsubp st(1), st
        fstp dword ptr [esp+4]
        fld dword ptr [edx]
        fmul dword ptr [ecx+4]
        fld dword ptr [ecx]
        mov ecx, eax
        fmul dword ptr [edx+4]
        mov edx, [esp]
        mov [ecx], edx
        mov edx, [esp+4]
        fsubp st(1), st
        mov [ecx+4], edx
        fstp dword ptr [esp+8]
        mov edx, [esp+8]
        mov [ecx+8], edx
        add esp, 0Ch
        ret
    }
}
#else
void Vector3_Cross(Vector3* out, const Vector3* left, const Vector3* right) {
    if (out == 0 || left == 0 || right == 0) return;
    const float left_x = left->x;
    const float left_y = left->y;
    const float left_z = left->z;
    const float right_x = right->x;
    const float right_y = right->y;
    const float right_z = right->z;
    out->x = left_y * right_z - left_z * right_y;
    out->y = left_z * right_x - left_x * right_z;
    out->z = left_x * right_y - left_y * right_x;
}
#endif
