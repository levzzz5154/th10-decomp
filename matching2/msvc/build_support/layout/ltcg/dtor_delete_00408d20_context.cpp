// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_408d20.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00408d20(Deletable5** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00408d20_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
