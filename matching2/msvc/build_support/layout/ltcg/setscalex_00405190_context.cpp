// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_405190.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm5** items, int count, float value) {
    while (count--) (*items++)->SetScaleX(value);
    return 0;
}
#pragma code_seg()
