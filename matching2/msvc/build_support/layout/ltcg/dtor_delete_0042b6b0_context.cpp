// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_42b6b0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_0042b6b0(Deletable12** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0042b6b0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
