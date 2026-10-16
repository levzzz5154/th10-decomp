// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_450210.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FloatSlot** items, int count, float v) {
    while (count--) (*items++)->Store(v);
    return 0;
}
#pragma code_seg()
