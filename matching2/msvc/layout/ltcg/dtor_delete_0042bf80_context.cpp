// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0042bf80.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_0042bf80(Deletable_0042bf80** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0042bf80_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
