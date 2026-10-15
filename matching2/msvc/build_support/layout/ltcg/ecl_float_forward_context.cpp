// Compiler context only.
#include "../../../src/game/enemy/ecl_forward_float_00412aa0.cpp"
#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) float __stdcall EclFloatForwardContext(
        EclFloatEntityVm** items, int selector, int count, float value) {
    float result = 0;
    while (count--) result += ForwardEclFloat(*items++, selector, value);
    return result;
}
#pragma code_seg()
