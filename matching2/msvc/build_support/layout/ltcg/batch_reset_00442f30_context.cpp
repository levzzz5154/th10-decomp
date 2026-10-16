// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_442f30.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(QuadBatch** items, int count) {
    while (count--) (*items++)->Reset();
    return 0;
}
#pragma code_seg()
