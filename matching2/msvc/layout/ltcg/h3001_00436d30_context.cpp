#include "../../src/unidentified/FUN_00436d30_00436d30.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl H3001Context_00436d30(
        ColorAccumulator_00436d30 *result,
        unsigned int *count,
        const ColorRecord_00436d30 *record) {
    asm_FUN_00436d30_00436d30(result, count, record);
    return (int)result->red;
}
#pragma code_seg()
