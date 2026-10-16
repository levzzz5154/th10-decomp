// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4132a0.cpp"
#pragma code_seg(".text$03context")
Block2* __stdcall InitContext_004132a0(Block2** items, int count) {
    Block2* last = 0;
    while (count--) {
        last = InitBlock(*items++);
    }
    return last;
}
#pragma code_seg()
