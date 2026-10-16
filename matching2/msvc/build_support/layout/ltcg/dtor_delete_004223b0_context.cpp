// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4223b0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_004223b0(Deletable9** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_004223b0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
