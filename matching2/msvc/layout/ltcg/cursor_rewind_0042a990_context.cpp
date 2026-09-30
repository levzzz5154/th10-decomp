// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0042a990_0042a990.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Cursors_0042a990** items, int count) {
    while (count--) (*items++)->Rewind();
    return 0;
}
#pragma code_seg()
