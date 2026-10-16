// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4026e0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_004026e0(Deletable2** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_004026e0_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
