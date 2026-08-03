#include "th10/math/vector.hpp"

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

// 0x0041F800 - Convert a polar direction and length to Cartesian coordinates.
#ifdef _MSC_VER
__declspec(naked) void Vector2::SetPolar(float angle, float length) {
    // Retail uses FSINCOS with the destination pointer in ECX; the readable
    // fallback below keeps the host-side semantics.
    __asm {
        push ecx
        mov [esp], ecx
        mov eax, [esp]
        fld [esp+8]
        fsincos
        fmul [esp+0Ch]
        fstp dword ptr [eax]
        fmul [esp+0Ch]
        fstp dword ptr [eax+4]
        pop ecx
        ret 8
    }
}
#else
void Vector2::SetPolar(float angle, float length) {
    float cosine = (float)cos(angle);
    float sine = (float)sin(angle);
    x = cosine * length;
    y = sine * length;
}
#endif

// 0x004458B0 - Standalone polar-vector leaf used by the render helpers.
#ifdef _MSC_VER
__declspec(naked) void Vector2_SetPolar(Vector2* destination, float angle,
                                        float length) {
    __asm {
        push ecx
        mov [esp], ecx
        mov eax, [esp]
        fld [esp+8]
        fsincos
        fmul [esp+0Ch]
        fstp dword ptr [eax]
        fmul [esp+0Ch]
        fstp dword ptr [eax+4]
        pop ecx
        ret 8
    }
}
#else
void Vector2_SetPolar(Vector2* destination, float angle, float length) {
    destination->SetPolar(angle, length);
}
#endif
