// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00441e10.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall SubtractContext_00441e10(
        Vec_00441e10** results, Vec_00441e10** a, Vec_00441e10** b, int count) {
    for (int index = 0; index < count; ++index)
        Subtract_00441e10(results[index], a[index], b[index]);
}
#pragma code_seg()
