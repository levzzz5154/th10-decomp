// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00441e90.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AddContext_00441e90(
        Vec_00441e90** results, Vec_00441e90** a, Vec_00441e90** b, int count) {
    for (int index = 0; index < count; ++index)
        b[index]->Add(results[index], a[index]);
}
#pragma code_seg()
