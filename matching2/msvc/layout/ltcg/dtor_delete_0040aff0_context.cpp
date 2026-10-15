// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0040aff0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_0040aff0(Deletable_0040aff0** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0040aff0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
