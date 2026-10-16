// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_412e60.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AddContext_00412e60(
        Vec24** a, Vec24** b, Vec24** out, int count) {
    for (int index = 0; index < count; ++index)
        a[index]->AddTo(b[index], out[index]);
}
#pragma code_seg()
