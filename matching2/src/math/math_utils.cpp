// Readable reconstructions of the small register-ABI math helpers.  Callers
// that still use the retail EAX/ESI conventions remain supplied by the hybrid
// executable until their call sites receive typed interfaces too.
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"
#include "th10/math/quantized_vector.hpp"

extern uint32_t DAT_00476f78;

#ifdef _MSC_VER
extern "C" long __cdecl __ftol2(void);
#endif

void Timer_Set(FrameTimer* timer, int target) {
    if (!(timer->flags & 1)) {
        timer->previous = (int)0xFFF0BDC1;
        timer->current = 0;
        timer->elapsed = 0.0f;
        timer->speed = (const float*)&DAT_00476f78;
        timer->flags |= 1;
    }

    timer->current = target;
    timer->previous = target - 1;
    timer->elapsed = (float)target;
}

void Timer_Reset(FrameTimer* timer) {
    if (!(timer->flags & 1)) {
        timer->speed = (const float*)&DAT_00476f78;
        timer->flags |= 1;
    }

    timer->previous = -1;
    timer->current = 0;
    timer->elapsed = 0.0f;
}

struct ClampedValueOwner {
    uint8_t padding[0x58];
    int value;
};

void ClampValue(ClampedValueOwner* owner, int delta) {
    int value = owner->value + delta;
    if (value > 0x400) value = 0x400;
    if (value < -0x400) value = -0x400;
    owner->value = value;
}

// QuantizedVector and its byte-refresh helper now live in
// th10/math/quantized_vector.hpp so the parameter-block interpolator at
// 0x004049A0 can reuse these same two leaves.

QuantizedVector* Vec_Scale(
        QuantizedVector* destination, const QuantizedVector* source,
        float scalar) {
    for (int index = 0; index < 6; ++index) {
        destination->components[index] = source->components[index] * scalar;
    }
    QuantizedVector_UpdateBytes(destination);
    return destination;
}

// 0x00404D40 subtracts the EAX source from the ECX source. Older notes called
// this Vec_Add, but the retail arithmetic is unambiguously subtraction.
#ifdef _MSC_VER
__declspec(naked) QuantizedVector* Vec_Subtract(
        QuantizedVector* destination, const QuantizedVector* left,
        const QuantizedVector* right) {
    __asm {
        fld dword ptr [ecx+14h]
        fsub dword ptr [eax+14h]
        fld dword ptr [ecx+10h]
        fsub dword ptr [eax+10h]
        fld dword ptr [ecx+0Ch]
        fsub dword ptr [eax+0Ch]
        fld dword ptr [ecx+8]
        fsub dword ptr [eax+8]
        fld dword ptr [ecx+4]
        fsub dword ptr [eax+4]
        fld dword ptr [ecx]
        fsub dword ptr [eax]
        fstp dword ptr [esi]
        fstp dword ptr [esi+4]
        fst dword ptr [esi+8]
        fld st(1)
        fstp dword ptr [esi+0Ch]
        fld st(2)
        fstp dword ptr [esi+10h]
        fld st(3)
        fstp dword ptr [esi+14h]
        call __ftol2
        mov [esi+18h], al
        call __ftol2
        mov [esi+19h], al
        call __ftol2
        mov [esi+1Ah], al
        call __ftol2
        mov [esi+1Bh], al
        mov eax, esi
        ret
    }
}
#else
QuantizedVector* Vec_Subtract(
        QuantizedVector* destination, const QuantizedVector* left,
        const QuantizedVector* right) {
    for (int index = 0; index < 6; ++index) {
        destination->components[index] =
            left->components[index] - right->components[index];
    }
    QuantizedVector_UpdateBytes(destination);
    return destination;
}
#endif
