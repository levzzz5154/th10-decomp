// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41c0a0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) Rec12* __stdcall CopyContext_0041c0a0(
        Rec12** destinations, Rec12** sources, int count) {
    Rec12* last = 0;
    for (int index = 0; index < count; ++index)
        last = Copy2(destinations[index], sources[index]);
    return last;
}
#pragma code_seg()
