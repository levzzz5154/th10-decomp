// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00401490.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00401490(Deletable_00401490** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00401490_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
