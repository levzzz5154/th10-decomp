// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_42a990.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Cursors** items, int count) {
    while (count--) (*items++)->Rewind();
    return 0;
}
#pragma code_seg()
