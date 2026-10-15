// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_0042ba70.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm_0042ba70** items, int count, float value) {
    while (count--) (*items++)->SetSpriteWidth(value);
    return 0;
}
#pragma code_seg()
