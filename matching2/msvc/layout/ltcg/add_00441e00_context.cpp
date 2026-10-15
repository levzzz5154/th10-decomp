// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00441e00.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AddContext_00441e00(
        Vec2_00441e00** a, Vec2_00441e00** b, Vec2_00441e00** out, int count) {
    for (int index = 0; index < count; ++index) a[index]->AddTo(b[index], out[index]);
}
#pragma code_seg()
