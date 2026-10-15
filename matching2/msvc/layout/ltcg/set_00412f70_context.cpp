// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/FUN_00412f70_00412f70.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Float2_00412f70** items, int count, float a, float b) {
    while (count--) (*items++)->Set(a, b);
    return 0;
}
#pragma code_seg()
