// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00406120.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00406120(Deletable_00406120** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00406120_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
