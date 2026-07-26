// Readable reconstructions of the small register-ABI math helpers.  Callers
// that still use the retail EAX/ESI conventions remain supplied by the hybrid
// executable until their call sites receive typed interfaces too.
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"
#include "th10/math/quantized_vector.hpp"

extern uint32_t DAT_00476f78;

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
