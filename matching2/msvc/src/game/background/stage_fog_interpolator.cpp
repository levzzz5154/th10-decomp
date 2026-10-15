#include "th10/math/interpolator.hpp"
#include "th10/render/stage_fog.hpp"

// 0x004049A0: Interpolator<StageFog>::Step. The interpolator arrives in EBX
// and the result is written through the one stack argument. The fog record
// has its own version of the step: its results are assigned to a declared
// record, and the eased blend adds the start value last.
#pragma code_seg(".text$004049a0_fn")
template <>
StageFog Interpolator<StageFog>::Step() {
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
        StageFog current = value;
        value = current + target;
        return value;
    }
    if (mode == 17) {
        StageFog current = value;
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
        StageFog result;
        result = value * h1 + target * h2 + control * h3 + velocity * h4;
        return result;
    }
    float rate = Rate();
    StageFog result;
    result = (target - value) * rate + value;
    return result;
}
#pragma code_seg()
