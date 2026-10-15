// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0041c0a0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) Rec_0041c0a0* __stdcall CopyContext_0041c0a0(
        Rec_0041c0a0** destinations, Rec_0041c0a0** sources, int count) {
    Rec_0041c0a0* last = 0;
    for (int index = 0; index < count; ++index)
        last = Copy_0041c0a0(destinations[index], sources[index]);
    return last;
}
#pragma code_seg()
