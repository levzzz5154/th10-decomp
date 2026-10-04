#ifndef TH10_MATH_INTERPOLATOR_STEP_HPP
#define TH10_MATH_INTERPOLATOR_STEP_HPP

#include "th10/math/interpolator.hpp"

template <class T>
T Interpolator<T>::Step() {
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
        T current = value;
        value = current + target;
        return value;
    }
    if (mode == 17) {
        T current = value;
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
        T result = value * h1 + target * h2 + control * h3 + velocity * h4;
        return result;
    }
    float rate = Rate();
    T result = value + (target - value) * rate;
    return result;
}

#endif
