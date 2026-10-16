// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4223d0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_004223d0(Releasable** items, int count) {
    while (count--) {
        Releasable_004223d0_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
