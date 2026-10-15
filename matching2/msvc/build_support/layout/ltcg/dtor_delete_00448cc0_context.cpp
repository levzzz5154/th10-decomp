// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00448cc0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00448cc0(Deletable_00448cc0** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00448cc0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
