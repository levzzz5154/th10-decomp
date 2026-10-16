// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_40b010.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_0040b010(Destroyable5** items, int count) {
    while (count--) {
        Destroyable_0040b010_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
