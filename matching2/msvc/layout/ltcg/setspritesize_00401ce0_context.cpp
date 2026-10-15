// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/unassigned_00401ce0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm_00401ce0** items, int count, float a, float b) {
    while (count--) (*items++)->SetSpriteSize(a, b);
    return 0;
}
#pragma code_seg()
