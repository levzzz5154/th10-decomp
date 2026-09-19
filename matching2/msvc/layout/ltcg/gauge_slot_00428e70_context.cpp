// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00428e70.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot_00428e70* __stdcall GaugeSlotAtContext_00428e70(GaugeState_00428e70* state, int count) {
    GaugeSlot_00428e70* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
