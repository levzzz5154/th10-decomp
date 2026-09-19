// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0043e4d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall HolderCompilerContext(Holder_0043e4d0** items, int count, float seconds) {
    while (count--) {
        (*items++)->SetSeconds(seconds);
    }
    return 0;
}
#pragma code_seg()
