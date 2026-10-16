// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ac80.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Float23** items, int count, float a, float b) {
    while (count--) (*items++)->Set(a, b);
    return 0;
}
#pragma code_seg()
