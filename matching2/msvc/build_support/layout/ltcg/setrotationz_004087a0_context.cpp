// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_004087a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AnmVm_004087a0** items, int count, float value) {
    while (count--) (*items++)->SetRotationZ(value);
    return 0;
}
#pragma code_seg()
