// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_00450210_00450210.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FloatSlot_00450210** items, int count, float v) {
    while (count--) (*items++)->Store(v);
    return 0;
}
#pragma code_seg()
