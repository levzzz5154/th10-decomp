// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428e70.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot2* __stdcall GaugeSlotAtContext_00428e70(GaugeState3* state, int count) {
    GaugeSlot2* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
