// Compiler context only.
#include "../../src/script/ecl_resolve_float_operand_0044fe40.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) float __stdcall EclFloatOperandContext(
        EclFloatVm** items, int selector, int count) {
    float result = 0;
    while (count--) result += (*items++)->ResolveFloatOperand(selector);
    return result;
}
#pragma code_seg()
