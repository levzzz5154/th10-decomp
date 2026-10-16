// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_449fe0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00449fe0(Deletable17** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00449fe0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
