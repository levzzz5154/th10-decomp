// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_441e10.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall SubtractContext_00441e10(
        Vec** results, Vec** a, Vec** b, int count) {
    for (int index = 0; index < count; ++index)
        Subtract2(results[index], a[index], b[index]);
}
#pragma code_seg()
