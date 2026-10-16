// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_427e40.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot* __stdcall GaugeSlotAtContext_00427e40(GaugeState2* state, int count) {
    GaugeSlot* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
