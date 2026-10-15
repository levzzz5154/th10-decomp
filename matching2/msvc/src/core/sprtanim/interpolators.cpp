// 0x00441600: frame interpolation of a three-component integer colour.
#include "th10/math/interpolator.hpp"
#include "th10/math/int3.hpp"

// Linear interpolation expands its scale directly; Hermite keeps the four
// calls to the shared integer scaler at 0x00441E50.
__forceinline Int3 InterpolateLinear(const Int3& start, const Int3& end, float rate) {
    return start + (end - start).Scale(rate);
}

#pragma code_seg(".text$00441600_fn")
template <>
Int3 Interpolator<Int3>::Step() {
    if (duration > 0) {
        timer.TickInline();
        if (timer.current >= duration) {
            timer.Set(duration);
            duration = 0;
            if (mode != 7)
                return target;
            return value;
        }
    }
    if (mode == 7) {
        Int3 current = value;
        value = current + target;
        return value;
    }
    if (mode == 17) {
        Int3 current = value;
        value = current + velocity;
        velocity = velocity + target;
        return value;
    }
    if (mode == 8) {
        float t = timer.elapsed / duration;
        float h1 = (1.0f + 2.0f * t) * (t - 1.0f) * (t - 1.0f);
        float h2 = (3.0f - 2.0f * t) * t * t;
        float h3 = (1.0f - t) * (1.0f - t) * t;
        float h4 = (t - 1.0f) * t * t;
        Int3 result = value * h1 + target * h2 + control * h3 + velocity * h4;
        return result;
    }
    float rate = Rate();
    Int3 result = InterpolateLinear(value, target, rate);
    return result;
}
