// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4296d0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_004296d0(Deletable11** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_004296d0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
