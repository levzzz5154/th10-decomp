// Compiler context only; never selected as recovered game code.
#include "../../src/math/vec_subtract_00404d40.cpp"

#pragma code_seg(".text$03context")
int __stdcall VecSubtractCompilerContext(VecSubtractOperand** left, VecSubtractOperand** right,
                                         VecSubtractResult* result, int count) {
    while (count--) {
        result = Vec_Subtract(*left++, *right++, result);
    }
    return 0;
}
#pragma code_seg()
