// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_412e30.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall SubtractContext_00412e30(
        Vec22** a, Vec22** b, Vec22** out, int count) {
    for (int index = 0; index < count; ++index)
        a[index]->SubtractTo(b[index], out[index]);
}
#pragma code_seg()
