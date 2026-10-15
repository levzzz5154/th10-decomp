// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_00401d60.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm_00401d60** items, int count, float a, float b) {
    while (count--) (*items++)->SetScale(a, b);
    return 0;
}
#pragma code_seg()
