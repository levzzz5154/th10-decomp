// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_004132a0.cpp"
#pragma code_seg(".text$03context")
Block_004132a0* __stdcall InitContext_004132a0(Block_004132a0** items, int count) {
    Block_004132a0* last = 0;
    while (count--) {
        last = InitBlock_004132a0(*items++);
    }
    return last;
}
#pragma code_seg()
