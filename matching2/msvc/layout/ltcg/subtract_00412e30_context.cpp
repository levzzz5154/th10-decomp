// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00412e30.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall SubtractContext_00412e30(
        Vec2_00412e30** a, Vec2_00412e30** b, Vec2_00412e30** out, int count) {
    for (int index = 0; index < count; ++index)
        a[index]->SubtractTo(b[index], out[index]);
}
#pragma code_seg()
