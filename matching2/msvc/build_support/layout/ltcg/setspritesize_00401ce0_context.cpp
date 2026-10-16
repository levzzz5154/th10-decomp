// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_401ce0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm2** items, int count, float a, float b) {
    while (count--) (*items++)->SetSpriteSize(a, b);
    return 0;
}
#pragma code_seg()
