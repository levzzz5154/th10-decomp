// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00428e90.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot_00428e90* __stdcall GaugeSlotAtContext_00428e90(GaugeState_00428e90* state, int count) {
    GaugeSlot_00428e90* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
