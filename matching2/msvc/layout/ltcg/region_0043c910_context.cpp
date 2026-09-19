// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043c910.cpp"

#pragma code_seg(".text$03context")
int __stdcall RegionCompilerContext(Object_0043c910** items, int count) {
    while (count--) {
        (*items++)->Destroy();
    }
    return 0;
}
#pragma code_seg()
