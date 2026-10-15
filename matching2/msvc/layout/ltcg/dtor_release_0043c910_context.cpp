// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0043c910.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_0043c910(Destroyable_0043c910** items, int count) {
    while (count--) {
        Destroyable_0043c910_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
