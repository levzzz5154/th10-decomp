// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00412e60.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AddContext_00412e60(
        Vec2_00412e60** a, Vec2_00412e60** b, Vec2_00412e60** out, int count) {
    for (int index = 0; index < count; ++index)
        a[index]->AddTo(b[index], out[index]);
}
#pragma code_seg()
