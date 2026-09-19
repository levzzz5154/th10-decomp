// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040a430.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_0040a430(Destroyable_0040a430** items, int count) {
    while (count--) {
        Destroyable_0040a430_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
