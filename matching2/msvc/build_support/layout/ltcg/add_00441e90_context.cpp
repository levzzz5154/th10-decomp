// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_441e90.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AddContext_00441e90(
        VecList** results, VecList** a, VecList** b, int count) {
    for (int index = 0; index < count; ++index)
        b[index]->Add(results[index], a[index]);
}
#pragma code_seg()
