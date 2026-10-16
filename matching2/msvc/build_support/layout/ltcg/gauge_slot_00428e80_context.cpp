// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428e80.cpp"

#pragma code_seg(".text$03context")
extern "C" GaugeSlot3* __stdcall GaugeSlotAtContext_00428e80(GaugeState4* state, int count) {
    GaugeSlot3* last = 0;
    for (int index = 0; index < count; ++index) {
        last = state->SlotAt(index);
    }
    return last;
}
#pragma code_seg()
