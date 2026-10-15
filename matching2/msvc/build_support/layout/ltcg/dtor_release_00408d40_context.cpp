// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00408d40.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_00408d40(Destroyable_00408d40** items, int count) {
    while (count--) {
        Destroyable_00408d40_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
