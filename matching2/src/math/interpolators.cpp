// Embedded interpolator ticks: 0x00404610, 0x00441AD0, 0x00441600, 0x00441950.
#include "th10/math/interpolators.hpp"
#include "th10/math/easing.hpp"
#include "th10/math/retail_numeric.hpp"

namespace {
// The retail timer keeps its fractional field separately from the integer
// completion clock. FST preserves the wide sum for the integer conversion.
template<class State> bool Complete(State* s) {
    if (s->duration <= 0) return false;
    if (0.99f < s->speed && s->speed < 1.01f) {
        s->elapsed = Retail_AddI32(s->elapsed, 1);
        s->elapsed_fraction += 1.0f;
    } else {
        const long double sum = static_cast<long double>(s->elapsed_fraction) + s->speed;
        s->elapsed_fraction = static_cast<float>(sum);
        s->elapsed = Retail_TruncateI32(sum);
    }
    if (s->elapsed < s->duration) return false;
    s->elapsed = s->duration;
    s->elapsed_fraction = static_cast<float>(s->duration);
    s->duration = 0;
    return true;
}

void Hermite(float t, float basis[4]) {
    const float u = 1.0f - t;
    basis[0] = (1.0f + t + t) * u * u;
    basis[1] = (3.0f - (t + t)) * t * t;
    basis[2] = u * u * t;
    basis[3] = (t - 1.0f) * t * t;
}

int Difference(int target, int start) {
    return Retail_I32Bits(static_cast<unsigned int>(target) - static_cast<unsigned int>(start));
}

} // namespace

// 0x00404610 - Interp3F_Tick
int Interp3F_Tick(Interp3F* s) {
    if (Complete(s)) {
        for (int i = 0; i < 3; ++i)
            s->position[i] = s->mode == 7 ? s->start[i] : s->target[i];
        return 0;
    }
    if (s->mode == 7 || s->mode == 17) {
        for (int i = 0; i < 3; ++i) {
            s->start[i] += s->mode == 7 ? s->target[i] : s->acceleration[i];
            if (s->mode == 17) s->acceleration[i] += s->target[i];
            s->position[i] = s->start[i];
        }
        return 1;
    }
    const float t = s->elapsed_fraction / static_cast<float>(s->duration);
    if (s->mode == 8) {
        float b[4]; Hermite(t, b);
        for (int i = 0; i < 3; ++i)
            s->position[i] = b[0] * s->start[i] + b[1] * s->target[i] +
                             b[2] * s->velocity[i] + b[3] * s->acceleration[i];
    } else {
        const float eased = Easing_Evaluate(s->mode, s->elapsed_fraction, static_cast<float>(s->duration));
        for (int i = 0; i < 3; ++i)
            s->position[i] = s->start[i] + (s->target[i] - s->start[i]) * eased;
    }
    return 1;
}

// 0x00441AD0 - Interp2F_Tick
int Interp2F_Tick(Interp2F* s) {
    if (Complete(s)) {
        for (int i = 0; i < 2; ++i) s->value[i] = s->mode == 7 ? s->start[i] : s->target[i];
        return 0;
    }
    if (s->mode == 7 || s->mode == 17) {
        for (int i = 0; i < 2; ++i) {
            s->start[i] += s->mode == 7 ? s->target[i] : s->acceleration[i];
            if (s->mode == 17) s->acceleration[i] += s->target[i];
            s->value[i] = s->start[i];
        }
        return 1;
    }
    if (s->mode == 8) {
        float b[4]; Hermite(s->elapsed_fraction / static_cast<float>(s->duration), b);
        for (int i = 0; i < 2; ++i)
            s->value[i] = b[0] * s->start[i] + b[1] * s->target[i] +
                          b[2] * s->velocity[i] + b[3] * s->acceleration[i];
    } else {
        const float eased = Easing_Evaluate(s->mode, s->elapsed_fraction, static_cast<float>(s->duration));
        for (int i = 0; i < 2; ++i) s->value[i] = s->start[i] + (s->target[i] - s->start[i]) * eased;
    }
    return 1;
}

// 0x00441600 - Interp3I_Tick
int Interp3I_Tick(Interp3I* s) {
    if (Complete(s)) {
        for (int i = 0; i < 3; ++i) s->value[i] = s->mode == 7 ? s->start[i] : s->target[i];
        return 0;
    }
    if (s->mode == 7 || s->mode == 17) {
        for (int i = 0; i < 3; ++i) {
            s->start[i] = Retail_AddI32(s->start[i], s->mode == 7 ? s->target[i] : s->acceleration[i]);
            if (s->mode == 17) s->acceleration[i] = Retail_AddI32(s->acceleration[i], s->target[i]);
            s->value[i] = s->start[i];
        }
        return 1;
    }
    if (s->mode == 8) {
        float b[4]; Hermite(s->elapsed_fraction / static_cast<float>(s->duration), b);
        // 0x441E50 truncates each scaled vector before the integer sums.
        for (int i = 0; i < 3; ++i) {
            int v = Retail_TruncateI32(static_cast<long double>(s->start[i]) * b[0]);
            v = Retail_AddI32(v, Retail_TruncateI32(static_cast<long double>(s->target[i]) * b[1]));
            v = Retail_AddI32(v, Retail_TruncateI32(static_cast<long double>(s->velocity[i]) * b[2]));
            s->value[i] = Retail_AddI32(v, Retail_TruncateI32(static_cast<long double>(s->acceleration[i]) * b[3]));
        }
    } else {
        const float eased = Easing_Evaluate(s->mode, s->elapsed_fraction, static_cast<float>(s->duration));
        for (int i = 0; i < 3; ++i)
            s->value[i] = Retail_AddI32(s->start[i], Retail_TruncateI32(static_cast<long double>(Difference(s->target[i], s->start[i])) * eased));
    }
    return 1;
}

// 0x00441950 - Interp1I_Tick
int Interp1I_Tick(Interp1I* s) {
    if (Complete(s)) {
        s->value = s->mode == 7 ? s->start : s->target;
        return 0;
    }
    if (s->mode == 7 || s->mode == 17) {
        s->start = Retail_AddI32(s->start, s->mode == 7 ? s->target : s->acceleration);
        if (s->mode == 17) s->acceleration = Retail_AddI32(s->acceleration, s->target);
        s->value = s->start;
        return 1;
    }
    if (s->mode == 8) {
        float b[4]; Hermite(s->elapsed_fraction / static_cast<float>(s->duration), b);
        s->value = Retail_TruncateI32(static_cast<long double>(s->start) * b[0] +
            static_cast<long double>(s->target) * b[1] + static_cast<long double>(s->velocity) * b[2] +
            static_cast<long double>(s->acceleration) * b[3]);
    } else {
        const float eased = Easing_Evaluate(s->mode, s->elapsed_fraction, static_cast<float>(s->duration));
        // The scalar variant adds the start before __ftol2.
        s->value = Retail_TruncateI32(static_cast<long double>(Difference(s->target, s->start)) * eased + s->start);
    }
    return 1;
}
