// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_42bfa0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_0042bfa0(Releasable2** items, int count) {
    while (count--) {
        Releasable_0042bfa0_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
