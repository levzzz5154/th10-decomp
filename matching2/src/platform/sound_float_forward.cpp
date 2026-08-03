#include "th10/platform/sound_float_forward.hpp"

#ifdef _MSC_VER
extern "C" double _floor(double);
#endif

// 0x00427C50 - Push one float through the sound layer's double-argument
// entry point. Retail widens the single-precision volume/pan operand to
// double on the x87 stack before tail-calling 0x00452FF0.
#ifdef _MSC_VER
__declspec(naked) void Sound_ForwardFloatAsDouble(
        float value, void (*forward)(double value)) {
    __asm {
        fld [esp+4]
        sub esp, 8
        fstp qword ptr [esp]
        call _floor
        add esp, 8
        ret 4
    }
}
#else
void Sound_ForwardFloatAsDouble(float value, void (*forward)(double value)) {
    if (forward != 0) forward((double)value);
}
#endif
