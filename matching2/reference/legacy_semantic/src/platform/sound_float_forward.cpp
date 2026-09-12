#include "th10/platform/sound_float_forward.hpp"


// 0x00427C50 - Push one float through the sound layer's double-argument
// entry point. Retail widens the single-precision volume/pan operand to
// double on the x87 stack before tail-calling 0x00452FF0.
void Sound_ForwardFloatAsDouble(float value, void (*forward)(double value)) {
    if (forward != 0) forward((double)value);
}
