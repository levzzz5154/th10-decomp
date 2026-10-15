// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004014b0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_004014b0(Destroyable_004014b0** items, int count) {
    while (count--) {
        Destroyable_004014b0_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
