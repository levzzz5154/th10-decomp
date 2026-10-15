// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0042a870.cpp"
#pragma code_seg(".text$03context")
int __stdcall ReplayBufferedBytesContext_0042a870(
        ReplayBufferState_0042a870** states, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += states[index]->GetBufferedBytes();
    return total;
}
#pragma code_seg()
