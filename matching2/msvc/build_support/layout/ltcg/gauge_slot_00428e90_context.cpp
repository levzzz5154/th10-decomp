// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428e90.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot4* __stdcall GaugeSlotAtContext_00428e90(GaugeState5* state, int count) {
    GaugeSlot4* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
