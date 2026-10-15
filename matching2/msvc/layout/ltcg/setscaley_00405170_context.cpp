// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/unassigned_00405170.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm_00405170** items, int count, float value) {
    while (count--) (*items++)->SetScaleY(value);
    return 0;
}
#pragma code_seg()
