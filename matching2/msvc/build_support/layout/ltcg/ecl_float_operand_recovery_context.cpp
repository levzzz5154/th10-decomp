// Compiler context only.
#include "../../../src/script/sptcmd/ecl_resolve_float_operand.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) float __stdcall EclFloatOperandContext(
        EclFloatVm** items, int selector, int count) {
    float result = 0;
    while (count--) result += (*items++)->ResolveFloatOperand(selector);
    return result;
}
#pragma code_seg()
